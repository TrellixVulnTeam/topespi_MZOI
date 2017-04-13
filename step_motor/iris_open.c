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

void step0(void);
void step1(void);
void step2(void);
void step3(void);

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
	iris_control(1,0,1,0);
	delay(TIME);
}

void step1(void)
{
	iris_control(0,1,1,0);
	delay(TIME);
}

void step2(void)
{
	iris_control(0,1,0,1);
	delay(TIME);
}

void step3(void)
{
	iris_control(1,0,0,1);
	delay(TIME);
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

		iris_open(STEPS);
		//iris_close(STEPS);
	while(1)
	{
		
		softPwmWrite(PWMSET,PWM1);
		softPwmWrite(PWMSET,PWM2);
		

		/*iris_open(STEPS);
		delay(3000);
		iris_close(STEPS);
		delay(3000);*/
	}
	return 0;
}
