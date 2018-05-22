/*
 * ConfRoom.cpp
 *
 *  Created on: 22 kwi 2018
 *      Author: Bartosz Kubacki
 */

#include "Room.h"

#include <string>
#include <sstream>


Room::Room(unsigned int roomID, unsigned int roomType, string roomName, unsigned int roomSpace, unsigned int roomCost) {

	this->roomID = roomID;
	this->roomSpace = roomSpace;
	this->roomCost = roomCost;
	this->roomName = roomName;
	this->roomType = roomType;

}

Room::~Room() {
	// TODO Auto-generated destructor stub
}

const string Room::toString() const {
	stringstream temp;

	temp << "[" << roomID << ", " << roomType << ", " << roomName << ", " << roomSpace << ", " << roomCost << "]";

	return temp.str();
}

unsigned int Room::getRoomCost() const {
	return roomCost;
}

void Room::setRoomCost(unsigned int roomCost) {
	this->roomCost = roomCost;
}

unsigned int Room::getRoomId() const {
	return roomID;
}

void Room::setRoomId(unsigned int roomId) {
	roomID = roomId;
}

const string& Room::getRoomName() const {
	return roomName;
}

void Room::setRoomName(const string& roomName) {
	this->roomName = roomName;
}

unsigned int Room::getRoomSpace() const {
	return roomSpace;
}

void Room::setRoomSpace(unsigned int roomSpace) {
	this->roomSpace = roomSpace;
}

const string Room::getRoomType() const {

	switch(roomType) {

	case 0:
		return "Sala konferencyjna";
	case 1:
		return "Sala komputerowa";
	default:
		return "oops!";
	}

}

void Room::setRoomType(unsigned int roomType) {
	this->roomType = roomType;
}
