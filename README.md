# ESP32 Mini StageKit for RockBand 3 Enhanced

The ESP32 Mini StageKit is a device that shows the custom light shows programmed into Rock Band 3 when using Rock Band 3 Enhanced.

## Example of it in action

[![Example](https://img.youtube.com/vi/3aIkCyb1rkU/0.jpg)](https://www.youtube.com/watch?v=3aIkCyb1rkU)

*(Click the image for the YouTube video)*

> ### ⚠️ WARNING
> **You attempt any of this at your own risk. Incorrectly wiring and powering electronics can result in fires or even worse.**
>
> **You have been warned!**

## Build the LED Array

### Hardware

- **ESP32 WLED-compatible LED controller** — I used a [QuinLED Dig-Uno](https://quinled.info/quinled-dig-uno/), but any ESP32 board compatible with WLED should work.
- **WS281x LEDs** (WS2812B/WS2811/NeoPixel) — I'm using 60/m, cut and joined at 8 per side to make a square of 32. Although more can be used :)
- **Adafruit NeoPixel library** — install via the Arduino IDE Library Manager (`Adafruit NeoPixel`).
- **PSU** — The WS281x LEDs draw 0.06A per segment (each segment has 3 LEDs @ 0.02A each). So 70 segments = 70 × 0.06A = 4.2A.

For a 32 LED segment, I've been testing using a standard USB battery pack.

### Wiring it up

> **Ensure you use the correct fuse ratings on the LED strips!**

Multiple strips can be joined together using the data channel, then feed each strip with its own power.

Example — I use 4 strips, each with its own fuse and PSU connection:

| Strips | Segments per strip | Current | Fuse rating |
|---|---|---|---|
| 2 strips | 70 segments | 2 × 4.2A | 5A |
| 2 strips | 40 segments | 2 × 2.4A | 3A |

> **Ensure you use correct AWG rated wire for your power requirements.**

Connect the WS281x strip:

| Pin | Connect to |
|---|---|
| **GND** | Ground on the PSU/battery pack — the ESP32 mini should also share this ground. |
| **D(ata)(in)** | GPIO 16 on the ESP32 mini. |
| **5V** | Positive output on the PSU/battery pack. |

### Setting it up

1. Download the Arduino IDE, then open the sketch.

   > **WARNING: DO NOT POWER THE LEDs FROM AN EXTERNAL SOURCE UNTIL THE ESP32 HAS BEEN DISCONNECTED FROM THE PC.**
   > **YOU — HAVE — BEEN — WARNED!**

2. Connect the ESP32 mini via USB to a PC.
3. On the ESP32, hold the `0` button down, then press the `RST` button, then let go of the `0` button. This puts the device into program/flash mode.
4. In the Arduino IDE, click **Sketch → Upload**, then wait for the program to compile & upload to the ESP32.
5. You'll see a lot of `%` output until it reaches 100%, then it will complain about not being able to reset the device & give an error. Don't worry, this is normal :)
6. Disconnect the USB from the ESP32 so it's no longer connected to the PC, then power it from your PSU/battery pack.
7. Connect a device (phone/PC) to the WiFi hotspot `ESP32_StageKit` using the passcode `1234567890`.
8. Using a web browser, go to `http://192.168.1.1/` and a WiFi setup screen will appear.
9. Enter your local WiFi details in **WiFi SSID** & **Password**.
   - If your network has DHCP, check with your router which IP it will get from the MAC, or enter a static IP & subnet manually.
10. Click **Submit** and the device will restart. It will attempt to connect to the WiFi network given — if it fails, the hotspot will re-appear.

When the device connects to your network, open a browser and point it to its new IP.
Example: I set my DHCP server to assign `192.168.1.99`, so I open a web browser to `http://192.168.1.99/`.

When opened, a screen will appear allowing you to configure the LEDs. The default settings are for an ESP32 with 32×WS281x LED segments.

| Setting | Description |
|---|---|
| **RB3E IP** | IP of the device where the data will come from, or leave blank to accept from anywhere. |
| **RB3E Port** | The listening port. Hardware = `21070`, Xenia = `20050` or `21070` (if fixed). |
| **Ledstrip LEDs** | Number of LED segments in the lightstrip. Default = `32`. |
| **POD Brightness** | Default brightness of all LEDs, use `-1` to use individual brightness per group. |
| **GPIO DATA** | Pin used for the WS281x data line. Default = `16`. |
| **Colour Order** | The colour byte order your WS281x LEDs expect. Default = `GRB`. If colours look wrong (e.g. red shows as green), try changing this. |
| **Colours** | The SK colour can be changed — prefer orange instead of red? Then use `255, 255, 0`. |
| **SK Strobe** | Default is white, but maybe you want blue or green :) |

Next is the rough LED layout of a StageKit:

1. Click each circle to change the LED numbers to use.
2. Each LED number can then be linked to multiple LEDs — increase with **LED +** & decrease with **LED -**.
3. For each number, enter the LED strip position in the middle.
4. At the top you can set the brightness of this group. This only works if **POD Brightness** on the main page is set to `-1`.
5. Click **SAVE** to save these to the device, or **CANCEL** to revert any changes just made. Both return to the first config page.

In the middle of the config screen is a **STROBE** button — click to configure the strobe. You can enable/disable the strobe completely, or enable/disable using all LEDs.

If you want to set only some LEDs as strobe, you can add & remove LEDs, just like the LED colour groups.

There are 4 speed options: **Slow**, **Medium**, **Fast**, **Faster** — these are the time in milliseconds between flashes.

**Remember to click SAVE to save your settings!**

## Shoutouts

- **RB Enhanced team** — for pushing out the data over UDP.
- **AchillesPDX** — for trying to nail the strobe timings.
- **Sea Dog Andy** — for the HTML help, especially the circles :D
