//------------------------------------------------------------------------------------------// Fungsi LCD print untuk String
void lcdPrint(int x, int y, String msg) {
  lcd.setCursor(x, y);
  lcd.print(msg);
}
//------------------------------------------------------------------------------------------// Fungsi LCD print untuk CHAR
void lcdPrint(int x, int y, char msg) {
  lcd.setCursor(x, y);
  lcd.print(msg);
}
//------------------------------------------------------------------------------------------// Fungsi LCD print untuk CHAR Array
void lcdPrint(int x, int y, char* msg) {
  lcd.setCursor(x, y);
  lcd.print(msg);
}
String empatDigit(int val) {
  if (val < 10) return "000" + String(val);
  else if (val < 100) return "00" + String(val);
  else if (val < 1000) return "0" + String(val);
  else String(val);
}
//------------------------------------------------------------------------------------------// Jeda Tombol di pencet dan Bunyi Beep
void beep() {
  digitalWrite(BUZZER, ON);                                                                 // Buzzer ON
  delay(BOUNCE);                                                                            // Jeda Bounce
  digitalWrite(BUZZER, OFF);                                                                // Buzzer OFF
}
//------------------------------------------------------------------------------------------// Menulis Data SD card
void sdCardWrite(String file, float datas[], int c) {
  Serial.println("Write SD Card");
  Serial.print("Nama File: ");
  Serial.println(file);
  File dataFile = SD.open(file, FILE_WRITE);
  if (dataFile) {
    Serial.println(info);
    Serial.println("----------------------");
    dataFile.println(info);
    dataFile.close();
  }
  float total_data = 0.0;
  for (int i = 0; i < c ; i++) {
    total_data = total_data + datas[i];
    String dataString = String(i + 1) + " : " + String(datas[i]) + "g";
    dataFile = SD.open(file, FILE_WRITE);
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      Serial.println(dataString);
    }
  }
  dataFile = SD.open(file, FILE_WRITE);
  String dataString = "Total : " + String(total_data) + "g";
  if (dataFile) {
    Serial.println("----------------------");
    Serial.println(dataString);
    dataFile.println(dataString);
    dataFile.close();
  }
}
//------------------------------------------------------------------------------------------
void printingMode(float datas[], int c) {
  Serial.println("Printing..");
  TMU220.justifyLeft();
  TMU220.println(info);
  TMU220.println("------------------");
  float total = 0.0;
  for (int i = 0; i < c; i++) {
    total += datas[i];
    String dataString = String(i + 1) + " : " + String(datas[i]) + "g";
    Serial.println(dataString);
    TMU220.println(dataString);
  }
  String dataString = "TOTAL : " + String(total) + "g";
  TMU220.justifyRight();
  TMU220.println(dataString);
  TMU220.feed(6);
  Serial.println("--------------------");
  Serial.print("Total: ");
  Serial.print(total);
  Serial.println("g");

}
//------------------------------------------------------------------------------------------
void readSerial1() {
  while (timbangan.available() > 0) {
    char c = timbangan.read();
    raw  += c;
    if (c == 'g') {
      x++;
      if (x == 1) {
        TW = str.toFloat();
        //Serial.println("TW: " + String(TW));
      } else if (x == 2) {
        NW = str.toFloat();
        Serial.print("NW: ");
        Serial.print(NW);
        Serial.println("g");
      } else if (x == 3) {
        GW = str.toFloat();
        //Serial.println("GW: " + String(GW));
      }
      if (x >= 3) {
        //Serial.println(raw);
        //Serial.println();
        raw = "";
        x = 0;
        timbang = true;
      }
      parsing = false;
      str = "";
    }
    if (parsing) {
      if (c != ' ') {
        str += c;
      }
    }
    if (c == '+') {
      parsing = true;
    }
  }
}
//------------------------------------------------------------------------------------------
