#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

int red = 4;
int green = 2;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Esp32";
char pass[] = "moodesp32";
  
// mp3 credentials
SoftwareSerial mySoftwareSerial(19, 23); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

WebServer server(80);

void stopMusic(){
  String res = "mp3 stoped";
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
  myDFPlayer.stop();
  server.send(200, "text/html", res);
}


String dataMusic(int music) {
  String listMusic[10];
  listMusic[0] = "Tak Lagi Lagi";
  listMusic[1] = "Lebih Indah";  
  listMusic[2] = "Mantra Hujan";
  listMusic[3] = "Rumah Singgah";
  listMusic[4] = "Tertawan Hati";
  listMusic[5] = "Where the wind blows";
  listMusic[6] = "Lo-fi";
  listMusic[7] = "Canon Rock";
  listMusic[8] = "Ghibli Lo-Fi";
  String res = "";
  res = listMusic[music-1];
  return res;
}

void getMood() {
  String res = "";
  int mood;
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");

  if (server.method() == HTTP_POST) {
    String moodString = server.arg("plain");
    mood = moodString.toInt();
    Serial.println("mood :" + mood);
  }
  myDFPlayer.play(mood);
  res = dataMusic(mood);
  Serial.println(res);

  server.send(200, "text/html", res);
}


void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  
  // serial init
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);

  // mp3 
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    while(true);
  }
  Serial.println("DFPlayer Mini online.");

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30

  // Menghubungkan ESP32 ke jaringan WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  server.on("/getMood", getMood);
  server.on("/stop", stopMusic);
  server.begin();
  Serial.println("Server started");
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
}

void loop() {
  server.handleClient();
  while (Serial.available()) {
    Serial.write(Serial.read());
  }
}