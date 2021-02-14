#include <LedControl.h>
//-------------------------------------------------------------------------------------------------------------------------------------
//Definición de los pines utilizados
const int butPinUp = 7;
const int butPinDown = 6;
const int butPinLeft = 5;
const int butPinRight = 4;
const int ledPin = 3;
int Cont = 0;
int v_estatico = 500;
int vel_scroll = 0;
//-------------------------------------------------------------------------------------------------------------------------------------


///////********************************INSERCCION 1 DE CODIGO LETRERO***********************************************///////////////////////
//# DE PIN PARA CADA BOTON
const int btnIn1 = 11;
const int btnIn2 = 10;
const int btnIn3 = 9;
//ESTADO INICIAL DE LOS BOTONES
int btnIn1State = 0;
int btnIn2State = 0;
int btnIn3State = 0;




//***************************************FINALIZA INSERCION 1************************************************************************///





//-------------------------------------------------------------------------------------------------------------------------------------
//Creación de variable que manejará la matriz
LedControl lc = LedControl(51, 52, 45, 2);
//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//Variable para manejar el delay de actualización y velocidad de la snake
unsigned long delaytime = 0;

//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//Variables de estados de los botones
int butUpState = 0;
int butDownState = 0;
int butLeftState = 0;
int butRightState = 0;
//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//Variables para el manejo de la cola de la snake
byte ultimaX = 0;
byte ultimaY = 0;
byte ultimaMat = 0;
//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//clase de la comida
struct Point {
  int row = 0, col = 0, matriz = 0;
  Point(int row = 0, int col = 0, int matriz = 0): row(row), col(col), matriz(matriz) {}
};
//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//Clase snake
struct Cabeza {
  int y = 0, x = 0, matriz = 0, dir = 0;
  Cabeza(int y = 0, int x = 0, int matriz = 0, int dir = 0): y(y), x(x), matriz(matriz), dir(dir) {}
};
//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//Variables de estados del juego
int puntos = 0;
const short messageSpeed = 0;
bool snakeCrecio = false;
//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//Matriz para guardar el cuerpo de la snake
byte cuerpo[3][128];
byte longitud;
//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//Declaración de comida, cabeza y cola de la snake
Point food(-1, -1, -1);
Cabeza snake(0, 0, 0, 0);
Cabeza cola(0, 0, 0, 0);
//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//Valores para start y pause
int special = 8;
int specialState = 0;
//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//Nuevas variables para medir tiempo
unsigned long duration;
long tiempoJavier = 0;
bool pausabool = false;
bool gameOver = false;
bool modoPractica = false;
long modovelocidad = false;
long contador = 0;
int nivel = 1;
long time;
//-------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------
//Método setup, inicialización de variables
void setup() {

  //***********************************INSERCION 2 DE CODIGO LETRERO*********************************************************************//
  //DEFINICION DE LOS BOTONES COMO ENTRADA EN PINES
  pinMode(btnIn1, INPUT);
  pinMode(btnIn2, INPUT);
  pinMode(btnIn3, INPUT);


  //***********************************FINALIZA INSERCION 2 ******************************************************************************//

  Serial.begin(9600);

  //Inicializando los pines de los botones como entradas
  pinMode(butPinUp, INPUT);
  pinMode(butPinDown, INPUT);
  pinMode(butPinLeft, INPUT);
  pinMode(butPinRight, INPUT);
  pinMode(ledPin, OUTPUT);
  // pulso de buttom
  pinMode(special, INPUT);//JAVIER



  //Inicialización de la matriz
  //Obtener cantidad de matrices
  //Cancelar modo ahorro
  for (int i = 0; i < 2; i++) {
    lc.shutdown(i, false);
    //Configurar brillo
    lc.setIntensity(i, 8);
    //Limpiar la matriz
    lc.clearDisplay(i);
  }

  Serial.println(">>>>>>>presione (START) por 3 seg/veces! para iniciar<<<<<<<<)");//JAVIER

  time = 0;




  //delay(delaytime); //Limpiando delays, este no parece afectar nada
}
//-------------------------------------------------------------------------------------------------------------------------------------





