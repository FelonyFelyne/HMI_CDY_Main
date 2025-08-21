
//Libreria de la pantalla 
    // ( no olvidar configurar correctamente el archivo: User_Setup.h de la libreria )
    // (se agrega la configuracion de pines para el CDY al final de este main, solo inicialmente, despues se va a remover.)



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

int pagina = 0; // variable para declarar la pagina en curso que se está desplegando en ese momento IMPORTANTE
                // Se usa para hacer cambios entre diferentes pantallas y situaciones a mostrar, como un libro.


#define light 16 //pin del backlight de la pantalla
int back_light = 255; //valor PWM para el backlight
bool state_light = 0; //boleano de no repeticion en pag 6 backlight

#define roundr 10 //variable para el redondeo de los cuadrados (drawRoundRect, fillRoundRect)




void setup() {

  // TFT
  tft.init();
  tft.setRotation(0); // vertical
  tft.fillScreen(TFT_WHITE);


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








//Este es el que debe funcionar bien para su CDY, el V3, pero abajo tambien hay otro para el V1 y el V2
//Reemplazar lo necesario de esto en el User_Setup.h de la libreria TFT_eSPI

/*

// CDY V3, version YELLOW ESP32 DISPLAY 2.8"    
//#define ST7789_DRIVER
#define ILI9341_2_DRIVER
#define TFT_RGB_ORDER TFT_BGR 

#define TFT_INVERSION_ON //algunas pantallas no necesitan esto

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

#define TFT_BL   21
#define TFT_BACKLIGHT_ON HIGH  //DESACTIVAR SI SE USA CONTROL DE LUMINOSIDAD EN PIN TFT_BL

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST  -1  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST

#define TOUCH_CS 33     // Chip select pin (T_CS) of touch screen
#define TOUCH_MOSI 32 // Separate Touch SoftSPI bus
#define TOUCH_MISO 39 // Separate Touch SoftSPI bus
#define TOUCH_CLK 25  // Separate Touch SoftSPI bus
#define USE_HSPI_PORT  //Importante sin esta linea el touch no funciona

*/


/*
  
// CDY V1, V2, version YELLOW ESP32 DISPLAY 2.8"
#define ILI9341_2_DRIVER   
//#define TFT_INVERSION_ON //algunas pantallas no necesitan esto
//#define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue


#define TFT_WIDTH  240
#define TFT_HEIGHT 320

#define TFT_BL   21
#define TFT_BACKLIGHT_ON HIGH   //DESACTIVAR SI SE USA CONTROL DE LUMINOSIDAD EN PIN TFT_BL

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST  -1  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST

#define TOUCH_CS 33     // Chip select pin (T_CS) of touch screen
#define TOUCH_MOSI 32 // Separate Touch SoftSPI bus
#define TOUCH_MISO 39 // Separate Touch SoftSPI bus
#define TOUCH_CLK 25  // Separate Touch SoftSPI bus
#define USE_HSPI_PORT  //Importante sin esta linea el touch no funciona

*/
