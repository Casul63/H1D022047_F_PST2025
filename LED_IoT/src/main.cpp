#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFIClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFI.h>

const char *ssid = "Casul?HP";
const char *password = "GitGud00";

const char *sta_ssid = "TEKNIK UNSOED D3 5G";
const char *sta_password = "";

ESP8266WebServer server(80);
String webpage;

void setup()
{
  Serial.begin(9600);
  delay(10);

  pinMode(D0, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  Serial.println();
  Serial.print("Configuring Access Point....");

  WiFi.mode(WIFI_AP);
  WiFi.begin(ssid, password);

  Serial.println("IP Address : ");
  Serial.println(WiFi.softAPIP());

  webpage += "<h1>Web Control ESP8266</h1>";
  webpage += "<h1>Rizky</h1>";
  webpage += "<p>LED 1 : ";
  webpage += "<a href=\"/LED1ON\"><button>ON</button></a><a href=\"/LED1OFF\"><button>OFF</button></a></p><br>";
  webpage += "<p>LED 2 : ";
  webpage += "<a href=\"/LED2ON\"><button>ON</button></a><a href=\"/LED2OFF\"><button>OFF</button></a></p><br>";
  webpage += "<p>LED 3 : ";
  webpage += "<a href=\"/LED3ON\"><button>ON</button></a><a href=\"/LED3OFF\"><button>OFF</button></a></p><br>";

  server.on("/", []()
            { server.send(200, "text/html", webpage); });

  server.on("/LED1ON", []()
            {
    server.send(200, "text/html", webpage);
    digitalWrite(D0, HIGH);
    delay(1000); });

  server.on("/LED2ON", []()
            {
    server.send(200, "text/html", webpage);
    digitalWrite(D2, HIGH);
    delay(1000); });

  server.on("/LED3ON", []()
            {
    server.send(200, "text/html", webpage);
    digitalWrite(D3, HIGH);
    delay(1000); });

  server.on("/LED1OFF", []()
            {
    server.send(200, "text/html", webpage);
    digitalWrite(D0, LOW);
    delay(1000); });

  server.on("/LED2OFF", []()
            {
    server.send(200, "text/html", webpage);
    digitalWrite(D2, LOW);
    delay(1000); });

  server.on("/LED3OFF", []()
            {
    server.send(200, "text/html", webpage);
    digitalWrite(D3, LOW);
    delay(1000); });
}

void loop()
{
  server.handleClient();
}
