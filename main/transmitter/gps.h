TinyGPSPlus gps;
HardwareSerial gps_serial(1);

// ----- Location -----
String dataGPS = "";
// ----- datetime -----
String datetime = "";
// ----- VELETA -----
float previousLongitude = 0;
float previousLatitude = 0;

float deltaLatitude = 0;
float deltaLongitude = 0;

double windDirectionRad = 0;
double windDirectionDeg = 0;
String dataWindDir = "";



void gps_updateData() {
  while (gps_serial.available() > 0) {
    gps.encode(gps_serial.read());
  }
}

String gps_getLocation() {  
  dataGPS = String(gps.location.lat(), 6) + " " + String(gps.location.lng(), 6) + " " + String(gps.altitude.meters()) + " " + String(gps.speed.kmph());
  return dataGPS;
  }

String gps_getDatetime() {
  if (gps.date.isValid()) {
    datetime = String(gps.date.day()) + "-" + String(gps.date.month()) + "-" + String(gps.date.year()) + "_" + String (gps.time.hour()) + "-" + String(gps.time.minute()) + "-" + String(gps.time.second());
  }
   return datetime;
}


String gps_getWindDirection () {
  if (gps.location.isValid()){
    float currentLatitude = gps.location.lat();
    float currentLongitude = gps.location.lng();

    deltaLatitude = currentLatitude - previousLatitude;
    deltaLongitude = currentLongitude - previousLongitude;
    windDirectionRad = atan2(deltaLatitude, deltaLongitude);
    windDirectionDeg = windDirectionRad * 180/M_PI;

    if(deltaLatitude>0 && deltaLongitude>0){
      dataWindDir = "E" + String(abs(windDirectionDeg)) + "N";
    }else if (deltaLatitude>0 && deltaLongitude<0){
      dataWindDir = "O" + String(abs(windDirectionDeg)) + "N";
    }else if (deltaLatitude<0 && deltaLongitude<0){
      dataWindDir = "O" + String(abs(windDirectionDeg)) + "S";
    }else if (deltaLatitude<0 && deltaLongitude>0){
      dataWindDir = "E" + String(abs(windDirectionDeg)) + "S";
    }else if (deltaLatitude==0 && deltaLongitude>0){
      dataWindDir = "E";
    }else if (deltaLatitude==0 && deltaLongitude<0){
      dataWindDir = "O";
    }else if (deltaLatitude>0 && deltaLongitude==0){
      dataWindDir = "N";
    }else if (deltaLatitude<0 && deltaLongitude==0){
      dataWindDir = "S"; 
    }
    previousLongitude = currentLongitude;
    previousLatitude = currentLatitude;
  }else {
    dataWindDir = String(0);
  }

  return dataWindDir;
}
