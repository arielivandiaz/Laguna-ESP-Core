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
#define PAVA 0  //On board LED

#define CLOSED_POS 180
#define OPEN_POS 60
#define SERVO_TIMEMULTI 5
//SSID and Password of your WiFi router
const char* ssid = "Flash";
const char* password = "nashwa47";

int adc = -1;
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
  adc = analogRead(A0);
  String adcValue = String(adc);

  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}

void handleServo() {

  String s_state = server.arg("SERVOstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);

  _servo.write(OPEN_POS);
  Serial.println(OPEN_POS);
  String posValue = String(CLOSED_POS);
  delay(adc * SERVO_TIMEMULTI);
  _servo.write(CLOSED_POS);
  Serial.println(CLOSED_POS);
  server.send(200, "text/plane", posValue); //Send web page
}

void handleLED() {
  String ledState = "OFF";
  String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);

  Serial.println(t_state);
  if (t_state == "1")
  {
    digitalWrite(PAVA, HIGH); //LED OFF
    digitalWrite(LED, LOW); //LED ON
    ledState = "ON"; //Feedback parameter
  }
  else
  {
    digitalWrite(PAVA, LOW); //LED OFF
    digitalWrite(LED, HIGH); //LED OFF
    ledState = "OFF"; //Feedback parameter
  }

  server.send(200, "text/plane", ledState); //Send web page
}
void handleMate () {

  digitalWrite(PAVA, HIGH); //LED OFF
  digitalWrite(LED, LOW); //LED ON

  _servo.write(OPEN_POS);
  delay(adc * SERVO_TIMEMULTI);
  _servo.write(CLOSED_POS);

  delay(6000);

  digitalWrite(PAVA, LOW); //LED OFF
  digitalWrite(LED, HIGH); //LED ON

  String mateStat = "MATE LISTO";
  server.send(200, "text/plane", mateStat); //Send web page

}
//==============================================================
//                  SETUP
//==============================================================
void setup(void) {
  Serial.begin(115200);

  _servo.attach(2);
  _servo.write(CLOSED_POS);
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(LED, OUTPUT);
  pinMode(PAVA, OUTPUT);

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
  server.on("/setMate", handleMate);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void) {
  server.handleClient();          //Handle client requests
}
