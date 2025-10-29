# Integrated-IoT-Power-BI-Framework-for-Real-Time-Air-Quality-Monitoring-and-Advanced-Analytics
##  Project Overview  
Designed and implemented an **IoT–Power BI integrated system** for **real-time air quality monitoring** using **Arduino**, **ESP8266 WiFi module**, and **multi-gas/dust sensors** (MQ-135, GP2Y1010AU0F, BMP280).  
This framework streams live environmental data to the cloud, logs it in Google Sheets/Firebase, and visualizes it dynamically in **Power BI dashboards** for pollution trend analysis and smart-city insights.  

---

##  Features  
- **Real-time air quality monitoring** with gas and dust sensors  
- **Cloud-based logging** through ESP8266 and Google Sheets/Firebase integration  
- **Interactive Power BI dashboards** for dynamic visualization and pollutant correlation  
- **Early alerts** for air-quality threshold violations  
- **Smart-city analytics** enabling data-driven decisions  


---

##  Hardware Components
| Component | Description |
|------------|-------------|
| Arduino UNO / NodeMCU (ESP8266) | Main microcontroller for data acquisition and WiFi connectivity |
| MQ-135 | Detects gases (NH₃, CO₂, benzene, smoke) |
| GP2Y1010AU0F | Optical dust sensor for particulate matter |
| BMP280 | Measures temperature and atmospheric pressure |
| ESP8266 WiFi Module | Sends sensor data to Firebase/Google Sheets |
| Power Supply | 5 V regulated supply |
| Connecting Wires, Breadboard | For circuit connections |

---

##  Pin-to-Pin Connections  

### **MQ-135 Gas Sensor**
| Pin | Connected To |
|------|---------------|
| VCC  | 5 V |
| GND  | GND |
| AOUT | A0 (Arduino analog input) |

### **GP2Y1010AU0F Dust Sensor**
| Pin | Connected To |
|------|---------------|
| VCC  | 5 V |
| LED  | D2 |
| OUT  | A1 |
| GND  | GND |

### **BMP280 Sensor**
| Pin | Connected To |
|------|---------------|
| VCC  | 3.3 V |
| GND  | GND |
| SDA  | A4 (SDA) |
| SCL  | A5 (SCL) |

### **ESP8266 WiFi Module**
| Pin | Connected To |
|------|---------------|
| VCC  | 3.3 V |
| GND  | GND |
| TX   | Arduino RX |
| RX   | Arduino TX (via voltage divider) |
| CH_PD | 3.3 V |

---

##  Dataset Description  
  

| Column | Description | Unit |
|---------|--------------|------|
| Timestamp | Date and time of reading | ISO 8601 |
| Dust_Density | Dust concentration | µg/m³ |
| MQ135_Value | Analog gas reading | ADC value |
| Temperature | Air temperature | °C |
| Pressure | Atmospheric pressure | hPa |
| Humidity | Relative humidity | % |
| Latitude | Sensor location latitude | — |
| Longitude | Sensor location longitude | — |
| Plant_Type | Tulasi / Peepal (monitoring site) | — |
| Alert | Air-quality status | Normal / Warning |



---

##  Power BI Integration  

- Imported dataset from Google Sheets into **Power BI Desktop**.  
- Created **interactive dashboards** with:
  - **Line charts** for multi-day trends of dust and gas levels  
  - **Card visuals** showing current AQI category  
  - **Correlation plots** between gas concentration and dust density  
  - **Conditional alerts** (color codes for pollution severity)  
- Dashboards automatically refresh from live Google Sheets data.  

---

## How It Works  
1. Arduino reads real-time sensor data (MQ-135, GP2Y1010, BMP280).  
2. ESP8266 transmits readings to Google Sheets/Firebase.  
3. Power BI fetches the live dataset and visualizes it in charts.  
4. Dynamic dashboards highlight pollution patterns, enabling early warnings.  

---


##  Outcomes  
- Showed clear multi-day variations in air quality between Tulasi & Peepal sites.  
- Enabled early-alert mechanism for pollution spikes.  
- Proved IoT–Power BI integration feasibility for smart-city environmental monitoring.  

---

##  Future Enhancements  
- Add MQ-2, MQ-4, MQ-5, MQ-7 sensors for greenhouse-gas detection.  
- Develop FPGA-based integrated hardware board.  
- Implement real-time AQI index computation in Power BI.  

---

##  Author  
**Goluguri Mrudula Danisri**  
B.Tech — Electronics & Communication Engineering  
SRM University  


---

