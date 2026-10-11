#include <DHT.h>

#define DHTPIN D7
#define DHTTYPE DHT22

#define LDR_PIN A0
#define RELAY_PIN D6
#define LED_PIN D1

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Kondisi awal: relay dan LED mati
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Smart Warehouse Started");
}

void loop() {
  // Membaca DHT22
  float suhu = dht.readTemperature();

  // Membaca LDR
  int nilaiLDR = analogRead(LDR_PIN);

  // Cek DHT22
  if (isnan(suhu)) {
    Serial.println("Gagal membaca sensor DHT22!");
    delay(2000);
    return;
  }

  // Tampilkan hasil sensor
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" C | LDR: ");
  Serial.println(nilaiLDR);

  // Rule Engine
  if (suhu > 34 || nilaiLDR < 300) {

    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);

    Serial.println("Peringatan: Aktuator Aktif!");

  } else {

    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);

    Serial.println("Kondisi Aman");
  }

  Serial.println("-------------------------");

  delay(2000);
}