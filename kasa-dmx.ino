#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "settings.h"

ESP8266WebServer server(80);
HTTPClient http;
uint frame = 0;

void setup()
{
	// Begin serial and connect to WiFi
	Serial.begin(115200);
	Serial.println("Connecting to WiFi...");

	// WiFi.softAP(SSID, PASSWORD);

	WiFi.begin("TP-LINK_Smart Bulb_E8F2");

	while (WiFi.status() != WL_CONNECTED)
	{
	    Serial.print(".");
	    delay(200);
	}

	Serial.print("SSID: ");
	Serial.println(SSID);
	Serial.print("Local IP: ");
	Serial.println(WiFi.localIP());

	// Initiate webserver
	server.on("/", _index);

	server.begin();
	Serial.println("HTTP server started");
}

void loop()
{
	server.handleClient();

	delay(MAIN_LOOP_DELAY);
	frame += MAIN_LOOP_DELAY;
}

// Handler for /index.html
void makeIndex(char *buffer, String units, int interval)
{
	sprintf(buffer,
			"<!DOCTYPE html> <html lang=en-US > <title>COUNTER-DMX</title> <meta name=viewpor"
			"t  content=\"width=device-width, initial-scale=1\" /> <meta charset=utf-8  /> <h"
			"1>COUNTER-DMX</h1>");
}

void _index()
{
	char buffer[1500];
	makeIndex(buffer, "", 0);

	server.send(200, "text/html", buffer);
}