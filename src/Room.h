/*
 * ConfRoom.h
 *
 *  Created on: 22 kwi 2018
 *      Author: Bartosz Kubacki
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <iostream>

using namespace std;

class Room {
public:
	// constructors
	Room(unsigned int roomID, unsigned int roomType, string roomName, unsigned int roomSpace, unsigned int roomCost);
	virtual ~Room();

	// getters and setters
	unsigned int getRoomCost() const;
	void setRoomCost(unsigned int roomCost);
	unsigned int getRoomId() const;
	void setRoomId(unsigned int roomId);
	const string& getRoomName() const;
	void setRoomName(const string& roomName);
	unsigned int getRoomSpace() const;
	void setRoomSpace(unsigned int roomSpace);
	const string getRoomType() const;
	void setRoomType(unsigned int roomType);
	const string toString() const;

private:
	// variables
	unsigned int roomID;
	unsigned int roomSpace;
	unsigned int roomCost;
	unsigned int roomType;
	string roomName;

};

#endif /* ROOM_H_ */
