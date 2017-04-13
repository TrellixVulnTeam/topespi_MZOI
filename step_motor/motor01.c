#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#define A	22
#define AA	23
#define B	24
#define BB	25

#define PWM1	27
#define PWM2	29
#define PWMSET	1
#define TIME	500	
#define STEPS	1
int STEP_STATUS = 0;
int ON_OFF_STATUS;      // iris_ON = 1, iris_OFF = 0;
int STEP_TABLE[4][4]= { 
			{1,0,1,0},
			{0,1,1,0},
			{0,1,0,1},
			{1,0,0,1}
	 	      };

///////////////////////////FUNCTION/////////////////////////////
void initialize(void);

void iris_reset(int a, int b, int c, int d);

void iris_control(int a, int b, int c, int d);

void iris_open(int steps);
void iris_close(int steps);
////////////////////////////////////////////////////////////////

void initialize(void)
{
	pinMode(A,OUTPUT);
	pinMode(B,OUTPUT);
	pinMode(AA,OUTPUT);
	pinMode(BB,OUTPUT);
	pinMode(PWM1,INPUT);
	pinMode(PWM2,INPUT);

	iris_reset(0,0,0,0);	
}

void iris_reset(int a, int b, int c, int d)
{
	digitalWrite(A,a);
	digitalWrite(AA,b);
	digitalWrite(B,c);
	digitalWrite(BB,d);
}

void iris_control(int a, int b, int c, int d)
{
	digitalWrite(A,a);
	digitalWrite(AA,b);
	digitalWrite(B,c);
	digitalWrite(BB,d);
}

void step0(void)
{
	digitalWrite(A,1);
	digitalWrite(AA,0);
	digitalWrite(B,1);
	digitalWrite(BB,0);
	if(ON_OFF_STATUS == 1) STEP_STATUS++;
	else STEP_STATUS = 3;
}

void step1(void)
{
	digitalWrite(A,0);
	digitalWrite(AA,1);
	digitalWrite(B,1);
	digitalWrite(BB,0);
	if(ON_OFF_STATUS == 1) STEP_STATUS++;
	else STEP_STATUS--;
	
}

void step2(void)
{
	digitalWrite(A,0);
	digitalWrite(AA,1);
	digitalWrite(B,0);
	digitalWrite(BB,1);
	if(ON_OFF_STATUS == 1) STEP_STATUS++;
	else STEP_STATUS--;
}

void step3(void)
{
	digitalWrite(A,1);
	digitalWrite(AA,0);
	digitalWrite(B,0);
	digitalWrite(BB,1);
	if(ON_OFF_STATUS == 1) STEP_STATUS = 0;
	else STEP_STATUS = 2;
}

void iris_close(int steps)
{
	int i;
	for(i=0; i<steps; i++)
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
}

void iris_open(int steps)
{
	int k;
	for(k=0; k<steps; k++)
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
}

int main(void)
{	
	if(wiringPiSetup() == -1) 	
		return 1;
	initialize();
	softPwmCreate(PWMSET,0,200);
		
	while(1)
	{
	//	softPwmWrite(PWMSET,PWM1);
	//	softPwmWrite(PWMSET,PWM2);
		if(ON_OFF_STATUS == 1)
		{
			switch(STEP_STATUS)
			{
				case 0:
					step(0);
				case 1:
					step(1);
				case 2:
					step(2);
				case 3:
					step(3);
					break;
			}
		}
		else
		{
			switch(STEP_STATUS)
			{
				case 3:
					step(3);
				case 2:
					step(2);
				case 1: 
					step(1);
				case 0:
					step(0);
					break;
			}

				

		}
	}
	return 0;
}
