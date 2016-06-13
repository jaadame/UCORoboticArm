void Altura(){
  valIntAlt = 0;                                    //Inicializa a 0 el integral
  for (int i=0; i<integral; i++){                   //for para acumular valores y "alisar" el valor recogido
    valIntAlt = valIntAlt + analogRead(potAltura);  //Lee potenciómetro altura
  }
  valIntAlt = valIntAlt / integral;                 //Hace la media
  alturaReal = valIntAlt;                           //Asigna a valor real la media
                                                    //De esta forma podemos saber si tenemos que entrar en el siguiente while
  while(((alturaReal<=alturaConsigna[realContadora]+horqAltura) && (alturaReal>alturaConsigna[realContadora]-horqAltura))==false){    //Mientras que la altura no se encuentre en el valor objetivo atendiendo
                                                                                                        //a los errores permitidos
    Serial.println("Allllllllllll");
    valIntAlt = 0;
    for (int i=0; i<integral; i++){                   //Una vez está dentro vuelve a leer para saber dónde nos encontramos
      valIntAlt = valIntAlt + analogRead(potAltura);
    }
    valIntAlt = valIntAlt / integral;
    alturaReal = valIntAlt;
  
    pwmAltura = abs (alturaReal-alturaConsigna[realContadora]);     //Diferencia en valor absoluto entre la posición que estamos y a la que queremos llegar
    if(pwmAltura>40){                                //Si estamos "lejos" del punto objetivo
      pwmAltura = 180;                               //le damos una amplitud de pulso "alta"
    }
    else{
      pwmAltura = 150;                               //En caso contrario, que sea más baja.
    }
  
    if (alturaReal>alturaConsigna[realContadora]+horqAltura){       //Si está por encima del punto objetivo

      digitalWrite(EnablePin2,0);                   //apagamos los dos motores de avance
      digitalWrite(EnablePin1, 0);
      Avance();
    }
    if (alturaReal<alturaConsigna[realContadora]-horqAltura){      //Si está por debajo del punto objetivo
      digitalWrite(IDPin, HIGH);
      digitalWrite(ICPin, LOW);
      digitalWrite(IAPin, LOW);
      digitalWrite(IBPin, HIGH);                    //habilitamos ambos motores
      analogWrite(EnablePin2, pwmAltura);
      analogWrite(EnablePin1, pwmAltura-100);        //El pwm del motor que también controla el avance va a ser inferior para eliminar el movimiento de avance
    }
    if((alturaReal<=alturaConsigna[realContadora]+horqAltura) && (alturaReal>alturaConsigna[realContadora]-horqAltura)){    //Si nos encontramos en el objetivo
      analogWrite(EnablePin2, 100);                  //Dejamos el motor de altura para que mantenga
      analogWrite(EnablePin1, 60);                   //y desactivamos al motor de avance

      if(escucha == false && mueve == true){
        int valor = analogRead(A0);
        sprintf(cadena,"*%d,%d,%d,%d,%d,",posX[realContadora],posY[realContadora],posZ[realContadora],valor,valor);
        Serial.println(cadena);
        delay(50);
        Serial1.println(cadena);
        delay(500);
        *cadena = 0;
        
        realContadora++;
        if(realContadora >= contadora){
          realContadora = 0;
          alturaConsigna[0] = alturaOrigen;
          avanceConsigna[0] = avanceOrigen;
          giroConsigna[0] = giroOrigen;

          AlturaMovimiento();
    
          Giro();                                   //Función movimiento giro -> Segundo movimiento
  
          Avance();                                 //Función movimiento avance -> Tercer movimiento
          
          escucha = true;                                   //reanudamos la escucha
          mueve = false;                                    //desactivamos el movimiento
          break;
        }
        break;
     }

      if(escucha == true && mueve == true){
        mueve = false;
        escucha = true;
      }
    }    
  }



}
