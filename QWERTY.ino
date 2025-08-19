

/*
 * Mandar a llamar las siguientes instancias:
drawQWERTY();   // escribir cada uno de los caracteres en la posicion correcta
touchQWERTY(); //mandar a llamar revision de touch de teclas
printQWERTY(); //dibujar recuadro amarillo donde se escribe
 */



// ======================= Passwords válidos ==============================
// Lista de contraseñas válidas para ingresar a otras funciones
const char* passwords[] = {"1234", "password", "qwerty", "manual"};
const int   numPasswords = 4;


 // caracteres del teclado QWERTY
char stLast[17]=""; //cantidad maxima de caracteres que caben en la pantalla para hacer backscrolling
int pos_conect = 0; //posicion del cursor para config por qwerty
int bloq_mayus = 0; //mayusculas = 0, minusculas = 1;


//  Buffer de entrada 
#define MAX_INPUT 51  //tamano maximo de array de caracteres a almacenar
char stCurrent[MAX_INPUT + 1] = "";
int  stCurrentLen = 0;


//  Entrada de caracteres 
void updateStr(char val) {
  if (stCurrentLen < MAX_INPUT) {
    stCurrent[stCurrentLen] = val;
    stCurrent[++stCurrentLen] = '\0';
    mostrarTexto();  // muestra lo que se va escribiendo
  }
}

// Backspace eficiente 
void backspaceStr() {
  if (stCurrentLen > 0) {
    stCurrent[--stCurrentLen] = '\0';
    mostrarTexto();
  }
}

//  Mostrar texto en pantalla 
void mostrarTexto() {
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  // limpiar área
  tft.fillRect(1, 83, 240, 16, TFT_BLACK);

  // Calculamos el ancho aproximado de cada carácter
  int charWidth = 12; // depende de la fuente y tamaño
  int maxChars = 240 / charWidth;

  // Si excede el ancho de la pantalla, mostramos la parte final
  if (stCurrentLen > maxChars) {
    tft.drawString(&stCurrent[stCurrentLen - maxChars], 1, 83, 1);
  } else {
    tft.drawString(stCurrent, 1, 83, 1);
  }
}

// Enter y/o comparación de passwords
void checkPassword() {
  for (int i = 0; i < numPasswords; i++) {
    if (strcmp(stCurrent, passwords[i]) == 0) {
      passwordCorrecto();
      //clearInput();   // opcional: limpiar campo después de correcto
      return;
    }
  }
  passwordIncorrecto();
  clearInput(); // opcional: limpiar campo después de password incorrecto
}