//-------------------------------------------------------------------------------------------------------------------------------------
//Método LOOP
void loop() {


  if (modoPractica == false && modovelocidad == false) {
    lc.clearDisplay(0);
  lc.clearDisplay(1);
    Letrero();
    BIFROST();// sin esto no se puede empesar el juego lo q hace es si start no se oprime por 3 seg o veces no inicial el juego esto mismo se hace despues del game over
    //********************************************INSERCCION CODIGO 3 TABLERO*************************************************************//

  }

  if (modoPractica == false && modovelocidad == true) { // Entrar en modod velocidad
    BIFROST();// 
  }


  //modoPractica se habilita en metodo BIFROST


  if (modoPractica == true) {


    generateFood();
    specialState = digitalRead(special);//JAVIER para el boton de START
    //Leer los estados de los botones
    butUpState = digitalRead(butPinUp);
    butDownState = digitalRead(butPinDown);
    butLeftState = digitalRead(butPinLeft);
    butRightState = digitalRead(butPinRight);

    actualizarDireccion();

    //Pintar y actualizar posición snake --> si pausa esta activa la serpiente no pinta ni se mueve
    if (pausabool == false && gameOver == false) { //<-falta condición
      //Actualizar posiciones y pintar la matriz

      actualizarPosicion();

    }

    //Generar nueva comida

  }


}
//-------------------------------------------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------------------------------------------
//Método para inicializar y generar la posición aleatoría de la cabeza de la serpiente
void generarPosicionInicial() {
  //snake.y = random(1, 8);
  snake.y = 0;
  snake.x = random(1, 8);
  snake.dir = random(1, 5);
  snake.matriz = random(1, 2);
  cola.y = snake.y;
  cola.x = snake.x;
  cola.dir = snake.dir;
  cola.matriz = snake.matriz;
  cuerpo[0][0] = snake.x;
  cuerpo[1][0] = snake.y;
  cuerpo[2][0] = snake.matriz;
}
//-------------------------------------------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------------------------------------------
//Método que actualiza la dirección de la snake
void actualizarDireccion() {
  if (butUpState == HIGH && pausabool == false && gameOver == false) {
    //Se enciende el led
    digitalWrite(ledPin, HIGH);
    snake.dir = 1;
  } else if (butDownState && pausabool == false && gameOver == false) {
    digitalWrite(ledPin, HIGH);
    snake.dir = 2;
  } else if (butLeftState && pausabool == false && gameOver == false) {
    digitalWrite(ledPin, HIGH);
    snake.dir = 3;
  } else if (butRightState && pausabool == false && gameOver == false) {
    digitalWrite(ledPin, HIGH);
    snake.dir = 4;
  } else if (specialState == HIGH) { // si START FUE PRECIONADO tengo q calcular si es pause o endgame su funcion es la de contar el n numero de seg de presion
    duration = pulseIn(special, HIGH);

    if (duration == 0) {
      tiempoJavier += 1;
      Serial.println(tiempoJavier);
      return;

    }
  } else {
    //Se mantiene apagado el led
    digitalWrite(ledPin, LOW);


    //Validación de pausa

    if (tiempoJavier == 1) { //JAVIER aqui valido el n numero de segundos q calcule anterior

      pausabool = !pausabool;//JAVIER cambio de estado automaticamente si es pausa
      pausa();//JAVIER llamo al metodo de desplique de mensaje de score o que reanima el juego
      tiempoJavier = 0; //JAVIER
      //return;//JAVIER

    } else if (tiempoJavier >= 3) { //JAVIER

      Serial.println("modo EXIT");//JAVIER  *******************MODO EXIT
      tiempoJavier = 0; //JAVIER
      showGameOverMessage();//AQUI VAN EL GAME OVER///////JAVIER
      //modoPractica = false;

      //return;//JAVIER
    }//JAVIER
    //tiempoJavier=0;
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------------------------------------------
//Método que actualiza la posición de la cabeza
void actualizarPosicion() {
  if (!snakeCrecio) {

  } else {
    snakeCrecio = false;
  }

  switch (snake.dir) {
    case 1:
      snake.y--;
      if (snake.y < 0) {
        showGameOverMessage();//AQUI VAN EL GAME OVER///////JAVIER
        return;///////JAVIER
      }
      break;
    case 2:
      snake.y++;
      if (snake.y > 7) {
        showGameOverMessage();//AQUI VAN EL GAME OVER///////JAVIER
        return;///////JAVIER
      }
      break;
    case 3:
      snake.x--;
      if (snake.x < 0 && snake.matriz == 1) {
        showGameOverMessage();//AQUI VAN EL GAME OVER///////JAVIER
        return;///////JAVIER
      } else if (snake.x < 0 && snake.matriz == 0) {
        snake.matriz = 1;
        snake.x = 7;
      } else {
        //snake.matriz = ultimaMatriz;
      }
      break;
    case 4:
      snake.x++;
      if (snake.x > 7 && snake.matriz == 1) {
        snake.x = 0;
        snake.matriz = 0;
      } else if (snake.x > 7 && snake.matriz == 0) {
        showGameOverMessage();//AQUI VAN EL GAME OVER///////JAVIER
        return;///////JAVIER
      } else {
        //snake.matriz = ultimaMatriz;
      }
      break;
  }
  if (snake.x == food.col && snake.y == food.row && snake.matriz == food.matriz) {
    snakeCrecio = true;
  }
  //Fila 1 para X y fila 2 para Y, fila 3 para matriz
  //Recuperar las posiciones de la cola
  cola.x = cuerpo[0][longitud];
  cola.y = cuerpo[1][longitud];
  cola.matriz = cuerpo[2][longitud];

  for (byte j = longitud; j > 0; j--) {
    cuerpo[0][j] = cuerpo[0][j - 1];
    cuerpo[1][j] = cuerpo[1][j - 1];
    cuerpo[2][j] = cuerpo[2][j - 1];
  }
  //Actualizar cabeza
  cuerpo[0][0] = snake.x;
  cuerpo[1][0] = snake.y;
  cuerpo[2][0] = snake.matriz;
  mover();
}
//-------------------------------------------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------------------------------------------
// Método que repinta la matriz con las nuevas posiciones
void mover() {
  lc.setLed(snake.matriz, snake.y, snake.x, true);

  //Verificar si la snake se come a sí misma

  for (byte i = longitud; i > 0; i--) {
    if (snake.x == cuerpo[0][i] && snake.y == cuerpo[1][i] && snake.matriz == cuerpo[2][i]) {
      showGameOverMessage();
      return;
    }
  }

  lc.setLed(cola.matriz, cola.y, cola.x, false);
  if (longitud > 0) {
    pintarCuerpo();
  }

  //Recuperar las posiciones de la cola
  cola.x = cuerpo[0][longitud];
  cola.y = cuerpo[1][longitud];
  cola.matriz = cuerpo[2][longitud];

  delay(delaytime);
}
//-------------------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------------------
//Método que actualiza y pinta las partes de la snake
void pintarCuerpo() {
  for (byte i = longitud; i > 0; i--) {
    lc.setLed(cuerpo[2][i], cuerpo[1][i], cuerpo[0][i], true);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------------------
//Método para ocultar snake
void ocultarSnake() {
  for (byte i = longitud; i > -1; i--) {
    lc.setLed(cuerpo[2][i], cuerpo[1][i], cuerpo[0][i], false);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------------------
//Método para la generación de la comida y para evaluar si la snake comió
void generateFood() {
  //P.displayReset();

  bool posicionCorrecta = false;
  //delay(50);<-------------------------------Probando sin este delay
  if (gameOver == false && pausabool == false) {
    lc.setLed(food.matriz, food.row, food.col, true);
  } else {

    return;
  }

  // ver si cuadran la posicion de la serpiente con la de la comida (por ahora)
  if (food.row == -1 || food.col == -1 || food.matriz == -1) {


    //Crear comida aleatoria y verificar que la posición sea correcta
    while (!posicionCorrecta) {
      food.col = random(1, 7); //asigno col a comida
      food.row = random(8);//asigno fila a comida
      food.matriz = random(2);//asigno matrz a comida

      for (byte i = longitud; i > -1; i--) {
        if (food.col == cuerpo[0][i] && food.row == cuerpo[1][i] && food.matriz == cuerpo[2][i]) {
          posicionCorrecta = false;
        } else {
          posicionCorrecta = true;
          break;
        }
      }
    }

    lc.setLed(food.matriz, food.row, food.col, true);

    Serial.print("ComidaRow:");
    Serial.print(food.row);
    Serial.println("");
    Serial.print("ComidaCol:");
    Serial.print(food.col);
    Serial.println("");
    Serial.print("ComidaMatriz:");
    Serial.print(food.matriz);
    Serial.println("");
    Serial.println("------------------------");

    //AQUI PUEDE IR EL +1 AL PUNTEO


  } else if (snake.x == food.col && snake.y == food.row && snake.matriz == food.matriz) { //si la cabeza se come la comida
    //Actualización de la snake
    ultimaX = cola.x;
    ultimaY = cola.y;
    ultimaMat = cola.matriz;
    cola.x = food.col;
    cola.y = food.row;
    cola.matriz = food.matriz;
    longitud++;
    cuerpo[0][longitud] = cola.x;
    cuerpo[1][longitud] = cola.y;
    cuerpo[2][longitud] = cola.matriz;
    //snakeCrecio = true;
    //Actualización de comida
    food.col = -1;
    food.row = -1;
    delaytime = delaytime - 20; //COMO COMIO LE AUMENTO LA VELOCIDAD
    Serial.print(">>>velocidad:");
    Serial.print(delaytime);
    puntos += 1;
    Serial.print(">>>puntos:");
    Serial.print(puntos);
    Serial.println();

  }
}
//-------------------------------------------------------------------------------------------------------------------------------------





const PROGMEM bool gameOverMessage[8][90] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const PROGMEM bool scoreMessage[8][58] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};



const PROGMEM bool digits[][8][8] = {
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
  }
};

//Mensaje 
const PROGMEM bool Message[8][184] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,1,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0},
{0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0},
{0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0},
{0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0},
{0,0,0,1,0,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,0,0,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0}
};

void showGameOverMessage() {
  [&] {
    int numMat = 1; //****

    gameOver = true;

    for (int d = 0; d < sizeof(gameOverMessage[0]) - 7; d++) {

      for (int col = 0; col < 8; col++) {
        numMat = col < 8 ? 1 : 0; //****
        delay(messageSpeed);
        for (int row = 0; row < 8; row++) {

          // this reads the byte from the PROGMEM and displays it on the screen
          lc.setLed(0, row, col, pgm_read_byte(&(gameOverMessage[row][col + d]))); //****
          lc.setLed(1, row, col, pgm_read_byte(&(gameOverMessage[row][col - 7 + d]))); //****

        }
      }

    }
    showScoreMessage(puntos);//AQUI MUESTRO EL SCORE LUEGO Q SE DESPLEGUE GAME OVER
    //reset de puntos
    puntos = 0;
  }();

  lc.setLed(food.matriz, food.row, food.col, false); // RECORDAR CUANDO SE RESETEE LA PARTIDA SE DEBE DE INICIALUZAR NUEVAMENTE LA COMIDA
  Serial.println(">>>>>>>presione START por 3 seg/veces! para iniciar el juego<<<<<<<<)");//JAVIER
  lc.clearDisplay(0);
  lc.clearDisplay(1);


  modoPractica = false;
  //Serial.println(">>>>>>><<<<<<<<)");//JAVIER
  //Letrero();//EDIN
  BIFROST();
  return;

}


// scrolls the 'score' message with numbers around the matrix
void showScoreMessage(int score) {

  /* specialState = digitalRead(special);//JAVIER para el boton de START para saber cuando se esta pulsando

    if (specialState == HIGH) {
     modoPractica = false;
     return;
     }
  */


  //**************************************************8
  if (score < 0 || score > 99) return;

  // specify score digits
  int second = score % 10;
  int first = (score / 10) % 10;

  [&] {
    for (int d = 0; d < sizeof(scoreMessage[0]) + 2 * sizeof(digits[0][0]); d++) {

      for (int col = 0; col < 8; col++) {

        delay(messageSpeed);



        for (int row = 0; row < 8; row++) {

          if (d <= sizeof(scoreMessage[0]) - 8) {
            lc.setLed(0, row, col, pgm_read_byte(&(scoreMessage[row][col + d])));
            lc.setLed(1, row, col, pgm_read_byte(&(scoreMessage[row][col - 7 + d]))); //****
          }

          int c = col + d - sizeof(scoreMessage[0]) + 6; // move 6 px in front of the previous message

          // if the score is < 10, shift out the first digit (zero)
          if (score < 10) c += 8;

          if (c >= 0 && c < 8) {
            if (first > 0) {
              lc.setLed(0, row, col, pgm_read_byte(&(digits[first][row][c])));
              // lc.setLed(0, row, col, pgm_read_byte(&(digits[first][row][c]))); //****

            }// show only if score is >= 10 (see above)
          } else {
            c -= 8;
            if (c >= 0 && c < 8) {
              lc.setLed(0, row, col, pgm_read_byte(&(digits[second][row][c]))); // show always
              //lc.setLed(0, row, col, pgm_read_byte(&(digits[second][row][c]))); //****

            }
          }
        }
      }

    }
  }();

  lc.clearDisplay(0);
  lc.clearDisplay(1);


}

//Mostrar mensaje del nivel
void showLevelMessage() {

  lc.clearDisplay(0);
  lc.clearDisplay(1);
  showzero();

  if(nivel == 1){
  showone();
  }else if(nivel == 2){
  showtwo();
  }
  else if(nivel == 3){
  showthree();
  }
  else if(nivel == 4){
  showfour();
  }




}

void showzero(){
   byte C[8] = {B00000000,
               B00111100,
               B01100110,
               B01101110,
               B01110110,
               B01100110,
               B01100110,
               B00111100
              };

  lc.setRow(0, 0, C[0]);
  lc.setRow(1, 1, C[1]);
  lc.setRow(1, 2, C[2]);
  lc.setRow(1, 3, C[3]);
  lc.setRow(1, 4, C[4]);
  lc.setRow(1, 5, C[5]);
  lc.setRow(1, 6, C[6]);
  lc.setRow(1, 7, C[7]);
  delay(v_estatico);
}

void showone(){
   byte C[8] = {B00000000,
               B00011000,
               B00011000,
               B00111000,
               B00011000,
               B00011000,
               B00011000,
               B01111110
              };

  lc.setRow(0, 0, C[0]);
  lc.setRow(0, 1, C[1]);
  lc.setRow(0, 2, C[2]);
  lc.setRow(0, 3, C[3]);
  lc.setRow(0, 4, C[4]);
  lc.setRow(0, 5, C[5]);
  lc.setRow(0, 6, C[6]);
  lc.setRow(0, 7, C[7]);
  delay(v_estatico);
}
void showtwo(){
   byte C[8] = {B00000000,
               B00111100,
               B01100110,
               B00000110,
               B00001100,
               B00110000,
               B01100000,
               B01111110
              };

  lc.setRow(0, 0, C[0]);
  lc.setRow(0, 1, C[1]);
  lc.setRow(0, 2, C[2]);
  lc.setRow(0, 3, C[3]);
  lc.setRow(0, 4, C[4]);
  lc.setRow(0, 5, C[5]);
  lc.setRow(0, 6, C[6]);
  lc.setRow(0, 7, C[7]);
  delay(v_estatico);
}
void showthree(){
   byte C[8] = {B00000000,
               B00111100,
               B01100110,
               B00000110,
               B00011100,
               B00000110,
               B01100110,
               B00111100
              };

  lc.setRow(0, 0, C[0]);
  lc.setRow(0, 1, C[1]);
  lc.setRow(0, 2, C[2]);
  lc.setRow(0, 3, C[3]);
  lc.setRow(0, 4, C[4]);
  lc.setRow(0, 5, C[5]);
  lc.setRow(0, 6, C[6]);
  lc.setRow(0, 7, C[7]);
  delay(v_estatico);
}
void showfour(){
   byte C[8] = {B00000000,
               B00001100,
               B00011100,
               B00101100,
               B01001100,
               B01111110,
               B00001100,
               B00001100
              };

  lc.setRow(0, 0, C[0]);
  lc.setRow(0, 1, C[1]);
  lc.setRow(0, 2, C[2]);
  lc.setRow(0, 3, C[3]);
  lc.setRow(0, 4, C[4]);
  lc.setRow(0, 5, C[5]);
  lc.setRow(0, 6, C[6]);
  lc.setRow(0, 7, C[7]);
  delay(v_estatico);
}

//***********************************************************************

//METODO PARA PAUSA NECESITA DE UN BOOL LLAMADO pausabool si es true entra en pausa y apago la comida como la cabeza he imprimo el score actual.// si pausabool es false reactivo la comida como el led de la cabeza de la snake
void pausa() {

  if (pausabool == true) {
    Serial.println("modo PAUSA ON");//JAVIER  *******************MODO PAUSA on
    lc.setLed(food.matriz, food.row, food.col, false); //PARA QUE NO SE MIRE LA COMIDA
    //lc.setLed(numMatriz, snakePosY, snakePosX, false); //PARA Q NO SE MIRE LA SNAKE
    //ocultarSnake();//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    showScoreMessage(puntos);//AQUI MUESTRO EL SCORE LUEGO Q entre en modo pausa

  } else {
    //CUANDO SE QUITE EL MODO PAUSA SE TIENE Q VER DE NUEVO LA COMIDA Y LA SERPIENTE
    Serial.println("modo PAUSA OFF");//JAVIER  *******************MODO PAUSA off
    lc.setLed(food.matriz, food.row, food.col, true); //PARA QUE SE MIRE LA COMIDA
    //lc.setLed(snake.matriz, snake.y, snake.x, true); //PARA Q SE MIRE LA SNAKE
    mover();
  }

}

void BIFROST() {

  specialState = digitalRead(special);//JAVIER para el boton de START para saber cuando se esta pulsando
  butUpState = digitalRead(butPinUp);
  butDownState = digitalRead(butPinDown);

  if (specialState == HIGH && modovelocidad == false ) { //JAVIER si START FUE PRECIONADO su funcion es la de contar el n numero de seg de presion
    duration = pulseIn(special, HIGH); //JAVIER

    if (duration == 0) { //JAVIER
      tiempoJavier += 1; //JAVIER
      Serial.println(tiempoJavier);//JAVIER
    }//JAVIER

    if (tiempoJavier >= 3) { //JAVIER
      Serial.println("iniciando juego SNAKE.....");//JAVIER  *******************MODO INICIAL
      Serial.println(">>>>>>>presione (START) por 3 seg/veces! para seleccionar la velocidad<<<<<<<<)");
      tiempoJavier = 0; //JAVIER

      velocidadsnake();

    }
  }
    //Cuando estamos en el menu de velocidades 
    else if (specialState == HIGH && modovelocidad == true ) { //JAVIER si START FUE PRECIONADO su funcion es la de contar el n numero de seg de presion
    duration = pulseIn(special, HIGH); //JAVIER

    if (duration == 0) { //JAVIER
      tiempoJavier += 1; //JAVIER
      Serial.println(tiempoJavier);//JAVIER
    }//JAVIER

    if (tiempoJavier >= 3) { //JAVIER
      Serial.println("Velocidad seleccionada");//JAVIER  *******************MODO INICIAL
      tiempoJavier = 0; //JAVIER

      lc.clearDisplay(0);
      lc.clearDisplay(1);

      startgame(); //Iniciar a jugar
    }}

    //controles de la velocidad
    else if (butUpState == HIGH && modovelocidad == true) {

     duration = pulseIn(butPinUp, HIGH); 

    if (duration == 0) {
      contador += 1; 
      //Serial.println(contador);
    }

    if (contador == 1) {
      //Serial.println("SUBIR VELOCIDAD");
      contador = 0;
      
      if (nivel <= 3){
        nivel = nivel + 1;
      }
      
      Serial.println("Nivel:");
      Serial.println(nivel);

    }

    
    }
    else if (butDownState == HIGH && modovelocidad == true) {

       duration = pulseIn(butPinDown, HIGH); 

    if (duration == 0) {
      contador += 1; 
      //Serial.println(contador);
    }

    if (contador == 1) {
      //Serial.println("BAJAR VELOCIDAD");
      contador = 0;

       if (nivel >= 2){
        nivel = nivel - 1;
      }
      
      Serial.println("Nivel:");
      Serial.println(nivel);

    }
 
  }
  //Mostrar nivles del juego
  if(modovelocidad == true){
    showLevelMessage();
    
  }
}


void seAutoDestruye() {
  

}

//Velocidades Snake
void velocidadsnake(){

  tiempoJavier=0;

  nivel = 1;

  delaytime = 0;
  
  modovelocidad = true;

  Serial.println("Seleccionar velocidad");


    
  }

//iniciar a jugar
 void startgame(){

      modovelocidad = false;
      //velocidades de la serpiente
      if(nivel == 1){
        delaytime = 700;
      }else if(nivel == 2){
        delaytime = 550;
      }else if(nivel == 3){
        delaytime = 400;
      }else if(nivel == 4){
        delaytime = 250;
      }

    //restablesco todas las variables nuevamente
      food.col = -1;
      food.row = -1;
      puntos = 0;
      //snake.x = 0;
      //snake.y = 0;
      //snake.matriz = 1;
      specialState = 0; //JAVIER
      duration = 0; //JAVIER
      tiempoJavier = 0; //JAVIER
      pausabool = false; //JAVIER
      gameOver = false; //Javier

      //Reiniciando cuerpo de la serpiente
      for (int i = longitud; i > -1; i--) {
        cuerpo[0][i] = 0;
        cuerpo[1][i] = 0;
        cuerpo[2][i] = 0;
      }
      //Generando nueva snake
      longitud = 0;
      generarPosicionInicial();

      //hacer ver a la serpiente inicialmente

      lc.setLed(snake.matriz, snake.y, snake.x, true); // posicion inicial de snake JOEL

      //paso de modo de mensaje a modo del juego habilitando el bool
      modoPractica = true;

      Serial.print("Nivel selecciondao: ");
      Serial.println(nivel);
      Serial.print("Velocidad ");
      Serial.println(delaytime);
    
  }



//***********************************************************METODOS TABLERO***********************************************************************//

void Velocidad() {
  if (digitalRead(btnIn3) == HIGH) {

    v_estatico = 200;
    vel_scroll = 0;
  }
  else {

    v_estatico = 500;
    vel_scroll = 10;
  }
}


void Letrero() {
  int btnIn1State = digitalRead(btnIn1);
  int btnIn2State = digitalRead(btnIn2);
  int btnIn3State = digitalRead(btnIn3);
  Velocidad();

  if (btnIn1State == LOW)   //SI BTN ES 0 MENSAJE CON MOVIMIENTO
  {

    if (btnIn2State == HIGH)//si esta en 1 bt2 derecha a izquierda
    {
      mensajeScroll(1);
    }
    else // IRA DE IZQUIERDA A DERECHA
    {
      mensajeScroll(0);
    }
  }
  else { //DE LO CONTRARIO ES MENSAJE SIN MOVIMIENTO
    mensajeEstatico();
  }
 
}

void mensajeScroll(int estado) {

  //se lee el estado de los botones
  int btnIn1State = digitalRead(btnIn1);
  int btnIn2State = digitalRead(btnIn2);
  int btnIn3State = digitalRead(btnIn3);

  if (estado == 1) {   //*********************************************MOVIMIENTO DE DERECHA A IZQUIERDA***********************************************************
    [&] {

      for (int d = 0; d < sizeof(Message[0]) - 7; d++) { //***AQUI SE INSTANCIA EL MENSAJE DE TP1-GRUPO12-SECCION EN VEZ DEL DE GAME OVER A Y YA QUEDO

        for (int col = 0; col < 8; col++) {
          delay(vel_scroll);
          while (digitalRead(specialState) == 1) {

            duration = pulseIn(special, HIGH);

            if (duration == 0) {
              tiempoJavier += 1;
              Serial.println(tiempoJavier);
              return;

            }

            if (tiempoJavier >= 3) { //JAVIER

              Serial.println("FFFF");//JAVIER  *******************MODO EXIT
              tiempoJavier = 0; //JAVIER
              modoPractica = false;
              return;
            }//JAVIER


          }
          for (int row = 0; row < 8; row++) {

            // this reads the byte from the PROGMEM and displays it on the screen
            lc.setLed(0, row, col, pgm_read_byte(&(Message[row][col + d]))); //****
            lc.setLed(1, row, col, pgm_read_byte(&(Message[row][col - 7 + d]))); //****

          }
        }

      }
    }();
  }
  else {    //*********************************************MOVIMIENTO DE IZQUIERDA A DERECHA***********************************************************
    [&] {
      for (int d = 0; d < sizeof(Message[0]) - 7; d++) { //aca se obtiene columna por columna por ejemplo si fuera la letra l se obtiene como tal la columna de su primer punto de bits
        for (int col = 0; col < 8; col++) {
          delay(vel_scroll);
          while (digitalRead(specialState) == 1) {

            duration = pulseIn(special, HIGH);

            if (duration == 0) {
              tiempoJavier += 1;
              Serial.println(tiempoJavier);
              return;

            }

            if (tiempoJavier >= 3) { //JAVIER

              Serial.println("FFFF");//JAVIER  *******************MODO EXIT
              tiempoJavier = 0; //JAVIER
              modoPractica = false;
              return;
            }//JAVIER


          }
          for (int row = 0; row < 8; row++) {
            // this reads the byte from the PROGMEM and displays it on the screen
            lc.setLed(0, row, col, pgm_read_byte(&(Message[row + 1][col + 2 - d])));
            lc.setLed(1, row, col, pgm_read_byte(&(Message[row + 1][col - 7 - d]))); //****
          }
        }
      }
    }();
  }
}


void mensajeEstatico() {
  Escuchar();
  byte AST[8] = {B00000000,
                 B10010010,
                 B01010100,
                 B00111000,
                 B11111110,
                 B00111000,
                 B01010100,
                 B10010010
                };

  byte T[8] = {B00000000,
               B01111110,
               B00011000,
               B00011000,
               B00011000,
               B00011000,
               B00011000,
               B00011000
              }       ;


  byte UNO[8] = {B00000000,
                 B00001100,
                 B00010100,
                 B00100100,
                 B00000100,
                 B00000100,
                 B00000100,
                 B00000100
                }      ;

  byte guion[8] = {B00000000,
                   B00000000,
                   B00000000,
                   B00000000,
                   B01111110,
                   B00000000,
                   B00000000,
                   B00000000
                  };


  byte G[8] = {B00000000,
               B01111110,
               B01000000,
               B01000000,
               B01011110,
               B01000010,
               B01000010,
               B01111010
              };

  byte R[8] = {B00000000,
               B01111000,
               B01000100,
               B01000100,
               B01111000,
               B01001000,
               B01000100,
               B01000010
              };

  byte U[8] = {B00000000,
               B01000010,
               B01000010,
               B01000010,
               B01000010,
               B01000010,
               B01000010,
               B00111100
              };

  byte P[8] = {B00000000,
               B01111000,
               B01000100,
               B01000100,
               B01111100,
               B01000000,
               B01000000,
               B01000000
              };

  byte O[8] = {B00000000,
               B00111000,
               B01000100,
               B01000100,
               B01000100,
               B01000100,
               B01000100,
               B00111000
              };

  byte dos[8] = {B00000000,
                 B00111000,
                 B01000100,
                 B00001000,
                 B00010000,
                 B00100000,
                 B01000000,
                 B01111100
                };

  byte S[8] = {B00000000,
               B00111000,
               B01000100,
               B01000000,
               B01111000,
               B00000100,
               B01000100,
               B00111000
              };

  byte E[8] = {B00000000,
               B01111100,
               B01000000,
               B01000000,
               B01111000,
               B01000000,
               B01000000,
               B01111100
              };

  byte C[8] = {B00000000,
               B00111000,
               B01000100,
               B01000000,
               B01000000,
               B01000000,
               B01000100,
               B00111000
              };

  byte I[8] = {B00000000,
               B01111100,
               B00010000,
               B00010000,
               B00010000,
               B00010000,
               B00010000,
               B01111100
              };

  byte N[8] = {B00000000,
               B01000010,
               B01100000,
               B01010010,
               B01001010,
               B01000110,
               B01000010,
               B01000010
              };

  byte A[8] = {B00000000,
               B00011000,
               B00100100,
               B01000010,
               B01111110,
               B01000010,
               B01000010,
               B01000010
              };

  Escuchar();
  lc.setRow(0, 0, AST[0]);
  lc.setRow(1, 1, AST[1]);
  lc.setRow(1, 2, AST[2]);
  lc.setRow(1, 3, AST[3]);
  lc.setRow(1, 4, AST[4]);
  lc.setRow(1, 5, AST[5]);
  lc.setRow(1, 6, AST[6]);
  lc.setRow(1, 7, AST[7]);
  delay(v_estatico);
  lc.setRow(0, 0, T[0]);
  lc.setRow(1, 1, T[1]);
  lc.setRow(1, 2, T[2]);
  lc.setRow(1, 3, T[3]);
  lc.setRow(1, 4, T[4]);
  lc.setRow(1, 5, T[5]);
  lc.setRow(1, 6, T[6]);
  lc.setRow(1, 7, T[7]);
  delay(v_estatico);
  Escuchar();
  lc.setRow(0, 0, P[0]);
  lc.setRow(1, 1, P[1]);
  lc.setRow(1, 2, P[2]);
  lc.setRow(1, 3, P[3]);
  lc.setRow(1, 4, P[4]);
  lc.setRow(1, 5, P[5]);
  lc.setRow(1, 6, P[6]);
  lc.setRow(1, 7, P[7]);
  delay(v_estatico);
  Escuchar();
  lc.setRow(0, 0, UNO[0]);
  lc.setRow(1, 1, UNO[1]);
  lc.setRow(1, 2, UNO[2]);
  lc.setRow(1, 3, UNO[3]);
  lc.setRow(1, 4, UNO[4]);
  lc.setRow(1, 5, UNO[5]);
  lc.setRow(1, 6, UNO[6]);
  lc.setRow(1, 7, UNO[7]);
  delay(v_estatico);
  Escuchar();
  lc.setRow(0, 0, guion[0]);
  lc.setRow(1, 1, guion[1]);
  lc.setRow(1, 2, guion[2]);
  lc.setRow(1, 3, guion[3]);
  lc.setRow(1, 4, guion[4]);
  lc.setRow(1, 5, guion[5]);
  lc.setRow(1, 6, guion[6]);
  lc.setRow(1, 7, guion[7]);
  delay(v_estatico);
  Escuchar();
  lc.setRow(0, 0, G[0]);
  lc.setRow(1, 1, G[1]);
  lc.setRow(1, 2, G[2]);
  lc.setRow(1, 3, G[3]);
  lc.setRow(1, 4, G[4]);
  lc.setRow(1, 5, G[5]);
  lc.setRow(1, 6, G[6]);
  lc.setRow(1, 7, G[7]);
  delay(v_estatico);
  Escuchar();
  lc.setRow(0, 0, R[0]);
  lc.setRow(1, 1, R[1]);
  lc.setRow(1, 2, R[2]);
  lc.setRow(1, 3, R[3]);
  lc.setRow(1, 4, R[4]);
  lc.setRow(1, 5, R[5]);
  lc.setRow(1, 6, R[6]);
  lc.setRow(1, 7, R[7]);
  delay(v_estatico);
  Escuchar();
  lc.setRow(0, 0, U[0]);
  lc.setRow(1, 1, U[1]);
  lc.setRow(1, 2, U[2]);
  lc.setRow(1, 3, U[3]);
  lc.setRow(1, 4, U[4]);
  lc.setRow(1, 5, U[5]);
  lc.setRow(1, 6, U[6]);
  lc.setRow(1, 7, U[7]);
  delay(v_estatico);
  Escuchar();
  lc.setRow(0, 0, P[0]);
  lc.setRow(1, 1, P[1]);
  lc.setRow(1, 2, P[2]);
  lc.setRow(1, 3, P[3]);
  lc.setRow(1, 4, P[4]);
  lc.setRow(1, 5, P[5]);
  lc.setRow(1, 6, P[6]);
  lc.setRow(1, 7, P[7]);
  delay(v_estatico);
  Escuchar();
  lc.setRow(0, 0, O[0]);
  lc.setRow(1, 1, O[1]);
  lc.setRow(1, 2, O[2]);
  lc.setRow(1, 3, O[3]);
  lc.setRow(1, 4, O[4]);
  lc.setRow(1, 5, O[5]);
  lc.setRow(1, 6, O[6]);
  lc.setRow(1, 7, O[7]);
  delay(v_estatico);
  Escuchar();
  lc.setRow(0, 0, UNO[0]);
  lc.setRow(1, 1, UNO[1]);
  lc.setRow(1, 2, UNO[2]);
  lc.setRow(1, 3, UNO[3]);
  lc.setRow(1, 4, UNO[4]);
  lc.setRow(1, 5, UNO[5]);
  lc.setRow(1, 6, UNO[6]);
  lc.setRow(1, 7, UNO[7]);
  delay(v_estatico);
  lc.setRow(0, 0, dos[0]);
  lc.setRow(1, 1, dos[1]);
  lc.setRow(1, 2, dos[2]);
  lc.setRow(1, 3, dos[3]);
  lc.setRow(1, 4, dos[4]);
  lc.setRow(1, 5, dos[5]);
  lc.setRow(1, 6, dos[6]);
  lc.setRow(1, 7, dos[7]);
  delay(v_estatico);
  lc.setRow(0, 0, guion[0]);
  lc.setRow(1, 1, guion[1]);
  lc.setRow(1, 2, guion[2]);
  lc.setRow(1, 3, guion[3]);
  lc.setRow(1, 4, guion[4]);
  lc.setRow(1, 5, guion[5]);
  lc.setRow(1, 6, guion[6]);
  lc.setRow(1, 7, guion[7]);
  delay(v_estatico);
  lc.setRow(0, 0, S[0]);
  lc.setRow(1, 1, S[1]);
  lc.setRow(1, 2, S[2]);
  lc.setRow(1, 3, S[3]);
  lc.setRow(1, 4, S[4]);
  lc.setRow(1, 5, S[5]);
  lc.setRow(1, 6, S[6]);
  lc.setRow(1, 7, S[7]);
  delay(v_estatico);
  lc.setRow(0, 0, E[0]);
  lc.setRow(1, 1, E[1]);
  lc.setRow(1, 2, E[2]);
  lc.setRow(1, 3, E[3]);
  lc.setRow(1, 4, E[4]);
  lc.setRow(1, 5, E[5]);
  lc.setRow(1, 6, E[6]);
  lc.setRow(1, 7, E[7]);
  delay(v_estatico);
  lc.setRow(0, 0, C[0]);
  lc.setRow(1, 1, C[1]);
  lc.setRow(1, 2, C[2]);
  lc.setRow(1, 3, C[3]);
  lc.setRow(1, 4, C[4]);
  lc.setRow(1, 5, C[5]);
  lc.setRow(1, 6, C[6]);
  lc.setRow(1, 7, C[7]);
  delay(v_estatico);
  lc.setRow(0, 0, C[0]);
  lc.setRow(1, 1, C[1]);
  lc.setRow(1, 2, C[2]);
  lc.setRow(1, 3, C[3]);
  lc.setRow(1, 4, C[4]);
  lc.setRow(1, 5, C[5]);
  lc.setRow(1, 6, C[6]);
  lc.setRow(1, 7, C[7]);
  delay(v_estatico);
  lc.setRow(0, 0, I[0]);
  lc.setRow(1, 1, I[1]);
  lc.setRow(1, 2, I[2]);
  lc.setRow(1, 3, I[3]);
  lc.setRow(1, 4, I[4]);
  lc.setRow(1, 5, I[5]);
  lc.setRow(1, 6, I[6]);
  lc.setRow(1, 7, I[7]);
  delay(v_estatico);
  lc.setRow(0, 0, O[0]);
  lc.setRow(1, 1, O[1]);
  lc.setRow(1, 2, O[2]);
  lc.setRow(1, 3, O[3]);
  lc.setRow(1, 4, O[4]);
  lc.setRow(1, 5, O[5]);
  lc.setRow(1, 6, O[6]);
  lc.setRow(1, 7, O[7]);
  delay(v_estatico);
  lc.setRow(0, 0, N[0]);
  lc.setRow(1, 1, N[1]);
  lc.setRow(1, 2, N[2]);
  lc.setRow(1, 3, N[3]);
  lc.setRow(1, 4, N[4]);
  lc.setRow(1, 5, N[5]);
  lc.setRow(1, 6, N[6]);
  lc.setRow(1, 7, N[7]);
  delay(v_estatico);
  lc.setRow(0, 0, A[0]);
  lc.setRow(1, 1, A[1]);
  lc.setRow(1, 2, A[2]);
  lc.setRow(1, 3, A[3]);
  lc.setRow(1, 4, A[4]);
  lc.setRow(1, 5, A[5]);
  lc.setRow(1, 6, A[6]);
  lc.setRow(1, 7, A[7]);
  delay(v_estatico);
  lc.setRow(0, 0, AST[0]);
  lc.setRow(1, 1, AST[1]);
  lc.setRow(1, 2, AST[2]);
  lc.setRow(1, 3, AST[3]);
  lc.setRow(1, 4, AST[4]);
  lc.setRow(1, 5, AST[5]);
  lc.setRow(1, 6, AST[6]);
  lc.setRow(1, 7, AST[7]);
  delay(v_estatico);
Escuchar();
}

void Escuchar() {
  while (digitalRead(specialState) == 1) {

    duration = pulseIn(special, HIGH);

    if (duration == 0) {
      tiempoJavier += 1;
      Serial.println(tiempoJavier);
      return;

    }

    if (tiempoJavier >= 3) { //JAVIER

      Serial.println("FFFF");//JAVIER  *******************MODO EXIT
      tiempoJavier = 0; //JAVIER
      modoPractica = false;
      return;
    }//JAVIER


  }
}


//******************************************************************************************FIN METODOS TABLERO*********************************************************************//
