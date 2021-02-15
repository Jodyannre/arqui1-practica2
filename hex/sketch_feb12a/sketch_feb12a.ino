#include <Servo.h>
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

bool passwordincorrecta = false;


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

Servo servo;

int cm = 0;

long distancia(int trigger, int echo) {
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH);
}

//const int butPinUp = 3;
//int butUpState = 0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  //lcd.print("Lab Arqui");
  pinMode(ledPin, OUTPUT);

  servo.attach(A0);

  pinMode(A1, INPUT);//javier
  pinMode(A2, INPUT); //javier
  pinMode(A3, INPUT); //javier
  pinMode(A4, INPUT); //javier
  //pinMode(butPinUp, INPUT); //javier

}
//--------------------------------------------------------Javier

char * txt = "CASA INTELIGENTE ACE1";//javier
char * txt2 = "ACE1-A-G12-S1";//javier
//int iCursor = 0;//javier
//int linea = 1;//javier
//--------------------------------------------------------Javier
/*
  void actualizador() {
  int leng1 = strlen(txt);//calcula longitud del 1er string
  if (iCursor == leng1 - 1) {
    iCursor = 0;
  }
  lcd.setCursor(0, linea);
  if (iCursor < leng1 - 16) {

    for (int iChar = iCursor; iChar < iCursor + 16; iChar++) {
      lcd.print(txt[iChar]);
    }

  } else {
    for (int iChar = iCursor; iChar < (leng1 - 1); iChar++) {
      lcd.print(txt[iChar]);
    }
    for (int iCgar = 0; iCgar <= 16 - (leng1 - iCursor); iCgar++) {
      lcd.print(txt[iCgar]);
    }


  }
  iCursor++;
  Serial.println(iCursor);

  if (iCursor == 22) {
    Serial.println("XD");
  }
  //lcd.print(txt);
  //delay(2000);
  //lcd.print(txt2);


  }*/

bool modoDeteccion = false;//javier

void loop() {

  //actualizador();
  //delay(300);
  //--------------------------------------------------------Javier----------------------------------------------------------------

  //estado();
  
  if (modoDeteccion == false) {   //modo inicial
    intro();

    //AUX
  
    //delay(500);
    cm = 0.01723 * distancia(6, 6);
    if(cm<=150){
      inputPass();
    /*lcd.setCursor(0,0);
    lcd.print("Contrasenia:");
    char c = '\0';
    String contra_pad= "";
    int i=0;
    while(true){
      c=pad.getKey();
      if(c=='*') break;
      if(c!=NO_KEY){
        contra_pad+=c;
        lcd.setCursor(i,1);
        lcd.print(c);
        i++;
      }
    }
    lcd.clear();
    if(contra_pad=="202112"){
      lcd.print("Correcto");
      delay(500);
      servo.write(180);
      delay(3000);
      servo.write(90);
      modoDeteccion = !false;
    }else{
      lcd.print("Incorrecto");
    }
    
    delay(1000);*/
    }

  }
  else { // el detector de la puerta se activo <=150cm

    verificarEstadoHabitacion();

    //Serial.println(porcentaje);
    //delay(500);

    //pasamos al modo teclado
    //NOS TOCARIA MOSTRAR:::: INGRESE SU CONTRASEÑA
    /*
        if(confirmacion==true){//si metio algo por el teclado

        if(contrasenya correcta==true){
        //entramos aqui con casa
        //NOS TOCARIA MOSTRAR:::: BIENVENIDO A CASA ^_^

        //Control de la iluminación();//AQUI VENDRIA EL MODO VERIFICARESTADOHABITACION();

        }else{//modo alarma
        //NOS TOCARIA MOSTRAR::::  ERROR EN CONTRASEÑA
        if(contador==3){
        //modo bloqueado
            //NOS TOCARIA MOSTRAR::::   “Acceso No Autorizado”
            contador=0
        }
        contador++
        }
        }
    */

  }

  //--------------------------------------------------------Javier----------------------------------------------------------------

  //:::::::::::::::::::::::::AUX:::::::::::::::::::::::::::::::::::::
  /*lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Lab Arqui");
    char c = '\0';
    String contra_pad= "";
    int i=0;
    while(true){
    c=pad.getKey();
    if(c=='*') break;
    if(c!=NO_KEY){
      contra_pad+=c;
      lcd.setCursor(i,1);
      lcd.print(c);
      i++;
    }
    }

    lcd.clear();
    if(contra_pad=="456"){
    lcd.print("Correcto");
    }else{
    lcd.print("Incorrecto");
    }

    delay(3000);*/

  /*
    cm = 0.01723 * distancia(6, 6);
    Serial.println(cm);
    delay(500);*/

  /*
    servo.write(180);
    delay(1000);
    servo.write(90);
    delay(1000);
  */

  /*
    int val = analogRead(A1);
    int por = map(val, 10, 975, 0, 100);
    Serial.println(por);
    delay(500);*/

    
  
  //:::::::::::::::::::::::::AUX:::::::::::::::::::::::::::::::::::::
}
//--------------------------------------------------------Javier----------------------------------------------------------------
void intro() {

  if(passwordincorrecta == false){ //validaciion para que no se inicie la intro cada vez que que se ingrese una contraseña incorrecta
    //defino la posicion en el LCD
    //         setCursor(col,row)
    lcd.setCursor(0, 0);
    //imprimo lo q quiero en LCD
    lcd.print(txt);
    //delay par q sea visto
    delay(2000);
    //limpio el LCD
    lcd.clear();
    delay(1000);
    //mensaje 2
    lcd.setCursor(2, 1);
    lcd.print(txt2);
    delay(2000);
    lcd.clear();
    delay(1000);
    
  }
  

}

