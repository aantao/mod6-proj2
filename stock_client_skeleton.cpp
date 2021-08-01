/*
 * stock_client_skeleton.cpp -- 
 * skeleton code for a stream socket client for a stock market simulation
 * EK -- July 2021 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "Account.h"

// the port client will be connecting to 
#define PORT 3500 

// max number of bytes we can get at once 
#define MAXDATASIZE 5000 

/*
 * requestListing sends an "L" to the server 
 * and receives a buffer containing the current stock
 * listing in response.  It then displays the listing 
 */ 
void requestListing(int sockfd){
	int numbytes;
	char buf[MAXDATASIZE];

	/* send Listing request code (L) to server */
	if (send(sockfd, "L\n", 3, 0) == -1)
		perror("send L");

	/* wait for response */
	if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
	    perror("recv");
	    exit(1);
	}

	/* dislay response */
	buf[numbytes] = '\0';
	printf("\n    **** Market Stock Listing ***     \n");
	printf("%s\n",buf);
	return;
}

/* 
 * requestBuy prompts the user to enter the symbol and 
 * number of shares to buy. It fills a buffer with the
 * request in the format below and sends the request
 * to the server:
 * 	B symbol quantity balance 
 * 
 * The server will check that sufficient shares exist
 * in the market to fulfill the buy and also that the
 * client's balance is sufficient to cover the cost.
 * If conditions are met, the server will decrement
 * the number of shares of that stock in the market
 * accordingly. 
 * 
 * The server's response includes:
 * 	name symbol quantity cost_per_share total_cost
 * 
 * If the total_cost is 0.0 the client can conclude
 * that the purchase failed either because too few
 * shares were available or their cash balance was
 * insufficient to cover the purchase.
 * If the purchase was successful, the client records
 * the purchase in their account.
 */
void requestBuy(int sockfd, Account &acc){
	int numbytes;
	char buf[MAXDATASIZE];
	char sym[5];
	int quantity;

	// prompt user for purchase data
	printf("What stock symbol to buy? ");
	scanf("%s", sym);
	
	printf("How many to buy? ");
	scanf("%d", &quantity);

	// construct request in buffer 
	sprintf(buf, "B %s %d %f\n", sym, quantity, acc.getBalance());

	/* send buy request code to server */
	if (send(sockfd, buf, strlen(buf), 0) == -1)
		perror("send buy request");

	//receive response from server
	if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
	    perror("recv");
	    exit(1);
	}
	buf[numbytes] = '\0';

	// parse out elements of response 
	string name = strtok(buf, ",\n");
	string symbol = strtok(NULL, ",\n");
	int q = atoi(strtok(NULL, ",\n"));
	double cps = atof(strtok(NULL, ",\n"));
	double cost = atof(strtok(NULL, ",\n"));

	// record purchase if successful
	if (cost > 0.0){
		acc.recordPurchase(name, symbol, q, cps);
	}
	// display error message if unsuccessful
	else
		printf("===> Purchase failed: insufficient quantity or funds \n");

	return;
}

/* 
 * requestLimitBuy prompts the user to enter the symbol and 
 * number of shares to buy and the limit_price.
 * It fills a buffer with the request in the format below 
 * and sends the request to the server:
 * 	b symbol quantity limit_price balance 
 * The server will check that sufficient shares exist
 * in the market to fulfill the buy and also that the
 * client's balance is sufficient to cover the cost.
 * If conditions are met, the server will decrement
 * the number of shares of that stock in the market
 * accordingly. 
 * The server's response includes:
 * 	name symbol quantity cost_per_share total_cost
 * If the total_cost is 0.0 the client can conclude
 * that the purchase failed either because too few
 * shares were available or their cash balance was
 * insufficient to cover the purchase or the current
 * share price on the market is too high.
 * If the purchase was successful, the client records
 * the purchase in their account.
 */
void requestLimitBuy(int sockfd, Account &acc){
	// You: declare needed variables


	// You: prompt user for purchase data 

	// You: fill buffer with Limit Buy (b) request

	// You: send Limit Buy request to server 

	// You: get response from server

	// You: parse out elements of server response 

	// You: record purchase if successful 
	// You: display error message if unsuccessful

	return;
}


/* 
 * requestSell prompts the user to enter the symbol and 
 * number of shares to sell.
 * It checks that the client account has enough shares
 * of that stock to cover the sale.  If so, it fills
 * a buffer with the request in the format below 
 * and sends the request to the server:
 * 	S symbol quantity 
 * 
 * The server's response includes:
 * 	symbol quantity cost_per_share proceeds
 *
 * The client records the purchase in their account.
 */
void requestSell(int sockfd, Account &acc){
	// You: declare needed variables

	// You: prompt user for sale data

	// You: check that the client owns sufficent shares to sell

	// You: if so ..
		// You: prepare the buffer to send to server(S, symbol, quantity)

		// You: send sell request to server(S,symbol,quantity);

		// You: get response from server

		// You: parse response into sym, quantity, cps, and proceeds

		//You: record the sale in the client account

	return;
}

