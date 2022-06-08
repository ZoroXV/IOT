#include <WiFi.h>
#include <WiFiClient.h>
#include <WireGuard-ESP32.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "DHT.h"

const char* ssid = "Fairphone";
const char* password = "SunnyBeach";

static WireGuard wg;
WebServer server(80);
DHT dht(19, DHT11);

const int led = LED_BUILTIN;
bool is_led_on = false;

IPAddress local_ip(192, 168, 20, 2);

void handleNotFound() {
	digitalWrite(led, 1);
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++) {
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
	digitalWrite(led, 0);
}

void setup(void) {
	pinMode(led, OUTPUT);
	digitalWrite(led, 0);
	Serial.begin(115200);
	dht.begin();
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	configTime(9 * 60 * 60, 0, "0.fr.pool.ntp.org", "1.fr.pool.ntp.org", "time.google.com");

	wg.begin(
			local_ip,
			"gIuwaFK/moWr0aKxa4Qyqp9dgTiPezpAl5LWw2VeNmw=",
			"192.168.43.150",
			"k4RCgqHnSCxMoDTzjtbBGSUkpBALKVGAgptQkbwwDHM=",
			51820
			);

	if (MDNS.begin("esp32")) {
		Serial.println("MDNS responder started");
	}

	server.on("/", []() {
			Serial.println("Root Request");
			server.send(200, "text/plain", "Hello from ESP32 !");
			});

	server.on("/led", []() {
			Serial.println("LED Request");
			is_led_on = !is_led_on;
			if (is_led_on)
			digitalWrite(led, 1);
			else
			digitalWrite(led, 0);
			server.send(200, "text/plain", "Toggle ESP32's Led");
			});

	server.on("/temp", []() {
			Serial.println("Temp Request");
			server.send(200, "text/json", "{\"temperature\":"
					+ String(dht.readTemperature())
					+ ",\"humidity\":"
					+ String(dht.readHumidity())
					+ "}");
			});

	server.onNotFound(handleNotFound);

	server.begin();
	Serial.println("HTTP server started");
}

void loop(void) {
	server.handleClient();
	delay(2);//allow the cpu to switch to other tasks
}
