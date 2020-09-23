# AirBagECU_emulation

Emulation of Air Bag ECU logic on a microcontroller.
Detection of front and side collision using 3D acceleration sensor.
Includes Ignition and Seatbelt status detection to detect presence of passenger in the vehicle.
Changing state of LEDs to emulate deployment of front and/or side airbags.
Display of current state on LCD.

Hardware used:
- Kinetis K40P144M100SF2V2RM Development Board
- MMA8451Q Accelerometer

Functions covered:
- Accelerometer Calibration
- I2C interfacing with Accelerometer
