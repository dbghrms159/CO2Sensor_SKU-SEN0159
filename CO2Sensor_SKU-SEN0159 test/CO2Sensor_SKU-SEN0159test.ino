int val,co2;
float ppm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Sample value.");
  
  val = analogRead(0);
  co2 = map(val ,0 ,1023, 10000, 0);
  
  Serial.print("\t");
  Serial.print(co2);
  Serial.println("ppm");
  delay(100);
}
