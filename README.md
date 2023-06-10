
# GPS Tracking Project with ESP32

This project utilizes an ESP32 microcontroller and a GPS module to enable GPS tracking and position monitoring.

## Project Overview

The main objective of this project is to develop a GPS tracking system using an ESP32 microcontroller and a GPS module. The ESP32 acts as the central controller, which receives GPS data from the module and processes it to determine the current position.

## Components

The project requires the following components:

- ESP32 Lolin Wemos
- GPS module (e.g., GPS NEO-6M)
- Breadboard or PCB for prototyping
- Jumper wires for connections
- Power source (e.g., battery (5.0 V) or USB power bank)


## Circuit Diagram

Here is a simplified circuit diagram illustrating the connections:

| ![Montaje en digital](/Images/des.png "Montaje en digital") | ![Montaje fisico](/Images/MF.png "MOntaje fisico") |
|:---:|:---:|
| Assembly in Proteus | Physical assembly |



## Functionality

The ESP32 reads NMEA sentences transmitted by the GPS module. It extracts essential information such as latitude, longitude, and time from the NMEA data. The microcontroller can then process and utilize this data for various purposes, such as:

1. Real-time Position Tracking: The ESP32 continuously receives GPS data and updates the current position. This information can be stored locally or transmitted to a server for remote monitoring.

2. Geofencing: The system can define geographical boundaries and trigger alerts when the tracked object/device crosses those boundaries. This feature is useful for applications such as asset tracking or vehicle monitoring.

3. Data Logging: The project can incorporate an SD card module to log GPS data over extended periods. This logged data can later be analyzed or visualized for further analysis.

4. User Interface: If an optional display module is integrated, the ESP32 can showcase real-time GPS data, including latitude, longitude, altitude, and speed. Additionally, it can display additional information like signal strength and satellite count.

## Software Implementation

To implement this project, you will need to:

1. Set up the development environment for ESP32 using the Arduino IDE or any compatible development platform.

2. Install the necessary libraries for GPS parsing and communication (<TinyGPS++>, <SoftwareSerial.h>, <WiFi.h> ).

3. Create a sketch that configures the ESP32 and establishes communication with the GPS module.

4. Implement the parsing logic to extract essential GPS information from the received NMEA sentences.

5. Utilize the extracted GPS data for the desired functionalities, such as real-time tracking, geofencing, or data logging.

