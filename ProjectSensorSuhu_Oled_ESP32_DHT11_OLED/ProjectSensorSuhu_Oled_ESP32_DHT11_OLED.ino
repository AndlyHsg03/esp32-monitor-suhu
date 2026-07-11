/*
  Monitor Suhu & Kelembapan — ESP32 + DHT11 + OLED
  ---------------------------------------------------
  Wiring:
    DHT11  -> ESP32
    VCC (+)   -> 3.3V
    GND (-)   -> GND
    DATA(out) -> GPIO 25

    OLED (I2C, SSD1306 0.96") -> ESP32
    VCC    -> 3.3V
    GND    -> GND
    SDA    -> GPIO 32
    SCL    -> GPIO 33

  Library yang dibutuhkan (install via Library Manager):
    - DHT sensor library (by Adafruit)
    - Adafruit Unified Sensor
    - Adafruit GFX Library
    - Adafruit SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ---- Konfigurasi DHT11 ----
#define DHTPIN 25
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---- Konfigurasi OLED ----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C  // umumnya 0x3C, kadang 0x3D — cek datasheet/label modul

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Interval baca sensor (DHT11 minimal butuh ~2 detik antar baca)
const unsigned long INTERVAL = 2000;
unsigned long lastRead = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Inisialisasi I2C dengan pin custom (SDA = 21, SCL = 22)
  Wire.begin(21, 22);

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED tidak terdeteksi, cek wiring/alamat I2C!"));
    while (true); // stop di sini kalau OLED gagal init
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Menyiapkan sensor...");
  display.display();
  delay(1000);
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead >= INTERVAL) {
    lastRead = now;

    float suhu = dht.readTemperature();     // Celsius
    float kelembapan = dht.readHumidity();  // %

    if (isnan(suhu) || isnan(kelembapan)) {
      Serial.println("Gagal membaca sensor DHT11!");
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.println("Sensor error!");
      display.println("Cek wiring DHT11");
      display.display();
      return;
    }

    // Tampilkan di Serial Monitor
    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print(" C, Kelembapan: ");
    Serial.print(kelembapan);
    Serial.println(" %");

    // Tampilkan di OLED
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Monitor Suhu ESP32");
    display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

    display.setTextSize(2);
    display.setCursor(0, 20);
    display.print(suhu, 1);
    display.println(" C");

    display.setCursor(0, 44);
    display.print(kelembapan, 1);
    display.println(" %");

    display.display();
  }
}
