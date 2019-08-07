void detectarcambioestadopines(void)
{
  //rutina para detectar el cambio-----------------------------------BOTON ON OFF----
  if (estadoanteriorbotononoff != botononoff) {
    contadorbotononoff++;
    int validarpar = contadorbotononoff % 2;
    if (validarpar == 1)
    {
      iniciodeplanta = 1;
      cronometroinicio = millis();
    }
    estadoanteriorbotononoff = botononoff;
  }


//-------------------------------------------------------------boton auxiliar------
 if (estadoanteriorbotonauxiliar != botonauxiliar) {
    contadorbotonauxiliar++;
    int validarpar = contadorbotonauxiliar % 2;
    if (validarpar == 1)
    {
     cronometrocambiofiltro = millis();
    }
    estadoanteriorbotonauxiliar = botonauxiliar;
  }
else {
    if (millis() - cronometrocambiofiltro > 3000 && botonauxiliar == 1) //aqui detecto si presionaron el boton por mas de tres segundo
    {
      iniciocambiofiltro=1;
    }
    else iniciocambiofiltro = 0;
  }


//--------------------------------------------------------------------------------


  //rutina para detectar el cambio y un tiempo en ese estado--------------------PRESOSTATO BAJA
  if (estadoanteriorpresostatobaja != presostatobaja) {
    contadorpresostatobaja++;
    int validarpar = contadorpresostatobaja % 2;
    if (validarpar != 1)
    {
      cronometropresostatobaja = millis();
    }

    estadoanteriorpresostatobaja = presostatobaja;
  }
  else {
    if (millis() - cronometropresostatobaja > 4000 && presostatobaja == 0) //si el presostato de baja se mantiene 4 segundos en bajo, recien en ese momento se cambia el estado.
    {
      estadopresostatobaja = 1;
    }
    else estadopresostatobaja = 0;
  }
  //fin rutina para detectar el cambio y un tiempo en ese estado------------------------------------------------

  //--------------------------------------------------------------------------------PRESOSTATO ALTA
  if (estadoanteriorpresostatoalta != presostatoalta) {
    contadorpresostatoalta++;
    int validarpar = contadorpresostatoalta % 2;
    if (validarpar != 1)
    {
      cronometropresostatoalta = millis();
    }

    estadoanteriorpresostatoalta = presostatoalta;
  }
  else {
    if (millis() - cronometropresostatoalta > 4000 && presostatoalta == 0) //si el presostato de baja se mantiene 4 segundos en bajo, recien en ese momento se cambia el estado.
    {
      estadopresostatoalta = 1;
    }
    else estadopresostatoalta = 0;
  }

  //-------------------------------------------------------------------      ----------


  //--------------------------------------------------------------------------------FILTRO ZEOLITA
  if (estadoanteriorfiltrozeolita != filtrozeolita) {
    contadorfiltrozeolita++;
    int validarpar = contadorfiltrozeolita % 2;
    if (validarpar == 1) //cuando se quiere detectar de cero a uno se pone "==1", cuando se quiere dectectar el cambio de uno a cero se pone"!=1"
    {
      cronometrofiltrozeolita = millis();
      cronometrozeolita=millis();
    }
    else
    {
      iniciodeplanta = 1; //esta instruccion se va a activar cuando el filtro de zeolita termine su lavado, y solo se activará una sola vez (por cada lavado)
      cronometroinicio = millis(); //despues del lavado de filtro de zeolita es importante y necesario volver a partir, por eso el contador de inicio de la planta vuelve a cero.
    //  estadomemflush = 1;          //ESTA LINEA SE COMENTA PARA QUE NO INICIE EL LAVADO DE MEMBRANAS DESPUES DEL FILTRO DE ZEOLITA
    //  cronometromemflush = millis(); //despues del lavado de zeolita viene el lavado de membranas //ESTA LINEA SE COMENTA PARA QUE NO INICIE EL LAVADO DE MEMBRANAS DESPUES DEL FILTRO DE ZEOLITA
    }
    estadoanteriorfiltrozeolita = filtrozeolita;
  }
  else {
    if (millis() - cronometrofiltrozeolita > 2000 && filtrozeolita == 1) //si el filtro de zeolita se mantiene X segundos en bajo, recien en ese momento se cambia el estado para evitar rebotes.
    {
      estadofiltrozeolita = 1;
     
    }
    else estadofiltrozeolita = 0;
  }

  //----------------------------------------------------------------------------------


  //--------------------------------------------------------------------------------NIVEL ALTO ESTANQUE--------
  if (estadoanteriornivelaltoestanque != nivelaltoestanque) {
    contadornivelaltoestanque++;
    int validarpar = contadornivelaltoestanque % 2;
    if (validarpar == 1) //cuando se quiere detectar de cero a uno se pone "==1", cuando se quiere dectectar el cambio de uno a cero se pone"!=1"
    {
      cronometronivelaltoestanque = millis();
    }

    else
    {
      iniciodeplanta = 1; //esta instruccion se va a activar cuando el filtro de zeolita termine su lavado, y solo se activará una sola vez (por cada lavado) 
      cronometroinicio = millis(); //despues del lavado de filtro de zeolita es importante y necesario volver a partir, por eso el contador de inicio de la planta vuelve a cero.
      cronometronivelaltoestanque = millis(); //despues del lavado de zeolita viene el lavado de membranas
    }

    estadoanteriornivelaltoestanque = nivelaltoestanque;
  }
  else {
    if (millis() - cronometronivelaltoestanque > 4000 && nivelaltoestanque == 1) //si
    {
      estadonivelaltoestanque = 1;
    }
    else if (millis() - cronometronivelaltoestanque > 4000 && nivelaltoestanque == 0)
    {
      estadonivelaltoestanque = 0;
      
      
    }


    //  else estadonivelaltoestanque=0; //quizas esto lo saque porque ya está en la condicional anterior
  }

  //----------------------------------------------------------------------------------












}

