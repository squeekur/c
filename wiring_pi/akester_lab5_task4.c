#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <wiringPi.h>

struct termios initial_settings,new_settings;

int newGame[100]; //global array of colors
int counter = 0;  //global counter of array items

  int pinRed   = 7;
  int pinGreen = 0;
  int pinBlue  = 4;
  int pinWhite = 5; //hard coded pin values

void blinkLights(int pinRed, int pinGreen, int pinBlue, int pinWhite){
int i; 
for(i = 0; i < 4; i++){ 
  digitalWrite(pinRed, HIGH);
  digitalWrite(pinGreen, HIGH);
  digitalWrite(pinBlue, HIGH);
  digitalWrite(pinWhite, HIGH);
  delay(100);
  digitalWrite(pinRed, LOW);
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinBlue, LOW);
  digitalWrite(pinWhite, LOW);
  delay(100);
 }
}

void startOver(){
  blinkLights(pinRed, pinGreen, pinBlue, pinWhite);
  int i = 0;
  for(i; i<counter; i++){
    newGame[i] = 0;
  }
  counter = 0;
}

void setPins(int pinRed, int pinGreen, int pinBlue, int pinWhite){
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinWhite, OUTPUT);
}

int randomNumber(){
  int pin;
  int r = rand()%4;
  if(r == 0) {
   pin = 7;
  }else {
   if(r == 1) {
   pin = 0;
   }else {
   if(r == 2) {
   pin = 4;
   }else {
   if(r == 3) {
   pin = 5;
   }}}}
  return pin;
}

void showNewColor(){
  int pin = randomNumber();
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(1000);
  newGame[counter] = pin;
  counter++;
}

void repeatColors(){
  int i = 0;
  for(i; i<counter; i++){
    digitalWrite(newGame[i], HIGH);
    delay(1000);
    digitalWrite(newGame[i], LOW);
    delay(1000);
  }
  showNewColor();
}

void declareTermiosCrap(){
	tcgetattr(0,&initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 0;
	new_settings.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
}

int keyboard(){
  while(1) {
      int n;
      if((n = getchar()) != EOF) {
        int key = n;
        if(key == 27 || key == 10) {
          exit(EXIT_SUCCESS);
			}
			if(key == 97 || key == 115 || key == 100 || key == 101){
         return key;
			}else{
        printf("Please use 'a' 's' 'd' 'e' as inputs\n");
			}
		}
	}
}

void verify(){
  int guess[100];
  int key;
  int i = 0;
  while(i<counter){
    key = keyboard();
    key = convert(key);
    guess[i] = key;
    i++;
  }
  int j = 0;
  while(j<counter){
    if(newGame[j] == guess[j]){
      j++;
      printf("correct\n");
    }else{
      printf("wrong\n");
      startOver();
      repeatColors();
      verify();
   }
  }
  printf("go again\n");
   repeatColors();
   verify();
}


int convert(int key){
  if(key == 97)
    return 7;
  if(key == 115)
    return 0;
  if(key == 100)
    return 4;
  if(key == 101)
    return 5;
}


int main(int argc, char **argv) {

  declareTermiosCrap();
  wiringPiSetup();
  setPins(pinRed, pinGreen, pinBlue, pinWhite);
  blinkLights(pinRed, pinGreen, pinBlue, pinWhite);
  repeatColors();
  verify();
  

	tcsetattr(0, TCSANOW, &initial_settings);
	return 0;
}

