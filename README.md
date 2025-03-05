# Cycling Computer - University Project (3rd Semester)

## Overview

This is an **IoT cycling computer** developed as a univeristy project using an **ESP32** microcontroller and multiple sensors. It tracks various cycling parameters in real time and transmits data to a mobile app for visualization. The entire system is assembled on a custom **PCB**, with al components soldered for durability and reliability.
The device has been successfully tested on a bicycle and performs as expected.

## Hardware Components

+ **ESP32** - Microcontroller for data processing and Bluetooth communication
+ **RFP602** - Pressure sensor for measuring braking intensity
+ **MPU6050** - Accelerometer for detecting jumps
+ **NEO6M GPS MODULE** - Captures real time location data

## Features & Application Integration

+ Real time data transmission to the **TrailCompanion app** via Bluetooth
+ **Braking intensity visualization** based on pressure sensor readings
+ **Acceleration and jump detection** via MPU6050 sensor
+ **GPS based route tracking**, with distance, top speed and average speed

 ## Future Improvements

 Development for a **new prototype** is already underway. The next version will:
 + Use an **Arduino Nano ESP32** for **reduced size**
 + Feature more **precise** and **energy efficient** sensors
 + Be **smaller** and **consume less power**
