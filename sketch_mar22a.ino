#include <SPI.h>
#include <Ethernet.h>

// Set the MAC address
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// Set the IP address
IPAddress ip(192, 168, 103,220);

// Start a server at port 80 (http)
EthernetServer server(80);

void setup() {
  // Open serial communications
  Serial.begin(9600);

  // start the Ethernet connection and the server
  Ethernet.begin(mac, ip);
  server.begin();

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
 
}


void loop() {
  // Check if client connected
  EthernetClient client = server.available();
  
  if (client) { // If there is a client...
    boolean currentLineIsBlank = true;
    String buffer = ""; // A buffer for the GET request
    
    while (client.connected()) {

      if (client.available()) {
        char c = client.read();
        buffer += c; 
        
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println(); // Blank line ==> end response
          break;
        }
        if (c == '\n') { // if New line
          currentLineIsBlank = true;
          buffer = "";  // Clear buffer
        } else if (c == '\r') { // If cariage return...
          //Read in the buffer if there was send "GET /?..."
          if(buffer.indexOf("GET /?led1=1")>=0) { // If led1 = 1
            digitalWrite(8, HIGH); // led 1 > on
          }
          if(buffer.indexOf("GET /?led2=1")>=0) { // If led2 = 1
            digitalWrite(9, HIGH); // led 2 > on
          }
          delay(3000);
          if(buffer.indexOf("GET /?led1=0")>=0) { // If led1 = 0
            digitalWrite(8, LOW); // led 1 > off
          }
          delay(3000);
          if(buffer.indexOf("GET /?led2=0")>=0) { // If led2 = 0
            digitalWrite(9, LOW); // led 2 > off
          }
        } else {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1000);
    client.stop();
  }
}
