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

//Bool para verificar que entra o sale de la casa.
bool puertaEntrada = true;
bool puertaSalida = false;


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

//Declaración de motores
Servo servoMotor;
Servo servoMotor2;



//SENSOR---------------------------------------
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
//SENSOR---------------------------------------


//const int butPinUp = 3;
//int butUpState = 0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  //lcd.print("Lab Arqui");
  pinMode(ledPin, OUTPUT);

  //Inicialización del servoMotor en el pin A0
  servoMotor.attach(A0);
  servoMotor2.attach(A8);

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


bool modoDeteccion = false;//javier

void loop() {

  //--------------------------------------------------------Javier----------------------------------------------------------------


  if (modoDeteccion == false) {   //modo inicial
    calcularDistancia(1);
    Serial.print("Distancia de puerta de entrada ");
    Serial.print("cm: ");
    Serial.println(cm);
    intro();

    //Calculo de distancia en cm


    if (cm <= 150) {
      inputPass();
    }

  }
  else { // el detector de la puerta se activo <=150cm

    verificarEstadoHabitacion();

    //NOS TOCARIA MOSTRAR:::: INGRESE SU CONTRASEÑA

  }

}
//--------------------------------------------------------Javier----------------------------------------------------------------
void intro() {
  lcd.clear();

  if (passwordincorrecta == false || cm > 150) { //validaciion para que no se inicie la intro cada vez que que se ingrese una contraseña incorrecta
    //Que se inicie si la persona se aleja de la puerta
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
  } else {

  }


}

void verificarEstadoHabitacion () {
  habitacion1();
  habitacion2();
  habitacion3();
  habitacion4();
  //Calcular distnancia del a puerta de salida
  calcularDistancia(2);
  Serial.print("Distancia de puerta de salida ");
  Serial.print("cm: ");
  Serial.println(cm);
  if (cm <= 150) {
    moverMotor();
  }
}


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
  /*lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INGRESE SU CONTRASENIA");*/
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("INGRESE SU");
  lcd.setCursor(0, 1);
  lcd.print("CONTRASENIA");
  delay(2000);
  lcd.clear();
  lcd.print("CONTRASENIA:");
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
    lcd.print("BIENVENIDO A");
    lcd.setCursor(0, 1);
    lcd.print("CASA ^_^");
    //****AQUI SE PUEDE INSTANCIAR EL METODO PARA GIRAR MOTORO**///////////////
    delay(75);
    moverMotor();
    lcd.clear();
    modoDeteccion = !false;
    passwordincorrecta = false;
  }
  else {
    passwordincorrecta = !false; //para que no se inicie la intro
    ContadorPass++;
    if (ContadorPass < 3) {
      lcd.print("ERROR EN");
      lcd.setCursor(0, 1);
      lcd.print("CONTRASENIA");
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
    lcd.print("Acceso No");
    lcd.setCursor(0, 1);
    lcd.print("Autorizado");
    lcd.setCursor(11, 1);
    lcd.print(contadorSegundos);
    if (contadorSegundos == 0) {
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
  ContadorPass = 0;
}

void moverMotor() {
  if (puertaEntrada) {
    servoMotor.write(-90);
    delay(3000);
    servoMotor.write(90);
    puertaEntrada = false;
    puertaSalida = true;
  } else if (puertaSalida) {
    servoMotor2.write(-90);
    delay(3000);
    servoMotor2.write(90);
    puertaSalida = false;
    puertaEntrada = true;
    //Reiniciar todo
    modoDeteccion = false;
  }
}

void calcularDistancia(int numero) {
  if (numero == 1 && puertaEntrada) {
    cm = 0.01723 * distancia(6, 6);
  } else if (numero == 2 && puertaSalida) {
    cm = 0.01723 * distancia(5, 5);
  }
  delay(30);
}
