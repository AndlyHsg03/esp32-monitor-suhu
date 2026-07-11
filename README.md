# Monitor Suhu & Kelembapan — ESP32 + DHT11 + OLED

Proyek sederhana untuk membaca suhu dan kelembapan menggunakan sensor DHT11, lalu menampilkan hasilnya secara real-time di layar OLED menggunakan mikrokontroler ESP32.

## 📋 Deskripsi

Proyek ini merupakan langkah awal untuk belajar IoT dengan ESP32. Sensor DHT11 membaca suhu (°C) dan kelembapan (%) setiap 2 detik, kemudian data tersebut ditampilkan langsung di layar OLED 0.96" tanpa perlu terhubung ke laptop/komputer.

## 🧰 Komponen yang Dibutuhkan

| Komponen | Jumlah | Keterangan |
|---|---|---|
| ESP32 DevKit | 1 | Board ESP32-D0WD-V3 atau sejenisnya |
| Sensor DHT11 | 1 | Modul dengan 3 pin (+, -, out) |
| OLED Display 0.96" | 1 | I2C, chip SSD1306, 128x64 |
| Kabel jumper | Secukupnya | Female-to-female |
| Breadboard | 1 | Opsional |
| Kabel USB | 1 | Untuk upload program & power |

## 🔌 Wiring / Rangkaian

### DHT11 → ESP32
| DHT11 | ESP32 |
|---|---|
| VCC (+) | 3.3V |
| GND (-) | GND |
| DATA (out) | GPIO 25 |

### OLED (I2C) → ESP32
| OLED | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 32 |
| SCL | GPIO 33 |

## 📚 Library yang Dibutuhkan

Install melalui Arduino IDE (`Tools > Manage Libraries`):

- `DHT sensor library` (by Adafruit)
- `Adafruit Unified Sensor`
- `Adafruit GFX Library`
- `Adafruit SSD1306`

## ⚙️ Setup & Instalasi

1. Install [Arduino IDE](https://arduino.cc/en/software).
2. Tambahkan board ESP32 melalui `File > Preferences > Additional Boards Manager URLs`:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Install board **esp32** via `Tools > Board > Boards Manager`.
4. Install semua library yang disebutkan di atas.
5. Sambungkan rangkaian sesuai tabel wiring.
6. Pilih board **ESP32 Dev Module** di `Tools > Board`.
7. Pilih port yang sesuai di `Tools > Port`.
8. Upload sketch `monitor_suhu_dht11_oled.ino`.

## 🖥️ Cara Kerja

1. Sensor DHT11 membaca suhu & kelembapan setiap 2 detik.
2. Data ditampilkan di:
   - **Serial Monitor** (baud rate `115200`) — untuk debugging.
   - **Layar OLED** — tampilan utama, langsung terlihat tanpa laptop.
3. Jika sensor gagal terbaca, layar OLED akan menampilkan pesan error.

## 🐛 Troubleshooting

| Masalah | Solusi |
|---|---|
| OLED tidak menyala | Cek alamat I2C (`0x3C` atau `0x3D`), cek wiring SDA/SCL |
| Sensor error / nilai "nan" | Cek wiring DATA DHT11, pastikan tidak longgar |
| Upload gagal / write timeout | Cek kabel USB, turunkan Upload Speed ke 115200, cek driver CP210x/CH340 |
| Chip stopped responding saat upload | Lepas VCC sensor & OLED sementara saat upload, lalu sambung kembali |

## 📄 Lisensi

Proyek ini bebas digunakan dan dimodifikasi untuk keperluan belajar.
