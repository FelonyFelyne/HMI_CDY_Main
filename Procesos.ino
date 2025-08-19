

void touchCheck() {

    // Leer toque táctil
  if (touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();
    y = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    x = map(p.y, 3800, 240, 1, SCREEN_HEIGHT);
    z = p.z;
    pressed = (z > 100);
    state = 0; //permirir dibujar de nuevo los graficos una vez
    //Serial.printf("Touch detectado: x=%d, y=%d, z=%d\n", x, y, z); //debug de coordenadas
  } else {
    pressed = false;
  }

} //fin de void touchCheck()




void beep(int del){  // aqui se relaiza un beep con un buzzer

//Ejemplo: beep(100);  donde 100 son 100 milisegundos que durara el sonido

}


