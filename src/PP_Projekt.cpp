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
				unsigned int choice;
				// get date in format yyyy-mm-dd
				time_t t = time(0);
				tm* now = localtime(&t);

				stringstream tempStream;
				tempStream << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << now->tm_mday;

				string formattedDate = tempStream.str();

				cout << "Choose which room you would like to order:" << endl;
				cout << endl;
				showRooms(rooms);
				cout << endl;
				cout << "Your choice: ";
				cin >> choice;

				// check if correct value
				while(cin.fail() || choice > rooms.size()) {

					// if not, clear cin
					cin.clear();
					cin.ignore(256, '\n');
					cout << "You need to select from available options." << endl;
					cout << "Your choice: ";
					cin >> choice;
				}

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
