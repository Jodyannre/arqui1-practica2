#include <Key.h>
#include <Keypad.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(53,51,49,47,45,43);

const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};


byte rowPins[rows]={10,9,8,7};
byte colPins[cols]={13,12,11};
Keypad pad = Keypad(makeKeymap(keys),rowPins,colPins,rows,cols);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("Lab arquí");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Lab Arqui");
  char c = '\0';
  String contra_pad = "";
  int i = 0;
}
