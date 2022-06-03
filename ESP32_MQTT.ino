#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "DHT.h"

const char* ssid = "Viens on Ken";
const char* password = "victor-wifi";

const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(19, DHT11);

long lastMsg = 0;
char msg[50];
int value = 0;

float temperature = 0;
float humidity = 0;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, 0);
	Serial.begin(115200);
	dht.begin();


	setup_wifi();
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);

}

void setup_wifi() {
	delay(10);
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
	Serial.print("Message arrived on topic: ");
	Serial.print(topic);
	Serial.print(". Message: ");
	String messageTemp;

	for (int i = 0; i < length; i++) {
		Serial.print((char)message[i]);
		messageTemp += (char)message[i];
	}
	Serial.println();

	if (String(topic) == "esp32/led") {
		Serial.print("Turning led to ");
		if(messageTemp == "on"){
			Serial.println("on");
			digitalWrite(LED_BUILTIN, HIGH);
		}
		else if(messageTemp == "off"){
			Serial.println("off");
			digitalWrite(LED_BUILTIN, LOW);
		}
	}
}

void reconnect() {
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		if (client.connect("ESP32_Client")) {
			Serial.println("connected");
			client.subscribe("esp32/led");
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			delay(5000);
		}
	}
}
void loop() {
	if (!client.connected()) {
		reconnect();
	}
	client.loop();

	long now = millis();
	if (now - lastMsg > 5000) {
		lastMsg = now;

		char* tempString = String(dht.readTemperature());
		Serial.print("Temperature: ");
		Serial.println(tempString);
		client.publish("esp32/temp", tempString);

		char* humString = String(dht.readHumidity());;
		dtostrf(humidity, 1, 2, humString);
		Serial.print("Humidity: ");
		Serial.println(humString);
		client.publish("esp32/temp", humString);
	}
}
