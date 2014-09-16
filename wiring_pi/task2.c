#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

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
		}
	}
	tcsetattr(0, TCSANOW, &initial_settings);
	return 0;
}

