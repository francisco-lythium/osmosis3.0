void comunicacionrpi(void){
    if(millis()-cronometrorpi>5000)
    {
    cronometrorpi=millis();  
    question["puerta"] = "que hora es";
    question.printTo(Serial);
    }

 //-----------------------codigo nuevo ----------------------------------------------
 tiemporespuesta = millis();
  do { 
    
    if(Serial.available())
    {
    StaticJsonBuffer<600> jsonBafer;
    JsonObject& roots = jsonBafer.parseObject(Serial);
      if (!roots.success()) 
      {
      return;
      }
  
  //--------------------fin declaracion--------------------------------------------------

} 
//-------------------------fin codigo nuevo------------------------------------------------
  
}while(millis()-tiemporespuesta<300);

}

