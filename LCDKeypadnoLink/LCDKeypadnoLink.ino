#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte numRows= 4; //baris pada keypad
const byte numCols= 4; //Kolom pada keypad
const int col = 16; // untuk LCD
const int row = 2;
LiquidCrystal_I2C lcd(0x27, col, row);
int posisi = 0;

/*keymap mendefinisikan tombol ditekan sesuai
dengan baris dan kolom seperti muncul pada keypad*/
char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};


byte rowPins[numRows]= {9,8,7,6}; 
byte colPins[numCols]= {5,4,3,2}; 


Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{
Serial.begin(9600);

lcd.init();
lcd.backlight();
lcd.clear();
}

// Jika tombol ditekan, tombol ini disimpan dalam 'keypressed' variabel
// Jika kunci tidak sama dengan 'NO_KEY', maka tombol ini dicetak
// Jika jumlah = 17, maka penghitungan reset kembali ke 0 (ini berarti tidak ada tombol yang ditekan selama proses pemindaian seluruh keypad

void loop(){
char keypressed = myKeypad.getKey();
if (keypressed != NO_KEY){
Serial.print(keypressed);
};
// LCD
  lcd.clear();
  lcd.setCursor(posisi,0);
  lcd.print("ARYA&");
  lcd.setCursor(posisi, 1);
  lcd.print("GADIS");
  delay(500);

  posisi += 1;

  if(posisi < 0 || posisi >= col){
    posisi = 0;
  };

}
