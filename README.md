# 🏥 IoT-Based Remote Patient Health Monitoring System

## 📌 Description
This project is an IoT-based system designed to monitor vital health parameters such as heart rate, blood oxygen level (SpO₂), and temperature in real time. The system uses ESP32 and sensors to collect data and sends it to the Blynk cloud platform for remote monitoring.

---

## 🚀 Features
- Real-time health monitoring  
- Heart Rate (BPM) measurement  
- SpO₂ (blood oxygen level) monitoring  
- Temperature monitoring  
- LCD display output  
- Cloud-based monitoring using Blynk  
- Wi-Fi enabled system  

---

## 🛠️ Components Used
- ESP32 Microcontroller  
- MAX30102 Pulse Oximeter Sensor  
- DHT11 Temperature Sensor  
- 16x2 LCD Display (I2C)  
- Jumper Wires  
- Breadboard  
- Blynk IoT Platform  

---

## ⚙️ Working Principle
Sensors collect health data → ESP32 processes the data → data is displayed on LCD → data is sent to Blynk cloud via Wi-Fi → user can monitor data remotely on mobile.

---

## 🔌 Connections
- MAX30102 → SDA (GPIO 21), SCL (GPIO 22)  
- LCD → I2C (GPIO 21, 22)  
- DHT11 → GPIO 4  
- All components share common GND  

---

## 📊 Output
- Heart Rate (BPM)  
- SpO₂ (%)  
- Temperature (°F)  
- Real-time data on LCD and Blynk dashboard  

---

## 🧪 Setup Instructions

1. Install Arduino IDE  
2. Install required libraries:
   - Blynk  
   - MAX30105  
   - DHT  
   - LiquidCrystal_I2C  

3. Replace the following in code:
   YOUR_WIFI_NAME,
   YOUR_WIFI_PASSWORD,
   YOUR_BLYNK_AUTH_TOKEN.

5. Upload code to ESP32  
6. Connect hardware as per circuit  
7. Open Blynk app/dashboard  

---

## 🔮 Future Scope
- Add ECG and Blood Pressure sensors  
- AI-based health prediction  
- Wearable device implementation  
- Improved mobile application  

---

## 👨‍💻 Team Members
- Vedant Awachar  
- Yashraj Kadam  
- Sarvesh Bolatlji  
- Anant Darade  

---

## 📄 License
This project is licensed under the MIT License.

---

## ⚠️ Disclaimer
This project is for educational purposes only and is not intended for medical use.

---

## © Copyright
© 2026 Vedant Awachar and Team. All rights reserved.

