
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFly.h>
#include "HTTPClient.h"

#define SSID      "wifiJarvis"
#define KEY       "1234Jarvis"
// WIFLY_AUTH_OPEN / WIFLY_AUTH_WPA1 / WIFLY_AUTH_WPA1_2 / WIFLY_AUTH_WPA2_PSK
#define AUTH      WIFLY_AUTH_WPA2_PSK
#define LINE 2
#define COLUMN 1
#define WORD 20
#define HTTP_GET_URL "http://10.42.0.1:8890/sparql?query=PREFIX+ns%3A+<http%3A%2F%2Fexample.org%2Fns%23>%0D%0Aselect+%3Fprice%0D%0A%7B+<http%3A%2F%2Fexample%2Fbook1>++ns%3Aprice++%3Fprice+%7D&format=text%2Fcsv"
#define HTTP_GET_URL_WRITE "http://10.42.0.1:8890/sparql?update=PREFIX+ns%3A+<http%3A%2F%2Fexample.org%2Fns%23>%0D%0AINSERT+DATA%0D%0A%7B+GRAPH+<http%3A%2F%2Fexample%2FbookStore>+%7B+<http%3A%2F%2Fexample%2Fbook1>++ns%3Aprice++42+%7D+%7D"
#define HTTP_GET_URL_CLEAR "http://10.42.0.1:8890/sparql?update=CLEAR+GRAPH+<http%3A%2F%2Fexample%2FbookStore>"
// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX

SoftwareSerial uart(2, 3);
WiFly wifly(uart);
HTTPClient http;
char get;
int x = 0;
int y = 0;
int c = 0;
int i;
int j;
bool isWord = false;
char last = '0' ;
bool  isBody = false;
char arrayString[LINE][COLUMN][WORD] ;

void setup() {
  Serial.begin(9600);    
  Serial.println("------- WIFLY HTTP --------");
  
  
  uart.begin(9600);         // WiFly UART Baud Rate: 9600
  // Wait WiFly to init
//  delay(3000);

  // check if WiFly is associated with AP(SSID)
  if (!wifly.isAssociated(SSID)) {
    while (!wifly.join(SSID, KEY, AUTH)) {
      Serial.println("Failed to join " SSID);
      Serial.println("Wait 0.1 second and try again...");
      delay(100);
    }
    
    wifly.save();    // save configuration, 
  }  
}

void loop() {

//write
  while (http.get(HTTP_GET_URL_WRITE, 10000) < 0) {
  }
  while (wifly.receive((uint8_t *)&get, 1, 1000) == 1) {
    //Serial.print(get);
  }
  
  Serial.println("\r\nTry to get url - " HTTP_GET_URL);
  Serial.println("------------------------------");

  while (http.get(HTTP_GET_URL, 10000) < 0) {
  }
/////////////READ CSV
 /*  x = 0;
   y = 0;
    c = 0;
   isWord = false;
   last = '0' ;
   isBody = false;*/
  while (wifly.receive((uint8_t *)&get, 1, 1000) == 1) {
     Serial.print(get); //42
  /*  if(! isBody){
      
      //Serial.print(get);
      if(get == '"'){
          isBody = true;
          isWord = true;
        }          
    }else{
          if(isWord){
            if(get == '"' ){
                isWord = false;
                arrayString[y][x][c] = '\0' ;
            }else{
             
               if(c < (WORD-1)){
                 arrayString[y][x][c] = get ;
                 c++;
               }
            }
          }else{ //notword
            if(get == '"' ){
              isWord = true; 
              x++;
              c=0;
            }
          }
          if(get == '\n'){
              y++;
              x=0;
              c=0;
           }
    }*/
  }
  
 /* for(i=0;i<5;i++){  
    for(j=0;j<3;j++){
    Serial.println(&arrayString[i][j][0]);
    }
  }*/

  ///CLEAR GRAPH
  while (http.get(HTTP_GET_URL_CLEAR, 10000) < 0) {
  }
  while (wifly.receive((uint8_t *)&get, 1, 1000) == 1) {
   // Serial.print(get);
  }
}
