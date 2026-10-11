const int buttonPin = 4;
const int ledPin = 5;

bool ledState = false;  // Menyimpan status LED: false = mati
int buttonState = LOW;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Saat awal dinyalakan, LED dalam keadaan mati
  digitalWrite(ledPin, LOW);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    // Ubah status LED setiap kali tombol ditekan
    ledState = !ledState;

    digitalWrite(ledPin, ledState ? HIGH : LOW);

    if (ledState) {
      Serial.println("Toggle: LED ON");
    } else {
      Serial.println("Toggle: LED OFF");
    }

    // Debouncing agar satu tekanan tidak terbaca berkali-kali
    delay(200);

    // Tunggu sampai tombol dilepas
    while (digitalRead(buttonPin) == HIGH) {
      delay(10);
    }
  }
}