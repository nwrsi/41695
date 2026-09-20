#define BLYNK_TEMPLATE_ID "TMPL6jfWTUTZZ" 
#define BLYNK_TEMPLATE_NAME "Quickstart Template" 
#define BLYNK_AUTH_TOKEN "tkFyHR-b6JOOCC8SsxIuCwZ7BX5N2bkJ"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char ssid[] = "secret"; 
char pass[] = "secret";
BlynkTimer timer;

#define WATER_PIN D0

void sendWaterSensor()
{
  int water = analogRead(D0);

  Serial.print("Water Sensor = ");
  Serial.println(water);

  Serial.print("Blynk connected = ");
  Serial.println(Blynk.connected());

  if (Blynk.connected())
  {
    Blynk.virtualWrite(V0, water);
    Serial.println("Sent to Blynk V0!");
  }
  else
  {
    Serial.println("NOT connected to Blynk!");
  }
  if(water == 1023){
    digitalWrite(D4,HIGH);
    digitalWrite(D5,LOW);
    delay(200);
  }
  else{
    digitalWrite(D4,LOW);
    digitalWrite(D5,HIGH);
    delay(200);
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("ESP8266 START");

  pinMode(WATER_PIN, INPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);

  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");

  Blynk.config(BLYNK_AUTH_TOKEN);

  if (Blynk.connect(5000))
  {
    Serial.println("Blynk connected!");
  }
  else
  {
    Serial.println("Blynk NOT connected!");
  }

  timer.setInterval(1000L, sendWaterSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
