button_states = {
    'telephone': `
        <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-telephone" viewBox="0 0 16 16">
            <path d="M3.654 1.328a.678.678 0 0 0-1.015-.063L1.605 2.3c-.483.484-.661 1.169-.45 1.77a17.568 17.568 0 0 0 4.168 6.608 17.569 17.569 0 0 0 6.608 4.168c.601.211 1.286.033 1.77-.45l1.034-1.034a.678.678 0 0 0-.063-1.015l-2.307-1.794a.678.678 0 0 0-.58-.122l-2.19.547a1.745 1.745 0 0 1-1.657-.459L5.482 8.062a1.745 1.745 0 0 1-.46-1.657l.548-2.19a.678.678 0 0 0-.122-.58L3.654 1.328zM1.884.511a1.745 1.745 0 0 1 2.612.163L6.29 2.98c.329.423.445.974.315 1.494l-.547 2.19a.678.678 0 0 0 .178.643l2.457 2.457a.678.678 0 0 0 .644.178l2.189-.547a1.745 1.745 0 0 1 1.494.315l2.306 1.794c.829.645.905 1.87.163 2.611l-1.034 1.034c-.74.74-1.846 1.065-2.877.702a18.634 18.634 0 0 1-7.01-4.42 18.634 18.634 0 0 1-4.42-7.009c-.362-1.03-.037-2.137.703-2.877L1.885.511z" />
        </svg>
    `,
    'loading': `
        <div class="spinner-border spinner-border-sm" role="status">
            <span class="sr-only">Loading...</span>
        </div>
    `,
    'cancel': `
        <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-x-lg" viewBox="0 0 16 16">
            <path fill-rule="evenodd" d="M13.854 2.146a.5.5 0 0 1 0 .708l-11 11a.5.5 0 0 1-.708-.708l11-11a.5.5 0 0 1 .708 0Z" />
            <path fill-rule="evenodd" d="M2.146 2.146a.5.5 0 0 0 0 .708l11 11a.5.5 0 0 0 .708-.708l-11-11a.5.5 0 0 0-.708 0Z" />
        </svg>
    `
}

SOCKS_URL = SOCKS_URL
var connected = false;
var socks = undefined;


document.addEventListener("DOMContentLoaded", function () {
    var connectWs = function () {
        const sockt = io(SOCKS_URL, {
            reconnectionDelayMax: 10000
        });
        sockt.on('connect', () => {
            connected = true;
        });
        sockt.on('disconnect', () => {
            connected = false;
        });
        sockt.on('chat', (data) => {
            group = document.getElementById("group").value;
            pset = document.getElementById("pset").value;
            alert('mine is: '.concat(group, pset));
            alert('what I received is '.concat(data.group, data.pset));
        });
        sockt.on('message', (data) => {
            console.log(data);
        });

        return sockt;
    }
    socks = connectWs();
});




function look_button_telephone() {
    document.getElementById("btnJoin").innerHTML = button_states.telephone;
    button_state = 'telephone';
};

function look_button_cancel() {
    document.getElementById("btnJoin").innerHTML = button_states.cancel;
    button_state = 'cancel';
};

function look_button_loading() {
    document.getElementById("btnJoin").innerHTML = button_states.loading;
    button_state = 'loading';
};


function send_request_to(event) {
    group = document.getElementById("group").value;
    pset = document.getElementById("pset").value;
    jsn = {
        'event': event,
        'group': group,
        'pset': pset
    };
    socks.emit('chat', jsn);
};

function telephone_click() {
    look_button_cancel();
    send_request_to('join_room');

};

function cancel_click() {
    look_button_telephone();
    send_request_to('leave_room');
};

function button_click() {
    if (button_state == 'telephone') {
        telephone_click();
    } else if (button_state == 'cancel') {
        cancel_click();
    }
};

function button_mouse_over() {
    if (button_state == 'loading') {
        look_button_cancel();
    }
};

function button_mouse_out() {
    if (button_state == 'cancel') {
        look_button_loading();
    }
};