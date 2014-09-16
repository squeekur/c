#include <stdio.h>
#include <wiringPi.h>

int main()
{
	printf("Raspberry Pi blink\n");
	int pin = 7;

	wiringPiSetup();
	pinMode(pin, OUTPUT);

	int i;
	for (i=0;i<10;i++) {

		printf("led on\n");
		digitalWrite(pin, HIGH);

		sleep(1);

		printf("led off\n");
		digitalWrite(pin, LOW);

		sleep(1);
	}
	return 0;
}
