#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <wiringPi.h>

struct termios initial_settings,new_settings;
int main(int argc, char **argv) {

	tcgetattr(0,&initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 0;
	new_settings.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
	while(1) {
		int n = getchar();
		if(n != EOF) {
			int key = n;
			if(key == 27 || key == 10) {
				break;
			}
			printf("[%c:%d]\n",key,key);
			if(key == 97 || key == 101 || key == 105 || key == 111 || key == 117
			|| key == 65 || key == 69 || key == 73 || key == 79 || key == 85) {
				int pin = 7;
				wiringPiSetup();
				pinMode(pin, OUTPUT);
				digitalWrite(pin, HIGH);

				sleep(1);
				digitalWrite(pin, LOW);
			}else{
				if((key >65 && key <=90)||(key >97 && key <=122)){	
					int pin = 0;
					wiringPiSetup();
					pinMode(pin, OUTPUT);
					digitalWrite(pin, HIGH);

					sleep(1);
					digitalWrite(pin, LOW);
					}
			}

		}
	}
	tcsetattr(0, TCSANOW, &initial_settings);
	return 0;
}

