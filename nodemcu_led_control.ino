#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
 
const char* ssid = "becrazy123";
const char* password = "becrazybro";
 
int ledPin = D5; // GPIO13
WiFiServer server(80);
// ESP8266WebServer server(80);
void setup() {
// Serial.begin(115200);
// delay(10);
 
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 // server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
 /* while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }*/
 /* Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 */
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 client.println("<head><title>IoT via nodeMCU</title></head>");
 client.println("<body>");
  client.print("<h2>Led pin is now: </h2>");
 
  if(value == HIGH) {
    client.print("<b>On</b>");
  } else {
    client.print("<b>Off</b>");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</body>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}

