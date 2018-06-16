/*
 * Order.h
 *
 *  Created on: 22 maj 2018
 *      Author: Bartosz
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <iostream>
#include "Room.h"
#include <vector>

namespace std {

class Order {
public:
	// constructors
	Order(unsigned int orderId, unsigned int userID, unsigned int roomId, string date, string startHour, unsigned int duration);
	virtual ~Order();
	unsigned int getOrderId() const;
	void setOrderId(unsigned int orderId);
	unsigned int getRoomId() const;
	void setRoomId(unsigned int roomId);
	unsigned int getDuration() const;
	void setDuration(unsigned int duration);
	const string& getDate() const;
	void setDate(const string& date);
	const string& getStartHour() const;
	void setStartHour(const string& startHour);
	bool checkAvail(vector<Room> rooms, unsigned int bookRoom, string bookDate, string startTime, unsigned int duration);
	const string getTimeFrame() const;
	static unsigned int getOrderQty();
	unsigned int getUserId() const;

	//const string toString() const;

private:
	// variables
	unsigned int orderId;
	unsigned int roomId;
	unsigned int userID;
	string startHour;
	string date;
	unsigned int duration;

};

} /* namespace std */

#endif /* ORDER_H_ */
