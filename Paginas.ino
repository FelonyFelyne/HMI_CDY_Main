

void paginas_Principal() {  // donde se leera segun el touch la pagina que se va a desplegar al momento+
  
  touchCheck(); //revisar el touch de pantalla

  //Serial.println((String) "Pagina: " + pagina); //debug

  switch(pagina) {

    case 0: //pagina de default
        
          printQWERTY();  //mostrar teclado en pantalla 
          touchQWERTY();

        if (state == 0){
          DrawRegresar();
          drawQWERTY();
          state = 1;
        }
  

      if ( (x>=201) && (y>=6) && (x<=230) && (y<=30) && ( pressed == 1 )  ) {   //Boton de REGRESO  //verificacion touch
        //beep(3);
        //drawFrame(201, 280, 45, 30);   
      delay(300); 
      tft.fillScreen(TFT_BLACK);
      tft.setTextFont(0);
      tft.setTextSize(1);

     state = 0;
     pagina = 1;
   } //fin de touch boundaries 

    break; //case 0



    case 1:

      //ejemplo basico de otra pagina IMPORTANTE CAMBIAR
       tft.fillScreen(TFT_WHITE);
       tft.pushImage(0, 0, medicalsWidth, medicalsHeight, medicals);  //colocar aqui un mapa de bits
       tft.setTextColor(TFT_BLACK, tft.color565(255, 255, 255));
       tft.drawString("http://medicalsystems.mex.tl" ,25 ,280 , 2); // string, xpos, ypos, font
       delay(2000); //mostrar bitmap por 2 segundos
       tft.fillScreen(TFT_BLACK);
       pagina = 0; //regresar a pagina 0

    break; //case 1



    default:

    break;


  } //fin de switch (pagina)

} //fin de void paginas_Principal()


