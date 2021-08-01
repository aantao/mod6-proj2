#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <string.h>
#include <map>
#include <iostream>
#include <iomanip>
#include "Stock.h"
#include "Account.h"

using namespace 

/*
 * class Account manages a stock market client's account data:
 *  a cash balance
 *  a collection of stocks, as a mapping from symbols to Stock objects
 */

class Account {

//displays the account listing
friend ostream& operator<<(ostream& os, Account acc);

public:
	// if no account data yet exists
	Account();					

	// if an account filename is provided
	Account(string fname);	

	// returns cash balance
	double getBalance();		

	// does the client own this stock?
	bool ownsStock(string sym);	

	//does the client own this many shares?
	bool hasNumShares(string sym, int quant); 

	// record a stock purchase in the client account
	void recordPurchase(string name, string sym, int quant, double cps);

	// record a stock sale in the client account
	void recordSale(string sym, int quant, double cps);

	//display account info
	void showAccountInfo();

	//save account info to a file
	void saveAccount(char *fname);

private:
	map <string, Stock> StockMap;
	double balance;
};

#endif

