import paho.mqtt.client as mqtt
import requests

def on_connect(client, userdata, flags, rc):
    print("Connected with result code {0}".format(str(rc)))
    client.subscribe("esp32/temp")
    client.subscribe("esp32/humidity")

def on_message(client, userdata, msg):
    value = int(msg.payload.decode('UTF-8'))
    print(value)
    if (msg.topic == "esp32/temp"):
        requests.post('http://localhost:5000/temperature', json = {"temperature": value})
    elif (msg.topic == "esp32/humidity"):
        requests.post('http://localhost:5000/humidity', json = {"humidity": value})

client = mqtt.Client("PythonSub")
client.on_connect = on_connect
client.on_message = on_message
client.connect('127.0.0.1', 1883)
client.loop_forever()
