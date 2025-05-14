
// findSPIpins.ino
// Find the default (Hardware) SPI pins for your board.
// Make sure you have the right board selected in: Tools > Boards...

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);         // Initialize Serial communication
  while(!Serial);               // Wait for the Serial port to open

  Serial.print(" MOSI: ");
  Serial.println(MOSI);
  Serial.print(" MISO: ");
  Serial.println(MISO);
  Serial.print("  SCK: ");
  Serial.println(SCK);
  Serial.print("SS/CS: ");
  Serial.println(SS);
}

void loop() {
  // put your main code here, to run repeatedly:
}
