# Gotcha-Fi 🎣

**Gotcha-Fi** is an educational security demonstration project for the ESP32. It creates a "Free Wi-Fi" Access Point that mimics a public hotspot login page. When users attempt to log in, it captures the dummy credentials, logs them to the Serial Monitor, and then reveals that it was a prank—teaching a valuable lesson about digital security.

---

## ⚠️ Disclaimer

> **This project is for educational purposes only.**
>
> * **Do not** use this tool to collect real personal data without consent.
> * **Do not** deploy this in public spaces to harass or deceive unsuspecting individuals maliciously.
>
> The goal is to demonstrate how easily "Evil Twin" or "Captive Portal" attacks work to raise awareness about public Wi-Fi safety.

---

## Features

* **📱 Captive Portal:** Automatically redirects all DNS requests to the ESP32 web server, forcing the "Login" page to open on connected devices (Android/iOS/Windows).
* **🎨 Realistic UI:** Clean, modern CSS mimicking a standard public Wi-Fi login screen.
* **📝 Credential Logging:** Captures entered Name, Email, and Phone Number and prints them to the Serial Monitor.
* **⚡ Silent Submission:** Uses JavaScript `fetch` API to send data asynchronously without reloading the page, ensuring the prank animation plays smoothly.
* **🤡 Prank Reveal:** Displays a "Hacking..." animation followed by a "Just Kidding" message and a security tip.
* **😀 Emoji Support:** Fully supports UTF-8 for rendering emojis on the client device.

## Hardware Requirements

* **ESP32 Development Board** (any standard model like ESP32 DevKit V1).
* Micro-USB cable for programming and power.

## Software Requirements

* **Arduino IDE**
* **ESP32 Board Support:** Installed via Board Manager in Arduino IDE.
* **Libraries:** (Standard ESP32 libraries, usually pre-installed)
    * `WiFi.h`
    * `DNSServer.h`
    * `WebServer.h`

---

## Installation & Setup

### 1. Install ESP32 in Arduino IDE
1.  Go to **File > Preferences**.
2.  Add the following URL to "Additional Board Manager URLs":
    ```text
    [https://dl.espressif.com/dl/package_esp32_index.json](https://dl.espressif.com/dl/package_esp32_index.json)
    ```
3.  Go to **Tools > Board > Boards Manager**, search for **"esp32"**, and install.

### 2. Flash the Code
1.  Open `FreeWifi_Captive_Prank.ino` in Arduino IDE.
2.  Select your board model under **Tools > Board**.
3.  Select the correct **COM port**.
4.  Click **Upload**.

### 3. Monitor Output
1.  Open the Serial Monitor (**Tools > Serial Monitor**).
2.  Set the baud rate to **115200**.
3.  Press the **EN** (Reset) button on the ESP32 if needed.
4.  Wait for the message: `AP Started: Free-wifi`.

---

## How to Use

1.  **Connect:** On a phone or laptop, search for Wi-Fi networks and connect to **"Free-wifi"**.
2.  **The Portal:** The "Sign in to network" prompt should appear automatically.
    * *Note: If it doesn't appear automatically, open a browser and type `192.168.0.4`.*
3.  **The Form:** Enter dummy details (e.g., Name: "Test", Email: "test@test.com") and click **"Connect Now"**.
4.  **The Prank:**
    * The card will shake.
    * A "GOTCHA!" screen will appear with a funny fake "Uploading data..." list.
    * A security message will explain the danger of open networks.
5.  **The Log:** Check the Arduino Serial Monitor to see the captured data.

### Example Output

```text
======== Data Received ========
Name: Test
Email: test@test.com
Phone: 1234567890
===============================

