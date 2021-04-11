// Download ESP8266 and DHT in your Arduino libraries

#include <ESP8266WiFi.h>
#include <DHT.h>

#define dhtpin 5 // Pin D1
#define DHTTYPE DHT11

DHT dht (dhtpin, DHTTYPE);
WiFiClient client;

String apiKey = "TM83AXXIJ2ZTRG2F"; // You will get apiKey in the Website

const char *ssid = "Naufal"; // Your wifi name
const char *pswd = "Naufal2020"; // Your wifi password
const char *server = "api.thingspeak.com"; // The website

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
Serial.println ("Connecting to ");
  Serial.println(ssid);
WiFi.begin(ssid,pswd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
   
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h)||isnan(t)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
if(client.connect(server, 80)) {
  String postStr= apiKey;
  postStr += "&field1=";
  postStr += String(t);
  postStr += "&field2=";
  postStr += String(h);
  postStr += "\r\n\r\n";
client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
 Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celcius, Humidity: ");
    Serial.print(h);
    Serial.print("%. Send to Thingspeak.");
  }
  client.stop();
  Serial.println("Waiting...");
  delay(1000);
}