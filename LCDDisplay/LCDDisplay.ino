#include <LiquidCrystal_I2C.h>

const int col = 16;
const int row = 2;
LiquidCrystal_I2C lcd(0x27, col, row);
int position = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.clear();
  /*lcd.setCursor(1,0);
  lcd.print("ARYA");
  lcd.setCursor(5, 1);
  lcd.print("GADIS");*/
}

void loop() {
  lcd.clear();
  lcd.setCursor(position,0);
  lcd.print("ARYA");
  delay(500);
  position += 1;

  if(position < 0 || position >= col){
    position = 0;
  }

}
