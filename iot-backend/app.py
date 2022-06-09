#!/usr/bin/python3

from flask import Flask
from flask import jsonify,request
import infra
import sys

mode = ["none"]

def create_app():
    mode[0] = "none"
    if (len(sys.argv) > 1):
        mode[0] = sys.argv[1]

    if (mode[0] == "mqtt"):
        infra.init_mqtt()

    return Flask(__name__)

app = create_app()

# Endpoints
@app.route("/", methods=['GET'])
def get_stats():
    if (mode[0] == "mqtt"):
        temperature, humidity = infra.get_stats_mqtt()
    elif (mode[0] == "rest"):
        temperature, humidity = infra.get_stats_from_esp32()
    else:
        temperature, humidity = infra.get_stats_mock()

    data = {
        "temperature": temperature,
        "humidity": humidity,
        "time": "0"
    }

    return jsonify(data)

@app.route("/", methods=['POST'])
def post_led():
    if (mode[0] == "mqtt"):
        infra.turn_on_led_mqtt()
    elif (mode[0] == "rest"):
        infra.turn_on_led_mock()
    else:
        infra.turn_on_led_mock()

    return ""

@app.route("/temperature", methods=['POST'])
def post_temperature():
    res = request.get_json()
    infra.stats["temperature"] = res["temperature"]
    return ""

@app.route("/humidity", methods=['POST'])
def post_humidity():
    res = request.get_json()
    infra.stats["humidity"] = res["humidity"]
    return ""

if __name__ == '__main__':
    app.run(host='0.0.0.0')
