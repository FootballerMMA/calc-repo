#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define BUFFER_LENGTH 1024
typedef unsigned int U32;
void PRINT_WELCOME();
void PRINT_MENU_SELECTION();
void RECEIVE_USERINPUT(char **pBUFFER);
void INVALID_OPTION();
void CLEAR_BUFFER(char **pBUFFER);
long COMPUTE_FACTORIAL(int FACT);
bool EXTRACT_FROM_BUFFER(char **pBUFFER, char* pUSER_SELECTION);
bool VERIFY_INPUT(char **pBUFFER, bool FLAG, bool smallerFlag);
bool VALID_SELECTION_CHECKER(char* pUSER_SELECTION);
void PRIMES_GCD_LCM_RECEIVE_INPUT(char **pBUFFER, U32 *pINTEGER_A, U32 *pINTEGER_B);
void PRINT_PRIMES(U32 INTEGER_INPUT);
void PRIMES_PRINT(U32 INTEGER_A, U32 INTEGER_B);
U32  GCD(U32 INTEGER_A, U32 INTEGER_B);
U32  LCM(U32 INTEGER_A, U32 INTEGER_B, U32 GCD_F);
void GCD_LCM_PRINT(U32 INTEGER_A, U32 INTEGER_B);
void PRIMES_GCD_LCM(char **pBUFFER);
void BINOMIAL_THEOREM_RECEIVE_INPUT(char **pBUFFER, int *pN);
void BINOMIAL_THEOREM_COMPUTE(int *pN);
void BINOMIAL_THEOREM(char **pBUFFER);
void MODULAR_ARITHMETIC_RECEIVE_INPUT(char **pBUFFER, U32 *pPOSITIVE_INT_M, U32 *pNON_NEGATIVE_INT_A, U32 *pNON_NEGATIVE_INT_B);
void MODULAR_ARITHMETIC_PRINT_ZM(U32 POSITIVE_INT_M);
void MODULAR_ARITHMETIC_PRINT_MOD_ADD_MULT(U32 POSITIVE_INT_M, U32 NON_NEGATIVE_INT_A, U32 NON_NEGATIVE_INT_B);
void MODULAR_ARITHMETIC(char **pBUFFER);
void DELIBERATOR(char **pBUFFER, char* pUSER_SELECTION);
int main()
{
    bool GATE_KEEPER_ = false;
    char BUFFER[BUFFER_LENGTH];
    char *pBUFFER = (char*)&BUFFER;
    char USER_SELECTION;
    char *pUSER_SELECTION = (char*)&USER_SELECTION;
    PRINT_WELCOME();
    do
    {
        PRINT_MENU_SELECTION();
        RECEIVE_USERINPUT(&pBUFFER);
        GATE_KEEPER_ = EXTRACT_FROM_BUFFER(&pBUFFER, pUSER_SELECTION);
        if (GATE_KEEPER_){
            INVALID_OPTION();
            continue;
        }
        GATE_KEEPER_ = VALID_SELECTION_CHECKER(pUSER_SELECTION);
        if (!GATE_KEEPER_){
            INVALID_OPTION();
            continue;
        }
        DELIBERATOR(&pBUFFER, pUSER_SELECTION);
    } while (USER_SELECTION != 'Q');
    return 0;
}

void PRINT_WELCOME()
{
    puts("Welcome to Matrix Program !");
    puts("Please use menu keys to navigate around !");
}

void PRINT_MENU_SELECTION()
{
    puts("A - Primes (GCD & LCM), B - Binomial Theorem, C - Modular Arithmetic, Q - Exit Program");
    printf("> ");
}

void RECEIVE_USERINPUT(char **pBUFFER)
{
    CLEAR_BUFFER(pBUFFER);
    fgets(*pBUFFER, BUFFER_LENGTH, stdin);
}

void INVALID_OPTION()
{
    puts("INVALID OPTION");
}

void CLEAR_BUFFER(char **pBUFFER)
{
    memset(*pBUFFER, 1024, '\0');
    fflush(stdout);
}

long COMPUTE_FACTORIAL(int FACT)
{
    if (FACT == 0)  
    return 1;  
  else  
    return(FACT * COMPUTE_FACTORIAL(FACT-1));  
}

