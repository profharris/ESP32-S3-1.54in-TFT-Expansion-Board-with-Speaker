// WiFiSSLClient.ino
// ESP32-S3 1.54in TFT Expansion Board with Speaker
// Prof. Michael P. Harris

/* NOTE¹:  When first run, After the message “Attempting to connect to SSID: ”,
 * ¯¯¯¯¯¯  the “.”s repeate for ever... with no WiFi connection.
 *         Researching the Internet, I found based on this Github post:
 *           https://github.com/espressif/arduino-esp32/issues/6767
 *        
 *         Adding the following line, after WiFi.begin() fixed the issue:
 *        
 *          WiFi.setTxPower(WIFI_POWER_8_5dBm);
 *
 * This example creates a WiFi client object that connects using 
 * SSL (Secure Socket Layer) and transfers data always using SSL.
 * 
 * This sketch is compatible with the methods normally related to 
 * plain connections, like client.connect(host, port).
 * 
 * Original code by Arturo Guadalupi, revision November 2015
 */

/*******************************************************************
Type-C USB Data cable plugged into Left-side ESP32-S3 USB-OTG port.
                                   ¯¯¯¯¯¯¯¯¯          ¯¯¯¯¯¯¯
Arduino IDE > Tools                                  [CONFIGURATION]
                   Board: "ESP32S3 Dev Module"
         USB CDC On Boot: "Enabled"  **Cable plugged into Left USB**
           CPU Frequency: "240MHz (WiFi)"                 ¯¯¯¯
         USB DFU On Boot: "Disabled"
              Flash Mode: "QIO 80MHz"
              Flash Size: "16MB 128Mb"
USB Firmware MSC On Boot: "Disabled"
        Partition Scheme: "16M Flash (3MB APP/9.9MB FATFS)"
                   PSRAM: "OPI PSRAM"
             Upload Mode: "UART0/Hardware CDC"
            Upload Speed: "115200"
                USB Mode: "Hardware CDC and JTAG"
*******************************************************************/

#include <WiFiClientSecure.h>
#include <WiFi.h>

// Enter your WiFi SSID and password
char ssid[] = "HAGGIS24";          // your network SSID (name)
char pass[] = "P@ssw0rdSpectrum";  // your network Password (use for WPA, or use as key for WEP)
int keyIndex = 0;                  // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// If you do not want to use DNS (and reduce your sketch size),
// use a numeric IP-Address instead of the name for the server:
//IPAddress server(74.125.232.128);  // numeric IP for Google (no DNS)

#define SERVER "cdn.syndication.twimg.com"
#define PATH   "/widgets/followbutton/info.json?screen_names=adafruit"

// Initialize the SSL client library with the IP-Address and Port-Number 
// of the server you want to connect to... (Port 443 is default for HTTPS)
WiFiClientSecure client;


void setup() {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  // Attempt to connect to the Wifi network:
  Serial.print("\nAttempting to connect to SSID: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  WiFi.setTxPower(WIFI_POWER_8_5dBm);       // See NOTE¹: above!!!
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to WiFi: ");
  printWifiStatus();
  client.setInsecure();                     // Don't use a root cert

  Serial.println("\nStarting connection to server...");
  // If you get a connection, report back via the Serial Monitor:
  if(client.connect(SERVER, 443)) {
    Serial.println("Connected to server: ");
    // Make a simple HTTP request: (close the connection)
    client.println("GET " PATH " HTTP/1.1");
    client.println("Host: " SERVER);
    client.println("Connection: close");
    client.println();
  }
}

uint32_t bytes = 0;

void loop() {
  // If there are incoming bytes available from the Server, 
  // Read them and Print them...
  while(client.available()) {
    char c = client.read();
    Serial.write(c);
    bytes++;
  }

  // If the Server is Disconnected, Stop the client, report stats.
  if(!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from Server.");
    client.stop();
    Serial.print("Read "); Serial.print(bytes); Serial.println(" bytes.");

    // do nothing forevermore:
    while(true);
  }
}


void printWifiStatus() {
  // Print the SSID of the Network you attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Print the IP-Address the DNS assigned to you:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Print the received Signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
19:27:57.827 -> ESP-ROM:esp32s3-20210327

19:28:34.194 -> Attempting to connect to SSID: HAGGIS24
19:28:34.301 -> ...
19:28:35.241 -> Connected to WiFi: 
19:28:35.241 -> SSID: HAGGIS24
19:28:35.241 -> IP Address: 192.168.1.33
19:28:35.241 -> Signal strength (RSSI):-41 dBm
19:28:35.241 -> 
19:28:35.241 -> Starting connection to server...
19:28:35.592 -> Connected to server: 
19:28:35.754 -> HTTP/1.1 200 OK
19:28:35.754 -> Connection: close
19:28:35.754 -> Content-Length: 0
19:28:35.754 -> perf: 7402827104
19:28:35.754 -> cache-control: no-cache, no-store, max-age=0
19:28:35.754 -> x-transaction-id: 7cbf9e7ce6497d44
19:28:35.754 -> strict-transport-security: max-age=631138519; includeSubdomains
19:28:35.754 -> x-response-time: 2
19:28:35.754 -> x-connection-hash: bf592e0575cf85cd2f91cea56a70b63c00c56299b0a40bde84b0342984298f91
19:28:35.754 -> Access-Control-Allow-Origin: https://platform.twitter.com
19:28:35.754 -> Accept-Ranges: bytes
19:28:35.754 -> Date: Sun, 06 Jul 2025 00:28:35 GMT
19:28:35.754 -> Via: 1.1 varnish
19:28:35.754 -> Age: 0
19:28:35.754 -> X-Served-By: cache-iah1720110-IAH
19:28:35.754 -> X-Cache: MISS
19:28:35.754 -> X-Timer: S1751761716.831964,VS0,VE26
19:28:35.754 -> Vary: Accept-Encoding
19:28:35.754 -> 
19:28:35.754 -> 
19:28:35.754 -> Disconnecting from Server.
19:28:35.754 -> Read 582 bytes.

--------------------------------------------------------------------
Output:
¯¯¯¯¯¯¯
Sketch uses 969598 bytes (30%) of program storage space. 
Maximum is 3145728 bytes.
Global variables use 46516 bytes (14%) of dynamic memory, 
            leaving 281164 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c

Leaving...
Hard resetting with RTC WDT...

*******************************************************************/
