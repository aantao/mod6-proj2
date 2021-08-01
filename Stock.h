#ifndef STOCK_H
#define STOCK_H
#include <string>
#include <iostream>

using namespace std;

/*
 * class Stock encapsulates a stock position
 * including name, symbol, price, and numshares 
 * Provides methods used by the stock_server to 
 * to support buying and selling of shares.
 */

class Stock {

friend ostream& operator<<(ostream& os, const Stock& st);

public:
	Stock(string n, string sym, int num, double pr);

	string getName();
	string getSymbol();
	double getPrice();
	int getNumShares();
	string getString();

	void setName(string s);
	void setSymbol(string s);
	void setPrice(double p);
	void setShares(double s);

	double buyShares(int num, double funds);
	double sellShares(int num);

private:
	string name;
	string symbol;
	double price;
	int num_shares;
};

#endif
