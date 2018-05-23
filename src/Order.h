/*
 * Order.h
 *
 *  Created on: 22 maj 2018
 *      Author: Bartosz
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <iostream>

namespace std {

class Order {
public:
	// constructors
	Order(unsigned int orderId, unsigned int roomId, string date);
	virtual ~Order();
	const string& getDate() const;
	void setDate(const string& date);
	unsigned int getOrderId() const;
	void setOrderId(unsigned int orderId);
	unsigned int getRoomId() const;
	void setRoomId(unsigned int roomId);
	const string toString() const;

private:
	// variables
	unsigned int orderId;
	unsigned int roomId;
	string date;

};

} /* namespace std */

#endif /* ORDER_H_ */
