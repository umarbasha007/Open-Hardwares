/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "TechMonk123";
const char *password = "beInnovative";

//char page[]=("<!DOCTYPE><html><head><title>Arduino Ethernet Shield</title></head><body><h1><b><u>IoT via Ethernet Shield</u></b></h1><img src=\"Internet-of-Things.png\" alt=\"IoT\"><form action="" method=\"get\"><input type=\"hidden\" name='L' value='7' /><input id= \"redButton\"type=\"submit\" value=\"Toggle Red\" /></form><form action="" method=\"get\"><input type=\"hidden\" name='L' value='6' /><input id= \"greenButton\"type=\"submit\" value=\"Toggle Green\" /></form><form action="" method=\"get\"><input type=\"hidden\" name='L' value='5' /><input id= \"yellowButton\"type=\"submit\" value=\"Toggle Yellow\" /></form><p>This is my first IoT enabled web page <br/>Enter the pin number</p><form action="" method=\"get\" ><input type='text' name='L' size='15' maxlength='30' /></form><audio src=\"Jeena_Jeena.mp3\" autoplay controls loop id=\"audio_song\"></audio></body></html>");

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  server.send(200, "text/html","<!DOCTYPE><html><head><title>NodeMCU</title></head><body><h1 style=\"color:rgb(255,0,255)\"><u>IoT via nodeMCU</u></h1><br /><h2 style=\"color:blue\">Transfer of data</h2></body></html>");

}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP); //192.168.4.1
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
