#include <Adafruit_GPS.h>

#define GPSSerial Serial1
Adafruit_GPS GPS(&GPSSerial);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Adafruit GPS Test");

  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);
}

void loop() {
  static unsigned long lastPrintTime = 0;

  char c = GPS.read();

  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) return;

    if (GPS.fix && millis() - lastPrintTime > 10000) {
      lastPrintTime = millis();

      // Convert latitude to decimal degrees
      float decimalLatitude = (int)(GPS.latitude / 100) + (GPS.latitude - (int)(GPS.latitude / 100) * 100) / 60.0;

      // Convert longitude to decimal degrees
      float decimalLongitude = (int)(GPS.longitude / 100) + (GPS.longitude - (int)(GPS.longitude / 100) * 100) / 60.0;

      // Print formatted GPS data
      Serial.print("Latitude: ");
      Serial.print(decimalLatitude, 6);
      Serial.print(" ");
      Serial.println(GPS.lat); // Print N/S indicator

      Serial.print("Longitude: ");
      Serial.print(decimalLongitude, 6);
      Serial.print(" ");
      Serial.println(GPS.lon); // Print E/W indicator

      Serial.print("Altitude: ");
      Serial.print(GPS.altitude);
      Serial.println(" meters");

      Serial.print("Satellites: ");
      Serial.println(GPS.satellites);
      Serial.println();

      Serial.print("Open in Google Maps: https://www.google.com/maps?q=");
      Serial.print(decimalLatitude, 6);
      Serial.print(GPS.lat);
      Serial.print(",");
      Serial.print(decimalLongitude, 6);
      Serial.println(GPS.lon);


    }
  }
}


