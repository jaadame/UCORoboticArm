// Las coordenadas de los puntos vendrán definidas por la posición establecidas en los ejes X,Y,Z
// Eje X: 1 - 16
// Eje Y: 1 - 11
// Eje Z: 1 - 10

void ConversionCoordenadas(){       //PRUEBAAAAA
  for(int i=0; i<contadora; i++){
    Serial.println("conVVVVVVVVVVVVVVVVVierte");
    if (posZ[i]<6){
      alturaConsigna[i] = 120;
    }
    else{
      alturaConsigna[i] = 350;
    }
    if (posX[i]<6){
      avanceConsigna[i] = 100+alturaConsigna[i];
    }
    else{
      avanceConsigna[i] = 300+alturaConsigna[i];
    }
    if (posY[i]<5){
      giroConsigna[i] = 200;
    }
    else{
      giroConsigna[i] = 500;
    }
  }
  convierte=false;
}
