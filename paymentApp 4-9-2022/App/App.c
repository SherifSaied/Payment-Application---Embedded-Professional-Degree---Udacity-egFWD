#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // for check format MM/YY
#include "App.h"
int main()
{
    // Card Module
    ST_cardData_t cardData;
    EN_cardError_t x, y, z;
    x = getCardHolderName(&cardData);
    printf("card data= %s\n",cardData);
	y = getCardExpiryDate(&cardData);
	printf("card data= %s\n",cardData);
	z = getCardPAN(&cardData) ;
	printf("card data= %s\n",cardData.primaryAccountNumber);
	// Terminal Module
	ST_terminalData_t termData;
	EN_terminalError_t a,b,c,d,e;
	a=getTransactionDate(&termData);
	b=isCardExpired(&cardData,&termData);
	if(b == 2 )
        {printf("Declined Expired Card\n");
        return 0;
        }
	d=setMaxAmount(&termData);
	c=getTransactionAmount(&termData) ;
	e=isBelowMaxAmount(&termData);
	if(e == 5)
        {printf("Declined Amount Exceeding Limit\n");
        return 0;
        }
    //Server Module
    //ST_cardData_t ca
    ST_accountsDB_t accountRefrence ;
    ST_transaction_t transData ;
    transData.terminalData = termData;
    //ST_terminalData_t termData ;
    EN_serverError_t q , r , u;
    EN_transState_t p ;
    EN_accountState_t f;
    f=isBlockedAccount(&accountRefrence) ;
    if(f == 1)
        {printf("Blocked account\n") ;
        return 0;
        }
    q = isValidAccount(&cardData,&accountRefrence);
    if(q == 3)
        {printf("Declined Invalid account\n") ;
        return 0;
        }

    r = isAmountAvailable(&termData) ;
    if(r == 4)
        {printf("Declined Insufficient funds ") ;
        return 0;
        }
        else printf("True2\n") ;
   // printf ("amount transfered %f\n",transData.terminalData.transAmount) ;
    //printf ("amount transfered %f\n",termData.transAmount) ;
    //arr_account[m].balance = (arr_account[m].balance - termData.transAmount );
    p = recieveTransactionData(&transData) ;
    if(p==0)
     {printf("True3\n %d\n",p) ;}



    u = saveTransaction(&transData) ;
    printf("True5\n %d",u) ;




    return 0 ;
}
