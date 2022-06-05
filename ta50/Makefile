default: build

.PHONY: build
build:
	pip install -r src/requirements.txt

.PHONY: run
run:
	export FLASK_APP=development && export GEVENT_SUPPORT=True && export IP=127.0.0.1 && export PORT=5005 && export SECRET_KEY=abc123def456 && python3 src/main.py

.PHONY: deploy
deploy:
	export IP=127.0.0.1 && export PORT=5005 && export SECRET_KEY=abc123def456 && python3 src/main.py
