# 🚀 IoT-Enabled UAV for Smart Environmental Monitoring 🌍  

[![Python](https://img.shields.io/badge/Python-3.8%2B-blue)](https://www.python.org/)  
[![Flask](https://img.shields.io/badge/Flask-API-orange)](https://flask.palletsprojects.com/)  
[![AWS](https://img.shields.io/badge/AWS-Cloud_Integration-yellow)](https://aws.amazon.com/)  
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)  

## 📌 Overview  
This project integrates **IoT and UAV technologies** to develop an intelligent drone system for **environmental monitoring, obstacle detection, and real-time data visualization**.  

The UAV is equipped with multiple **sensors** and communicates with a **Flask-based API** running on **Raspberry Pi**, which connects to **AWS for cloud processing**. A **web dashboard** provides real-time insights and remote control functionality.

## 🚀 Features  
✅ **Multi-Sensor Data Acquisition:**  
   - **DHT-11** → Temperature & Humidity Monitoring 🌡️  
   - **Ultrasonic Radar** → Collision Avoidance 🚧  
   - **LDR** → Light Intensity Monitoring 💡  
   - **LM-35** → Body Temperature Tracking 🏥  
   - **ADXL345 Accelerometer** → Motion Sensing 📡  

✅ **Real-Time Data Processing & Visualization:**  
   - Sensor data sent via **NodeMCU → Raspberry Pi**  
   - Flask API handles **data transmission to AWS**  
   - **Dynamic Web Dashboard** for real-time monitoring 📊  

✅ **Intelligent Control Modes:**  
   - **Manual Mode:** User-controlled flight via web interface.  
   - **Autonomous Mode:** Automatic obstacle detection & avoidance.  

✅ **Smart Alerts & Notifications:**  
   - 🚨 Overheating Detection  
   - 🌘 Low Light Warning  
   - ⚠️ Critical Obstacle Alert  

---

## 📂 Project Structure  
📁 UAV-IoT-Project
│── 📜 README.md # Project Documentation
│── 📜 requirements.txt # Dependencies
│── 📜 LICENSE # MIT License
│── 📜 main.py # Sensor Data Processing
│── 📜 flask_api.py # Flask API for Data Handling
│── 📜 aws_integration.py # Cloud Communication with AWS
│── 📜 dashboard.html # Web Interface (Frontend)
│── 📜 static/css/style.css # Web Dashboard Styling
│── 📜 static/js/main.js # Web Dashboard Logic
│── 📜 uav_control.py # Manual & Auto Flight Control
│── 📁 hardware # Sensor Schematics & UAV Wiring
│── 📁 tests # Test Cases & Debugging Scripts

yaml
Copy
Edit

---

## 🛠 Installation & Setup  
To set up and run the UAV IoT system, follow these steps:  

### **1️⃣ Install Dependencies**  
Ensure you have **Python 3.8+** installed, then clone the repository and install dependencies:  
```bash
git clone https://github.com/YOUR_GITHUB/UAV-IoT-Project.git  
cd UAV-IoT-Project  
pip install -r requirements.txt  
2️⃣ Run the Flask API on Raspberry Pi
bash
Copy
Edit
python flask_api.py  
3️⃣ Start the Web Dashboard
Open dashboard.html in a browser to view real-time UAV data.

📡 Sensor & Hardware Integration
🔹 Microcontrollers & Processing Units
NodeMCU ESP8266: Collects data from sensors and transmits to Raspberry Pi.
Raspberry Pi 4: Runs the Flask API and communicates with AWS for cloud processing.
🔹 Sensors Used
Sensor	Functionality
DHT-11	Measures Temperature & Humidity 🌡️
Ultrasonic Radar	Detects obstacles for Collision Avoidance 🚧
LDR (Light Sensor)	Monitors Ambient Light Levels 💡
LM-35	Measures Body Temperature 🏥
ADXL345	Tracks UAV Motion & Orientation 📡
📊 Real-Time Data Visualization
The web-based dashboard allows users to:
✅ Monitor real-time sensor data
✅ Control UAV flight modes (Manual/Auto)
✅ Receive alerts for critical conditions
✅ Visualize UAV position and telemetry data

🔮 Future Work
🔹 Integration with AI Models for Predictive Analytics
🔹 Cloud-Based UAV Fleet Management
🔹 Extended Range with LoRa Communication
🔹 Autonomous Flight Path Optimization with Reinforcement Learning

🤝 Contributing
We welcome contributions! Feel free to fork the repository, submit pull requests, or open issues for feature requests.

📜 License
This project is licensed under the MIT License – see the LICENSE file for details.

