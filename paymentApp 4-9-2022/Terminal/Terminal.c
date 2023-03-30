#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    EN_terminalError_t a;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Date and time: %d/%02d/%02d %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("please enter the transaction date in format of DD/MM/YYYY \n");
    scanf("%s",&(termData->transactionDate));
    /*if (tm.tm_mday != termData->transactionDate[0] && termData->transactionDate[1] && tm.tm_mon+1 != termData->transactionDate[3,4] && tm.tm_year + 1900 != termData->transactionDate[6,7] )
    {
        printf("WRONG_DATE\n");
    }*/
    //printf("%s",termData->transactionDate);
    if(strlen(termData->transactionDate)==NULL || strlen(termData->transactionDate) < 10 )
    {
           a = WRONG_DATE;
           printf("WRONG_DATE\n");
    }
    else if (!isdigit(termData->transactionDate[0]) || !isdigit(termData->transactionDate[1])) //check digits of DD
    {
           a = WRONG_DATE;
           printf("WRONG_DATE\n");
    }
    else if (termData->transactionDate[2]!= '/' || termData->transactionDate[5]!= '/' ) //check '/'
    {
           a = WRONG_DATE;
           printf("WRONG_DATE\n");
    }
    else if (!isdigit(termData->transactionDate[3]) || !isdigit(termData->transactionDate[4]))
    {
           a = WRONG_DATE;
           printf("WRONG_DATE\n");
    }
    else if (!isdigit(termData->transactionDate[6]) || !isdigit(termData->transactionDate[7]) || !isdigit(termData->transactionDate[8]) || !isdigit(termData->transactionDate[9]))
    {
           a = WRONG_DATE;
           printf("WRONG_DATE\n");
    }
    else
    {
        a= TERMINAL_OK;
       printf("Right transaction date,TERMINAL_OK\n");
    }


return a;

}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    //printf("test of isCardExpired:\n" );
    EN_terminalError_t b;
    if ((cardData->cardExpirationDate[3]-'0')  < (termData->transactionDate[8]-'0' )) //check MM/_Y with DD/MM/YYYY// atoi asahl 7aga or (ASCII bs 7waaar) or hgaayes


        {b = EXPIRED_CARD;
        printf("EXPIRED_CARD\n");}

     else if ((cardData->cardExpirationDate[3]-'0')  == (termData->transactionDate[8]-'0'))
    {
        if ((cardData->cardExpirationDate[4]-'0')  < (termData->transactionDate[9]-'0' )) //check MM/Y_ with DD/MM/YYY_

            {b = EXPIRED_CARD;
            printf("EXPIRED_CARD\n");}

        else if ((cardData->cardExpirationDate[4]-'0')  == (termData->transactionDate[9]-'0' )) //check MM/Y_ with DD/MM/YYY_
        {
            if ((cardData->cardExpirationDate[0]-'0')  < (termData->transactionDate[3]-'0' )) //check _M/YY with DD/_M/YYYY

                {b = EXPIRED_CARD;
                 printf("EXPIRED_CARD\n");}

            else if ((cardData->cardExpirationDate[0]-'0')  == (termData->transactionDate[3]-'0' )) //check _M/YY with DD/_M/YYYY
            {

                if ((cardData->cardExpirationDate[1]-'0')  < (termData->transactionDate[4]-'0' )) //check M_/YY with DD/M_/YYYY
                    {b = EXPIRED_CARD;
                     printf("EXPIRED_CARD\n");}

            }
        }
    }else {printf("your card is not expired,TERMINAL_OK\n");


            //printf("your card is not expired,TERMINAL_OK\n");
            b = TERMINAL_OK;

            }

    return b ;

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t c;
    printf("please enter your transaction amount\n");
    scanf("%f",&(termData->transAmount));
    //float transaction amount ;
    if(termData->transAmount <= 0)
    {
        c = INVALID_AMOUNT ;
        //printf("INVALID_AMOUNT\n");
    }
    else
    {

        c = TERMINAL_OK ;
        printf("your transaction amount is: %f \n",termData->transAmount);
    }
    return c ;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t d;
    termData->maxTransAmount = 500.00;
    printf("your max transaction amount is : %f\n",termData->maxTransAmount);
    //scanf("%f",&(termData->maxTransAmount));
    if(termData->maxTransAmount <= 0)
    {
        d = INVALID_MAX_AMOUNT ;
        printf("INVALID_MAX_AMOUNT\n");
    }
    else
    {
        d = TERMINAL_OK ;
        printf("Valid Max amount,TERMINAL_OK\n");
    }
    return d ;
}



EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t e;
    if(termData->transAmount > termData->maxTransAmount)
    {
        e = EXCEED_MAX_AMOUNT ;
        //printf("EXCEED_MAX_AMOUNT\n");
    }
    else
    {
        e = TERMINAL_OK ;
        //printf("below your max amount,TERMINAL_OK\n");
    }
    return e ;

}








/*
int main()
{
    ST_cardData_t cardData;
    EN_cardError_t x, y, z;
	//x = getCardHolderName(&cardData);
	//y = getCardExpiryDate(&cardData);
	//z = getCardPAN(&cardData) ;

    ST_terminalData_t termData;
    //ST_cardData_t cardData;
    EN_terminalError_t a,b,c,d,e;
	//a=getTransactionDate(&termData);
	//b=isCardExpired(&cardData,&termData);
	c=getTransactionAmount(&termData);
	d=setMaxAmount(&termData);
	//e=isBelowMaxAmount(&termData);



	return 0;
}*/

