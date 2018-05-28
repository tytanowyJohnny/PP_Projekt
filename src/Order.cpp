/*
 * Order.cpp
 *
 *  Created on: 22 maj 2018
 *      Author: Bartosz
 */

#include "Order.h"
#include "Room.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

namespace std {

Order::Order(unsigned int orderId, unsigned int roomId, string date, string startHour, unsigned int duration) {

	this->orderId = orderId;
	this->roomId = roomId;
	this->startHour = startHour;
	this->duration = duration;
	this->date = date;

}

Order::~Order() {
	// TODO Auto-generated destructor stub
}

/*
const string Order::toString() const {
	stringstream temp;

	temp << "[" << orderId << ", " << roomId << ", " << date << "]";

	return temp.str();
}*/

const string Order::getTimeFrame() const {

	unsigned int hour;
	unsigned int minutes;
	unsigned int totalMinutes;
	size_t pos = 0;
	string delimiter_1 = ":";
	stringstream tempStream;

	pos = startHour.find(delimiter_1);
	hour = stoi(startHour.substr(0, pos));
	minutes = stoi(startHour.substr(pos + delimiter_1.length(), startHour.length()));

	totalMinutes = (hour * 60) + minutes + duration;

	// TODO: You know what to do
	tempStream << startHour << " - " << (totalMinutes / 60) << ":" /* << setprecision(2) << fixed */ << (totalMinutes % 60);

	return tempStream.str();
}

bool Order::checkAvail(vector<Room> rooms, unsigned int bookRoom, string bookDate, string startTime, unsigned int bookDuration) {

	string delimiter_1 = ":";
	size_t pos = 0;

	unsigned int sT_hour;
	unsigned int sT_minutes;
	unsigned int sT_totalMinutes;
	unsigned int sT_startMinutes;

	unsigned int sH_hour;
	unsigned int sH_minutes;
	unsigned int sH_totalMinutes;
	unsigned int sH_startMinutes;

	// for startTime
	pos = startTime.find(delimiter_1);
	sT_hour = stoi(startTime.substr(0, pos));
	sT_minutes = stoi(startTime.substr(pos + delimiter_1.length(), startTime.length()));
	sT_startMinutes = (sT_hour * 60) + sT_minutes;
	sT_totalMinutes = sT_startMinutes + bookDuration;

	// debug:
	cout << "sT_startMinutes: " << sT_startMinutes << endl;
	cout << "sT_totalMinutes: " << sT_totalMinutes << endl;

	// for startHour
	pos = startHour.find(delimiter_1);
	sH_hour = stoi(startHour.substr(0, pos));
	sH_minutes = stoi(startHour.substr(pos + delimiter_1.length(), startHour.length()));
	sH_startMinutes = (sH_hour * 60) + sH_minutes;
	sH_totalMinutes = sH_startMinutes + duration;

	// debug
	cout << "sH_startMinutes: " << sH_startMinutes << endl;
	cout << "sH_totalMinutes: " << sH_totalMinutes << endl;

	for(Room tempRoom : rooms) {

		if(tempRoom.getRoomId() == bookRoom && date == bookDate) {

			if((sT_startMinutes >= sH_startMinutes && sT_startMinutes <= sH_totalMinutes) || (sT_totalMinutes >= sH_startMinutes && sT_totalMinutes <= sH_totalMinutes)) {

				return false;
			}
		}
	}

	return true;
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

const string& Order::getDate() const {
	return date;
}

void Order::setDate(const string& date) {
	this->date = date;
}

const string& Order::getStartHour() const {
	return startHour;
}

void Order::setStartHour(const string& startHour) {
	this->startHour = startHour;
}

} /* namespace std */

unsigned int std::Order::getDuration() const {
	return duration;
}

void std::Order::setDuration(unsigned int duration) {
	this->duration = duration;
}
