#include <stdio.h>
#include <wiringPi.h>

#define A	22
#define AA	23
#define B	24
#define BB	25

#define TRIG	28
#define ECHO	29

#define SW	21
#define TIME	80
#define STEPS	100
int change = 0;
///////////////////////////FUNCTION/////////////////////////////
void initialize(void);
void iris_reset(int a, int b, int c, int d, int e, int f);

void iris_control(int a, int b, int c, int d);
void modeSwitch(void);
void modeChange(void);

void iris_open(void);
void iris_close(void);
////////////////////////////////////////////////////////////////

void initialize(void)
{
	pinMode(TRIG,OUTPUT);
	pinMode(ECHO,INPUT);	

	pinMode(A,OUTPUT);
	pinMode(B,OUTPUT);
	pinMode(AA,OUTPUT);
	pinMode(BB,OUTPUT);
	pinMode(SW,INPUT);

	iris_reset(1,0,0,0,0,0);	
}
void iris_reset(int a, int b, int c, int d, int e, int f)
{
	digitalWrite(A,a);
	digitalWrite(AA,b);
	digitalWrite(B,c);
	digitalWrite(BB,d);
	digitalWrite(TRIG,e);
	digitalWrite(ECHO,f);
}

void iris_control(int a, int b, int c, int d)
{
	digitalWrite(A,a);
	digitalWrite(AA,b);
	digitalWrite(B,c);
	digitalWrite(BB,d);
}

void iris_open(void)
{
	iris_control(1,0,1,0);
	delay(TIME);
	iris_control(0,1,1,0);
	delay(TIME);
	iris_control(0,1,0,1);
	delay(TIME);
	iris_control(1,0,0,1);
	delay(TIME);
	
}

void iris_close(void)
{
	
	iris_control(1,0,0,1);
	delay(TIME);
	iris_control(0,1,0,1);
	delay(TIME);
	iris_control(0,1,1,0);
	delay(TIME);
	iris_control(1,0,1,0);
	delay(TIME);
}
void modeChange(void)
{
	if(digitalRead(ECHO) == 0)
	{
		printf("open\n");
		iris_open();
	}
	else
	{
		printf("close\n");
		iris_close();
	}
}
void modeSwitch(void)
{
	if(change == 0)
	{
		change=1;	
		printf("open\n");
		iris_open();
	}
	else
	{
		printf("close\n");
		iris_close();
	}
}
int main(void)
{	
	if(wiringPiSetup() == -1) 	
		return 1;

	initialize();
		//wiringPiISR(29, INT_EDGE_RISING, modeChange);
	while(1)
	{

	iris_control(1,0,0,0);
	delay(TIME);
	iris_control(1,0,1,0);
	delay(TIME);
	iris_control(0,1,1,0);
	delay(TIME);
	iris_control(0,1,0,1);
	delay(TIME);
	iris_control(1,0,0,1);
	delay(TIME);


		/*if(change == 0)
		{
		        printf("open\n");
			iris_open();
		}
		else
		{
		        printf("close\n");
			iris_close();
		}*/
	}

	return 0;
}