bool EXTRACT_FROM_BUFFER(char **pBUFFER, char* pUSER_SELECTION)
{
    size_t length = strlen(*pBUFFER);
    if (length != 2){
        return true;
    }
    *pUSER_SELECTION = *pBUFFER[0];
    return false;
}

bool VALID_SELECTION_CHECKER(char* pUSER_SELECTION)
{
  *pUSER_SELECTION = toupper(*pUSER_SELECTION);
  switch (*pUSER_SELECTION)
  {
    case 'A':
        puts("Selected Primes (GCD & LCM)");
        return true;
    case 'B':
        puts("Selected Binomial Theorem");
        return true;
    case 'C':
        puts("Selected Modular Arithmetic");
        return true;
    case 'Q':
        // PRINT_EXIT_MESSAGE();
        puts("Exiting program !");
        return true;
    default:
        return false;
  }
  return false;
}

bool VERIFY_INPUT(char **pBUFFER, bool FLAG, bool smallerFlag)
{
    char small[30];
    int num;
    sscanf(*pBUFFER,"%[^\t\n]",small);
    if (FLAG){
        if(strspn(small, "0123456789") == strlen(small)){
            num = atoi(small);
            if (smallerFlag){
                if (num >= 10 || num <= 1){
                    return true;
                }
                return false;
            } else {
                if (num > 0){
                    return false;
                }
            }
        return true;
        }
    } else {
        if(strspn(small, "0123456789") == strlen(small)){
        return false;
        }
    }
    return true;
}

void PRIMES_GCD_LCM_RECEIVE_INPUT(char **pBUFFER, U32 *pINTEGER_A, U32 *pINTEGER_B)
{
    bool FLAG;
    do
    {
        puts("Please enter non-negative integer a !");
        printf("> ");
        RECEIVE_USERINPUT(pBUFFER);
        FLAG = VERIFY_INPUT(pBUFFER, false, false);
        if (FLAG){
            INVALID_OPTION();
            continue;
        } else *pINTEGER_A = atoi(*pBUFFER);
    } while (FLAG);
   
    do
    {
        puts("Please enter non-negative integer b !");
        printf("> ");
        RECEIVE_USERINPUT(pBUFFER);
        FLAG = VERIFY_INPUT(pBUFFER, false, false);
        if (FLAG){
            INVALID_OPTION();
            continue;
        } else *pINTEGER_B = atoi(*pBUFFER);
    } while (FLAG);
}

void PRINT_PRIMES(U32 INTEGER_INPUT)
{
    while (INTEGER_INPUT%2 == 0)
    {
        printf("%d, ", 2);
        INTEGER_INPUT = INTEGER_INPUT/2;
    }
    for (int i = 3; i <= sqrt(INTEGER_INPUT); i = i+2)
    {
        while (INTEGER_INPUT%i == 0)
        {
            printf("%d, ", i);
            INTEGER_INPUT = INTEGER_INPUT/i;
        }
    }
    if (INTEGER_INPUT > 2){
        printf ("%d ", INTEGER_INPUT);
    }
}

void PRIMES_PRINT(U32 INTEGER_A, U32 INTEGER_B)
{
    if (INTEGER_A == 0 && INTEGER_B == 0){
        printf("Prime factors for %u are : ", INTEGER_A);
        printf("Zero is neither prime nor composite. Since any number times zero equals zero, there are an infinite number of factors for a product of zero.");
    } else {
        printf("Prime factors for %u are : ", INTEGER_A);
    if (INTEGER_A == 0){
        printf("Zero is neither prime nor composite. Since any number times zero equals zero, there are an infinite number of factors for a product of zero.");
    } else PRINT_PRIMES(INTEGER_A);
    puts("");
    printf("Prime factors for %u are : ", INTEGER_B);
    if (INTEGER_B == 0){
        printf("Zero is neither prime nor composite. Since any number times zero equals zero, there are an infinite number of factors for a product of zero.");
    } else PRINT_PRIMES(INTEGER_B);
    puts("");
    }
}

U32 GCD(U32 INTEGER_A, U32 INTEGER_B)
{
  if (INTEGER_A == 0)
    return INTEGER_B;
  return GCD(INTEGER_B % INTEGER_A, INTEGER_A);
}

