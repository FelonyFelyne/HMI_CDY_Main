//Libreria de la pantalla 
    // ( no olvidar configurar correctamente el archivo: User_Setup.h de la libreria )
#include <TFT_eSPI.h>               //https://github.com/Bodmer/TFT_eSPI
#include <XPT2046_Touchscreen.h>    //https://github.com/PaulStoffregen/XPT2046_Touchscreen

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;
bool pressed = 0;


// variables globales de impresion de graficos
bool state = 0; // variable para cambio de estado y correr ciertas cosas de los graficos solo una vez
int pagina = 0; // variable para declarar la pagina en curso que se está desplegando en ese momento


#define light 16 //pin del backlight de la pantalla
int back_light = 255; //valor PWM para el backlight
bool state_light = 0; //boleano de no repeticion en pag 6 backlight

#define roundr 10 //variable para el redondeo de los cuadrados (drawRoundRect, fillRoundRect)


#include "medicals.h"  //El bitmap de inicio (puede cambiarse por cualquier otro)



void setup() {

  // TFT
  tft.init();
  tft.setRotation(0); // vertical
  tft.fillScreen(TFT_WHITE);

   tft.setSwapBytes(true);
   tft.pushImage(0, 0, medicalsWidth, medicalsHeight, medicals);  //colocar aqui un mapa de bits
   tft.setTextColor(TFT_BLACK, tft.color565(255, 255, 255));
   tft.drawString("http://medicalsystems.mex.tl" ,25 ,280 , 2); // string, xpos, ypos, font
   
   delay(2000); //mostrar bitmap por 2 segundos

  //Touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(1);

  tft.fillScreen(TFT_BLACK);  //apagar todos los pixeles de inicio (borrar pantalla)

  tft.setFreeFont(NULL);
  tft.setTextSize(1);


  pagina = 0; //iniciar en pantalla de pagina 0

} //fin de void setup()







void loop() {

paginas_Principal(); // revision de pagina en curso a desplegar

} //fin de void loop()
