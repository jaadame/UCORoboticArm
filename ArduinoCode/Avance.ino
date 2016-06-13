void Avance() {
  
  valIntAvan = 0;
  for (int i=0; i<integral; i++){                     //for para calcular la media de valores de potenciómetro
    valIntAvan = valIntAvan + analogRead(potAvance);  //acumula valores
  }
  valIntAvan = valIntAvan / integral;                 //hace la media
  avanceReal = valIntAvan;                            //asigna el valor a real
  
  while((((avanceReal<=avanceConsigna[realContadora]+horqAvance) && (avanceReal>avanceConsigna[realContadora]-horqAvance))==false)&&    //Hasta que el avance no se encuentra en el punto objetivo
  (((giroReal<=giroConsigna[realContadora]+horqGiro) && (giroReal>giroConsigna[realContadora]-horqGiro))==true))                     //el giro SÍ se encuentra en el punto objetivo
  {

    Serial.println("Av");
    valIntAvan = 0;
    for (int i=0; i<integral; i++){                     //Vuelve a leer el valor de potenciómetro y calcula la media
      valIntAvan = valIntAvan + analogRead(potAvance);
    }
    valIntAvan = valIntAvan / integral;
    avanceReal = valIntAvan;
  
    pwmAvance = abs (avanceReal-avanceConsigna[realContadora]);        //Diferencia en valor absoluto del punto en el que estamos y al que queremos ir
    if(pwmAvance>40){                                   //Si estamos lejos
      pwmAvance = 170;                                  //da una amplitud de pulso alta
    }
    else{
      pwmAvance = 140;                                  //en caso contario, que sea más baja
    }
  
    if (avanceReal>avanceConsigna[realContadora]+horqAvance){          //Si estamos por encima del valor objetivo
      digitalWrite(IBPin,LOW);
      digitalWrite(IAPin,HIGH);                         //Ve hacia adentro
      analogWrite(EnablePin1,pwmAvance);                //con esta amplitud
      analogWrite(EnablePin2, 100);                      //y la amplitud del motor altura que sea ésta
    }
    if (avanceReal<avanceConsigna[realContadora]-horqAvance){          //Si estamos por debajo del valor
      digitalWrite(IBPin,HIGH);                         //ve hacia afuera
      digitalWrite(IAPin,LOW); 
      analogWrite(EnablePin1,pwmAvance);                //con esta amplitud
      analogWrite(EnablePin2, 110);                     //y aumenta el valor de la amplitud del motor de altura
    }
    if((avanceReal<=avanceConsigna[realContadora]+horqAvance) && (avanceReal>avanceConsigna[realContadora]-horqAvance)){    //Si estamos en el objetivo atendiendo a los errores permitidos
      analogWrite(EnablePin1, 60);                       //apaga al motor avance
      analogWrite(EnablePin2, 110);                      //que el motor altura mantenga al brazo
   
       
      valIntAlt = 0;
      for (int i=0; i<integral; i++){                     //Volvemos a leer la altura
        valIntAlt = valIntAlt + analogRead(potAltura);
      }
      valIntAlt = valIntAlt / integral;
      alturaReal = valIntAlt;
      if (((alturaReal<=alturaConsigna[realContadora]+horqAltura) && (alturaReal>alturaConsigna[realContadora]-horqAltura))==false){    //En caso de haber perdido la altura objetivo
        digitalWrite(EnablePin1, 0);      //desactiva el motor avance
        Altura(); 
        break;                            //y sal de éste bucle
      }
    }
  }
}

