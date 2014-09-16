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
	
	int pin = 2;
	wiringPiSetup();
	pinMode(pin, INPUT);
	int button;
	

	
	while(1) {
		int n;
		button = digitalRead(pin);
		printf("%d\n", button);
		sleep(1);
		if((n = getchar()) != EOF) {
			int key = n;
			if(key == 27 || key == 10) {
				break;
			}
					
			}
	}

		
	tcsetattr(0, TCSANOW, &initial_settings);
	return 0;
}

