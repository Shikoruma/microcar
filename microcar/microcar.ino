#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#include "index.h"

class Microcar{
  private:
  

  Servo servoRight;
  Servo servoLeft;
  const int VMAX;
  int speedRight;
  int speedLeft;
  ESP8266WebServer server;
  
  void handleRoot();
  void ron();
  void rron();
  void roff();
  void lon();
  void lron();
  void loff();

  
  public:
  Microcar();
  void initWheels(int pinL, int pinR);

  void foward();
  void backward();
  void turnLeft();
  void turnRight();
  void stop();
  void setSpeedRight(int v);
  void setSpeedLeft(int v);
  int getSpeedRight();
  int getSpeedLeft();

  void initWeb(const char *ssid,const char *password);
  
  void loopWeb();
};


Microcar::Microcar():VMAX(100),speedRight(0),speedLeft(0),
server(80)
{
  
}

void Microcar::initWheels(int pinL, int pinR)
{
  servoRight.attach(pinR);
  servoLeft.attach(pinL);
  stop();
}

void Microcar::foward()
{
  setSpeedRight(VMAX);
  setSpeedLeft(VMAX);
}
void Microcar::backward()
{
  setSpeedRight(-VMAX);
  setSpeedLeft(-VMAX);
}
void Microcar::turnLeft()
{
  setSpeedRight(VMAX);
  setSpeedLeft(-VMAX);
}
void Microcar::turnRight()
{
  setSpeedRight(-VMAX);
  setSpeedLeft(VMAX);
}
void Microcar::stop()
{
  setSpeedRight(0);
  setSpeedLeft(0);
}
void Microcar::setSpeedRight(int v)
{
  servoRight.write(map(v, -VMAX, VMAX, 0, 180));
  speedRight=v;
}
void Microcar::setSpeedLeft(int v)
{
  servoLeft.write(map(-v, -VMAX, VMAX, 0, 180)); 
  speedLeft=v;
}
int Microcar::getSpeedRight()
{
  return speedRight;
}
int Microcar::getSpeedLeft()
{
  return speedLeft;
}
void Microcar::handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void Microcar::ron() {
  server.send(200, "text/html", "<h1>Right on</h1>");
  setSpeedRight(VMAX);
}
void Microcar::rron() {
  server.send(200, "text/html", "<h1>Right on</h1>");
  setSpeedRight(-VMAX);
}
void Microcar::roff() {
  server.send(200, "text/html", "<h1>Right off</h1>");
  setSpeedRight(0);
}
void Microcar::lon() {
  server.send(200, "text/html", "<h1>Left on</h1>");
  setSpeedLeft(VMAX);
}
void Microcar::lron() {
  server.send(200, "text/html", "<h1>Left on</h1>");
  setSpeedLeft(-VMAX);
}
void Microcar::loff() {
  server.send(200, "text/html", "<h1>Left off</h1>");
  setSpeedLeft(0);
}



void Microcar::initWeb(const char *ssid,const char *password)
{
  
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  server.on("/", std::bind(&Microcar::handleRoot,this));
  server.on("/ron", std::bind(&Microcar::ron,this));
  server.on("/rron", std::bind(&Microcar::rron,this));
  server.on("/roff", std::bind(&Microcar::roff,this));
  server.on("/lon", std::bind(&Microcar::lon,this));
  server.on("/lron", std::bind(&Microcar::lron,this));
  server.on("/loff", std::bind(&Microcar::loff,this));
  server.begin();
}
void Microcar::loopWeb()
{
  server.handleClient();
}


const char *ssid = "Microcar";
const char *password = "fabmstic";

Microcar m;

void setup() {
  Serial.begin(9600);
  m.initWeb(ssid,password);
  m.initWheels(D1,D2);

}

void loop() {
  m.loopWeb();

}
