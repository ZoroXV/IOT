import random
import requests
import paho.mqtt.client as mqttClient

mqtt_utils = {
    "client": None
}

stats = {
    "temperature": 0,
    "humidity": 0,
    "led": "off"
}

def get_stats_mqtt():
    return (stats["temperature"], stats["humidity"])

def turn_on_led_mqtt():
    client = mqtt_utils["client"]
    if (stats["led"] == "off"):
        client.publish("esp32/led", "on")
    else:
        client.publish("esp32/led", "off")

def get_stats_rest():
    r = requests.get("http://192.168.20.2/temp")
    j = r.json()
    return (j["temperature"], j["humidity"])

def turn_on_led_rest():
    requests.get("http://192.168.20.2/led")

def get_stats_mock():
    t = (30.0) * random.random()
    h = (100.0) * random.random()
    return (t, h)

def turn_on_led_mock():
    print("Turn on led")

# MQTT specific
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to a MQTT broker!")
        global Connected
        Connected = True
    else:
        print("Connection failed")

def init_mqtt():
    client = mqttClient.Client("PythonPub")
    client.on_connect= on_connect
    client.connect('127.0.0.1', 1883)
    client.loop_start()
    mqtt_utils["client"] = client