void passwordCorrecto() {
  tft.fillRect(1, 110, 240, 16, TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Password correcto", 1, 110, 1);
  delay(1000);
  tft.fillRect(1, 110, 240, 16, TFT_BLACK);
  //a partir de aqui, mandar a lamar la funcion requerida.

   for (int i = 0; i < numPasswords; i++) {
    if (strcmp(stCurrent, passwords[i]) == 0) {
      ejecutarAccion(i);   // ejecutar según índice
      clearInput();   // opcional: limpiar campo después de correcto
      return;
    }
  }
}

void passwordIncorrecto() {
  tft.fillRect(1, 110, 240, 16, TFT_BLACK);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Password incorrecto", 1, 110, 1);
  delay(1000);
  tft.fillRect(1, 110, 240, 16, TFT_BLACK);
}

//  Limpiar campo (todos los caracteres del array)
void clearInput() {
  stCurrent[0] = '\0';
  stCurrentLen = 0;
  mostrarTexto();
}



void ejecutarAccion(int idx) {  //ejecutar la accion requerida segun el password ingresado
  switch (idx) {
    case 0:
      numeros();
      break;
    case 1:
      seguridad();
      break;
    case 2:
      teclado();
      break;
    case 3:
      modoManual();
      break;
    default:
      // para futuros passwords
      break;
  }
}



//  Funciones ejemplo
void numeros() {
  tft.fillRect(1, 110, 240, 16, TFT_BLACK);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("Funcion: NUMEROS", 1, 110, 1);
}

void seguridad() {
  tft.fillRect(1, 110, 240, 16, TFT_BLACK);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("Funcion: SEGURIDAD", 1, 110, 1);
}

void teclado() {
  tft.fillRect(1, 110, 240, 16, TFT_BLACK);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("Funcion: TECLADO", 1, 110, 1);
}

void modoManual() {
  tft.fillRect(1, 110, 240, 16, TFT_BLACK);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("Funcion: MANUAL", 1, 110, 1);
}





void printQWERTY(){

 tft.setTextFont(0);
  //tft.setTextDatum(TC_DATUM);
  tft.setTextSize(2);

  if ((pos_conect == 0 ) || (pos_conect == 2)) {
    tft.drawString(stCurrent, 1, 83); // posicion del texto escrito en el teclado
    tft.drawRoundRect(0, 79, 239, 22, 3, tft.color565(255, 255, 0)); // contorno
  }

  if ((pos_conect == 1 ) || (pos_conect == 3)) {
    tft.drawString(stCurrent, 1, 123); // posicion del texto escrito en el teclado
    tft.drawRoundRect(0, 119, 239, 22, 3, tft.color565(255, 255, 0)); // contorno
  }


} // fin de printQWERTY(){



void copyStrings(){


    switch (pos_conect) {

     case 0:  // 

     break;

     case 1:  //

     break;

     case 2:  //
     
     break;

     case 3:  //
     
     break;

    } // fin de switch case


} //fin de vois copystrings










// VERSION NUEVA Y MAS COMPACTA de void drawQWERTY() PARA ESCRIBIR LOS CARACTERES DEL TECLADO
   //(version vieja y entendible de este void al final de esta pestana)
// Definir estructura para cada tecla
struct Tecla {
  int x, y, w, h;     // posición y tamaño
  const char* chars[3]; // [0]=mayúscula, [1]=minúscula, [2]=símbolo
  int cursorX, cursorY;
};

// mapa del teclado, definir todas las teclas normales del teclado QWERTY por arreglos matriciales
Tecla teclas[] = {
  //  FILA NÚMEROS 
  {3,160,20,25, {"1","1","1"},   9,166},
  {25,160,20,25,{"2","2","2"},  31,166},
  {50,160,20,25,{"3","3","3"},  56,166},
  {75,160,20,25,{"4","4","4"},  81,166},
  {100,160,20,25,{"5","5","5"},106,166},
  {125,160,20,25,{"6","6","6"},131,166},
  {150,160,20,25,{"7","7","7"},156,166},
  {175,160,20,25,{"8","8","8"},181,166},
  {200,160,20,25,{"9","9","9"},206,166},
  {222,160,18,25,{"0","0","0"},225,166},

  //  FILA QWERTY 
  {3,190,20,25, {"Q","q","@"},   9,196},
  {25,190,20,25,{"W","w","#"},  31,196},
  {50,190,20,25,{"E","e","$"},  56,196},
  {75,190,20,25,{"R","r","&"},  81,196},
  {100,190,20,25,{"T","t","_"},106,196},
  {125,190,20,25,{"Y","y","-"},131,196},
  {150,190,20,25,{"U","u","("},156,196},
  {175,190,20,25,{"I","i",")"},181,196},
  {200,190,20,25,{"O","o","="},206,196},
  {222,190,18,25,{"P","p","%"},225,196},

  //  FILA ASDF 
  {11,220,20,25, {"A","a","{"}, 17,226},
  {33,220,20,25, {"S","s","\""},39,226},
  {58,220,20,25, {"D","d","*"}, 64,226},
  {83,220,20,25, {"F","f","'"}, 89,226},
  {108,220,20,25,{"G","g",":"},114,226},
  {133,220,20,25,{"H","h","/"},139,226},
  {158,220,20,25,{"J","j","!"},164,226},
  {183,220,20,25,{"K","k","?"},189,226},
  {208,220,20,25,{"L","l","+"},214,226},

  //  FILA ZXCV 
  {33,250,20,25, {"Z","z",";"}, 39,256},
  {58,250,20,25, {"X","x","<"}, 64,256},
  {83,250,20,25, {"C","c",">"}, 89,256},
  {108,250,20,25,{"V","v","¡"},114,256},
  {133,250,20,25,{"B","b","?"},139,256},
  {158,250,20,25,{"N","n","{"},164,256},
  {183,250,20,25,{"M","m","}"},189,256},

  //  FILA SÍMBOLOS ABAJO 
  {58,280,20,25, {",",",",","},  64,286},
  {183,280,20,25,{".",".","."}, 189,286},
};

// Cantidad de teclas definidas
int numTeclas = sizeof(teclas) / sizeof(teclas[0]);

// Función para dibujar teclado
void drawQWERTY() {
  tft.setFreeFont(NULL);
  tft.setTextColor(TFT_WHITE);  
  tft.setTextSize(2);

  for (int i = 0; i < numTeclas; i++) {
    Tecla t = teclas[i];
    // Dibujar la tecla
    tft.drawRoundRect(t.x, t.y, t.w, t.h, 2, tft.color565(255,255,255));
    // Poner el texto según el modo (0=mayus,1=min,2=símbolo)
    tft.setCursor(t.cursorX, t.cursorY);
    tft.println(t.chars[bloq_mayus]);
  }



  // Aquí se dibuja las teclas especiales como espacio, enter, backspace 
  tft.drawRoundRect(200+8, 250, 31, 25, 2, tft.color565(255, 255, 255)); // BACK
  tft.setCursor(206+8, 256);  tft.println("<-");

tft.setTextSize(1);

tft.drawRoundRect(3, 250, 30, 25, 2, tft.color565(255, 255, 255)); // BLQMAYUS
 tft.setCursor(8, 260);  tft.println("abc");

tft.drawRoundRect(3, 280, 30, 25, 2, tft.color565(255, 255, 255)); // Num Symbols
 tft.setCursor(8, 290);  
if (bloq_mayus == 0) { tft.println("123"); }
  if (bloq_mayus == 1) { tft.println("123"); }
  //if (bloq_mayus == 2) { tft.println("abc"); }
 
tft.drawRoundRect(25+8, 280, 20, 25, 2, tft.color565(255, 255, 255)); // SYM
 tft.setCursor(36, 290);  tft.println(":-)");

  tft.setTextSize(2);
tft.drawRoundRect(50+8, 280, 20, 25, 2, tft.color565(255, 255, 255)); // ,
 tft.setCursor(56+8, 286);  tft.println(",");
 
tft.drawRoundRect(75+8, 280, 95, 25, 2, tft.color565(255, 255, 255)); // SPACE
 //tft.setCursor(81+8, 286);  tft.println("_____");

   tft.drawRoundRect(175+8, 280, 20, 25, 2, tft.color565(255, 255, 255)); // .
   tft.setCursor(181+8, 286);  tft.println(".");
   
tft.drawRoundRect(200+8, 280, 31, 25, 2, tft.color565(255, 255, 255)); // ENTER
  tft.drawLine(215, 295, 230, 295, tft.color565(255, 255, 255));
  tft.drawLine(230, 287, 230, 295, tft.color565(255, 255, 255));
 tft.fillTriangle(215,295,220,290,220,300,tft.color565(255, 255, 255));

}






void touchQWERTY(){

if (pressed  == 1){
  state = 0;
}
  
 if ( (x>=3) && (y>=160) && (x<=23) && (y<=185) && ( pressed == 1 )  ) {   //1
        beep(3);
        drawFrame(3, 160, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('1'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('1'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('1'); } //Numeros               
   } //fin de touch boundaries

 if ( (x>=25) && (y>=160) && (x<=45) && (y<=185) && ( pressed == 1 )  ) {   //2
        beep(3);
        drawFrame(25, 160, 20, 25);   
        delay(100);
        if( bloq_mayus == 0 ){  updateStr('2'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('2'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('2'); } //Numeros 
   } //fin de touch boundaries
 if ( (x>=50) && (y>=160) && (x<=70) && (y<=185) && ( pressed == 1 )  ) {   //3
        beep(3);
        drawFrame(50, 160, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('3'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('3'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('3'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=75) && (y>=160) && (x<=95) && (y<=185) && ( pressed == 1 )  ) {   //4
        beep(3);
        drawFrame(75, 160, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('4'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('4'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('4'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=100) && (y>=160) && (x<=120) && (y<=185) && ( pressed == 1 )  ) {   //5
        beep(3);
        drawFrame(100, 160, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('5'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('5'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('5'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=125) && (y>=160) && (x<=145) && (y<=185) && ( pressed == 1 )  ) {   //6
        beep(3);
        drawFrame(125, 160, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('6'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('6'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('6'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=150) && (y>=160) && (x<=170) && (y<=185) && ( pressed == 1 )  ) {   //7
        beep(3);
        drawFrame(150, 160, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('7'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('7'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('7'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=175) && (y>=160) && (x<=195) && (y<=185) && ( pressed == 1 )  ) {   //8
        beep(3);
        drawFrame(175, 160, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('8'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('8'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('8'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=200) && (y>=160) && (x<=220) && (y<=185) && ( pressed == 1 )  ) {   //9
        beep(3);
        drawFrame(200, 160, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('9'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('9'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('9'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=222) && (y>=160) && (x<=240) && (y<=185) && ( pressed == 1 )  ) {   //0
        beep(3);
        drawFrame(222, 160, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('0'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('0'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('0'); } //Numeros
   } //fin de touch boundaries


// SEGUNDA FILA   //   // SEGUNDA FILA   //   // SEGUNDA FILA   //   // SEGUNDA FILA   //   

//tft.drawRoundRect(3, 190, 20, 25, 2, tft.color565(255, 255, 255)); // Q


 if ( (x>=3) && (y>=190) && (x<=23) && (y<=215) && ( pressed == 1 )  ) {   //Q
        beep(3);
        drawFrame(3, 190, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('Q'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('q'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('@'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=25) && (y>=190) && (x<=45) && (y<=215) && ( pressed == 1 )  ) {   //W
        beep(3);
        drawFrame(25, 190, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('W'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('w'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('#'); } //Numeros
   } //fin de touch boundaries
 if ( (x>=50) && (y>=190) && (x<=70) && (y<=215) && ( pressed == 1 )  ) {   //E
        beep(3);
        drawFrame(50, 190, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('E'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('e'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('$'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=75) && (y>=190) && (x<=95) && (y<=215) && ( pressed == 1 )  ) {   //R
        beep(3);
        drawFrame(75, 190, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('R'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('r'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('&'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=100) && (y>=190) && (x<=120) && (y<=215) && ( pressed == 1 )  ) {   //T
        beep(3);
        drawFrame(100, 190, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('T'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('t'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('_'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=125) && (y>=190) && (x<=145) && (y<=215) && ( pressed == 1 )  ) {   //Y
        beep(3);
        drawFrame(125, 190, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('Y'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('y'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('-'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=150) && (y>=190) && (x<=170) && (y<=215) && ( pressed == 1 )  ) {   //U
        beep(3);
        drawFrame(150, 190, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('U'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('u'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('('); } //Numeros
   } //fin de touch boundaries

 if ( (x>=175) && (y>=190) && (x<=195) && (y<=215) && ( pressed == 1 )  ) {   //I
        beep(3);
        drawFrame(175, 190, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('I'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('i'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr(')'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=200) && (y>=190) && (x<=220) && (y<=215) && ( pressed == 1 )  ) {   //O
        beep(3);
        drawFrame(200, 190, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('O'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('o'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('='); } //Numeros
   } //fin de touch boundaries

 if ( (x>=222) && (y>=190) && (x<=240) && (y<=215) && ( pressed == 1 )  ) {   //P
        beep(3);
        drawFrame(222, 190, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('P'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('p'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('%'); } //Numeros
   } //fin de touch boundaries   




// TERCERA FILA   //   // TERCERA FILA   //   // TERCERA FILA   //   // TERCERA FILA   //   


 if ( (x>=3+8) && (y>=220) && (x<=23+8) && (y<=245) && ( pressed == 1 )  ) {   //A
        beep(3);
        drawFrame(3+8, 220, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('A'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('a'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('{'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=25+8) && (y>=220) && (x<=45+8) && (y<=245) && ( pressed == 1 )  ) {   //S
        beep(3);
        drawFrame(25+8, 220, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('S'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('s'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('"'); } //Numeros
   } //fin de touch boundaries
 if ( (x>=50+8) && (y>=220) && (x<=70+8) && (y<=245) && ( pressed == 1 )  ) {   //D
        beep(3);
        drawFrame(50+8, 220, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('D'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('d'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('*'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=75+8) && (y>=220) && (x<=95+8) && (y<=245) && ( pressed == 1 )  ) {   //F
        beep(3);
        drawFrame(75+8, 220, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('F'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('f'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('´'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=100+8) && (y>=220) && (x<=120+8) && (y<=245) && ( pressed == 1 )  ) {   //G
        beep(3);
        drawFrame(100+8, 220, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('G'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('g'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr(':'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=125+8) && (y>=220) && (x<=145+8) && (y<=245) && ( pressed == 1 )  ) {   //H
        beep(3);
        drawFrame(125+8, 220, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('H'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('h'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('/'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=150+8) && (y>=220) && (x<=170+8) && (y<=245) && ( pressed == 1 )  ) {   //J
        beep(3);
        drawFrame(150+8, 220, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('J'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('j'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('!'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=175+8) && (y>=220) && (x<=195+8) && (y<=245) && ( pressed == 1 )  ) {   //K
        beep(3);
        drawFrame(175+8, 220, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('K'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('k'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('?'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=200+8) && (y>=220) && (x<=220+8) && (y<=245) && ( pressed == 1 )  ) {   //L
        beep(3);
        drawFrame(200+8, 220, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('L'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('l'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('+'); } //Numeros
   } //fin de touch boundaries
  


// CUARTA FILA   //   // CUARTA FILA   //   // CUARTA FILA   //   // CUARTA FILA   //   


 if ( (x>=3) && (y>=250) && (x<=33) && (y<=275) && ( pressed == 1 )  ) {   //BLQMAYUS
        beep(3);
        drawFrame(3, 250, 30, 25);   
        delay(100); 
        bloq_mayus = bloq_mayus+1;  
        if (bloq_mayus >=2 ) { bloq_mayus = 0; }
        tft.fillRoundRect(1, 160, 339, 159, 2, tft.color565(0, 0, 0)); 
 
   } //fin de touch boundaries

 if ( (x>=25+8) && (y>=250) && (x<=45+8) && (y<=275) && ( pressed == 1 )  ) {   //Z
        beep(3);
        drawFrame(25+8, 250, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('Z'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('z'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr(';'); } //Numeros
   } //fin de touch boundaries
 if ( (x>=50+8) && (y>=250) && (x<=70+8) && (y<=275) && ( pressed == 1 )  ) {   //X
        beep(3);
        drawFrame(50+8, 250, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('X'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('x'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('<'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=75+8) && (y>=250) && (x<=95+8) && (y<=275) && ( pressed == 1 )  ) {   //C
        beep(3);
        drawFrame(75+8, 250, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('C'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('c'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('>'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=100+8) && (y>=250) && (x<=120+8) && (y<=275) && ( pressed == 1 )  ) {   //V
        beep(3);
        drawFrame(100+8, 250, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('V'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('v'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('¡'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=125+8) && (y>=250) && (x<=145+8) && (y<=275) && ( pressed == 1 )  ) {   //B
        beep(3);
        drawFrame(125+8, 250, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('B'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('b'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('?'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=150+8) && (y>=250) && (x<=170+8) && (y<=275) && ( pressed == 1 )  ) {   //N
        beep(3);
        drawFrame(150+8, 250, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('N'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('n'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('{'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=175+8) && (y>=250) && (x<=195+8) && (y<=275) && ( pressed == 1 )  ) {   //M
        beep(3);
        drawFrame(175+8, 250, 20, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr('M'); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr('m'); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr('}'); } //Numeros
   } //fin de touch boundaries

 if ( (x>=200+8) && (y>=250) && (x<=239) && (y<=275) && ( pressed == 1 )  ) {   //BACK
        beep(3);
        drawFrame(200+8, 250, 31, 25);   
 
        backspaceStr(); //borrar ultimo caracater
        delay(100);

   } //fin de touch boundaries




// QUINTA FILA   // QUINTA FILA   // QUINTA FILA   // QUINTA FILA   // QUINTA FILA   // QUINTA FILA   

 if ( (x>=3) && (y>=280) && (x<=33) && (y<=305) && ( pressed == 1 )  ) {   //NUM KEYBOARD
        beep(3);
        drawFrame(3, 280, 30, 25);   
        delay(100); 
        if (bloq_mayus <= 1) {
        bloq_mayus = 2;  
        tft.fillRoundRect(1, 160, 339, 159, 2, tft.color565(0, 0, 0)); 
        }
        if (bloq_mayus >=3 ) { bloq_mayus = 0; tft.fillRoundRect(1, 160, 339, 159, 2, tft.color565(0, 0, 0)); }
   } //fin de touch boundaries

 if ( (x>=25+8) && (y>=280) && (x<=45+8) && (y<=305) && ( pressed == 1 )  ) {   //FACES
        beep(3);
        drawFrame(25+8, 280, 20, 25);   
        delay(100); 
   } //fin de touch boundaries
 if ( (x>=50+8) && (y>=280) && (x<=70+8) && (y<=305) && ( pressed == 1 )  ) {   //,
        beep(3);
        drawFrame(50+8, 280, 20, 25);   
        delay(100); 
        updateStr(',');
   } //fin de touch boundaries



 if ( (x>=75+8) && (y>=280) && (x<=186) && (y<=305) && ( pressed == 1 )  ) {   //SPACE
        beep(3);
        drawFrame(75+8, 280, 95, 25);   
        delay(100); 
        if( bloq_mayus == 0 ){  updateStr(' '); } //Mayusculas
        if( bloq_mayus == 1 ){  updateStr(' '); } //Minusculas
        if( bloq_mayus == 2 ){  updateStr(' '); } //Numeros
   } //fin de touch boundaries


 if ( (x>=175+8) && (y>=280) && (x<=195+8) && (y<=305) && ( pressed == 1 )  ) {   //.
        beep(3);
        drawFrame(175+8, 280, 20, 25);   
        delay(100); 
        updateStr('.');
   } //fin de touch boundaries

 if ( (x>=200+8) && (y>=280) && (x<=239) && (y<=305) && ( pressed == 1 )  ) {   //ENTER
        beep(3);
        drawFrame(200+8, 280, 31, 25);   
        delay(100); 

checkPassword(); //revisar contrasena
copyStrings(); // copiar los char array a las variables que corresponden

    // delay(1);
    // stCurrent[0]='\0';
     
   } //fin de touch boundaries
 

} // fin de touchQWERTY()





/*

//VERSION ANTIGUA PERO MAS ENTENDIBLE PARA MOSTRAR CADA CARACTER ASCCII

void drawQWERTY(){  

tft.setFreeFont(NULL);
tft.setTextColor(TFT_WHITE);  
tft.setTextSize(2);

tft.drawRoundRect(3, 160, 20, 25, 2, tft.color565(255, 255, 255)); // 1
 tft.setCursor(9, 166);   tft.println("1");
tft.drawRoundRect(25, 160, 20, 25, 2, tft.color565(255, 255, 255)); // 2
 tft.setCursor(31, 166);  tft.println("2");
tft.drawRoundRect(50, 160, 20, 25, 2, tft.color565(255, 255, 255)); // 3
 tft.setCursor(56, 166);  tft.println("3");
tft.drawRoundRect(75, 160, 20, 25, 2, tft.color565(255, 255, 255)); // 4
 tft.setCursor(81, 166);  tft.println("4");
tft.drawRoundRect(100, 160, 20, 25, 2, tft.color565(255, 255, 255)); // 5
   tft.setCursor(106, 166);  tft.println("5");
tft.drawRoundRect(125, 160, 20, 25, 2, tft.color565(255, 255, 255)); // 6
   tft.setCursor(131, 166);  tft.println("6");
tft.drawRoundRect(150, 160, 20, 25, 2, tft.color565(255, 255, 255)); // 7
   tft.setCursor(156, 166);  tft.println("7");
tft.drawRoundRect(175, 160, 20, 25, 2, tft.color565(255, 255, 255)); // 8
   tft.setCursor(181, 166);  tft.println("8");
tft.drawRoundRect(200, 160, 20, 25, 2, tft.color565(255, 255, 255)); // 9
  tft.setCursor(206, 166);  tft.println("9");
tft.drawRoundRect(225-3, 160, 18, 25, 2, tft.color565(255, 255, 255)); // 0
  tft.setCursor(228-3, 166);  tft.println("0");



tft.drawRoundRect(3, 190, 20, 25, 2, tft.color565(255, 255, 255)); // Q
 tft.setCursor(9, 196); 
 if (bloq_mayus == 0) { tft.println("Q"); }
  if (bloq_mayus == 1) { tft.println("q"); }
  if (bloq_mayus == 2) { tft.println("@"); }
tft.drawRoundRect(25, 190, 20, 25, 2, tft.color565(255, 255, 255)); // W
 tft.setCursor(31, 196);  
 if (bloq_mayus == 0) { tft.println("W"); }
  if (bloq_mayus == 1) { tft.println("w"); }
  if (bloq_mayus == 2) { tft.println("#"); }
tft.drawRoundRect(50, 190, 20, 25, 2, tft.color565(255, 255, 255)); // E
 tft.setCursor(56, 196);  
 if (bloq_mayus == 0) { tft.println("E"); }
  if (bloq_mayus == 1) { tft.println("e"); }
  if (bloq_mayus == 2) { tft.println("$"); }
tft.drawRoundRect(75, 190, 20, 25, 2, tft.color565(255, 255, 255)); // R
 tft.setCursor(81, 196);  
if (bloq_mayus == 0) { tft.println("R"); }
  if (bloq_mayus == 1) { tft.println("r"); }
  if (bloq_mayus == 2) { tft.println("&"); }
tft.drawRoundRect(100, 190, 20, 25, 2, tft.color565(255, 255, 255)); // T
   tft.setCursor(106, 196);  
if (bloq_mayus == 0) { tft.println("T"); }
  if (bloq_mayus == 1) { tft.println("t"); }
  if (bloq_mayus == 2) { tft.println("_"); }
tft.drawRoundRect(125, 190, 20, 25, 2, tft.color565(255, 255, 255)); // Y
   tft.setCursor(131, 196); 
if (bloq_mayus == 0) { tft.println("Y"); }
  if (bloq_mayus == 1) { tft.println("y"); }
  if (bloq_mayus == 2) { tft.println("-"); }
tft.drawRoundRect(150, 190, 20, 25, 2, tft.color565(255, 255, 255)); // U
   tft.setCursor(156, 196); 
if (bloq_mayus == 0) { tft.println("U"); }
  if (bloq_mayus == 1) { tft.println("u"); }
  if (bloq_mayus == 2) { tft.println("("); }
tft.drawRoundRect(175, 190, 20, 25, 2, tft.color565(255, 255, 255)); // I
   tft.setCursor(181, 196);  
if (bloq_mayus == 0) { tft.println("I"); }
  if (bloq_mayus == 1) { tft.println("i"); }
  if (bloq_mayus == 2) { tft.println(")"); }
tft.drawRoundRect(200, 190, 20, 25, 2, tft.color565(255, 255, 255)); // O
  tft.setCursor(206, 196);  
if (bloq_mayus == 0) { tft.println("O"); }
  if (bloq_mayus == 1) { tft.println("o"); }
  if (bloq_mayus == 2) { tft.println("="); }
tft.drawRoundRect(225-3, 190, 18, 25, 2, tft.color565(255, 255, 255)); // P
  tft.setCursor(228-3, 196);  
if (bloq_mayus == 0) { tft.println("P"); }
  if (bloq_mayus == 1) { tft.println("p"); }
  if (bloq_mayus == 2) { tft.println("%"); }

tft.drawRoundRect(3+8, 220, 20, 25, 2, tft.color565(255, 255, 255)); // A
 tft.setCursor(9+8, 226);  
if (bloq_mayus == 0) { tft.println("A"); }
  if (bloq_mayus == 1) { tft.println("a"); }
  if (bloq_mayus == 2) { tft.println("{"); }
tft.drawRoundRect(25+8, 220, 20, 25, 2, tft.color565(255, 255, 255)); // S
 tft.setCursor(31+8, 226); 
if (bloq_mayus == 0) { tft.println("S"); }
  if (bloq_mayus == 1) { tft.println("s"); }
  if (bloq_mayus == 2) { tft.println(""""); }
tft.drawRoundRect(50+8, 220, 20, 25, 2, tft.color565(255, 255, 255)); // D
 tft.setCursor(56+8, 226);  
if (bloq_mayus == 0) { tft.println("D"); }
  if (bloq_mayus == 1) { tft.println("d"); }
  if (bloq_mayus == 2) { tft.println("*"); }
tft.drawRoundRect(75+8, 220, 20, 25, 2, tft.color565(255, 255, 255)); // F
 tft.setCursor(81+8, 226);  
if (bloq_mayus == 0) { tft.println("F"); }
  if (bloq_mayus == 1) { tft.println("f"); }
  if (bloq_mayus == 2) { tft.println("'"); }
tft.drawRoundRect(100+8, 220, 20, 25, 2, tft.color565(255, 255, 255)); // G
   tft.setCursor(106+8, 226);  
if (bloq_mayus == 0) { tft.println("G"); }
  if (bloq_mayus == 1) { tft.println("g"); }
  if (bloq_mayus == 2) { tft.println(":"); }
tft.drawRoundRect(125+8, 220, 20, 25, 2, tft.color565(255, 255, 255)); // H
   tft.setCursor(131+8, 226);  
if (bloq_mayus == 0) { tft.println("H"); }
  if (bloq_mayus == 1) { tft.println("h"); }
  if (bloq_mayus == 2) { tft.println("/"); }
tft.drawRoundRect(150+8, 220, 20, 25, 2, tft.color565(255, 255, 255)); // J
   tft.setCursor(156+8, 226);  
if (bloq_mayus == 0) { tft.println("J"); }
  if (bloq_mayus == 1) { tft.println("j"); }
  if (bloq_mayus == 2) { tft.println("!"); }
tft.drawRoundRect(175+8, 220, 20, 25, 2, tft.color565(255, 255, 255)); // K
   tft.setCursor(181+8, 226);  
if (bloq_mayus == 0) { tft.println("K"); }
  if (bloq_mayus == 1) { tft.println("k"); }
  if (bloq_mayus == 2) { tft.println("?"); }
tft.drawRoundRect(200+8, 220, 20, 25, 2, tft.color565(255, 255, 255)); // L
  tft.setCursor(206+8, 226);  
if (bloq_mayus == 0) { tft.println("L"); }
  if (bloq_mayus == 1) { tft.println("l"); }
  if (bloq_mayus == 2) { tft.println("+"); }
//tft.drawRoundRect(225, 190, 20, 25, 2, tft.color565(255, 255, 255)); // 0
// tft.setCursor(228, 196);  tft.println("P");


tft.setTextSize(1);
tft.drawRoundRect(3, 250, 30, 25, 2, tft.color565(255, 255, 255)); // BLQMAYUS
 tft.setCursor(8, 260);  tft.println("abc");
tft.setTextSize(2);
tft.drawRoundRect(25+8, 250, 20, 25, 2, tft.color565(255, 255, 255)); // Z
 tft.setCursor(31+8, 256);  
if (bloq_mayus == 0) { tft.println("Z"); }
  if (bloq_mayus == 1) { tft.println("z"); }
  if (bloq_mayus == 2) { tft.println(";"); }
tft.drawRoundRect(50+8, 250, 20, 25, 2, tft.color565(255, 255, 255)); // X
 tft.setCursor(56+8, 256);  
if (bloq_mayus == 0) { tft.println("X"); }
  if (bloq_mayus == 1) { tft.println("x"); }
  if (bloq_mayus == 2) { tft.println("<"); }
tft.drawRoundRect(75+8, 250, 20, 25, 2, tft.color565(255, 255, 255)); // C
 tft.setCursor(81+8, 256);  
if (bloq_mayus == 0) { tft.println("C"); }
  if (bloq_mayus == 1) { tft.println("c"); }
  if (bloq_mayus == 2) { tft.println(">"); }
tft.drawRoundRect(100+8, 250, 20, 25, 2, tft.color565(255, 255, 255)); // V
   tft.setCursor(106+8, 256);  
if (bloq_mayus == 0) { tft.println("V"); }
  if (bloq_mayus == 1) { tft.println("v"); }
  if (bloq_mayus == 2) { tft.println("¡"); }
tft.drawRoundRect(125+8, 250, 20, 25, 2, tft.color565(255, 255, 255)); // B
   tft.setCursor(131+8, 256);  
if (bloq_mayus == 0) { tft.println("B"); }
  if (bloq_mayus == 1) { tft.println("b"); }
  if (bloq_mayus == 2) { tft.println("?"); }
tft.drawRoundRect(150+8, 250, 20, 25, 2, tft.color565(255, 255, 255)); // N
   tft.setCursor(156+8, 256);  
if (bloq_mayus == 0) { tft.println("N"); }
  if (bloq_mayus == 1) { tft.println("n"); }
  if (bloq_mayus == 2) { tft.println("{"); }
tft.drawRoundRect(175+8, 250, 20, 25, 2, tft.color565(255, 255, 255)); // M
   tft.setCursor(181+8, 256);  
if (bloq_mayus == 0) { tft.println("M"); }
  if (bloq_mayus == 1) { tft.println("m"); }
  if (bloq_mayus == 2) { tft.println("}"); }
   
tft.drawRoundRect(200+8, 250, 31, 25, 2, tft.color565(255, 255, 255)); // BACK
  tft.setCursor(206+8, 256);  tft.println("<-");



tft.setTextSize(1);
tft.drawRoundRect(3, 280, 30, 25, 2, tft.color565(255, 255, 255)); // Num Symbols
 tft.setCursor(8, 290);  
if (bloq_mayus == 0) { tft.println("123"); }
  if (bloq_mayus == 1) { tft.println("123"); }
  //if (bloq_mayus == 2) { tft.println("abc"); }
 
tft.drawRoundRect(25+8, 280, 20, 25, 2, tft.color565(255, 255, 255)); // SYM
 tft.setCursor(36, 290);  tft.println(":-)");

  tft.setTextSize(2);
tft.drawRoundRect(50+8, 280, 20, 25, 2, tft.color565(255, 255, 255)); // ,
 tft.setCursor(56+8, 286);  tft.println(",");
 
tft.drawRoundRect(75+8, 280, 95, 25, 2, tft.color565(255, 255, 255)); // SPACE
 //tft.setCursor(81+8, 286);  tft.println("_____");

   tft.drawRoundRect(175+8, 280, 20, 25, 2, tft.color565(255, 255, 255)); // .
   tft.setCursor(181+8, 286);  tft.println(".");
   
tft.drawRoundRect(200+8, 280, 31, 25, 2, tft.color565(255, 255, 255)); // ENTER
  tft.drawLine(215, 295, 230, 295, tft.color565(255, 255, 255));
  tft.drawLine(230, 287, 230, 295, tft.color565(255, 255, 255));
 tft.fillTriangle(215,295,220,290,220,300,tft.color565(255, 255, 255));

} // fin de drawQWERTY()
*/


