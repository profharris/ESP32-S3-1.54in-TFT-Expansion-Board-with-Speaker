/* PSRAM_Test.ino
 * ESP32-S3 1.54in TFT Expansion Board with Speaker
 *
 * Enable & Test PSRAM and the System Environment on the ESP32-S3
 *
 * Original code By: Nathan Seidle, SparkFun Electronics
 * License: MIT. Please see LICENSE.md for more information.
 * Expanded and documented by: Prof. Michael P. Harris
 *
 * This example shows how to enable PSRAM on ESP32-S3 modules that
 * have it, --and use it for RAM requests above a certain byte threshold.
 *
 * Most of the ‘ESP.get*’ functions are defined in “esp.h” for the
 * appropriate ESP32 chip.
 *
 * NOTE:  Not all ESP32 modules have PSRAM built-in. The ESP32-S3-WROOM-1
 * ¯¯¯¯¯  (SparkFun) uses the ESP32-S3 Mini N8R2 has 8MB Flash and
 *        2MB PSRAM. The original Espressif ESP32-S3-DevKitC-1 N16R8
 *        has 16MB Flash and 8MB PSRAM.
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

unsigned long lastHeapReport;

void setup() {
  Serial.begin(15200);              // Serial Monitor
  while(!Serial);                   // Wait for Serial Port to open

  if(psramInit() == false)
    Serial.println("PSRAM Failed to Initialize!");
  else
    Serial.println("PSRAM Initialized.");

  Serial.printf("PSRAM Size available (bytes): %d\r\n",
    ESP.getFreePsram());

  // Use PSRAM for memory requests larger than 1,000 bytes
  heap_caps_malloc_extmem_enable(1000);
  
  printStats();
}

void loop() {
  delay(20); // Report Heap stats & PSRAM used every 1 second
  if(millis() - lastHeapReport > 1000) {
    lastHeapReport = millis();
    reportHeap();
  }
  if(Serial.available()) ESP.restart();
}

void reportHeap() {             // Report Heap stats & PSRAM used
  Serial.printf("FreeHeap: %d / HeapLowestPoint: %d / LargestBlock: %d / Used PSRAM: %d\r\n",
    ESP.getFreeHeap(),
    xPortGetMinimumEverFreeHeapSize(),
    heap_caps_get_largest_free_block(MALLOC_CAP_8BIT),
    ESP.getPsramSize() - ESP.getFreePsram());
}

void printStats() {
	uint32_t chipId = 0; // Calculate the CPU ID, e.g. 12734324.

    Serial.println("\nPrint System Environment Stats:");
	Serial.print(  "Source file: " );
	Serial.println( __FILE__ );
    Serial.println("");

	for(int i=0; i < 17; i+=8) {
      chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff ) << i;
	}

	/* Most of the ESP.get* functions are defined in “esp.h”
     * for the appropriate ESP32 chip.
     */
	Serial.printf( "ESP32 Chip model: %s\n", ESP.getChipModel());
	Serial.printf( "        Revision: %d\n", ESP.getChipRevision());
	Serial.printf( "      Core count: %d\n", ESP.getChipCores());
	Serial.printf( "         Chip ID: %u\n", chipId);
	Serial.print(  "       Frequency: " );
	Serial.println( ESP.getCpuFreqMHz());
	Serial.printf( "     Cycle count: %u\n", ESP.getCycleCount());
	Serial.printf( "     SDK version: %s\n", ESP.getSdkVersion());
    Serial.println("");
    
	Serial.println("  Heap: " );
	Serial.printf( " Total: %u\n", ESP.getHeapSize());
	Serial.printf( "  Used: %u\n", ESP.getHeapSize() - ESP.getFreeHeap());
	Serial.printf( "  Free: %u\n", ESP.getFreeHeap());
	Serial.printf( "  Largest block: %u\n", ESP.getMaxAllocHeap());
	Serial.printf( "  Minimum free since boot: %u\n", ESP.getMinFreeHeap());
    Serial.println("");
    
	Serial.println("  Flash: " );
	Serial.printf( "  Total: %u\n", ESP.getFlashChipSize());
	Serial.printf( "  Speed: %u\n", ESP.getFlashChipSpeed());
    Serial.println("");
    
	// None of the boards I tried supported these functions.
	//Serial.println( "?Magic? Flash: " );
	//Serial.printf( "  Total: %u\n", ESP.magicFlashChipSize());
	//Serial.printf( "  Speed: %u\n", ESP.magicFlashChipSpeed());

	if(psramFound()) {
      Serial.println("  PSRAM: " );
      Serial.printf( "  Total: %u\n", ESP.getPsramSize());
      Serial.printf( "   Used: %u\n", ESP.getPsramSize() - ESP.getFreePsram());
      Serial.printf( "   Free: %u\n", ESP.getFreePsram());
      Serial.printf( "  Largest block: %u\n", ESP.getMaxAllocPsram());
      Serial.printf( "  Minimum free since boot: %u\n", ESP.getMinFreePsram());
	  Serial.println("");
    } else {
      Serial.println( "This device lacks PSRAM!" );
      Serial.println("");
    }
    
	Serial.println(" Sketch: " );
	Serial.printf( "   Size: %u\n", ESP.getSketchSize());
	Serial.printf( "   Free: %u\n", ESP.getFreeSketchSpace());
    Serial.println("");
  } // END: printStats()

