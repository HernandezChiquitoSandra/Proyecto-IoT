#include <Servo.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <UrlEncode.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define DHTPIN 13        // Pin de datos del sensor DHT11
#define DHTTYPE DHT11    // Tipo de sensor DHT
#define SERVOPIN 14      // Pin de señal del servo
#define SERVOMIN 0       // Valor mínimo para el servo
#define SERVOMAX 180     // Valor máximo para el servo
#define TEMP_MIN 1       // Temperatura mínima para encender el ventilador
#define TEMP_MAX 20      // Temperatura máxima para apagar el ventilador
#define HUM_MIN 40       // Humedad mínima para encender el ventilador
#define HUM_MAX 60       // Humedad máxima para apagar el ventilador
#define BUZZERPIN 27     // Pin de señal del buzzer
#define GAS_THRESHOLD 2000  // Umbral de detección de gas
#define PIRPIN 12        // Pin de señal del sensor PIR
#define LEDPIN1 2       // Pin de salida del LED 1


// Configuración de RED y Broker
const char* ssid = "OPPO Reno5 Lite";
const char* password = "esmeralda25";
const char* mqtt_server = "192.168.71.135";
const char* mqtt_topic = "iot/temp";


// Wifi network station credentials
#define WIFI_SSID "OPPO Reno5 Lite"
#define WIFI_PASSWORD "esmeralda25"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "6039973965:AAG4YKk0_y0bL3Swto-967W8Jo8Uh3nlCu4"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

const int ledPin = LEDPIN1;
int ledStatus = 0;

void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/ON")
    {
      digitalWrite(ledPin, LOW); // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led is ON", "");
    }

    if (text == "/OFF")
    {
      ledStatus = 0;
      digitalWrite(ledPin, HIGH); // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led is OFF", "");
    }

    if (text == "/status")
    {
      if (ledStatus)
      {
        bot.sendMessage(chat_id, "Led is ON", "");
      }
      else
      {
        bot.sendMessage(chat_id, "Led is OFF", "");
      }
    }

    if (text == "/start")
    {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Flash Led Bot example.\n\n";
      welcome += "/ledon : to switch the Led ON\n";
      welcome += "/ledoff : to switch the Led OFF\n";
      welcome += "/status : Returns current status of LED\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


//mqtt
WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

DHT dht(DHTPIN, DHTTYPE);  // Inicialización del sensor DHT
Servo servo;               // Inicialización del servo
int buzzerState = LOW;     // Estado inicial del buzzer
int pirState = LOW;        // Estado inicial del sensor PIR
int ledState1 = LOW;       // Estado inicial del LED 1


void setup() {
  Serial.begin(9600);
  dht.begin();
  servo.attach(SERVOPIN);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(PIRPIN, INPUT);
  pinMode(LEDPIN1, OUTPUT);//esta a cambio
  //pinMode(LEDPIN2, OUTPUT);
  pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(ledPin, HIGH); // initialize pin as off (active LOW)
  servo.write(SERVOMIN);  // Configuración inicial del servo

  Serial.println("Conectando");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Conectando...");
    Serial.println(".");
    delay(500);
  }
  Serial.println("Conexión WiFi establecida.");
  mqtt_client.setServer(mqtt_server, 1883);
  mqtt_client.setCallback(callback);
}

void callback(char* topic,byte* payload, unsigned int length){
  payload[length]='\0';
  String val=String((char*)payload);
  Serial.println(val);

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  if ((char)payload[0] == 'G') {
    servo.write(-90);
    digitalWrite(LEDPIN1, HIGH);
    delay(6000);
    servo.write(0);
    digitalWrite(LEDPIN1, LOW);
  }
}

void loop() {
  if(!mqtt_client.connected()){
	if(mqtt_client.connect("ESP32")){
	Serial.println("Conexion exitosa");
	}
}
  delay(2000);  // Retardo para la lectura del sensor

  float temp = dht.readTemperature();  // Lectura de la temperatura
  float hum = dht.readHumidity();      // Lectura de la humedad
  int gas = analogRead(4);            // Lectura del sensor MQ-2 de gas
  pirState = digitalRead(PIRPIN);      // Lectura del sensor PIR

  // Imprime los valores de temperatura, humedad, gas y PIR en la consola serial
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" C   Humedad: ");
  Serial.print(hum);
  Serial.print("%   Gas: ");
  Serial.print(gas);
  Serial.print("   PIR: ");
  Serial.print(pirState);
  Serial.println();

  // Si la temperatura está dentro del rango, enciende el ventilador
  if ( temp >= 20) {
    servo.write(180);
  } else {
    servo.write(90);  // Apaga el ventilador
  }

  // Si el sensor de gas detecta una concentración por encima del umbral, activa el buzzer
  if (gas >= GAS_THRESHOLD) {
    digitalWrite(BUZZERPIN, HIGH);
    buzzerState = HIGH;
  } else {
    digitalWrite(BUZZERPIN, LOW);
    buzzerState = LOW;
  }
  if (pirState == HIGH) {
    digitalWrite(LEDPIN1, HIGH);
    ledState1 = HIGH;
  } else {
    digitalWrite(LEDPIN1, LOW);
    ledState1 = LOW;
  }
  char temp_str[10]; 
  char hum_str[10];
  char gas_str[10];
  char pir_str[10];
  char led_str[10];

  sprintf(temp_str, "%.2f", temp);
  sprintf(hum_str, "%.2f", hum);
  sprintf(gas_str, "%d", gas);
  sprintf(pir_str, "%d", pirState);  
  sprintf(led_str, "%d", LEDPIN1); //

mqtt_client.publish("temperatura", temp_str);
mqtt_client.publish("humedad", hum_str);
mqtt_client.publish("gas", gas_str);
mqtt_client.publish("servo", led_str);
delay(1000);



 if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }  

}