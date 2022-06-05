"""
consts will always be capitalized.
"""
import json
import logging
import os
import sys
from datetime import date, datetime

import eventlet
import flask_socketio
from flask import Flask, render_template, request

SECRET_KEY = os.environ['SECRET_KEY']
PORT = os.environ['PORT']
IP = os.environ['IP']
SOCKS_URL = f'http://{IP}:{PORT}/'
PSETS = 'pset1,pset2,pset3,pset4,pset5,pset6,pset7,pset8,pset9'.split(',')
GROUPS = 'I need help with,I can help until'.split(',')
TITLE = 'TA50'

eventlet.monkey_patch()
app = Flask(__name__, static_folder='static')
app.config['SECRET_KEY'] = SECRET_KEY
sio = flask_socketio.SocketIO(app,
                              cors_allowed_origins='*',
                              async_mode='eventlet')

users = {}


def get_room(sid):
    rooms = flask_socketio.rooms(sid=sid)
    rooms.remove(sid)
    print(f'user {sid} in rooms: {rooms}')
    return rooms


def leave_all_rooms(sid):
    rooms = get_room(sid)
    for room in rooms:
        leave_room(sid, room)


def join_room(sid, data={}, room='ta50'):
    leave_all_rooms(sid)
    flask_socketio.join_room(room)
    data['sid'] = sid
    users[sid] = data
    print(f'user {sid} joined room {room}')
    get_room(sid)


def leave_room(sid, room='ta50'):
    if sid in users:
        flask_socketio.leave_room(room)
        del users[sid]
        print(f'user {sid} left room {room}')
    get_room(sid)


def get_user_by_sid(sid):
    if sid in users:
        return users[sid]
    return None


def get_match(sid):
    current_sid = users[sid]
    for key, value in users.items():
        if key != current_sid['sid']:
            match_sid = value
            their_room = current_sid['sid'] + match_sid['sid']
            print(f"current sid: {current_sid['sid']}. \
                    match_sid: {match_sid['sid']}")
            join_room(current_sid['sid'], room=their_room)
            join_room(match_sid['sid'], room=their_room)
            break

    try:
        return current_sid, match_sid, their_room
    except:
        return None

    #user = get_user_by_sid(sid)
    #if user['group'] == 'I need help with':
    #    for other_sid, other_user in users.items():
    #        if other_user['group'] == 'I can help until':
    #            if other_user['pset'][-1] >= user['pset'][-1]:
    #                #print("we've got ourselves a match!")
    #elif user['group'] == 'I can help until':
    #    for other_sid, other_user in users.items():
    #        if other_user['group'] == 'I need help with':
    #            #print(other_user['pset'], user['pset'])
    #            if int(other_user['pset'][-1]) <= int(user['pset'][-1]):
    #                #print("we've got ourselves a match!")
    #                leave_room(sid)
    #                leave_room(other_sid)
    #                flask_socketio.join_room('a')


@sio.on('chat')
def handle_chat(message):
    event = message['event']
    group = message['group']
    pset = message['pset']

    if event == 'join_room':
        data = {'group': group, 'pset': pset}
        join_room(request.sid, data)
        a, b, room = get_match(request.sid)
        sio.emit('chat', a, room=room)
    elif event == 'leave_room':
        leave_room(request.sid)

    # find two matching guys inside users. identifier can be the
    # request.sid (I don't know # how that's actually inside the
    # dict 'users', but I can check). If you're matching, create a room
    # (and leave 'ta50' room)  (with flask_socketio.join_room indeed) with only the
    # two of them and sio.emit. that's definitely gonna work cause
    # we're passing room.

    #msg2send = get_user_by_sid(request.sid)
    #if group == 'I need help with':
    #    sio.emit('chat', msg2send, room='ta50')


@app.route("/")
def hello_world():
    return render_template('chat.html',
                           socks_url=SOCKS_URL,
                           title=TITLE,
                           psets=PSETS,
                           groups=GROUPS)  # noqa


if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG,
                        format='%(asctime)s - %(levelname)s - %(message)s')
    logger = logging.getLogger(__name__)
    sio.run(app, host="0.0.0.0", port=PORT, debug=True)
