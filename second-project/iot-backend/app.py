#!/usr/bin/python3

from flask import Flask
from flask import jsonify,request
import infra
import sys
import base64

def create_app():
    infra.setup_mail()
    return Flask(__name__)

app = create_app()

# Endpoints
@app.route("/stats", methods=['GET'])
def get_stats():
    temperature, humidity, level = infra.get_stats()

    data = {
        "temperature": temperature,
        "humidity": humidity,
        "level": level
    }

    return jsonify(data)

@app.route("/stats", methods=['POST'])
def post_temperature():
    res = request.get_json()

    b64_payload = res["payload"]
    payload = base64.b64decode(b64_payload).decode('utf-8')
    values = payload.split()
    infra.stats["temperature"] = int(values[0])
    infra.stats["humidity"] = int(values[1])
    infra.stats["level"] = int(values[2])

    return ""

@app.route("/freq", methods=['POST'])
def post_frequency():
    infra.post_frequency()

    return ""

if __name__ == '__main__':
    app.run(host='0.0.0.0')
