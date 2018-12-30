/*
   ESP8266 NodeMCU AJAX Demo
   Updates and Gets data from webpage without page refresh
   https://circuits4you.com
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#include "index.h" //Our HTML webpage contents with javascripts

#define LED 2  //On board LED

//SSID and Password of your WiFi router
const char* ssid = "Flash";
const char* password = "aguanteelpaco";

ESP8266WebServer server(80); //Server on port 80

Servo _servo;
int pos;
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}

void handleADC() {
  int a = analogRead(A0);
  String adcValue = String(a);

  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}

void handleServo() {

  String s_state = server.arg("SERVOstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);

  String posValue = String(pos);

  _servo.write(pos);
  Serial.println(pos);
  pos += 15;
  delay(1500);
  _servo.write(pos);
  Serial.println(pos);
  server.send(200, "text/plane", posValue); //Send web page
}

void handleLED() {
  String ledState = "OFF";
  String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);

  Serial.println(t_state);
  if (t_state == "1")
  {
    digitalWrite(LED, LOW); //LED ON
    ledState = "ON"; //Feedback parameter
  }
  else
  {
    digitalWrite(LED, HIGH); //LED OFF
    ledState = "OFF"; //Feedback parameter
  }

  server.send(200, "text/plane", ledState); //Send web page
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void) {
  Serial.begin(115200);

  _servo.attach(2);

  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(LED, OUTPUT);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/setLED", handleLED);
  server.on("/readADC", handleADC);
  server.on("/setServo", handleServo);
  // server.on("/readServo", handleADC);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void) {
  server.handleClient();          //Handle client requests
}
