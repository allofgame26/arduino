String array [6];
int i;

void setup() {
  Serial.begin(9600);
  array [0] = "240403";
  array [1] = "260817";
  array [2] = "170822";
  array [3] = "250903";
  array [4] = "310303";

  for( i = 0; i < 6; i++){
    Serial.println(array[i]);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
