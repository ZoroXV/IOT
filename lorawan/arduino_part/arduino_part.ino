#include<SoftwareSerial.h>
#include "DHT.h"

SoftwareSerial e5(6, 7); // (RX, TX)

static char recv_buf[512];
static bool is_exist = false;
static bool is_join = false;
static int led = 0;
int ret=0;
short level=0;
 
// Definit la broche de l'Arduino sur laquelle la 
// broche DATA du capteur est reliee 
#define DHTPIN 13
 
// Definit le type de capteur utilise
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

/* Constantes pour les broches */
const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO

/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

static int at_send_check_response(char *p_ack, int timeout_ms, char *p_cmd, ...)
{
  int ch;
  int num = 0;
  int index = 0;
  int startMillis = 0;
  memset(recv_buf, 0, sizeof(recv_buf));
  e5.write(p_cmd);
  Serial.write(p_cmd);
  delay(200);
  startMillis = millis();

  do
  {
    while (e5.available() > 0)
    {
      ch = e5.read();
      recv_buf[index++] = ch;
      Serial.write(ch);
      delay(2);
    }
  } while (millis() - startMillis < timeout_ms);

  if (strstr(recv_buf, p_ack) != NULL)
  {
    return 1;
  }
  else return 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);

  dht.begin();
  
  e5.begin(9600);
  Serial.print("E5 LORAWAN TEST\r\n");

  if(at_send_check_response("+AT: OK", 100, "AT\r\n"))
  {
    is_exist = true;
    at_send_check_response("+ID: AppEui", 1000, "AT+ID\r\n");
    at_send_check_response("+MODE: LWOTAA", 1000, "AT+MODE=LWOTAA\r\n");
    at_send_check_response("+DR: EU868", 1000, "AT+DR=EU868\r\n");
    at_send_check_response("+CH: NUM", 1000, "AT+CH=NUM,0-2\r\n");
    at_send_check_response("+KEY: APPKEY", 1000,
    "AT+KEY=APPKEY,\"C51A49068445D42B7F441A815B307F5A\"\r\n");
    at_send_check_response("+CLASS: C", 1000, "AT+CLASS=A\r\n");
    ret=at_send_check_response("+PORT: 8", 1000, "AT+PORT=8\r\n");
    delay(200);
    is_join = true;
  }
  else
  {
    is_exist = false;
    Serial.print("No E5 module found.\r\n");
  }
}

void loop() {
  if (is_exist)
  {
    int ret = 0;
    if (is_join)
    {
      ret = at_send_check_response("+JOIN: Network joined", 12000, "AT+JOIN\r\n");
      if (ret)
      {
        is_join = false;
        Serial.println();
        Serial.print("Network JOIN !\r\n\r\n");
      }
      else
      {
        at_send_check_response("+ID: AppEui", 1000, "AT+ID\r\n");
        Serial.println();
        Serial.print("JOIN failed!\r\n\r\n");
        delay(5000);
      }
    }
    else
    {
      char cmd[128];
      sprintf(cmd, "AT+CMSGHEX=%04X%04X%04X\r\n", dht.readTemperature(), dht.readHumidity(), level);
      at_send_check_response("ACK Received", 5000, cmd);
      delay(20000);
    }
  }
  else
  {
    delay(1000);
  }

  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   
  /* 3. Calcul la distance à partir du temps mesuré */
  level = measure / 2.0 * SOUND_SPEED;
}
