#include "Account.h"

using namespace std;

Account::Account():balance(0.0){};

Account::Account(string fname){
	FILE *input;
   char *line = NULL;
   size_t len = 0;
   ssize_t nread;

   char *name;
   char *sym;
   double price;
   int quantity;

	/* open file of acount info */
   input = fopen(fname.c_str(), "r");
   if (input == NULL) {
      perror("fopen");
      exit(1);
   }

	/* read in account balance */
   if ((nread = getline(&line, &len, input)) != -1) {
		this->balance = atof(strtok(line, "\n"));
	}
	else{
      perror("read balance ");
      exit(1);
	}	


   /* while the file is not empty */
	/* read in the stock holdings */
   while ((nread = getline(&line, &len, input)) != -1) {
      sym = strtok(line, ",\n");
      while (sym != NULL){
         name = strtok(NULL, ",\n");
         price = atof(strtok(NULL, ",\n"));
         quantity = atoi(strtok(NULL, ",\n"));
         Stock *s = new Stock(name, sym, quantity, price);
         StockMap.insert(pair<string, Stock>(sym, *s));
         sym = strtok(NULL, ",\n");
      }
   }
   fclose(input);

};

double Account::getBalance(){
	return balance;
}

bool Account::ownsStock(string sym){
	map <string, Stock>::iterator it;
   it = StockMap.find(sym.c_str());

	if (it == StockMap.end()){
		return false;
	}
	else
		return true;
}

bool Account::hasNumShares(string sym, int quant){
	map <string, Stock>::iterator it;
   it = StockMap.find(sym.c_str());

	if (it == StockMap.end())
		return false;
	else
		return (it->second.getNumShares() >= quant);
}

//}  Extra Braces??

void Account::recordPurchase(string name, string sym, int quant, double cps){
	map <string, Stock>::iterator it;

	// find Stock object 
   it = StockMap.find(sym.c_str());

	if (it == StockMap.end()){ // not found
		// create Stock object 
		Stock *s = new Stock(name, sym, quant,cps);
		cout << "===> Purchase recorded " << endl;
		StockMap.insert(pair<string, Stock>(sym, *s));
		this->balance = this->balance - (quant * cps);
	}
	else{ // found
		it->second.setShares(it->second.getNumShares() + quant);
		this->balance -= (quant * cps);
		cout << "===> Purchase recorded " << endl;
	}	
}

void Account::recordSale(string sym, int quant, double cps){
	map <string, Stock>::iterator it;

	// find Stock object 
   it = StockMap.find(sym.c_str());
	if (it == StockMap.end()){ 
		// not found
		printf("Stock not found in account \n");
	}
	else{ // found
		// update stock quantity 
		it->second.setShares(it->second.getNumShares() - quant);
		if (it->second.getNumShares() == 0){
			StockMap.erase(sym);		
		}
		cout << "===> Sale recorded " << endl;
		// update account balance
		this->balance += quant * cps;
	}	
}
void Account::showAccountInfo(){
	double value = 0.0;
	cout.imbue(std::locale(""));
	cout << "Cash:	" << std::setw(19) << "$ " << fixed << std::setprecision(2) 
		  << std::setw(11) << std::put_money( this->balance * 100) << endl;
	value = value + this->balance;
	map <string, Stock>::iterator it;
   for (it = StockMap.begin(); it != StockMap.end(); ++it){
      cout << it->second << endl;
		value = value + it->second.getPrice() * it->second.getNumShares();
   }
	cout << "-------------------------------------------" << endl;
   cout << "Total: " << std::setw(20) << "$ " << std::right << std::fixed
		  << std::setprecision(2) << std::setw(11) 
		  << std::put_money(value * 100) << endl;

	return;
};

void Account::saveAccount(char *fname){
	FILE *output;
	char line[80];

	/* open file for account info */
   output = fopen(fname, "w");
   if (output == NULL) {
      perror("fopen");
      exit(1);
   }

	fprintf(output, "%.2f\n", balance);
	map <string, Stock>::iterator it;
   for (it = StockMap.begin(); it != StockMap.end(); ++it){
      fprintf(output, "%s,%s,%.2f,%d\n", it->second.getSymbol().c_str(), 
			it->second.getName().c_str(), it->second.getPrice(), 
			it->second.getNumShares());
	}

	fclose(output);	
}

ostream& operator<<(ostream& os, Account acc){
	return os << acc.balance << endl;
};

