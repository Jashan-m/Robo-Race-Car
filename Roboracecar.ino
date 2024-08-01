#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char* ssid = "Astrocar";
const char* password = "12345678";
ESP8266WebServer server(80);
const int motorPin1 = 5;  // D1 (GPIO 5)
const int motorPin2 = 4;  // D2 (GPIO 4)
const int motorPin3 = 0;  // D3 (GPIO 0)
const int motorPin4 = 2;  // D4 (GPIO 2)
const char html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ABC AIR Panel</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <style>
    body {
      background-color: #000;
      color: #00F;
      font-family: Arial, sans-serif;
      text-align: center;
      margin: 0;
      height: 100vh;
      display: flex;
      justify-content: center;
      align-items: center;
      overflow: hidden;
    }
    #controls {
      display: grid;
      grid-template-areas:
        ". up ."
        "left . right"
        ". down .";
      grid-gap: 10px;
    }
    button {
      width: 100px;
      height: 100px;
      font-size: 24px;
      color: #00F;
      background-color: #444;
      border: none;
      border-radius: 10px;
      cursor: pointer;
    }
    button:active {
      background-color: #666;
    }
    .up { grid-area: up; }
    .left { grid-area: left; }
    .right { grid-area: right; }
    .down { grid-area: down; }
    * {
      user-select: none;
      -webkit-user-select: none;
      -moz-user-select: none;
      -ms-user-select: none;
    }
  </style>
</head>
<body>
  <div id="controls">
    <button class="up" id="btn1" ontouchstart="sendCommand(1)" ontouchend="sendCommand(0)">Up</button>
    <button class="left" id="btn2" ontouchstart="sendCommand(2)" ontouchend="sendCommand(0)">Left</button>
    <button class="right" id="btn3" ontouchstart="sendCommand(3)" ontouchend="sendCommand(0)">Right</button>
    <button class="down" id="btn4" ontouchstart="sendCommand(4)" ontouchend="sendCommand(0)">Down</button>
  </div>
  <script>
    function sendCommand(cmd) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/command?move=" + cmd, true);
      xhr.send();
    }
  </script>
</body>
</html>
)rawliteral";
void handleRoot() {
  server.send_P(200, "text/html", html);
}
void handleCommand() {
  if (server.hasArg("move")) {
    String move = server.arg("move");
    Serial.println("Move: " + move);
    controlCar(move.toInt());
  }
  server.send(204); // No content to return
}
void controlCar(int command) {
  switch (command) {
    case 1: // Move up
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      break;
    case 2: // Move left
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      break;
    case 3: // Move right
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      break;
    case 4: // Move down
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      break;
    default: // Stop
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
      break;
  }
}
void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  controlCar(0);
  server.on("/", handleRoot);
  server.on("/command", handleCommand);
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
}
