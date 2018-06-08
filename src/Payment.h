/*
 * Payment.h
 *
 *  Created on: 31 maj 2018
 *      Author: Beata
 */

#ifndef PAYMENT_H_
#define PAYMENT_H_


#include <iostream>

using namespace std;

enum PaymentType {
	CreditCard,
	Transfer
};

class Payment {
private:
	PaymentType paymentType;
	bool isPending;
	bool isAccepted;
	string date;
	double price;
	string getPaymentTypeDescription ();

public:
	virtual ~Payment();
	Payment(PaymentType paymentType, double price);
	void setIfAccepted (bool isAccepted);
	void setIfPending (bool isPending);
	string getPaymentSummary();
};

#endif /* PAYMENT_H_ */
