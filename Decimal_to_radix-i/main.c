//********************************************************************
//*                    EEE2046F/EEE2050F C template                  *
//*==================================================================*
//* WRITTEN BY:  	NYAMBE TYRON NYMTYR001  	                 	 *
//* DATE CREATED:	03/04/2022                                       *
//* MODIFIED:       10/04/2022                                       *
//*==================================================================*
//* PROGRAMMED IN:	C                                                *
//* TARGET:        main.exe                                          *
//*==================================================================*
//* DESCRIPTION:Designing a decimal to radix-i conversion program    *
//*                                                                  *
//********************************************************************
// INCLUDE FILES 
//====================================================================
#include <stdio.h> //For screen input and output 
#include <stdint.h>
#include <math.h> //Math library
#include <string.h> //String library
//====================================================================
// GLOBAL CONSTANTS
#define TITLE(Decimal_TO_Radix_i_Converter) (#Decimal_TO_Radix_i_Converter) //Title
#define AUTHOR(Written_by_NYAMBE_TYRON_NYMTYR001) (#Written_by_NYAMBE_TYRON_NYMTYR001) //Author
#define YEAR 2022 //Year
//====================================================================

//====================================================================
// GLOBAL VARIABLES
	char *title=TITLE(Decimal_TO_Radix_i_Comverter);
    char *author=AUTHOR(Written_by__NYAMBE_TYRON_NYMTYR001);
    int date=YEAR;
	int num; //stores number input by user
    int radix; //stores radix input by user
	float logResult; //stores result from log function
	int result; //stores result from integer division
    int rem; //stores remainder of int division
//====================================================================

//====================================================================
// FUNCTION DECLARATIONS
void Dec2RadixI(int decValue, int radValue); //function to convert from dec to radix
//====================================================================

//====================================================================
// MAIN FUNCTION
//====================================================================
int main (void) //main method
{
    //print statements
	printf("****************************\n");
    printf("%s\n",TITLE(Decimal_TO_Radix_i_Converter));
    printf("%s\n",AUTHOR(Written_by_NYAMBE_TYRON_NYMTYR001));
    printf("%d\n",date);
    printf("****************************\n");
    int n=1;
    //while loop
	while (n==1)
    {   
    printf("Enter a decimal number: ");
    scanf("%d",&num);
    //If does not meet condition jump to exit
    if(num<0)
    { 
        printf("EXIT\n");
         return 0;
    }
    else 
    {
        //output number entered
        printf("The number you have entered is %d\n",num);
    }
    
    printf("Enter a radix for the converter between 2 and 16: ");
    scanf("%d",&radix);

    if(radix<2 || radix>16)
    {
        printf("Invalid radix input\n Exiting...\n");
        return 0;
    }
    //output radix entered
    else printf("The radix you have entered is %d\n",radix);
    //calculating log2(n)
    logResult=(log(num)/log(2));
    //output result from log function
	printf("Log2 of the number is %.2f\n",logResult);

    //output result from integer division
	result=(num/radix);
	printf("The integer result of the number divided by %d is %d\n",radix,result);

    //output remainder
    rem=num%radix;
    printf("The remainder is %d\n",rem);

    //calling dec2radic function and outputting result
 
    Dec2RadixI(num,radix);
    continue;
    }    
	return 0;
}						
	// End of main

//dectoradix function
void Dec2RadixI(int decValue, int radValue)
{
    int i=0;
    int dec=decValue;//decimal value
    int r=radValue;//radix
    char digits[100];//char array of bits   
    while(dec>0)
    {
        int rem=dec%r;

        if(rem<10)
        {
            digits[i]='0'+rem;

        }
        else
        {
            digits[i]='A'+(rem-10);
            
        }
        dec=dec/r;
        i++;
    } 

    printf("The radix-%d value is ",r);
    while(i--)
    {
        printf("%c",digits[i]);

    }
    printf("\n");
}

//********************************************************************
// END OF PROGRAM
//********************************************************************
