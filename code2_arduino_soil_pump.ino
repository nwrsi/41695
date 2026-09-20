/const int soilPin = A0;
const int relayPin = 7;

const int dryThreshold = 650;

// Most relay modules like yours are active LOW
const int PUMP_ON = LOW;
const int PUMP_OFF = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(relayPin, PUMP_OFF);
}

void loop() {
  digitalWrite(8,HIGH);
  int soilRaw = analogRead(soilPin);

  // Convert your calibration into roughly 0-100%
  int moisture = map(soilRaw, 1000, 200, 0, 100);
  moisture = constrain(moisture, 0, 100);

  Serial.print("Raw: ");
  Serial.print(soilRaw);

  Serial.print(" | Moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  // Higher raw value = drier
  if (soilRaw > dryThreshold) {

    Serial.println("DRY -> Pump ON");

    digitalWrite(relayPin, PUMP_ON);

    delay(2000); // water for 2 seconds

    digitalWrite(relayPin, PUMP_OFF);

    Serial.println("Pump OFF");

    // Prevent pump from repeatedly switching immediately
    delay(5000);
  }

  else {

    digitalWrite(relayPin, PUMP_OFF);

    Serial.println("Soil OK");

    delay(1000);
  }
}/
