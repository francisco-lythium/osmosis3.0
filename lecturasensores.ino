void lecturasensores(void)
{
  
  //presionuno    = map(ads1.readADC_SingleEnded(0),460,30000,0,58);
 // presiondos    = map(ads1.readADC_SingleEnded(1),460,30000,0,58);
 // presiontres   = map(ads1.readADC_SingleEnded(2),460,30000,0,58);
 // presioncuatro = map(ads1.readADC_SingleEnded(3),480,29400,0,1450); //1450 original //33600 original
  presionuno    = ads1.readADC_SingleEnded(0);
  presiondos    = ads1.readADC_SingleEnded(1);
  presiontres   = ads1.readADC_SingleEnded(2);
  presioncuatro = ads1.readADC_SingleEnded(3); //1450 original //33600 original

 //presionestanque    = map(ads2.readADC_SingleEnded(0),460,10000,0,880);
  presionestanque    = ads2.readADC_SingleEnded(0);
  temperaturaagua    = ads2.readADC_SingleEnded(1);
  tds                = ads2.readADC_SingleEnded(2);
 
 // temperaturaagua    = map(ads2.readADC_SingleEnded(1),0,32000,0,50);
 // tds                = map(ads2.readADC_SingleEnded(2),0,32000,0,2000);
 // sensorvibracion    = map(ads3.readADC_SingleEnded(0),460,30000,0,30); //ADS #37
 // sensorvibracion    = map(ads3.readADC_SingleEnded(0),460,30000,0,30); //ADS #37

  sensorvibracion    = ads3.readADC_SingleEnded(0); //ADS #37
  sensorvibracion2    = ads3.readADC_SingleEnded(1);
  posicionvalvula    = ads3.readADC_SingleEnded(2); //ADS #3 valor antiguo 17536
 
 // posicionvalvula    = map(ads3.readADC_SingleEnded(1),618,24391,0,2000); //ADS #3 valor antiguo 17536
  
  sensorcorriente    = ads4.readADC_SingleEnded(0); //ADS #4
  sensorcorriente2    = ads4.readADC_SingleEnded(1); //ADS #4
 
 
 // sensorcorriente    = map(ads3.readADC_SingleEnded(3),460,30000,0,30); //ADS #3

  sht.readSample();
  
  temperatura        = sht.getTemperature();
  humedad            = sht.getHumidity();


  puertatablero       =!pcf8574in.digitalRead(P0); //la entradas de este conjunto son negadas porque el pcf8574 mantiene sus estados en pullup
  filtrozeolita       =!pcf8574in.digitalRead(P1);
  nivelaltoestanque   =!pcf8574in.digitalRead(P2);
  nivelbajoestanque   =!pcf8574in.digitalRead(P3);
  presostatoalta      =!pcf8574in.digitalRead(P4);
  presostatobaja      =!pcf8574in.digitalRead(P5);
  botondeservicio     =!pcf8574in.digitalRead(P6);
  botondepcb          =!pcf8574in.digitalRead(P7);

  guardamotor1        =!pcf8574in2.digitalRead(P0);
  guardamotor2        =!pcf8574in2.digitalRead(P1);
  


  

  botononoff          = digitalRead(3);
  botonauxiliar       = digitalRead(2);
  botonautomatico     = digitalRead(4);
/*
 reporte = " /presion 1: "+String(presionuno) +" /presion 2: "+String(presiondos)+
                  " /presion 3: "+String(presiontres)+" /presion 4: "+String(presioncuatro)+
                  " /presion estanque: "+String(presionestanque)+" /t° agua: "+String(temperaturaagua)+
                  " /tds: "+String(tds)+" /Sensor Vibracion: "+String(sensorvibracion)+
                  " /sensor corriente: "+String(sensorcorriente)+" /t° ambiente: "+String(temperatura)+
                  " /rh ambiente: "+String(humedad);

*/
 data["presion1"] = presionuno;
 data["presion2"] = presiondos;
 data["presion3"] = presiontres;
 data["presion4"] = presioncuatro;
 data["estanque"] = presionestanque;
 data["tempagua"] = temperaturaagua;
 data["tds"] = tds;
 
 data["tempambiente"] = temperatura; //LO SAQUE PORQUE ME DABA ERROR EN EL JSON 
 data["humedad"] = humedad;

 data["puerta"] = puertatablero;
 data["zeolita"] = filtrozeolita;
 data["nivelalto"] = nivelaltoestanque;
 data["nivelbajo"] = nivelbajoestanque;
 data["presostatoalta"] = presostatoalta;
 data["presostatobaja"] = presostatobaja;
 
 data["onoff"] = botononoff;
 data["auxiliar"] = botonauxiliar;
 
 return;
  
}
