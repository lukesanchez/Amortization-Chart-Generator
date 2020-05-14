/*********************************************************************
Program Name: Amortization Chart Generator

Description: This program allows a user to input details about a loan,
then generates an Amortization Chart for the specified loan. It also 
outputs the total intrest, principal, and cost for the loan.              

Created by: Luke Sanchez	      	
Created on: Nov. 27, 2019    
Last modified: May 13, 2020	
**********************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN_PRINCIPAL 5000.00
#define MAX_PRINCIPAL 2000000.00
#define MIN_DURATION 3
#define MAX_DURATION 40
#define MIN_APR 0.010
#define MAX_APR 0.250

// Function prototypes
void flushScanf(void);
void CalcMonthlyPayment(int, double, float, double*);
int DurationInput(void);
float AprInput(void);
float PrincipalInput(double*);
void AmortizationGenerator(int, double*, float, double, double*);
void LoanTotals(double*, double*, double*);

int main(void){ // main begin
    //local declerations
    int loanDuration = 0;
    double loanPrincipal = 0.0;
    float loanAPR = 0.0;
    double monthlyPayment = 0.0;
    double totalIntrest = 0.0, totalPrincipal = 0.0, totalLoanCost = 0.0;

while (1){
    loanDuration = DurationInput();
        if (loanDuration == 0){
            break;
        }
    loanAPR = AprInput();
        if (loanAPR == 0){
            break;
        }
    loanPrincipal = PrincipalInput(&totalPrincipal);
        if (loanPrincipal == 0){
            break;
        }
    CalcMonthlyPayment(loanDuration, loanPrincipal, loanAPR , &monthlyPayment);
    AmortizationGenerator(loanDuration, &loanPrincipal, loanAPR, monthlyPayment, &totalIntrest);
    LoanTotals(&totalIntrest, &totalPrincipal, &totalLoanCost);
    }
return 0; 
} // main End


/************************************************************
* Function: flushScanf() clears the input buffer when called
* after a scanf statement. Helps with erroneous user inputs. 
************************************************************/
void flushScanf(void){
  char c;
  while((c = getchar()) != '\n' && c != EOF)
  {
    ;
  }
}

/******************************************************
* Function Name: DurationInput()
* Input Parameters: none
*
* Description: This function promts the user to enter
* the loan duration, then checks if the value is within
* the defined limits. If so it returns the duration in 
* months. Also quits program if value = 0. 
* 
* Return Value: int duration, stored in loanDuration in main
*******************************************************/
int DurationInput(){
    int duration = -1;
        printf("Enter duration of loan in years(%d - %d) or zero to quit: ",MIN_DURATION, MAX_DURATION);
        scanf("%d", &duration);
        flushScanf();
        if (duration == 0){
            duration = 0;
            printf("Quitting Program!\n");
            return 0;
        }
        if (duration >= MIN_DURATION && duration <= MAX_DURATION){
            return duration * 12; //returns duration in months
        }
        else{
            printf("Please enter a valid loan duration between %d and %d years.\n", MIN_DURATION, MAX_DURATION);
            DurationInput();
            }
    return duration * 12;
    }

/******************************************************
* Function Name: AprInput()
* Input Parameters: none
*
* Description: This function promts the user to enter
* the loan intrest rate, then checks if the value is within
* the defined limits. If so it returns the APR.
* Also quits program if return value = 0. 
* 
* Return Value: float userAPR, stored in loanAPR in main
*******************************************************/
float AprInput(void){
    float userAPR = -1.0;
    printf("Enter the intrest rate for loan(1%% - 25%%) or zero to quit: ");
    scanf("%f", &userAPR);
    flushScanf();
    if (userAPR >= MIN_APR && userAPR <= MAX_APR){
        return userAPR;
    }
    if (userAPR == 0){
        printf("Quitting Program!\n");
        return 0;
    }
    else{
        printf("Please enter a valid Intrest percentage in decimal format (%.2f - %.2f).\n", MIN_APR, MAX_APR);
        AprInput();
    }
}

