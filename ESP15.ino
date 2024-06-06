#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//Datele au fost schimbate
#ifndef APSSID
#define APSSID "NumeSSID"
#define APPSK "parola"
#endif

const char *ssid = APSSID;
const char *password = APPSK;
ESP8266WebServer server(80);

// Go to http://192.168.4.1 

void handleRoot() {
 String html = "<html><body>";
  html += "<h1>SMPixel de Dancau Rares-Andrei</h1>";
  html += "<p>Apasati un buton pentru a aprinde unul din LEDuri</p>";
  html += "<button onclick=\"sendData('R')\">Rosu</button>";
  html += "<button onclick=\"sendData('G')\">Verde</button>";
  html += "<button onclick=\"sendData('B')\">Albastru</button>";
  html += "<script>function sendData(color) {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.onreadystatechange = function() {";
  html += "if (this.readyState == 4 && this.status == 200) {";
  html += "console.log('Response: ' + this.responseText);";
  html += "}";
  html += "};";
  html += "xhttp.open('GET', '/color?c=' + color, true);";
  html += "xhttp.send();";
  html += "}</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleColor() {
  String color = server.arg("c");
  if(color.charAt(0) == 'R' || color.charAt(0) == 'G' || color.charAt(0) == 'B')
    Serial.print(color);
  server.send(200, "text/plain", "OK "+ color);
}

void setup() {
  delay(1000);

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/color", handleColor);
  server.begin();
  Serial.begin(9600); 
}

void loop() {
  server.handleClient();
}
