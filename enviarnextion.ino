void enviarnextion (String frase, String casilla)
{
  //esta rutina envia informacion a la pantalla nextion cada 2.5 segundos, el tiempo puede variar, la idea es no saturar el puerto de comunicacion innecesariamente.
   if(millis()-cronometronextion>2500)
    {
    Serial1.print(casilla);
    Serial1.print("\"");
    Serial1.print(frase);
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    cronometronextion=millis();  
    }

}

