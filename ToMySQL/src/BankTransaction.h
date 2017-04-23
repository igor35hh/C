/*
 * BankTransaction.h
 *
 *  Created on: Apr 23, 2017
 *      Author: user
 */

#ifndef BANKTRANSACTION_H_
#define BANKTRANSACTION_H_

#include <mysql.h>
#include <string>

class BankAccount;

using namespace std;

class BankTransaction {
public:
	BankTransaction(const string = "localhost", const string = "", const string = "", const string = "");
	virtual ~BankTransaction();

	void createAccount(BankAccount*);
	void closeAccount(int);
	void deposit(int, double);
	void withdraw(int, double);
	BankAccount* getAccount(int);
	void printAllAccounts();
	void message(string);

private:
	MYSQL* db_conn;
};

#endif /* BANKTRANSACTION_H_ */
