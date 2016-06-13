void AlturaMovimiento(){
  valIntAlt = 0;                                    //Inicializa a 0 el integral
  for (int i=0; i<integral; i++){                   //for para acumular valores y "alisar" el valor recogido
    valIntAlt = valIntAlt + analogRead(potAltura);  //Lee potenciómetro altura
  }
  valIntAlt = valIntAlt / integral;                 //Hace la media
  alturaReal = valIntAlt;                           //Asigna a valor real la media
                                                    //De esta forma podemos saber si tenemos que entrar en el siguiente while
  while(((alturaReal<=alturaOrigen+horqAltura) && (alturaReal>alturaOrigen-horqAltura))==false){    //Mientras que la altura no se encuentre en el valor objetivo atendiendo
                                                                                                    
    Serial.println("Al");
    valIntAlt = 0;
    for (int i=0; i<integral; i++){                   //Una vez está dentro vuelve a leer para saber dónde nos encontramos
      valIntAlt = valIntAlt + analogRead(potAltura);
    }
    valIntAlt = valIntAlt / integral;
    alturaReal = valIntAlt;
  
    pwmAltura = abs (alturaReal-alturaOrigen);     //Diferencia en valor absoluto entre la posición que estamos y a la que queremos llegar
    if(pwmAltura>40){                                //Si estamos "lejos" del punto objetivo
      pwmAltura = 200;                               //le damos una amplitud de pulso "alta"
    }
    else{
      pwmAltura = 160;                               //En caso contrario, que sea más baja.
    }
  
    if (alturaReal>alturaOrigen+horqAltura){       //Si está por encima del punto objetivo
      digitalWrite(EnablePin2, 0);                   //apagamos los dos motores de avance
      digitalWrite(EnablePin1, 0);
    }
    if (alturaReal<alturaOrigen-horqAltura){      //Si está por debajo del punto objetivo
      digitalWrite(IDPin, HIGH);
      digitalWrite(ICPin, LOW);
      digitalWrite(IAPin, LOW);
      digitalWrite(IBPin, HIGH);                    //habilitamos ambos motores
      analogWrite(EnablePin2, pwmAltura);
      analogWrite(EnablePin1, pwmAltura-100);        //El pwm del motor que también controla el avance va a ser inferior para eliminar el movimiento de avance
    }
    if((alturaReal<=alturaOrigen+horqAltura) && (alturaReal>alturaOrigen-horqAltura)){    //Si nos encontramos en el objetivo
      analogWrite(EnablePin2, 110);                  //Dejamos el motor de altura para que mantenga
      analogWrite(EnablePin1, 70);                   //y desactivamos al motor de avance
    }    
  }
}

