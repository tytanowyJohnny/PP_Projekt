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

#include "Room.h"


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
		cout << "You need to select from between available options." << endl;
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

/*
 * GENERAL FUNCTION
 */

int main() {

	// Variables
	int choosedOption; // stores option choosed from main menu

	vector<Room> rooms; // vector for storing rooms data


	// display header
	cout << "----------------------------------------------------------------" << endl;
	cout << "Conference Room Manager ver. 0.1" << endl;
	cout << "Component 1/4, Bartosz Kubacki/Bartlomiej Urbanek" << endl;
	cout << "----------------------------------------------------------------" << endl;

	cout << endl;

	// load all data from files
	string roomsData = loadRoomsFile();

	// convert raw data to objects
	string delimiter_1 = ";";
	string delimiter_2 = ",";
	size_t pos = 0;

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
				for(Room tempRoom : rooms) {

					cout << tempRoom.getRoomId() << ". " << tempRoom.getRoomName() << " -> [" << tempRoom.getRoomCost() << "z³] - " << tempRoom.getRoomType() << ", " << tempRoom.getRoomSpace() << " os." << endl;
				}

				// go back to main menu
				continue;

				break;
			}
			case 2:
				break;
			case 3:
				break;
			default:
				break;
		}
	}

	return 0;
}
