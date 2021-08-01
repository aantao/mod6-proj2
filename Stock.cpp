#include "Stock.h"
#include <iomanip>

Stock::Stock(string n, string sym, int num, double pr):
	name(n), symbol(sym), num_shares(num), price(pr) { };

string Stock::getName(){
	return name;
}

string Stock::getSymbol(){
	return symbol;
}

double Stock::getPrice(){
	return price;
};

int Stock::getNumShares(){
	return num_shares;
};

string Stock::getString(){
	std::ostringstream stream;
   stream << std::left << std::setw(5) << symbol << ": "  << std::setw(4) << num_shares 
		 << " @ $" << std::fixed 
		 << std::setprecision(2) << price << endl;
   std::string str =  stream.str();
	return str;
}

void Stock::setName(string s){
	name = s;
};

void Stock::setSymbol(string s){
	symbol = s;
};

void Stock::setPrice(double p){
	price = p;
};

void Stock::setShares(double s){
	num_shares = s;
};

double Stock::buyShares(int num, double acctBal){
	double cost;

	cost = this->price * num;

	// check number of shares is available
	// check that balance supports purchase
	if ( (num < num_shares) && (cost <= acctBal) ){
			this->num_shares = this->num_shares - num;
			return cost;
	}
	else
		return 0.0;
};

double Stock::sellShares(int num){
	this->num_shares = this->num_shares + num;
	return num * this->getPrice();
};

ostream& operator<<(ostream& os, const Stock& st) {
    os << std::left << std::setw(4) << st.symbol << ": "  << std::setw(4)<< st.num_shares 
		 << " @ $" << std::setw(8) << std::right << std::fixed 
		 << std::setprecision(2) << std::put_money(st.price * 100) << " = " 
		 << "$ " << std::setw(11) << std::put_money(st.num_shares * st.price * 100) ;

    return os;
}