U32 LCM(U32 INTEGER_A, U32 INTEGER_B, U32 GCD_F)
{
    if (GCD_F == 0){
        return 0;
    }
    U32 LCM_F = (INTEGER_A * INTEGER_B) / GCD_F;
    return LCM_F;
}

void GCD_LCM_PRINT(U32 INTEGER_A, U32 INTEGER_B)
{
    U32 GCD_F = GCD(INTEGER_A, INTEGER_B);
    U32 LCM_F = LCM(INTEGER_A, INTEGER_B, GCD_F);
    printf("GCD(%u,%u) = %u\r\n", INTEGER_A, INTEGER_B, GCD_F);
    printf("LCM(%u,%u) = %u\r\n", INTEGER_A, INTEGER_B, LCM_F);
}

void PRIMES_GCD_LCM(char **pBUFFER)
{
    U32 INTEGER_A, INTEGER_B;
    U32 *pINTEGER_A = &INTEGER_A;
    U32 *pINTEGER_B = &INTEGER_B;
    PRIMES_GCD_LCM_RECEIVE_INPUT(pBUFFER, pINTEGER_A, pINTEGER_B);
    PRIMES_PRINT(INTEGER_A, INTEGER_B);
    GCD_LCM_PRINT(INTEGER_A, INTEGER_B);
}

void BINOMIAL_THEOREM_RECEIVE_INPUT(char **pBUFFER, int *pN)
{
    bool FLAG;
    do
    {
        puts("Please enter integer n (where 1 < n < 10) !");
        printf("> ");
        RECEIVE_USERINPUT(pBUFFER);
        FLAG = VERIFY_INPUT(pBUFFER, true, true);
        if (FLAG){
            INVALID_OPTION();
            continue;
        } else {
                *pN = atoi(*pBUFFER);
            }
    } while (FLAG);
}

void BINOMIAL_THEOREM_COMPUTE(int *pN)
{
    int i = 0;
    long coeff;
    U32 xExponent, yExponent;
    for (i = 0; i <= *pN; i++){
        coeff = (COMPUTE_FACTORIAL(*pN))/(COMPUTE_FACTORIAL((*pN - i)) * (COMPUTE_FACTORIAL(i)));
        xExponent = *pN - i;
        yExponent = i;
        if (coeff > 1){
            printf("%ld", coeff);
        }
        if (xExponent > 0){
            if (xExponent == 1){
                printf("x");
            } else {
                printf("x^%d", xExponent);
            }
        }
        if (yExponent > 0){
            if (yExponent == 1){
                printf("y");
            } else{
                printf("y^%d", yExponent);
            }
        }
        if (i < *pN){
            printf(" + ");
        }
    }
    puts("");
}
void BINOMIAL_THEOREM(char **pBUFFER)
{
    int n;
    int *pN = &n;
    BINOMIAL_THEOREM_RECEIVE_INPUT(pBUFFER, pN);
    BINOMIAL_THEOREM_COMPUTE(pN);
}

void MODULAR_ARITHMETIC_RECEIVE_INPUT(char **pBUFFER, U32 *pPOSITIVE_INT_M, U32 *pNON_NEGATIVE_INT_A, U32 *pNON_NEGATIVE_INT_B)
{
    bool FLAG;
    do
    {
        puts("Please enter positive integer m !");
        printf("> ");
        RECEIVE_USERINPUT(pBUFFER);
        FLAG = VERIFY_INPUT(pBUFFER, true, false);
        if (FLAG){
            INVALID_OPTION();
            continue;
        } else {
            *pPOSITIVE_INT_M = atoi(*pBUFFER);
        }
    } while (FLAG);
   
    do
    {
        puts("Please enter non-negative integer a !");
        printf("> ");
        RECEIVE_USERINPUT(pBUFFER);
        FLAG = VERIFY_INPUT(pBUFFER, false, false);
        if (FLAG){
            INVALID_OPTION();
            continue;
        } else {
            *pNON_NEGATIVE_INT_A = atoi(*pBUFFER);
        }
    } while (FLAG);
   
    do
    {
        puts("Please enter non-negative integer b !");
        printf("> ");
        RECEIVE_USERINPUT(pBUFFER);
        FLAG = VERIFY_INPUT(pBUFFER, false, false);
        if (FLAG){
            INVALID_OPTION();
            continue;
        } else {
            *pNON_NEGATIVE_INT_B = atoi(*pBUFFER);
        }
    } while (FLAG);
}

