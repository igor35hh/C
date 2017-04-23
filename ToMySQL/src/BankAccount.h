/*
 * BankAccount.h
 *
 *  Created on: Apr 22, 2017
 *      Author: user
 */

#ifndef BANKACCOUNT_H_
#define BANKACCOUNT_H_

#include <string>
using std::string;

class BankAccount {
public:
	static const int MAX_SIZE = 30;

	BankAccount(int=0, string="", string="", double=0.0);
	virtual ~BankAccount();

	void setAccountNumber(int);
	void setLastName(string);
	void setFirstName(string);
	void setBalance(double);

	int getAccountNumber() const;
	string getFirstName() const;
	string getLastName() const;
	double getBalance() const;

private:
	int accountNumber;
	char firstName[MAX_SIZE];
	char lastName[MAX_SIZE];
	double balance;

};

#endif /* BANKACCOUNT_H_ */
