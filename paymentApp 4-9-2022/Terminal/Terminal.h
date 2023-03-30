#ifndef Terminal
#define Terminal
#include "../Card/Card.h"
typedef unsigned char uint8_t;
typedef struct ST_terminalData_t
{
float transAmount;
float maxTransAmount;
uint8_t transactionDate[11];
}ST_terminalData_t;


typedef enum EN_terminalError_t
{
TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

#endif // Terminal GuardHeaderFile






/*typedef struct ST_cardData_t
{

	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;*/
