#include <Key.h>
#include <Keypad.h>

#include <LiquidCrystal.h>

//pines de lcd
const int rs = 53;
const int enable = 51;
const int d4 = 49;
const int d3 = 47;
const int d2 = 45;
const int d1 = 43;
//pines de keypad
//filas
const int f1 = 10;
const int f2 = 9;
const int f3 = 8;
const int f4 = 7;
//columnas
const int c1 = 13;
const int c2 = 12;
const int c3 = 11;

//pin led alarma

const int ledPin = 2;


//PASSWORD
const String PASS = "202112";
int ContadorPass = 0;

const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[rows] = {f1, f2, f3, f4}; //connect to the row pinouts of the keypad
byte colPins[cols] = {c1, c2, c3}; //connect to the column pinouts of the keypad
Keypad teclado = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

LiquidCrystal lcd(rs, enable, d4, d3, d2, d1);


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Lab arquí");
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (distancia(149)) {
    inputPass();
  }
}


void inputPass() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("INGRESE SU CONTRASENIA");
  char c = '\0';
  String pass_pad = "";
  int contador_ingresopad = 0;
  while (true) {
    c = teclado.getKey();
    if (c == '*') break;
    if (c != NO_KEY) {
      pass_pad += c;
      lcd.setCursor(contador_ingresopad, 1);
      lcd.print(c);
      contador_ingresopad++;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  if (pass_pad == PASS) {
    lcd.print("BIENVENIDO A CASA ^_^");
    //****AQUI SE PUEDE INSTANCIAR EL METODO PARA GIRAR MOTORO**///////////////
  }
  else {
    ContadorPass++;
    if (ContadorPass < 3) {
      lcd.print("ERROR EN CONTRASEÑA");
      delay(1000);
    }
    else {
      //lcd.print("Acceso No Autorizado");
      AlarmaLed();
    }
  }
}

bool distancia(int distancia) {
  if (distancia >= 148) {
    return true;
  }
  else {
    return false;
  }
}

void AlarmaLed() {
  int contadorSegundos = 20;
  
  while (true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Acceso No Autorizado");
    lcd.setCursor(0, 1);
    lcd.print(contadorSegundos);
    if(contadorSegundos == 0){
      break;
    }
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    contadorSegundos--;
  }
  ContadorPass = 20;
}

