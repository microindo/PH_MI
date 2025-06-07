#define PH_SENSOR_PIN 34

const float offset = 0.8;      // Diubah berdasarkan hasil offset

const float calibration_value = 21.34 + offset;

float readPH();

void setup() {
  Serial.begin(115200);
}

void loop() {
  float ph = readPH();
  Serial.print("pH Value: ");
  Serial.println(ph, 2);
  delay(1000);
}

float readPH() {
  int readings[10];

  // Ambil 10 sampel pembacaan
  for (int i = 0; i < 10; i++) {
    readings[i] = analogRead(PH_SENSOR_PIN);
    delay(30);
  }

  // Urutkan data
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (readings[i] > readings[j]) {
        int temp = readings[i];
        readings[i] = readings[j];
        readings[j] = temp;
      }
    }
  }

  // Hitung rata-rata nilai tengah (index 2–7)
  unsigned long sum = 0;
  for (int i = 2; i < 8; i++) {
    sum += readings[i];
  }

  float voltage = (float)sum * 3.3 / 4095.0 / 6;
  return -5.70 * voltage + calibration_value;
}


