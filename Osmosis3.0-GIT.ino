//PROGRAMA OSMOSIS 3.0 PARA CLIENTE KEEPEX  
//DESARROLLADOR: FRANCISCO REATEGUI

#include <Wire.h> //para la lectura de i2c
#include <Adafruit_ADS1015.h> //libreria de los ADC
#include "SHTSensor.h" //Sensor de temperatura y humedad
#include <Adafruit_GFX.h> //pantalla oled
#include <Adafruit_SSD1306.h> //pantalla oled
#include "PCF8574.h"//expansor I/O
#include <Adafruit_MCP4725.h> //DAC
#include <ArduinoJson.h>
//--------------define-----
#define OLED_RESET 4 //pantalla oled

Adafruit_MCP4725 dac;

Adafruit_SSD1306 display(OLED_RESET);//pantalla oled
SHTSensor sht; //sensor de temperatura y humedad

Adafruit_ADS1115 ads1 (0x49); //presion #1, presion #2, presion #3, presion #4
Adafruit_ADS1115 ads2 (0x4a); //presion estanque, temperaturaagua, tds
Adafruit_ADS1115 ads3 (0x48); //vibracion, corriente, posicion valvula
Adafruit_ADS1115 ads4 (0x4B); ///corriente 1, corriente 2,

PCF8574 pcf8574out(0x26); //es de entrada...se debe cambiar el nombre out por in
//PCF8574 pcf8574out(0x3E); //es de entrada...se debe cambiar el nombre out por in


//PCF8574 pcf8574in(0x38); //direccion expansor input //ahora es el output//original es 20
PCF8574 pcf8574in(0x20);

PCF8574 pcf8574in2(0x24); //direccion expansor input
//PCF8574 pcf8574in2(0x3F); //direccion expansor input


unsigned long timeElapsed;//EXPANSOR I/O

//---------------------------inicio declaracion de variables analogas
unsigned int presionuno; //ADS #1
unsigned int presiondos; //ADS #1
unsigned int presiontres; //ADS #1
unsigned int presioncuatro; //ADS #1

unsigned int presionestanque; //ADS #2
unsigned int temperaturaagua; //ADS #2
unsigned int tds; //ADS #2

unsigned int sensorvibracion; //ADS #3
unsigned int sensorvibracion2; //ADS #3
unsigned int posicionvalvula; //ADS #3

unsigned int sensorcorriente; //ADS #4
unsigned int sensorcorriente2; //ADS #4

float temperatura;
float humedad;

float caudalimetrouno;

//---------------------------fin declaracion de variables analogas


//-------------------------inicio declaracion de variables digitales------------------
//input, las variables necesarias por cada evento fisico son: estadodesistema, actual, estadoanterior, contador y cronometro.




byte puertatablero; // sensor efecto hall en puerta

byte estadofiltrozeolita=0; //es la variable que utiliza el sistema, esta variable tiene mas restricciones para cambiar de estado
byte filtrozeolita; //input del filtro de zeolita
byte estadoanteriorfiltrozeolita=0;
byte contadorfiltrozeolita=0;
unsigned long cronometrofiltrozeolita;


byte estadonivelaltoestanque=0;
byte nivelaltoestanque; //nivel alto del estanque
byte estadoanteriornivelaltoestanque=0;
byte contadornivelaltoestanque=0;
unsigned int cronometronivelaltoestanque;


byte estadonivelbajoestanque=0;
byte nivelbajoestanque; //nivel bajo del estanque
byte estadoanteriornivelbajoestanque;
byte contadornivelbajoestanque=0;
unsigned int cronometronivelbajoestanque;


byte estadopresostatobaja=0; //es el estado que lee el sistema, puede que esta variable tenga mas restricciones para cambiar de estado
byte presostatobaja; //estado actual, estado fisico
byte estadoanteriorpresostatobaja=0;
byte contadorpresostatobaja=0;
unsigned long cronometropresostatobaja; //para detectar desde que se activa el presostato de baja


byte estadopresostatoalta=0; //es el estado que lee el sistema, puede que esta variable tenga mas restricciones para cambiar de estado
byte presostatoalta; //estado actual, estado fisico
byte estadoanteriorpresostatoalta=0;
byte contadorpresostatoalta=0;
unsigned long cronometropresostatoalta; //para detectar desde que se activa el presostato de baja


//variable memflush
byte estadomemflush=0;
unsigned long cronometromemflush; 
unsigned long cuentaregresivamemflush=60000;//este es el tiempo que durará el memflush en milisegundos (por definicion debe durar 4 minutos)

unsigned long cronometrozeolita; //esta variable muestra en pantalla la cantidad de segundos desde el inicio del lavado del filtro zeolita.


//---------------botones agregados---------
byte botondeservicio; //es el boton de servicio que puede servir para dar aviso a keepex...
byte botondepcb; //es un boton auxiliar para el funcionamiento de la placa, no para usuario.

//--------------se agregan guardamotores-------------

byte guardamotor1;
byte guardamotor2;



//output
byte contactoralta;
byte contactorbaja;
byte electrovalvula;
byte clorador;
byte alarmavisual;


byte botononoff;
byte estadoanteriorbotononoff=0;
byte contadorbotononoff=0;

byte botonauxiliar;
byte estadoanteriorbotonauxiliar=0;
byte contadorbotonauxiliar=0;
byte iniciocambiofiltro=0;
unsigned long cronometrocambiofiltro;

byte botonautomatico;



byte iniciodeplanta=0; //el sistema sabrá cuando esté en el estado de encendido con esta variable, cuando el inicio termine vuelve a cero

unsigned long cronometroinicio; //para detectar desde que enciende la planta

unsigned long cronometrorpi=0; //cronometro de la comunicacion con la raspberry, cada x segundo preguntará

unsigned long cronometropantallas=0;
unsigned long cronometronextion=0;


unsigned long tiemporespuesta=0;//para la comunicacion con la rpi

unsigned int horalavado; //para el lavado de las membranas.

//-------------------------fin declaracion de variables digitales------------------

//------------inicio variables string-----------------
String reporte; //para ver los valores en el puerto comm del pc
//------------fin variables string-----------------
//----------------------inicio declaracion JSON-----------------
StaticJsonBuffer<500> jsonBuffer; //DECLARACION DE BUFFER 
JsonObject& data = jsonBuffer.createObject();

StaticJsonBuffer<500> jsonBuffer2; //segundo JSON 
JsonObject& question = jsonBuffer2.createObject(); //segundo JSON



//----------------------fin declaracion JSON-----------------

//------------------inicio declaracion electrovalvula----------
int rango1=880; //rango bajo 
byte direccionrango1=0; //direccion en la eeprom de la direccion
int rango2=910;
byte direccionrango2=10;
int valorvalvula=3000; //original 1200
int retrovalorvalvula; //esta variable ya se lee antes y se llama posicion valvula
int precision=5; //velocidad de valvula
unsigned long cronometrovalvula=0;
int pidvalvula=300;

int valorsensor; //NO SE SI SE OCUPA
int rebootvalvula=1; //para empezar siempre desde la posicion de la valvula correcta


//------------------fin declaracion electrovalvula----------
