

void DrawRegresar(){   //boton de regresar posicion superior derecha
if(state == 0) {
   tft.fillRoundRect(201, 6, 37, 24, roundr, tft.color565(255, 0, 0));
   tft.drawRoundRect(200, 5, 38, 25, roundr, tft.color565(255, 255, 255));
    tft.setFreeFont(NULL);
    tft.setCursor(204, 10);
    tft.setTextColor(TFT_WHITE);  tft.setTextSize(2);
    tft.println("<-");
 }// fin if state = 0
}



void drawFrame(int x_1, int y_1, int x_2, int y_2) {  // Resaltado de botones cada que son presionados
   if (pagina == 0 ) {  //teclado QWERTY
       tft.drawRect(x_1, y_1, x_2, y_2, TFT_WHITE);
      if (pressed == 1) {
       tft.drawRect(x_1, y_1, x_2, y_2, TFT_GREEN);
      }
   }
} // fin de void drawFrame()