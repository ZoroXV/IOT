#!/usr/bin/python3

# set -x FLASK_APP hello
# flask run --host=0.0.0.0

from flask import Flask
from flask import jsonify,request
import requests
import random

app = Flask(__name__)

# Infrastructure

def get_stats_from_esp32():
    r = requests.get("http://172.20.10.9/temp")
    j = r.json()
    return (j["temperature"], j["humidity"])

def get_random_stats():
    t = (30.0) * random.random()
    h = (100.0) * random.random()
    return (t, h)

def turn_on_led_test():
    print("Turn on led")

def turn_on_led():
    requests.get("http://172.20.10.9/led")

# Endpoints
@app.route("/", methods=['GET'])
def get_stats():
    # temperature, humidity = get_stats_from_esp32()
    temperature, humidity = get_random_stats()

    data = {
        "temperature": temperature,
        "humidity": humidity,
        "time": "0"
    }

    return jsonify(data)

@app.route("/", methods=['POST'])
def post_led():
    turn_on_led_test()
    return ""
