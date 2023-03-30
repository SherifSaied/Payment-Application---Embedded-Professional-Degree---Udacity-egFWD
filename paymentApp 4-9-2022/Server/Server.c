#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Server.h"

ST_accountsDB_t arr_account[255]= {{2000.0,RUNNING,"8989374615436851"},
    {100000.0,BLOCKED,"5807007076043875"},
    {3000.0,RUNNING,"5807007076043825"},
    {4000.0,BLOCKED,"5807007076043830"},
    {300.0,RUNNING,"5807007076043840"}
};


ST_transaction_t arr_transaction[255];
int i=0;
int m;


EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{

    EN_serverError_t q;
    for(i = 0 ; i<255; i++)
    {
        //printf("user = %s\n",cardData->primaryAccountNumber) ;
        //printf("%s\n",arr_account[i].primaryAccountNumber) ;
        if(strcmp(cardData->primaryAccountNumber,arr_account[i].primaryAccountNumber)==0)
        {
            q = SERVER_OK;
            //printf("Valid Account,SERVER_OK\n");
            m=i;
            return q ;
        }
    }

   q = ACCOUNT_NOT_FOUND;

    //printf("ACCOUNT_NOT_FOUND\n");
    return q ;


}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    EN_serverError_t r;
   // printf ("amount transfered %f\n",termData->transAmount) ;

    if(termData->transAmount <= arr_account[m].balance )
    {
        r = SERVER_OK;
        return r ;
        //printf("Amount Available,SERVER_OK\n");
    }
    else
    {
        r = LOW_BALANCE;
        return r ;
        //printf("LOW_BALANCE\n");
    }

    // return r ;
}




EN_serverError_t getTransaction(uint32_t *transactionSequenceNumber, ST_transaction_t *transData)
{
    EN_serverError_t c;


    for(int k = 0 ; k<=255; k++)
    {
        if(strcmp(transData->transactionSequenceNumber,arr_transaction[k].transactionSequenceNumber)== 0)
        {
            c = SERVER_OK ;
            return c;

            //printf("SERVER_OK\n") ;
        }

    }
     c = TRANSACTION_NOT_FOUND ;


    //printf("TRANSACTION_NOT_FOUND\n") ;

    return c;

}



EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t f;
    accountRefrence->state = BLOCKED;
    for(int i=0; i<=255; i++)
    {
        if (arr_account[i].state == BLOCKED )
        {
            f = BLOCKED;
            //printf("BLOCKED\n");
        }
        f=RUNNING ;
        //printf("RUNNING\n");
    }
    return f ;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    EN_serverError_t u,c;
    uint32_t transactionNum =0;
    transData->transactionSequenceNumber = 0 + transactionNum  ;
    if (transData->transactionSequenceNumber < 255 )
    {
        arr_transaction[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData ;
        arr_transaction[transData->transactionSequenceNumber].terminalData = transData->terminalData ;
        arr_transaction[transData->transactionSequenceNumber].transState = transData->transState ;
        arr_transaction[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber+1 ;
        transactionNum ++ ;
        u = SERVER_OK ;

         return u;


    }
    else u = SAVING_FAILED;

    return u;
}





EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    EN_transState_t p,q,r,u,f;
    ST_cardData_t cardData;
    ST_terminalData_t termData ;
    //ST_transaction_t arr_transaction ;
    ST_accountsDB_t accountRefrence ;

    if(q== 3)
    {
        p = FRAUD_CARD;
        return p;
    }

    else if(r == 4 )
    {
        p = DECLINED_INSUFFECIENT_FUND;
        return p;
    }
    else if (f == 1)
    {
        p= DECLINED_STOLEN_CARD;
        return p;
    }
    else if(u == 1)
    {
        p = INTERNAL_SERVER_ERROR;
        return p;
    }
else
    {

    printf("your balance before transaction %f\n",arr_account[m].balance) ;
    arr_account[m].balance = (arr_account[m].balance - transData->terminalData.transAmount );
    printf ("amount transfered %f\n",transData->terminalData.transAmount) ;
    printf("your updated new balance is %f\n",arr_account[m].balance);

    p = APPROVED ;
    }
return p ;
}

//transData->terminalData.transAmount = (termData.transAmount) ;
//arr_account[m].balance = (arr_account[m].balance - termData.transAmount );
  //transData->terminalData.transAmount



/*
int main()
{

    ST_cardData_t cardData;
    ST_accountsDB_t accountRefrence;
    ST_transaction_t transData;
    EN_transState_t a,b,c,d,e,z;
    z = getCardPAN(&cardData) ;
    a = isValidAccount(&cardData,&accountRefrence);


    //e=recieveTransactionData(&transData);

    return 0 ;
}*/
