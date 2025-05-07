# Fan Controller for L018 Projector

Most Chinese projectors run their fans at full power, regardless of temperature.  
This custom fan controller adjusts fan speed based on real sensor data, making the projector quieter.  

<p align="center">
  <img src="Images/Schematic.png" width="600"/>
</p>

## 🛠️ Setup Instructions

1. **Install Arduino IDE 2**  
   If not already installed, download and install it from the official [Arduino website](https://www.arduino.cc/en/software).

2. **Copy Libraries**  
   Place the contents of the `Libraries` folder into:  `C:\Users[YOUR_USERNAME]\Documents\Arduino\Libraries`

3. **Install Board Drivers**  
	Most clone boards use the CH341 USB-to-serial driver. Install it if needed.

4. **Open the Project**  
	Navigate to and open:   `Firmware\ProjectorFanController`

5. **Connect the Board**  
	- Select **Arduino Nano** as the board type.  
	- Some boards require `ATMega328p (Old Bootloader)`, others use `ATMega328p`.

6. **Compile and Upload**  
	Compile the sketch and upload it to the board via USB.

7. **Verify Operation**  
	- Open the **Serial Monitor** at **115200 baud**.  
	- You should see logs from all three temperature sensors.  
	- Sensors should show valid temperatures and respond to changes.

8. **Install in Projector**  
	- Attach the sensors to:
	  - the **lamp radiator**
	  - a **corner of the LCD**
	  - the **CPU**
	- Recommended adhesive: **silicone glue** for best thermal contact.

---

**Made by Dr. Failov in Ukraine 🇺🇦**