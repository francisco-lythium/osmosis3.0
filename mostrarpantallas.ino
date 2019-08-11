void mostrarpantallas(void)
{//  Serial.println(reporte);
    if(millis()-cronometropantallas>1500) //original 2000
    {
    cronometropantallas=millis();  
    data.printTo(Serial);
 //  Serial.println(); //en la rpi puedo especificar que el mensaje empieza con "{" y termina co "}", asi evito el ponerle el println al final
 
 //------------------inicio imprimir en lcd nextion---------
    Serial1.print("n0.val=");  // Sensor presion uno
    Serial1.print(presionuno);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n1.val=");  // Sensor presion dos
    Serial1.print(presiondos);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n2.val=");  // Sensor presion tres
    Serial1.print(presiontres);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n3.val=");  // Sensor presion cuatro
    Serial1.print(presioncuatro);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n4.val=");  // Sensor presion estanque
    Serial1.print(presionestanque);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n5.val=");  //  temperatura del agua
    Serial1.print(temperaturaagua);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n6.val=");  // tds del agua
    Serial1.print(tds);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n7.val=");  // tds del agua
    Serial1.print(sensorvibracion);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n8.val=");  // tds del agua
    Serial1.print(sensorcorriente);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n9.val=");  // tds del agua
    //Serial1.print(posicionvalvula);  // ORIGINAL, VOLVER A SU ESTADO NORMAL
    Serial1.print( map(ads3.readADC_SingleEnded(2),4899,23300,0,100));
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n10.val=");  // temperatura ambiente
    Serial1.print(temperatura);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n11.val=");  // temperatura ambiente
    Serial1.print(humedad);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("t31.txt=");  // temperatura ambiente
   Serial1.print("\"");
    Serial1.print(caudalimetrouno);  // 
    Serial1.print("\"");
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n13.val=");  // temperatura ambiente
    Serial1.print(puertatablero);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n14.val=");  // temperatura ambiente
    Serial1.print(filtrozeolita);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n15.val=");  // temperatura ambiente
    Serial1.print(nivelaltoestanque);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n16.val=");  // temperatura ambiente
    Serial1.print(nivelbajoestanque);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);
         
    Serial1.print("n17.val=");  // temperatura ambiente
    Serial1.print(presostatoalta);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n18.val=");  // temperatura ambiente
    Serial1.print(presostatobaja);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);
        
    Serial1.print("n19.val=");  // temperatura ambiente
    Serial1.print(botononoff);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);
    
    Serial1.print("n20.val=");  // temperatura ambiente
    Serial1.print(botonauxiliar);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n21.val=");  // temperatura ambiente
    Serial1.print(contactoralta);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n22.val=");  // temperatura ambiente
    Serial1.print(contactorbaja);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n23.val=");  // temperatura ambiente
    Serial1.print(electrovalvula);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n24.val=");  // temperatura ambiente
    Serial1.print(clorador);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    Serial1.print("n25.val=");  // temperatura ambiente
    Serial1.print(alarmavisual);  // 
    Serial1.write(0xff);Serial1.write(0xff);Serial1.write(0xff);

    
display.clearDisplay();

  // text display tests
  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("1:");
  display.println(presionuno);
  
  display.setCursor(0,9);
  display.print("2:");
  display.println(presiondos);
  display.setCursor(0,18);

    display.print("3:");
  display.println(presiontres);
  display.setCursor(0,27);

  
  display.print("4:");
  display.println(presioncuatro);
  display.setCursor(0,36);

  display.print("A:");
  display.println(presionestanque);
  display.setCursor(0,45);

  display.print("B:");
  display.println(temperaturaagua);
  display.setCursor(0,54);

 display.print("C:");
  display.println(tds);
  display.setCursor(0,63);


 display.setCursor(44,0);
  display.print("X:");
  display.println(sensorvibracion);
  
 display.setCursor(44,9);
  display.print("Y:"); 
  display.println(sensorvibracion2);
  

  display.setCursor(44,18);
  display.print("Z:");
  display.println(posicionvalvula);
  

 display.setCursor(44,27);
  display.print("S:");
 display.println(sensorcorriente);
  

 display.setCursor(44,36);
  display.print("T:");
  display.println(sensorcorriente2);

display.setCursor(44,45);

display.print("I:");  
display.print(puertatablero);
display.print(filtrozeolita);
display.print(nivelaltoestanque);
display.print(nivelbajoestanque);
display.print(presostatobaja);
display.print(presostatoalta);
display.print(botondeservicio);
display.print(botondepcb);
display.print("'");
display.print(guardamotor1);
display.print(guardamotor2);


display.setCursor(44,54);
display.print("O:"); 
display.print(contactoralta);
display.print(contactorbaja);
display.print(electrovalvula);
display.print(clorador);
display.print(alarmavisual);
display.print("'");
display.print(botononoff);
display.print(botonauxiliar);
display.print(botonautomatico);



display.setCursor(88,0);
  display.print("T:");
  display.println(temperatura,1);

display.setCursor(88,9);
  display.print("H:");
  display.println(humedad,1);

display.setCursor(88,18);
  display.print("v:");
  display.println(valorvalvula,1);
  
display.setCursor(88,27);
  display.print("F:");
  display.println(caudalimetrouno);
  
  

 // display.print(contadorpresostatobaja);
  display.display();
  
 //-------------------fin imprimir en lcd nextion-----------
}
}
