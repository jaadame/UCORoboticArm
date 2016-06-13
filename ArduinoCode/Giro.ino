void Giro(){
  valIntGiro = 0;
  for (int i=0; i<integral; i++){                   //for para almacenar datos del pot de avance
    valIntGiro = valIntGiro + analogRead(potGiro);  //almacena valores
  }
  valIntGiro = valIntGiro / integral;               //hace la media
  giroReal = valIntGiro;                            //y asigna el valor a la variable giroReal
  
  while(((giroReal<=giroConsigna[realContadora]+horqGiro) && (giroReal>giroConsigna[realContadora]-horqGiro))==false)         //Mientras que no esté en el punto de giro de consigna
  { 

    Serial.println("G");
    valIntGiro = 0;
    for (int i=0; i<integral; i++){                     //Vuelve a leer el potenciómetro de giro
      valIntGiro = valIntGiro + analogRead(potGiro);    //acumula valores
    }
    valIntGiro = valIntGiro / integral;                 //haz la media
    giroReal = valIntGiro;                              //y asgina el valor
  
    pwmGiro = abs (giroReal-giroConsigna[realContadora]);              //Diferencia en absouto del giro consigna y el real
    if(pwmGiro>40){                                     //Si estamos "lejos"
      pwmGiro = 170;                                    //amplitud de pulso "alta"
      pwmAltura = 120;
    }
    else{
      pwmGiro = 160;                                     //En caso contrario, que sea "baja"
      pwmAltura = 110;
    }
  
    if (giroReal>giroConsigna[realContadora]+horqGiro){                //Si está por encima del valor
      digitalWrite(IFPin,LOW);                          //Gira en sentido levógiro
      digitalWrite(IEPin,HIGH);
      analogWrite(EnablePin3,pwmGiro);                  //A ésta amplitud
      analogWrite(EnablePin2, pwmAltura);                     //y sube la amplitud del motor que mantiene la altura
    }
    if (giroReal<giroConsigna[realContadora]-horqGiro){                //Si esta por debajo
      digitalWrite(IFPin,HIGH);                         //sentido destrógiro
      digitalWrite(IEPin,LOW);
      analogWrite(EnablePin3,pwmGiro);                  //a ésta amplitud
      analogWrite(EnablePin2, pwmAltura);                     //y subiendo la amplitud del motor altura
    }
    if((giroReal<=giroConsigna[realContadora]+horqGiro) && (giroReal>giroConsigna[realContadora]-horqGiro)){  //Si estamos en el giro de consigna
      analogWrite(EnablePin3, 0);                                               //apaga el motor
    }

    /*valIntAlt = 0;
    for (int i=0; i<integral; i++){                   //Vuelve a comprobar la altura
      valIntAlt = valIntAlt + analogRead(potAltura);
    }
    valIntAlt = valIntAlt / integral;
    alturaReal = valIntAlt;
    if (((alturaReal<=alturaConsigna[realContadora]+horqAltura) && (alturaReal>alturaConsigna[realContadora]-horqAltura))==false){  //Si no está en altura consigna
      digitalWrite(EnablePin3, 0);                                                                    //desactiva el motor
      Altura(); 
      break;                                                                                          //y sal del bucle
    }*/ 
  }
}

