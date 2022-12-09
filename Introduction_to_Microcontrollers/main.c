//********************************************************************
//*                    EEE2046F C template                           *
//*==================================================================*
//* WRITTEN BY:NYAMBE TYRON NYMTYR001    	                 		 *
//* DATE CREATED:09/05/2022											 *
//* MODIFIED:                                                        *
//*==================================================================*
//* PROGRAMMED IN: Atollic True Studio                               *
//* TARGET:        STM32F0                                           *
//*==================================================================*
//* DESCRIPTION: Inroduction to Microcontrollers via bit patterns	 *
//*                                                                  *
//********************************************************************
// INCLUDE FILES
//====================================================================
#include "stm32f0xx.h"
#include <math.h>
//====================================================================
// GLOBAL CONSTANTS
//delays
#define DELAY1 8
#define DELAY2 600000


//symbolic constants
#define TRUE 1
#define FALSE 0

#define SW0 GPIO_IDR_0
#define SW1 GPIO_IDR_1
#define SW2 GPIO_IDR_2
#define SW3 GPIO_IDR_3
//====================================================================

//====================================================================
// GLOBAL VARIABLES
uint32_t* RCCADDR=0x40021000 + 0x14; //Offset is 0x14 added to base address 0x40021000
//Above is a pointer to register in RCC which we'll use to set 18th bit high
//new variable type
typedef uint8_t flag_t;

//storing input of port A
uint16_t inpData;


//Patterns
int bitpattern1=0b00000000;
int bitpattern2=0b11111111;
int bitpattern3=0b10101010;

//Flags
flag_t startFlag=FALSE;
flag_t firstFlag=FALSE;
flag_t secondFlag=FALSE;
flag_t thirdFlag=FALSE;


//====================================================================

//====================================================================
// FUNCTION DECLARATIONS
void initGPIO(void);
void display(void);
void delay(void);
void checkPB(void);
void firstDisplay(void);
void secondDisplay(void);
void thirdDisplay(void);
//====================================================================


//====================================================================
// MAIN FUNCTION
//====================================================================
int main (void)
{
	initGPIO(); //initializing GPIO

  /* Infinite loop */
  while (1)
  {

	checkPB();//checking which button pressed
	display();//Display functions
  }

}							// End of main

//====================================================================
// FUNCTION DEFINITIONS
void initGPIO(void)
{

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	//inpData=GPIOA->IDR;

	GPIOA->MODER &= ~(GPIO_MODER_MODER0
					 |GPIO_MODER_MODER1
					 |GPIO_MODER_MODER2
					 |GPIO_MODER_MODER3);//configuring GPIOA pins 0-3 as digital inputs

	// enabling pull-up resistors
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR0_0|
					GPIO_PUPDR_PUPDR1_0|
					GPIO_PUPDR_PUPDR2_0|
					GPIO_PUPDR_PUPDR3_0);



	 //Setting things in GPIOB to allow some output and enable us to write
		GPIOB->MODER |= GPIO_MODER_MODER0_0|
				  GPIO_MODER_MODER1_0|
				  GPIO_MODER_MODER2_0|
				  GPIO_MODER_MODER3_0|
				  GPIO_MODER_MODER4_0|
				  GPIO_MODER_MODER5_0|
				  GPIO_MODER_MODER6_0|
				  GPIO_MODER_MODER7_0;

	GPIOB-> ODR =0; //enabling all turned off
}

//Delay method
void delay(void)
{
    volatile int i;
	volatile int j;
	for(i=0; i < DELAY1; i++);
	for(j=0; j < DELAY2; j++);

}

void firstDisplay(void)
 {

	 GPIOB->ODR = bitpattern1;
	 // GPIOB->ODR = 0;//switching of all LEDs
	 delay();
	 checkPB();

	  GPIOB->ODR = bitpattern2;
	 // GPIOB->ODR = 0;//switching of all LEDs
	  delay();
	  checkPB();

	  GPIOB->ODR = bitpattern3;
	 // GPIOB->ODR = 0;//switching of all LEDs
	  delay();

 }


 void secondDisplay(void)
  {
	  //displays bit pattern
	 for(int i=0;i<8;i++)
	 {
		 int j;
		 j=(int)(pow(2,i));
		 GPIOB->ODR=j;
		 delay();

		 checkPB();
		 if(secondFlag==FALSE)
		 	 {
			 	 break;//exit loop if new button pressed
		 	 }
	 }
	// GPIOB->ODR = 0;//switching of all LEDs
  }


 void thirdDisplay(void)
   {
 	  // displays the current count value on the LEDS of an 8-bit binary counter
	 for(int i=0;i<8;i++)
		 {
			 GPIOB->ODR=i;

			 delay();
			 checkPB();
			 if(thirdFlag==FALSE)
			 {
				 break;//exit loop if new button pressed
			 }
		 }
		 //GPIOB->ODR = 0;//switching of all LEDs
   }


 void checkPB(void)
 {
	  //checks whether SW0, SW1 or SW2 or SW3 has been pressed and updates
	 inpData=GPIOA->IDR;

	 //reading input data register
	 if((inpData & SW0)==0)//checks if SW0 pressed
	 {
		 startFlag=TRUE;
		 firstFlag=FALSE;
		 secondFlag=FALSE;
		 thirdFlag=FALSE;
	 }

	 if((inpData & SW1)==0)//checks if SW0 pressed
		 {
			 startFlag=TRUE;
			 firstFlag=TRUE;
			 secondFlag=FALSE;
			 thirdFlag=FALSE;
		 }

	 if((inpData & SW2)==0)//checks if SW0 pressed
		 {
			 startFlag=TRUE;
			 firstFlag=FALSE;
			 secondFlag=TRUE;
			 thirdFlag=FALSE;
		 }

	 if((inpData & SW3)==0)//checks if SW0 pressed
		 {
			 startFlag=TRUE;
			 firstFlag=FALSE;
			 secondFlag=FALSE;
			 thirdFlag=TRUE;
		 }
 }


 void display(void)
 {
	  //checks the state of your four global program flags and calls the correct LED display function based on the state of the flags.

	 if(firstFlag==TRUE) //SW1 Pressed
	 {
		 firstDisplay();
	 }

	 else if(secondFlag==TRUE)//SW2 Pressed
	 {
		 secondDisplay();
	 }
	 else if(thirdFlag==TRUE)//SW3 Pressed
	 {
		thirdDisplay();
	 }

	 else if(startFlag==TRUE)//SW0 Pressed i.e reset
	 {
		 //Turning on LED B0
		 GPIOB->ODR = 0b1;
		 checkPB();
	 }
 }




//====================================================================

//********************************************************************
// END OF PROGRAM
//********************************************************************
