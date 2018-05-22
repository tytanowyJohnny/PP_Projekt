/*
 * Order.cpp
 *
 *  Created on: 22 maj 2018
 *      Author: Bartosz
 */

#include "Order.h"

namespace std {

Order::Order(unsigned int orderId, unsigned int roomId, string date) {

	this->orderId = orderId;
	this->roomId = roomId;
	this->date = date;

}

Order::~Order() {
	// TODO Auto-generated destructor stub
}

const string& Order::getDate() const {
	return date;
}

void Order::setDate(const string& date) {
	this->date = date;
}

unsigned int Order::getOrderId() const {
	return orderId;
}

void Order::setOrderId(unsigned int orderId) {
	this->orderId = orderId;
}

unsigned int Order::getRoomId() const {
	return roomId;
}

void Order::setRoomId(unsigned int roomId) {
	this->roomId = roomId;
}

} /* namespace std */