void MODULAR_ARITHMETIC_PRINT_ZM(U32 POSITIVE_INT_M)
{
    int i = 0;
    printf("Zm = {");
    for (i = 0; i < POSITIVE_INT_M; i++){
        printf("%d", i);
        if (i < POSITIVE_INT_M - 1){
            printf(", ");
        }
    }
    puts("}");
}

void MODULAR_ARITHMETIC_PRINT_MOD_ADD_MULT(U32 POSITIVE_INT_M, U32 NON_NEGATIVE_INT_A, U32 NON_NEGATIVE_INT_B)
{
    int i, d;
    U32 modSOL;
    puts("");
    printf("%d +(%u)%d = %u\t", NON_NEGATIVE_INT_A, POSITIVE_INT_M, NON_NEGATIVE_INT_B, (NON_NEGATIVE_INT_A + NON_NEGATIVE_INT_B) % POSITIVE_INT_M);
    printf("%d *(%u)%d = %u\r\n", NON_NEGATIVE_INT_A, POSITIVE_INT_M, NON_NEGATIVE_INT_B, (NON_NEGATIVE_INT_A * NON_NEGATIVE_INT_B) % POSITIVE_INT_M);
    puts("");
    printf("(0 to a) +(m)(b)\t(0 to a) *(m)(b)\r\n");
    for (i = 0; i < NON_NEGATIVE_INT_A; i++){
        printf("%d +(%u)%d = %u\t\t", i, POSITIVE_INT_M, NON_NEGATIVE_INT_B, (i + NON_NEGATIVE_INT_B) % POSITIVE_INT_M);
        printf("%d *(%u)%d = %u\r\n", i, POSITIVE_INT_M, NON_NEGATIVE_INT_B, (i * NON_NEGATIVE_INT_B) % POSITIVE_INT_M);
    }
    puts("");
    printf("(a) +(m)(0 to b)\t(a) *(m)(0 to b)\r\n");
    for (i = 0; i < NON_NEGATIVE_INT_B; i++){
        printf("%d +(%u)%d = %u\t\t", NON_NEGATIVE_INT_A, POSITIVE_INT_M, i, (NON_NEGATIVE_INT_A + i) % POSITIVE_INT_M);
        printf("%d *(%u)%d = %u\r\n", NON_NEGATIVE_INT_A, POSITIVE_INT_M, i, (NON_NEGATIVE_INT_A * i) % POSITIVE_INT_M);
    }
    puts("");
}

void MODULAR_ARITHMETIC(char **pBUFFER)
{
    U32 POSITIVE_INT_M, NON_NEGATIVE_INT_A, NON_NEGATIVE_INT_B;
    U32 *pPOSITIVE_INT_M     = &POSITIVE_INT_M;
    U32 *pNON_NEGATIVE_INT_A = &NON_NEGATIVE_INT_A;
    U32 *pNON_NEGATIVE_INT_B = &NON_NEGATIVE_INT_B;
    MODULAR_ARITHMETIC_RECEIVE_INPUT(pBUFFER, pPOSITIVE_INT_M, pNON_NEGATIVE_INT_A, pNON_NEGATIVE_INT_B);
    MODULAR_ARITHMETIC_PRINT_ZM(POSITIVE_INT_M);
    MODULAR_ARITHMETIC_PRINT_MOD_ADD_MULT(POSITIVE_INT_M, NON_NEGATIVE_INT_A, NON_NEGATIVE_INT_B);
}

void DELIBERATOR(char **pBUFFER, char* pUSER_SELECTION)
{
    switch (*pUSER_SELECTION)
    {
        case 'A':
            PRIMES_GCD_LCM(pBUFFER);
            break;
        case 'B':
            BINOMIAL_THEOREM(pBUFFER);
            break;
        case 'C':
            MODULAR_ARITHMETIC(pBUFFER);
            break;
        case 'Q':
            //PRINT_EXIT();
            break;
        default:
            puts("DELIBERATOR FAILED !");
            exit(-1);
    }
}
