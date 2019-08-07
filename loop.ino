
void loop() {
  lecturasensores();
  detectarcambioestadopines();
  mostrarpantallas();
  comunicacionrpi();
  // delay(50);

  if(iniciocambiofiltro==1)
  {   iniciocambiofiltro=0;
    unsigned long cronometroauxiliar=millis();
    while((millis()-cronometroauxiliar)<5000)
      {
      Serial1.print("t28.txt=");
      Serial1.print("\"");
      Serial1.print("TIENE DOS MINUTOS PARA CAMBIO FILTRO "+String((millis()-cronometroauxiliar)/1000));
      //Serial1.print(String((millis()-cronometrozeolita)/1000));
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      }
    Serial1.print("t28.txt=");
      Serial1.print("\"");
      Serial1.print("TIEMPO TERMINADO");
      //Serial1.print(String((millis()-cronometrozeolita)/1000));
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    //AGREGAR QUE PUEDA SALIR DEL WHILE PRESIONANDO EL BOTON AUXILIAR
  
  }
  
  if (rebootvalvula == 1) //esta funcion lleva la valvula a una posicion segura antes de iniciar, SI LA VALVULA NO LLEGA A LA POSICION LA PLANTA NO PARTE
  { int division; //esta variable es solo para mostrar el numero de acercamiento al valor deseado
    dac.setVoltage(valorvalvula, false);
    if (posicionvalvula > valorvalvula)
    { division = posicionvalvula - valorvalvula;
      division = division * 100 / valorvalvula;
      if (division < 15)
      {
        rebootvalvula = 0;
      }
    }
  else
    { division = valorvalvula - posicionvalvula;
      division = division * 100 / valorvalvula;
      if (division < 15)
      {
        rebootvalvula = 0;
      }
    }
  }

  else if (estadofiltrozeolita == 1) //este es el estado más importante porque no depende del funcionamiento de la planta
  {   enviarnextion("LAVADO FILTRO DE ZEOLITA", "t26.txt=");
      activador("contactorbaja", 1);
      activador("electrovalvula", 0);
      activador("contactoralta", 0);
      Serial1.print("t28.txt=");
      Serial1.print("\"");
      Serial1.print(String((millis()-cronometrozeolita)/1000));
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      
  }

  else if (estadomemflush == 1 && (millis() - cronometromemflush < cuentaregresivamemflush)) //esta funciona se activará cuando el filtro de zeolita termine de su lavado
  {
    Serial1.print("t28.txt=");
    Serial1.print("\"");
    Serial1.print(String((cuentaregresivamemflush-(millis()-cronometromemflush))/1000));
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    dac.setVoltage(4000, false);//la valvulamotorizada se va a 0 incluir codigo.
    if (posicionvalvula >= 1900) //20 MENOS POR SEGURIDAD
    {
      activador("contactorbaja", 1);
      activador("contactoralta", 1);
      activador("electrovalvula", 1);
      enviarnextion("LAVADO DE MEMBRANAS EN PROCESO", "t26.txt=");
    }
    else
    {
      enviarnextion("POSICIONANDO VALVULA PARA LAVADO DE MEMBRANAS", "t26.txt=");
      activador("contactorbaja", 0);
      activador("electrovalvula", 0);
      activador("contactoralta", 0);
    }

  }
 else if (iniciodeplanta == 1 && botononoff == 1 ) //cuando la funcion "iniciodeplanta" está en 1, empieza la rutina de inicio.
  {
     
    if (millis() - cronometroinicio < 5000 ) //primer paso de inicio de la planta, bomba de baja y electrovalvula se activan por X segundos
    { dac.setVoltage(2000, false);//LA VALVULA SE ABRIRA EN EL INICIO DE LA PLANTA, DESPUES EMPIEZA LA REGULACION... (NUEVO)
      activador("contactorbaja", 1);
      activador("electrovalvula", 1);
    }
    else                                   //luego de eso se activa el contactor de la bomba de alta
    {
      activador("contactoralta", 1);
      iniciodeplanta = 0;
    }
    enviarnextion("INICIANDO CICLO DE PRODUCCION", "t26.txt=");
  }
  else if (iniciodeplanta == 0 && botononoff == 1 )
  {
    if (estadopresostatobaja == 1 || estadopresostatoalta == 1 || estadonivelaltoestanque == 1)
    { activador("contactorbaja", 0);
      activador("electrovalvula", 0);
      activador("contactoralta", 0);
      if (estadopresostatobaja == 1 || estadopresostatoalta == 1)
      {enviarnextion("FALLA PRESOSTATOS", "t26.txt="); //AQUI SEPARAR EL ESTADO DE ALTA Y BAJA PARA MOSTRAR EN PANTALLA, (ESTO ES UNA ALERTA ESTE ESTADO NO VA AQUI... SACAR DE INMEDIATO)
      }
     else {
      enviarnextion("PLANTA STANDBY (ESTANQUE FULL)", "t26.txt=");
    }
     
    }

    else if (estadonivelaltoestanque == 0)
    {

      //  enviarnextion(String(valorvalvula), "t26.txt=");
      enviarnextion("PRODUCIENDO AGUA", "t26.txt=");
    dac.setVoltage(valorvalvula, false);
      //-----------------inicio regulacion de valvula---------
     // enviarnextion("TEST", "t26.txt=");
      

      
      if(millis()-cronometrovalvula>pidvalvula) //con esto le doy rapidez al giro del motro cuando se esta acercando al valor deseado
      {cronometrovalvula=millis();
      if (presioncuatro >= rango1 && presioncuatro <= rango2)
      { dac.setVoltage(valorvalvula, false);
         
        // enviarnextion("VALVULA EN POSICION", "t26.txt=");
        //decir que la valvula está en posicion
      }
      else if (presioncuatro < rango1)
      { 
      //  enviarnextion("PRESION MENOR", "t26.txt=");
        if(rango1-presioncuatro>100)
         {pidvalvula=1; //mas velocidad
          }
        else pidvalvula=500; //menos velocidad

        
        if (valorvalvula > 0 && valorvalvula <= 2000)
        { valorvalvula = valorvalvula - precision;
          dac.setVoltage(valorvalvula, false);
        }
      }
      else if (presioncuatro > rango2)
      { //enviarnextion("PRESION MAYOR", "t26.txt=");
        if(presioncuatro-rango2>60)
         {pidvalvula=1;
          }
        else pidvalvula=500;
        
        if (valorvalvula >= 0 && valorvalvula < 2000)
        { valorvalvula = valorvalvula + precision;
          dac.setVoltage(valorvalvula, false);
        }
      }

     //-----------------fin regulacion de valvula-------------

      }

    }
    
   
   
    

  }

  else if (botononoff == 0)
  { dac.setVoltage(2000, false);//LA VALVULA SE ABRIRA EN EL INICIO DE LA PLANTA, DESPUES EMPIEZA LA REGULACION... (NUEVO)
    activador("contactorbaja", 0);
    activador("electrovalvula", 0);
    activador("contactoralta", 0);
    enviarnextion("PLANTA DETENIDA", "t26.txt=");
  }






}
