/*
 * Payment.cpp
 *
 *  Created on: 31 maj 2018
 *      Author: Beata
 */

#include "Payment.h"
#include <string>
#include <time.h>



Payment::Payment(PaymentType paymentType, double price) {
	this->paymentType = paymentType;
	this->price = price;

	time_t _tm = time(NULL);

	struct tm *curtime = localtime(&_tm);
	this->date = asctime(curtime);
}


string Payment::getPaymentTypeDescription () {
	switch (this->paymentType) {
		case CreditCard:
			return "Credit Card";

		case Transfer:
			return "Bank Transfer";

		default:
			return "-";

	}
}



void Payment::setIfAccepted (bool isAccepted) {
	this->isAccepted = isAccepted;
}

void Payment::setIfPending (bool isPending) {
	this->isPending = isPending;
}

string Payment::getPaymentSummary () {
	string isPendingString = this->isPending ? "pending" : "finished";
	string isAcceptedString = this->isAccepted ? "accepted" : "rejected";
	string result = this->date + "\t" + this->getPaymentTypeDescription() + "\t" + isPendingString + "\t" + isAcceptedString;

	return result;
}

Payment::~Payment() {

}