void verificarEstadoHabitacion () {
  habitacion1();
  habitacion2();
  habitacion3();
  habitacion4();

}

/*void estado() {

 butUpState = digitalRead(butPinUp);
 
  if (butUpState == HIGH ) {
    modoDeteccion = !false;
  } else {
    modoDeteccion = false;
  }
}*/

void habitacion1() {
  lcd.setCursor(0, 0);//defino la posicion en el LCD
  //imprimo lo q quiero en LCD
  lcd.print("Habitacion 1:");
  lcd.setCursor(0, 1);
  //imprimo lo q quiero en LCD
  int val = analogRead(A1);//leo en A1
  int porcentaje = map(val, 10, 975, 0, 100);//lo paso a porcentaje
  //imprimo en LCD el estado de la habitacion
  //lcd.print(porcentaje);
  if (porcentaje > 85) {
    lcd.print("Luz encendida");
  } else {
    lcd.print("Luz apagada");
  }

  //delay par q sea visto
  delay(2000);
  //limpio el LCD
  lcd.clear();
  //para q se aprececie limpio el LCD
  delay(1000);
}

void habitacion2() {
  lcd.setCursor(0, 0);//defino la posicion en el LCD
  //imprimo lo q quiero en LCD
  lcd.print("Habitacion 2:");
  lcd.setCursor(0, 1);
  //imprimo lo q quiero en LCD
  int val = analogRead(A2);//leo en A1
  int porcentaje = map(val, 10, 975, 0, 100);//lo paso a porcentaje
  //imprimo en LCD el estado de la habitacion
  //lcd.print(porcentaje);
  if (porcentaje > 85) {
    lcd.print("Luz encendida");
  } else {
    lcd.print("Luz apagada");
  }

  //delay par q sea visto
  delay(2000);
  //limpio el LCD
  lcd.clear();
  //para q se aprececie limpio el LCD
  delay(1000);
}

void habitacion3() {
  lcd.setCursor(0, 0);//defino la posicion en el LCD
  //imprimo lo q quiero en LCD
  lcd.print("Habitacion 3:");
  lcd.setCursor(0, 1);
  //imprimo lo q quiero en LCD
  int val = analogRead(A3);//leo en A1
  int porcentaje = map(val, 10, 975, 0, 100);//lo paso a porcentaje
  //imprimo en LCD el estado de la habitacion
  //lcd.print(porcentaje);
  if (porcentaje > 85) {
    lcd.print("Luz encendida");
  } else {
    lcd.print("Luz apagada");
  }

  //delay par q sea visto
  delay(2000);
  //limpio el LCD
  lcd.clear();
  //para q se aprececie limpio el LCD
  delay(1000);
}

void habitacion4() {
  lcd.setCursor(0, 0);//defino la posicion en el LCD
  //imprimo lo q quiero en LCD
  lcd.print("Habitacion 4:");
  lcd.setCursor(0, 1);
  //imprimo lo q quiero en LCD
  int val = analogRead(A4);//leo en A1
  int porcentaje = map(val, 10, 975, 0, 100);//lo paso a porcentaje
  //imprimo en LCD el estado de la habitacion
  //lcd.print(porcentaje);
  if (porcentaje > 85) {
    lcd.print("Luz encendida");
  } else {
    lcd.print("Luz apagada");
  }

  //delay par q sea visto
  delay(2000);
  //limpio el LCD
  lcd.clear();
  //para q se aprececie limpio el LCD
  delay(1000);
}
//--------------------------------------------------------Javier----------------------------------------------------------------


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
    delay(500);
    servo.write(180);
    delay(3000);
    servo.write(90);
    lcd.clear();
    modoDeteccion = !false;
    passwordincorrecta = false;
  }
  else {
    passwordincorrecta = !false; //para que no se inicie la intro
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
