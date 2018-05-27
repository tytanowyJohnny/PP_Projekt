//============================================================================
// Name        : PP_Projekt.cpp
// Author      : Bartosz Kubacki
// Version     : 0.1
// Copyright   : All rights reserved
// Description : Conference Room Manager
//============================================================================

#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <regex>

#include "Room.h"
#include "Order.h"


using namespace std;

// Functions

/**
 * Shows Main Menu of the application
 */
int showMainMenu() {

	// Variables
	int choosedOption; // choosed option at Main Menu

	// Main menu for this component
	cout << endl;
	cout << "What would you like to do?" << endl;
	cout << "1. Check actual prices" << endl;
	cout << "2. Book a conference room" << endl;
	cout << "3. Manage my orders" << endl;
	cout << endl;
	cout << "Your choice (1-3): ";

	// Save user choice (must input correct option)
	cin >> choosedOption;

	// check if correct value
	while(cin.fail() || choosedOption > 3 || choosedOption < 1) {

		// if not, clear cin
		cin.clear();
		cin.ignore(256, '\n');
		cout << "You need to select from available options." << endl;
		cout << "Please choose number from 1 to 3: ";
		cin >> choosedOption;
	}

	return choosedOption;

}

string loadRoomsFile() {

	fstream roomsFile;
	string buffer;

	roomsFile.open("rooms.txt");


	if(roomsFile.is_open()) {

		buffer.assign( (istreambuf_iterator<char>(roomsFile) ), (istreambuf_iterator<char>()));
	}

	roomsFile.close();

	return buffer;
}

string loadOrdersFile() {

	fstream ordersFile;
	string buffer;

	ordersFile.open("orders.txt");

	if(ordersFile.is_open()) {

		buffer.assign( (istreambuf_iterator<char>(ordersFile) ), (istreambuf_iterator<char>()));
	}

	ordersFile.close();

	return buffer;
}

void showRooms(const vector<Room>& rooms) {
	// list rooms with prices
	for (Room tempRoom : rooms) {
		cout << tempRoom.getRoomId() << ". " << tempRoom.getRoomName()
				<< " -> [" << tempRoom.getRoomCost() << "z³] - "
				<< tempRoom.getRoomType() << ", " << tempRoom.getRoomSpace()
				<< " os." << endl;
	}
}

void showRoomAvail(unsigned int roomID, vector<Order>& orders) {

	bool empty = true;
	stringstream ss;
	int counter = 1;

	for(Order tempOrder : orders) {

		if(tempOrder.getRoomId() == roomID) {

			ss << counter << ". " << tempOrder.getDate() << "\n";

			if(empty)
				empty = false;
		}
	}

	if(empty) { // there are no orders for this room

		cout << "This room has not been booked any anyone yet!" << endl;

	} else { // list already booked dates

		cout << "This room is already unavailable at below time:" << endl;
		cout << ss.str() << endl;
	}
}
/*
 * GENERAL FUNCTION
 */

