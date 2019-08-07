void activador(String palabra, bool valor){

if(palabra=="contactoralta"){
  pcf8574out.digitalWrite(P0,valor);
  contactoralta=valor;
  return;
}

if(palabra=="electrovalvula"){
  pcf8574out.digitalWrite(P2,valor);
  electrovalvula=valor;
  return;
}

if(palabra=="contactorbaja"){
  pcf8574out.digitalWrite(P1,valor);
  contactorbaja=valor;
  return;
}


  
  
}

