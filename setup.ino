
void setup() {

  //--------------------------------inicio setup expansor I/O --------------------
  Wire.begin();
  pinMode(LED_BUILTIN, OUTPUT);


  pcf8574out.pinMode(P0, OUTPUT); //se declaran los pines como salida
  pcf8574out.pinMode(P1, OUTPUT);
  pcf8574out.pinMode(P2, OUTPUT);
  pcf8574out.pinMode(P3, OUTPUT);
  pcf8574out.pinMode(P4, OUTPUT);
  pcf8574out.pinMode(P5, OUTPUT);
  pcf8574out.pinMode(P6, OUTPUT);
  pcf8574out.pinMode(P7, OUTPUT);
  pcf8574out.begin();              //inicializacion del integrado
  pcf8574out.digitalWrite(P0, LOW); // inician todos los pines en low
  pcf8574out.digitalWrite(P1, LOW);
  pcf8574out.digitalWrite(P2, LOW);
  pcf8574out.digitalWrite(P3, LOW);
  pcf8574out.digitalWrite(P4, LOW);
  pcf8574out.digitalWrite(P5, LOW);
  pcf8574out.digitalWrite(P6, LOW);
  pcf8574out.digitalWrite(P7, LOW);


  pcf8574in.pinMode(P0, OUTPUT);  //estos pines son de salida, pero deben mantenerse en alto
  pcf8574in.pinMode(P1, OUTPUT);  //por lo que se declaran en output, se ponen en alto, y luego se declaran como input
  pcf8574in.pinMode(P2, OUTPUT);
  pcf8574in.pinMode(P3, OUTPUT);
  pcf8574in.pinMode(P4, OUTPUT);
  pcf8574in.pinMode(P5, OUTPUT);
  pcf8574in.pinMode(P6, OUTPUT);
  pcf8574in.pinMode(P7, OUTPUT);
  pcf8574in.begin();             //inicializacion del integrado
  pcf8574in.digitalWrite(P0, HIGH); //se ponen todos los pines en alto
  pcf8574in.digitalWrite(P1, HIGH);
  pcf8574in.digitalWrite(P2, HIGH);
  pcf8574in.digitalWrite(P3, HIGH);
  pcf8574in.digitalWrite(P4, HIGH);
  pcf8574in.digitalWrite(P5, HIGH);
  pcf8574in.digitalWrite(P6, HIGH);
  pcf8574in.digitalWrite(P7, HIGH);

  pcf8574in.pinMode(P0, INPUT);  //finalmente quedan declarados como input, (ver mas detalle en datasheet, "quasi direccional")
  pcf8574in.pinMode(P1, INPUT);
  pcf8574in.pinMode(P2, INPUT);
  pcf8574in.pinMode(P3, INPUT);
  pcf8574in.pinMode(P4, INPUT);
  pcf8574in.pinMode(P5, INPUT);
  pcf8574in.pinMode(P6, INPUT);
  pcf8574in.pinMode(P7, INPUT);

  pcf8574in2.pinMode(P0, OUTPUT);  //estos pines son de salida, pero deben mantenerse en alto
  pcf8574in2.pinMode(P1, OUTPUT);  //por lo que se declaran en output, se ponen en alto, y luego se declaran como input
  pcf8574in2.pinMode(P2, OUTPUT);
  pcf8574in2.pinMode(P3, OUTPUT);
  pcf8574in2.pinMode(P4, OUTPUT);
  pcf8574in2.pinMode(P5, OUTPUT);
  pcf8574in2.pinMode(P6, OUTPUT);
  pcf8574in2.pinMode(P7, OUTPUT);
  pcf8574in2.begin();             //inicializacion del integrado
  pcf8574in2.digitalWrite(P0, HIGH); //se ponen todos los pines en alto
  pcf8574in2.digitalWrite(P1, HIGH);
  pcf8574in2.digitalWrite(P2, HIGH);
  pcf8574in2.digitalWrite(P3, HIGH);
  pcf8574in2.digitalWrite(P4, HIGH);
  pcf8574in2.digitalWrite(P5, HIGH);
  pcf8574in2.digitalWrite(P6, HIGH);
  pcf8574in2.digitalWrite(P7, HIGH);

  pcf8574in2.pinMode(P0, INPUT);  //finalmente quedan declarados como input, (ver mas detalle en datasheet, "quasi direccional")
  pcf8574in2.pinMode(P1, INPUT);
  pcf8574in2.pinMode(P2, INPUT);
  pcf8574in2.pinMode(P3, INPUT);
  pcf8574in2.pinMode(P4, INPUT);
  pcf8574in2.pinMode(P5, INPUT);
  pcf8574in2.pinMode(P6, INPUT);
  pcf8574in2.pinMode(P7, INPUT);










  //--------------------------------fin setup expansor I/O --------------------
  Serial.begin(115200); //puerto comm del PC

  //solo se ejecuta la primera vez que se configura la pantalla nextion
  /*
    Serial1.begin(9600);
    delay(200);
    Serial1.print("bauds=115200");
    Serial1.write(0xff);  // We always have to send this three lines after each command sent to nextion.
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.end();
  */

  Serial1.begin(115200);

  //descripcion de ganancias del ADS, cada inicializacion de ads tiene su ganancia.
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit =  0.1875mV (default)
  ads1.setGain(GAIN_TWOTHIRDS);        // 1x gain   +/- 4.096V  1 bit =  0.125mV
  ads2.setGain(GAIN_TWOTHIRDS);        // 1x gain   +/- 4.096V  1 bit =  0.125mV
  ads3.setGain(GAIN_TWOTHIRDS);        // 1x gain   +/- 4.096V  1 bit =  0.125mV
  ads4.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit =  0.125mV


  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit =  0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit =  0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit =  0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit =  0.0078125mV
  ads1.begin(); // inicialización del ads #1
  ads2.begin(); // inicialización del ads #2
  ads3.begin(); // inicialización del ads #3
  ads4.begin(); // inicialización del ads #4

  //---------------------------------------fin ads--------------------

  //-------------------inicio setup sensor de t y rh---------------
  if (sht.init()) {
    //Serial.print("init(): success\n");
  } else {
    //Serial.print("init(): failed\n");
  }
  sht.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM); // only supported by SHT3x
  //-------------------fin setup sensor de t y rh---------------

  //----------------------------inicio setup pantalla oled--------------
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //inicio pantalla oled

  display.clearDisplay();

  // presentacion de pantalla de inicio, se puede eliminar sin problemas
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("LYTHIUM");
  display.setCursor(0, 20);
  display.println("2019");
  display.display();
  delay(1000);


  //----------------------------fin setup pantalla oled--------------



  //------------------botones auxiliares----------------------------
  pinMode(3, INPUT); //declaracion del boton onoff
  pinMode(2, INPUT); //declaracion del boton auxiliar
  pinMode(4, INPUT); //declaracion del boton auxiliar


  //-------------------inicio setup dac------------
  dac.begin(0x63); //original 60
  // dac.setVoltage(0, false); //4095 tengo el maximo

  //-------------------fin setup dac------------

}