/***********************************************************
* Function Name: PrincipalInput()
* Input Parameters: double *totalPrincipal 
*
* Description: This function promts the user to enter
* the loan principal, then checks if the value is within
* the defined limits. If so it returns the principal value.
* Also asigns totalPrincipal with the validated input.
* Quits program if value = 0. 
* 
* Return Value: float userPrincipal, stored in loanPricipal in main
************************************************************/
float PrincipalInput(double* princTotal){
    float userPrincipal = -1.0;
    printf("Enter loan principal($%.0lf - $%.0lf): $", MIN_PRINCIPAL, MAX_PRINCIPAL);
    scanf("%f", &userPrincipal);
    flushScanf();
    if (userPrincipal >= MIN_PRINCIPAL && userPrincipal <= MAX_PRINCIPAL){
        *princTotal = userPrincipal; // asigns the total principal to inputed pricipal. 
        return userPrincipal;
    }
    if (userPrincipal == 0){
        printf("Quitting Program!\n");
    }
    else{
        printf("Please enter a valid loan amount between ($%.2f and $%.2f) or zero to quit.\n", MIN_PRINCIPAL, MAX_PRINCIPAL);
        PrincipalInput(princTotal);
    }
}

/********************************************************************
* Function Name: CalcMonthlyPayment()
* Input Parameters: duration, principal, apr, *mnthPayment
*
* Description: This function calculates the monthly payment
* for the loan using the inputed values. 
*
* Return Value: double *mnthPayment, stored in monthlyPayment in main
*********************************************************************/
void CalcMonthlyPayment(int duration, double principal, float apr, double* mnthPayment){
    float monthlyRate = apr / 12.0;   //rate per month.
    double Base = 1 + monthlyRate;
    *mnthPayment = principal * ((monthlyRate * pow(Base, duration)) / (pow(Base, duration) - 1));
    printf("\nMonthly Payment: $%.2lf\n", *mnthPayment);
return;
}

/********************************************************************
* Function Name: AmortizationGenerator()
* Input Parameters: month, *princ, apr, mnthPayment, *totInt
*
* Description: This function generates and prints out a formated
* Amortization chart. The chart shows the intrest, pricipal, balance,
* and month for each term.
* 
* Return Value: double *totInt, stored in totalIntrest in main
*********************************************************************/
void AmortizationGenerator(int month, double *princ, float apr, double mnthPayment, double* totInt){
    float monthlyRate = apr / 12;   //rate per month.
    float intrestTerm;
    double principalTerm = mnthPayment - monthlyRate * *princ;
    printf("|_Mnt___Int_________Princ_______Balance__|\n");
    for(int i = 1; i <= month; i++){
    intrestTerm = monthlyRate * *princ; 
    principalTerm = mnthPayment - monthlyRate * *princ;
    *princ -= principalTerm;
    *totInt += intrestTerm;
    printf("| %.3d | %8.2f | %8.2lf | %10.2lf |\n", i, intrestTerm, principalTerm, *princ);
    }
return;
}

/************************************************************************
* Function Name: LoanTotals()
* Input Parameters: *totInt, *totPrinc, *totCost
*
* Description: This function prints out the total inrest, total Principal, 
* and overall total cost for the loan. Then resets the values for the next
* program loop.
* 
* Return Value: none
**************************************************************************/
void LoanTotals(double* totInt, double* totPrinc, double* totCost){
    *totCost = *totInt + *totPrinc;
    printf("Total Intrest Cost:          $%10.2lf\n", *totInt);
    printf("Total Principal Cost:        $%10.2lf\n", *totPrinc);
    printf("Total Cost:                  $%10.2lf\n\n", *totCost);
    *totInt = 0.0; //resets values for next run. 
    *totPrinc = 0.0;
    *totCost = 0.0;
return;
}

