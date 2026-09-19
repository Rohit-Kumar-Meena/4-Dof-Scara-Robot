# 4-Dof-Scara-Robot
4-DOF SCARA robot for pick-and-place and nut-fastening operations with CAD-based mechanical design and analysis.

## 📌 Overview

This project focuses on the **design, analysis, and development of a 4-DOF SCARA (Selective Compliance Assembly Robot Arm)** for lightweight industrial automation applications.

The robot integrates mechanical components, motors, motor drivers, gear mechanisms, limit switches, and an Arduino-based control system. The design emphasizes **compactness, motion accuracy, structural stability, and smooth operation**.

## 🤖 Robot Configuration

The robot consists of four motion mechanisms:

- **J1:** Base rotational joint
- **J2:** Intermediate rotational joint
- **J3:** Rack-and-pinion based linear motion
- **J4:** Rotational motion of the geared motor at the end-effector

## ⚙️ Hardware Components

- Arduino Uno
- NEMA 17 Stepper Motor
- TB6600 Stepper Motor Driver
- 28BYJ-48 Stepper Motors
- ULN2003 Motor Drivers
- N20 Geared Motor
- Limit Switches
- Double Helical Gear Train
- Rack and Pinion Mechanism

## 🔩 Mechanical Design

The SCARA robot was designed using CAD software. Individual components were modeled and assembled to verify proper motion and alignment.

Major mechanical components include:

- Base frame
- Robotic links
- Motor mounts
- Shafts
- End-effector assembly
- Double helical gear train
- Rack-and-pinion mechanism

## 📐 Design Specifications

| Parameter | Value |
|---|---:|
| Link 1 Length | 140 mm |
| Link 2 Length | 140 mm |
| Link 3 Length | 120 mm |
| Rack Working Height | 60 mm |
| Arm Reach | 260 mm |

## ⚙️ Motor and Driver Configuration

### Link 1

- **Motor:** NEMA 17 Stepper Motor
- **Driver:** TB6600

### Link 2

- **Motor:** 28BYJ-48 Stepper Motor
- **Driver:** ULN2003

### Link 3

- **Motor:** 28BYJ-48 Stepper Motor
- **Driver:** ULN2003
- **Additional Actuator:** DC Motor for end-effector operation

Limit switches are integrated for motion limits and calibration.

## 🎮 Control System

The robot is controlled using an **Arduino-based control system**.

Features include:

- Manual control of Link 1
- Manual control of Link 2
- Link 3 calibration using a limit switch
- Forward motion sequence
- Reverse motion sequence
- DC motor forward and reverse control

The **AccelStepper library** is used for stepper motor motion control.

## ⚙️ Transmission System

The robot incorporates:

- Double helical gear transmission
- Pinion gear mechanisms
- Rack-and-pinion linear motion

Torque and gear ratio calculations were performed to achieve smooth and reliable motion.

## 📊 Engineering Calculations

The project includes:

- Force analysis
- Bending moment calculations
- Torque calculations
- Gear ratio calculations
- Stability calculations

## 🛠️ Technologies and Tools

- Arduino
- Arduino IDE
- C/C++
- CAD Software
- AccelStepper Library