/*******************************************************************
Serial Monitor:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
21:53:52.051 -> PSRAM Initialized.
21:53:52.051 -> PSRAM Size available (bytes): 8386088
21:53:52.051 -> 
21:53:52.051 -> Print System Environment Stats:
21:53:52.051 -> Source file: C:\ESP32_ESP8266\ESP32-S3-WROOM-1 Dev (YD-ESP32-S3)\
                             ESP32-S3 1.54in TFT Expansion Board with Speaker\code\
                             PSRAM_Test\PSRAM_Test.ino
21:53:52.051 -> 
21:53:52.051 -> ESP32 Chip model: ESP32-S3
21:53:52.051 ->         Revision: 2
21:53:52.051 ->       Core count: 2
21:53:52.051 ->          Chip ID: 12284828
21:53:52.051 ->        Frequency: 240
21:53:52.051 ->      Cycle count: 374942174
21:53:52.051 ->      SDK version: v5.4.1-1-g2f7dcd862a-dirty
21:53:52.051 -> 
21:53:52.051 ->   Heap: 
21:53:52.051 ->  Total: 386120
21:53:52.051 ->   Used: 36720
21:53:52.051 ->   Free: 349400
21:53:52.051 ->   Largest block: 278516
21:53:52.051 ->   Minimum free since boot: 345216
21:53:52.051 -> 
21:53:52.051 ->   Flash: 
21:53:52.051 ->   Total: 16777216
21:53:52.051 ->   Speed: 80000000
21:53:52.051 -> 
21:53:52.051 ->   PSRAM: 
21:53:52.051 ->   Total: 8388608
21:53:52.051 ->    Used: 2520
21:53:52.051 ->    Free: 8386088
21:53:52.051 ->   Largest block: 8257524
21:53:52.051 ->   Minimum free since boot: 8386088
21:53:52.051 -> 
21:53:52.051 ->  Sketch: 
21:53:52.051 ->    Size: 331312
21:53:52.051 ->    Free: 3145728
21:53:52.051 -> 
21:53:52.051 -> FreeHeap: 348956 / HeapLowestPoint: 345216 / LargestBlock: 8257524 / Used PSRAM: 2520
21:53:52.871 -> FreeHeap: 348956 / HeapLowestPoint: 345216 / LargestBlock: 8257524 / Used PSRAM: 2520

Output:
¯¯¯¯¯¯¯
Sketch uses 331170 bytes (10%) of program storage space. 
Maximum is 3145728 bytes.
Global variables use 21156 bytes (6%) of dynamic memory, 
            leaving 306524 bytes for local variables. 
         Maximum is 327680 bytes.

Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
MAC: 30:ed:a0:bb:73:9c
...
Leaving...
Hard resetting with RTC WDT...
*******************************************************************/
