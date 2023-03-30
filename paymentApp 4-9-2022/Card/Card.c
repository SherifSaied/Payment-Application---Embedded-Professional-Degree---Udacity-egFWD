#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // for check format MM/YY
#include "Card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    EN_cardError_t x;
    printf("please enter card holder name\n");
    scanf_s("%[^\n]s", &(cardData->cardHolderName));
    if (strlen(cardData->cardHolderName) == NULL || strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24)
    {

        x= WRONG_NAME;
        printf("WRONG_NAME\n");

    }
    else
    {
        //
        x = CARD_OK;
        printf("CARD_OK\n");
        printf("your card name %s\n",cardData->cardHolderName);
    }
    return x;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    EN_cardError_t y;
    printf("please enter card expiry date in format of MM/YY: \n");
    scanf_s("%s", &(cardData->cardExpirationDate));
    if (strlen(cardData->cardExpirationDate) == NULL || strlen(cardData->cardExpirationDate)!= 5 )
    {
        //
        y = WRONG_EXP_DATE;
        //printf("WRONG_EXP_DATE\n");
    }
    else if ( !isdigit(cardData->cardExpirationDate[0]) || !isdigit(cardData->cardExpirationDate[1]) )
    {
        //
        y = WRONG_EXP_DATE;
        //printf("WRONG_EXP_DATE\n");
    }
    else if ((cardData->cardExpirationDate[2]) != '/')
    {
        //
        y = WRONG_EXP_DATE;
        //printf("WRONG_EXP_DATE\n");
    }
    else if ( !isdigit(cardData->cardExpirationDate[3]) || !isdigit(cardData->cardExpirationDate[4]) )
    {
        //
        y = WRONG_EXP_DATE;
        //printf("WRONG_EXP_DATE\n");
    }

    else
    {
        //
        y = CARD_OK ;
        printf("CARD_OK\n");
        printf("your card expiry date is %s\n",cardData->cardExpirationDate);

    }
    return y;

}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    EN_cardError_t z;
    printf("please enter card Pan \n");
    scanf_s("%s", &(cardData->primaryAccountNumber));
    if (strlen(cardData->primaryAccountNumber) == NULL || strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19 )
    {
        z = WRONG_PAN;
        //printf("WRONG_PAN\n");

    }
    else
    {
        z = CARD_OK;
        //printf("CARD_OK\n");
        //printf("your PAN is %s\n",cardData->primaryAccountNumber);


    }
    return z;

}


/*
int main()
{
	ST_cardData_t cardData;
	EN_cardError_t x, y, z;
	x = getCardHolderName(&cardData);
	y = getCardExpiryDate(&cardData);
	z = getCardPAN(&cardData) ;

	return 0;
}*/


