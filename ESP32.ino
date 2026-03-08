#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

WebSocketsServer webSocket = WebSocketsServer(81);

// touch pins
int finger1 = 4;
int finger2 = 5;
int finger3 = 12;
int finger4 = 13;
int finger5 = 14;

int threshold = 30;

String gesture = "";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected");
  Serial.println(WiFi.localIP());

  webSocket.begin();
}

void loop() {

  webSocket.loop();

  int f1 = touchRead(finger1);
  int f2 = touchRead(finger2);
  int f3 = touchRead(finger3);
  int f4 = touchRead(finger4);
  int f5 = touchRead(finger5);

  if(f1 < threshold && f2 > threshold && f3 > threshold){
      gesture = "HELLO";
  }

  if(f1 < threshold && f2 < threshold && f3 > threshold){
      gesture = "YES";
  }

  if(f1 > threshold && f2 < threshold && f3 < threshold){
      gesture = "NO";
  }

  if(f1 < threshold && f2 < threshold && f3 < threshold){
      gesture = "HELP";
  }

  if(f4 < threshold && f5 < threshold){
      gesture = "WATER";
  }

  webSocket.broadcastTXT(gesture);

  Serial.println(gesture);

  delay(500);
}
