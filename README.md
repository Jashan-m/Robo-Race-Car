# Robo-Race-Car

## ESP8266 Motor Control Web Interface
This repository contains an Arduino sketch for controlling a motor-driven device using an ESP8266 microcontroller. The ESP8266 functions as a Wi-Fi Access Point (AP) and hosts a web server that provides a simple web-based control panel.

### **Features:**
- **Wi-Fi Access Point:** The ESP8266 creates its own Wi-Fi network with a configurable SSID and password.
- **Web Interface:** A user-friendly web page is served that includes buttons for controlling the motor's movement in four directions (up, down, left, right).
- **Motor Control:** The motor's direction is controlled via GPIO pins on the ESP8266. The code supports basic directional movement and stopping the motor.

### **Components:**
- **ESP8266 Microcontroller:** Serves as both the Wi-Fi Access Point and web server.
- **Motor Control Pins:** GPIO pins on the ESP8266 are connected to a motor driver circuit.

### **Code Details:**
- **HTML Interface:** 
  - The web page is designed with CSS grid layout for button positioning.
  - JavaScript is used to send HTTP GET requests to the ESP8266 to control the motor.
- **Motor Control Logic:** 
  - Commands are interpreted by the ESP8266 to control the motor's direction based on the GPIO pin states.

### **Setup Instructions:**
1. **Hardware Connections:**
   - Connect the ESP8266 GPIO pins to the motor driver as per the pin definitions in the code.
2. **Programming the ESP8266:**
   - Upload the sketch to the ESP8266 using the Arduino IDE.
   - Connect to the Wi-Fi network created by the ESP8266.
3. **Using the Web Interface:**
   - Access the web interface by navigating to the ESP8266's IP address in a web browser.
   - Use the control buttons to operate the motor.