/* 
 * requestLimitSell prompts the user to enter the symbol and 
 * number of shares to sell and the limit_price.
 * It fills a buffer with the request in the format below 
 * and sends the request to the server:
 * 	s symbol quantity limit_price 
 * The server will check that the market price 
 * is the limit_price or higher.  
 * If the condition is met, the server will increment
 * the number of shares of that stock in the market
 * accordingly. 
 * The server's response includes:
 * 	symbol quantity cost_per_share proceeds
 * If the proceeds are 0.0 the client can conclude
 * that the sale failed because the limit
 * price was not met (i.e., the current share price is too low)
 * If the purchase was successful, the client records
 * the purchase in their account.
 */
void requestLimitSell(int sockfd, Account &acc){
	// You: declare needed variables 


	// You: prompt user for sale data

	// You: if account has sufficient number of shares 
		// You: prepare the buffer to send to server(S, symbol, quantity)

		// You: send sell request to server(S,symbol,quantity);

		// You: get response from server

		// You: parse response into sym, quantity, cps, and proceeds

		// You: if successful, record the sale in client account
		 else 
			printf("Current share price did not meet limit \n");
	}	

	return;
}

/*
 * requestExit informs the server that the client is disconnecting
 * and closes the sockfd from the client side 
 */
void requestExit(int sockfd){
	// You: declare needed variables

	// You: send exit request code (X) to server 

	//  You: receive a confirmation from the server
	//  and display ...
	printf("Received: %s",buf);

	// You: close socket through which client has been communicating with server

	return;
}

/*
 * save_account_info prompts the user for a file name for the account info
 * and invokes the Account class's saveAccount method.
 */
void save_account_info(int sockfd, Account &acc){
	char fname[50];

	printf("Please enter filename for saved account info: ");
	scanf("%s", fname);
	printf("Saving account info to %s and exiting \n", fname);
	acc.saveAccount(fname);
	return;
}

/*
 * show_menu() displays a simple text-based menu
 * and returns the user's response 
 */
int show_menu(){
   int resp;

	printf("Enter the number of a desired action, or 0 to save & exit\n");
	printf(" ******************************************************* \n");
	printf("  1 - Display account info \n");
	printf("  2 - Get list of available stocks & prices \n");
	printf("  3 - Buy shares of a stock at market price \n");
	printf("  4 - Sell shares of a stock at market price \n");
	printf("  5 - Buy shares of a stock at specified limit \n");
	printf("  6 - Sell shares of a stock at specified limit \n");
	printf("  0 - Save account to file and exit \n");
	printf(" *******************************************************  \n");
	printf(" Choice: ");
	scanf("%d", &resp);
	return resp;
}

/*
 * the main method:
 * 1 - parses ot the command line parameters (hostname and accountname)
 * 2 - establishes a stream socket connection with the server
 * 3 - creates an Account object (invokes the Account constructor with
 *     the provided accountname as a parameter)
 * 4 - provides a main control loop that invokes show_menu and 
 *     then calls the appropriate method based on the response received.
 */
int main(int argc, char *argv[])
{
	int sockfd, numbytes;  
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr; // connector's address information 

	// You: check the number of command line parameters: 
	// should be: ./stock_client host account name 

	/* You: get the host info */


	/* You: create a socket */


	/* You: set up the address info */


	/* You: connect to the stock_server */


	/* open the local account file */
	Account acc("acct1.txt");


	int response;
	char dummy;

	response = show_menu();

	while ((response >= 0) && (response <= 6)){
		switch(response){
			case 1: 
				cout << endl << "Account Information: " << endl;
				cout << "******************************************* " << endl;
				acc.showAccountInfo();
				cout << endl << "******************************************* " 
				<< endl << endl;
				cout <<  "Press any key to continue " << endl;
				cin >> dummy;
				break;

			case 2: 
				requestListing(sockfd);
				cout <<  "Press any key to continue " << endl;
				cin >> dummy;
				break;

			case 3: 
				requestBuy(sockfd, acc);
				cout <<  "Press any key to continue " << endl;
				cin >> dummy;
				break;

			case 4: 
				requestSell(sockfd, acc);
				cout <<  "Press any key to continue " << endl;
				cin >> dummy;
				break;

			case 5: 
				requestLimitBuy(sockfd, acc);
				cout <<  "Press any key to continue " << endl;
				cin >> dummy;
				break;

			case 6: 
				requestLimitSell(sockfd, acc);
				cout <<  "Press any key to continue " << endl;
				cin >> dummy;
				break;

			case 0: 
				save_account_info(sockfd, acc);
				requestExit(sockfd);
				exit(0);
			default:
				printf("Bad input \n");
				
		}
		response = show_menu();
	}

	return 0;
}