int main() {

	// Variables
	int choosedOption; // stores option choosed from main menu

	vector<Room> rooms; // vector for storing rooms data
	vector<Order> orders; // vector for strong orders data


	// display header
	cout << "----------------------------------------------------------------" << endl;
	cout << "Conference Room Manager ver. 0.1" << endl;
	cout << "Component 1/4, Bartosz Kubacki/Bartlomiej Urbanek" << endl;
	cout << "----------------------------------------------------------------" << endl;

	cout << endl;

	// load all data from files
	string roomsData = loadRoomsFile();
	string ordersData = loadOrdersFile();

	// setup delimiters
	const string delimiter_1 = ";";
	const string delimiter_2 = ",";
	size_t pos = 0;

	/**
	 * rooms.txt to vectors
	 */

	// used to store tokens
	vector<string> roomTokens;

	// explode string loaded from file into separate objects in vector
	while((pos = roomsData.find(delimiter_1)) != string::npos) {

		roomTokens.push_back(roomsData.substr(0, pos));
		roomsData.erase(0, pos + delimiter_1.length());
	}

	// used to store single room details
	vector<string> tempRoomDetails;

	for(string s : roomTokens) {

		while((pos = s.find(delimiter_2)) != string::npos) {

			tempRoomDetails.push_back(s.substr(0, pos));
			s.erase(0, pos + delimiter_2.length());
		}
		rooms.push_back(Room(stoi(tempRoomDetails[0]), stoi(tempRoomDetails[1]), tempRoomDetails[2], stoi(tempRoomDetails[3]), stoi(tempRoomDetails[4])));
		tempRoomDetails.clear();
	}

	/**
	 * orders.txt to vectors
	 */

	// used to store tokens
	vector<string> orderTokens;

	// explode string loaded from file into separate objects in vector
	while((pos = ordersData.find(delimiter_1)) != string::npos) {

		orderTokens.push_back(ordersData.substr(0, pos));
		ordersData.erase(0, pos + delimiter_1.length());
	}

	// used to store single order details
	vector<string> tempOrderDetails;

	for(string s: orderTokens) {

		while((pos = s.find(delimiter_2)) != string::npos) {

			tempOrderDetails.push_back(s.substr(0, pos));
			s.erase(0, pos + delimiter_2.length());
		}
		orders.push_back(Order(stoi(tempOrderDetails[0]), stoi(tempOrderDetails[1]), tempOrderDetails[2]));
		tempOrderDetails.clear();
	}



	// start loop, makes it possible to go back
	while(true) {
		//show MainMenu
		choosedOption = showMainMenu();

		//handle choosedOption
		switch(choosedOption) {

			case 1:
			{
				// get date and time
				auto temp_time = chrono::system_clock::now();
				time_t actual_time = chrono::system_clock::to_time_t(temp_time);

				cout << "--------------------------------------------------" << endl;
				cout << "Room prices for: " << ctime(&actual_time) << endl;
				cout << "--------------------------------------------------" << endl;

				// list rooms with prices
				showRooms(rooms);

				break;
			}
			case 2:
			{
				// vars
				unsigned int choosedRoom;
				string startTime;
				string orderDate;

				// get date in format yyyy-mm-dd
				time_t t = time(0);
				tm* now = localtime(&t);

				stringstream tempStream;
				tempStream << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << now->tm_mday;

				string formattedDate = tempStream.str();

				cout << "Choose which room you would like to order:" << endl;
				cout << endl;

				// shows all rooms with already ordered dates
				showRooms(rooms);

				cout << endl;
				cout << "Your choice (press 0 to go back): ";
				cin >> choosedRoom; // save choice

				// check if correct value
				while(cin.fail() || choosedRoom > rooms.size()) {

					// if not, clear cin
					cin.clear();
					cin.ignore(256, '\n');
					cout << "You need to select from available options." << endl;
					cout << "Your choice (press 0 to go back): ";
					cin >> choosedRoom;

				}

				if(choosedRoom == 0) // handle going back to main menu
					continue;

				// show already booked dates for choosed room
				cout << endl;
				showRoomAvail(choosedRoom, orders);

				// get date from user, format: yyyy-m-dd hh:mm
				cout << endl;
				cout << "Enter date to book a room [YYYY-M(M)-D(D)]: ";
				cin.ignore();
				getline(cin, orderDate);
				cout << endl;

				// debug
				cout << orderDate << endl;

				// setup regex
				regex date_match("[2][0][1][8-9]-([1][0-2]|[1-9])-([1-9]|[1-2][0-9]|[3][0-1])");

				// handle invalid input
				while(cin.fail() || !regex_match(orderDate, date_match)) {

					cout << endl;
					cout << "Invalid date format, please enter date in format [YYYY-M(M)-D(D)]: ";

					getline(cin, orderDate);

					//debug
					cout << orderDate << endl;
				}

				// get start hour
				cout << endl;
				cout << "At what time would you like to book a room? (8 - 16) [:00, :15, :30, :45]: ";
				cin >> startTime;

				regex startTime_match("([8-9]|[1][0-6]):([0][0]|[1][5]|[3][0]|[4][5])");

				while(cin.fail() || !regex_match(startTime, startTime_match)) {

					cout << endl;
					cout << "Invalid hour format, please try again: ";
					cin >> startTime;
				}


				// get duration of booking
				cout << endl;

				cout << "Choose for how long you would like to book this room:" << endl;

				cout << endl;

				cout << "1. 30 minutes" << endl;
				cout << "2. 1 hour (60 minutes)" << endl;
				cout << "3. 1 hour 30 minutes (90 minutes)" << endl;
				cout << "4. 2 hours (120 minutes)" << endl;
				cout << "5. Custom length" << endl;

				cout << endl;
				cout << "Your choice: ";
				cin >> choosedRoom;

				while(cin.fail() || choosedRoom > 5 || choosedRoom == 0) {

					cout << "You choosed incorrectly, please try again: ";
					cin >> choosedRoom;
				}


				unsigned int bookingLength;

				switch(choosedRoom) {

					case 1:
						bookingLength = 30;
						break;
					case 2:
						bookingLength = 60;
						break;
					case 3:
						bookingLength = 90;
						break;
					case 4:
						bookingLength = 120;
						break;
					case 5:
					{
						cout << endl;
						cout << "Enter booking length in minutes (a multiply of 30, [30 - 480]): ";
						cin >> bookingLength;

						while(cin.fail() || bookingLength < 30 || bookingLength > 480 || bookingLength % 30 != 0) {

							cout << endl;
							cout << "Incorrect value, please try again: ";
							cin >> bookingLength;
						}
						break;
					}

				}

				// merge start hour with duration
				string hour_delimiter = ":";
				int tempHour;
				int tempMinutes;

				// extract hour and minutes
				pos = startTime.find(hour_delimiter);
				tempHour = stoi(startTime.substr(0, pos));
				tempMinutes = stoi(startTime.substr(pos + hour_delimiter.length(), startTime.length()));

				int totalMinutes = (tempHour * 60) + tempMinutes;

				cout << "========================================" << endl;
				cout << "ORDER SUMMARY" << endl;
				cout << "========================================" << endl;

				cout << endl;

				// TODO: When creating vectors, push new item at position set by its ID from file

				break;
			}
			case 3:
				break;
			default:
				break;
		}
	}

	return 0;
}
