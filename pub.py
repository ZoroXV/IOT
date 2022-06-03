import paho.mqtt.client as mqttClient
import time

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to broker")
        global Connected
        Connected = True
    else:
        print("Connection failed")

Connected = False

client = mqttClient.Client("PythonPub")
client.on_connect= on_connect

client.connect('127.0.0.1', 1883)

client.loop_start()

while Connected != True:
    time.sleep(0.1)

try:
    while True:
        topic = input('Enter the topic:')
        value = input('Enter the message:')
        client.publish(topic,value)

except KeyboardInterrupt:
    client.disconnect()
    client.loop_stop()
