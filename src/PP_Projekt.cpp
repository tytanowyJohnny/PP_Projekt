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
#include <windows.h>
#include <cstdlib>

#include "Room.h"
#include "Order.h"
#include "Payment.h"
#include "User.h"

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

/*
 * Functions for loading data from files
 */

// Load rooms data
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

// load orders data
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


// load users data
string loadUsersFile() {

	fstream usersFile;
	string buffer;


	usersFile.open("users.txt");

	if(usersFile.is_open()) {

		buffer.assign( (istreambuf_iterator<char>(usersFile) ), (istreambuf_iterator<char>()));
	}

	usersFile.close();

	return buffer;
}

/*
 * Other/helper functions
 */

// show all rooms in format "roomID. roomName -> [roomCost z³] - roomType, roomSpace os."
void showRooms(const vector<Room>& rooms) {
	// list rooms with prices
	for (Room tempRoom : rooms) {
		cout << tempRoom.getRoomId() << ". " << tempRoom.getRoomName()
				<< " -> [" << tempRoom.getRoomCost() << "z³] - "
				<< tempRoom.getRoomType() << ", " << tempRoom.getRoomSpace()
				<< " os." << endl;
	}
}

//show only your booked rooms
void yourRooms(const vector<Room>& rooms){

}
//show menu for "manage my rooms"
int ManageMyRooms(){
	int chosenOption;
		// menu for case 3
		cout << endl;
		cout << "What do you want to do?" << endl;
		cout << "1. Delete one of my orders" << endl;
		cout << "2. Edit my orders" << endl;
		cout << "3. Add new one" << endl;
		cout << endl;
		cout << "Your choice (1-3): ";
		// Save user choice (1-3)
		cin >> chosenOption;
		// check if correct value
		while(cin.fail() || chosenOption > 3 || chosenOption < 1) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "You need to select from available options." << endl;
			cout << "Please choose number from 1 to 3: ";
			cin >> chosenOption;
		}
		return chosenOption;
}
// show already booked days for specific room
void showRoomAvail(unsigned int roomID, vector<Order>& orders) {

	bool empty = true;
	stringstream ss;
	int counter = 1;

	for(Order tempOrder : orders) {

		if(tempOrder.getRoomId() == roomID) {

			ss << counter << ". " << tempOrder.getDate() << " " << tempOrder.getTimeFrame() << "\n";

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



int showPaymentMenu () {

	int selectedOption;

	// Main menu for this component
	cout << endl;
	cout << "How would you like to pay?" << endl;
	cout << "1. Use my credit card (master card only)" << endl;
	cout << "2. Use transfer" << endl;
	cout << "3. Cancel Order" << endl;
	cout << endl;
	cout << "Your choice (1-3): ";

	// Save user choice (must input correct option)
	cin >> selectedOption;

	// check if correct value
	while(cin.fail() || selectedOption > 3 || selectedOption < 1) {

		// if not, clear cin
		cin.clear();
		cin.ignore(256, '\n');
		cout << "You need to select from available options." << endl;
		cout << "Please choose number from 1 to 3: ";
		cin >> selectedOption;
	}

	return selectedOption;
}



int Register(vector<User> users){
	unsigned int userID;
	string inputLogin;
	string inputPassword;
	string inputFullName;
	string inputFirstName;
	string inputLastName;
	string inputPhoneNumber;
	string inputMailAddress;
	int tryOrback;
	bool registerIncomplete = true;

	while(registerIncomplete){

		cout <<endl;
		cout << "Please enter your Login:"<<endl;
		cin >> inputLogin;

		cout << "Please enter your password:"<<endl;
		cin >> inputPassword;

		cout << "Please enter your first name:"<<endl;
		cin >> inputFirstName;

		cout << "Please enter your last name:"<<endl;
		cin >> inputLastName;
		inputFullName += inputFirstName;
		inputFullName += " ";
		inputFullName += inputLastName;

		cout << "Please enter your phone number:"<<endl;
		cin >> inputPhoneNumber;

		cout << "Please enter your @ address:"<<endl;
		cin >> inputMailAddress;

		cout <<"If the data is correct?"<<endl;
		cout <<"Login: "<< inputLogin<<endl;
		cout <<"Password: "<< inputPassword<<endl;
		cout <<"Full name: " <<inputFullName<<endl;
		cout <<"Phone number: "<< inputPhoneNumber<<endl;
		cout <<"Mail Address: " << inputMailAddress<<endl;
		cout <<endl;
		cout <<"Yes, go to Main Menu. 	 (Press 1)"<<endl;
		cout <<"No, enter again.         (Press 2)"<<endl;
		cout <<"Go back to Welcome Menu. (Press 0)"<<endl;
		cin >> tryOrback;
		// check if correct value
							while(cin.fail() || tryOrback > 2 || tryOrback < 0) {

								// if not, clear cin
								cin.clear();
								cin.ignore(256, '\n');
								cout << "You need to select from available options." << endl;
								cout << "Please choose number from 0 to 2: ";
								cin >> tryOrback;
							}

		if (tryOrback==1){
			registerIncomplete=false;
			userID=users.size();

				fstream usersFile;

				usersFile.open("users.txt", ios::app);
				usersFile <<userID<<","<<inputLogin<<","<<inputPassword<<","<<inputFullName<<","<<inputPhoneNumber<<","<<inputMailAddress<<";";

				usersFile.close();
		}

		else if (tryOrback==2){

			cout<<"Please enter the data again."<<endl;
			inputFullName.clear();
		}

		else if (tryOrback==0){
			userID=0;
			break;}
	}

	return userID;
}

int LogIn (vector<User> users){
	unsigned int userID;
	string inputLogin;
	string inputPassword;
	bool loginFailed = true;
	int tryOrback;

while(loginFailed){

	cout<<endl;
	cout << "Please enter your Login:"<<endl;
	cin >> inputLogin;

	cout << "Please enter your password:"<<endl;
	cin >> inputPassword;


	for (int i =0; i<=users.size()-1; i++){

		if ((users[i].userLogin==inputLogin) && (users[i].userPassword==inputPassword)){
			cout<<"Access granted. Welcome "<<users[i].getUserFullName()<<endl;
			userID=users[i].getUserId();
			loginFailed = false;
			break;
		}
		else if (i==users.size()-1){
			cout << "Login or password incorrect! "<<endl;
			cout<<	"Press 1 to try again or 0 to go back."<<endl;
			cin >> tryOrback;

			if (tryOrback==1)
				break;

			else{
			// check if correct value
					while(cin.fail() || tryOrback > 1 || tryOrback < 0) {

						// if not, clear cin
						cin.clear();
						cin.ignore(256, '\n');
						cout << "You need to select from available options." << endl;
						cout << "Please choose number from 0 to 1: ";
						cin >> tryOrback;
					}

			}
		}

	}
	if (tryOrback==0){
		userID=0;
		break;}
}
return userID;
}

int showWelcomeMenu () {
	int loginOption;

	//Welcome information

	cout<<endl;
	cout<<"Welcome information..."<<endl;
	cout<<"----------------------------------------------------------------"<<endl;

	// Main menu for this component

	cout<<"Choose options to continue..."<<endl;
	cout<<"1. Log in"<<endl;
	cout<<"2. New customer? Create your account!"<<endl;
	cout<<"3. Continue as Guest"<<endl;
	cout << endl;
	cout << "Your choice (1-3): ";

	// Save user choice (must input correct option)
	cin >> loginOption;
	// check if correct value
		while(cin.fail() || loginOption > 3 || loginOption < 1) {

			// if not, clear cin
			cin.clear();
			cin.ignore(256, '\n');
			cout << "You need to select from available options." << endl;
			cout << "Please choose number from 1 to 3: ";
			cin >> loginOption;
		}

		return loginOption;
}


Payment payByTransfer (double price, string transferTitle) {
	cout << "========================================" << endl;
	cout << "TRANSFER DETAILS" << endl;
	cout << "Account number: 86 10202498 1111222233334444" << endl;
	cout << "Amount to pay" << price << endl;
	cout << "Transfer title" << transferTitle << endl;
	cout << "========================================" << endl;

	cout << endl;

	return Payment(Transfer, price);
}


Payment payByCreditCard (double price) {
	string cardNumber;
	string cvc;

	cout << "Amount to pay: " << price << endl;
	cout << "Put your card number please: ";
	cin >> cardNumber;

	regex number_match("^5[1-5]\\d{14}$");

	// handle invalid input
	while(cin.fail() || !regex_match(cardNumber, number_match)) {

		cout << endl;
		cout << "Invalid card number, try again: ";

		cin >> cardNumber;

	}


	cout << "Enter CVC code: ";
	regex cvc_match("^[0-9]{3}$");

	// handle invalid input
	while(cin.fail() || !regex_match(cvc, cvc_match)) {

		cout << endl;
		cout << "Invalid CVC, try again: ";

		cin >> cvc;
	}


	cout << "Thank you for your payment!" << endl;


	return Payment(CreditCard, price);
}

void showPaymentHistory () {

}

void saveOrder(vector<Order> orders, int ordersCounter) {
	/*
	 * write to orders.txt
	 */
	fstream ordersFile;
	stringstream buffer;
	ordersFile.open("orders.txt", ios::app);
	ordersFile << orders.at(ordersCounter).getOrderId() << ","
			<< orders.at(ordersCounter).getUserId() << ","
			<< orders.at(ordersCounter).getRoomId() << ","
			<< orders.at(ordersCounter).getDate() << ","
			<< orders.at(ordersCounter).getStartHour() << ","
			<< orders.at(ordersCounter).getDuration() << ";";
	ordersFile.close();
}

/*
 * GENERAL FUNCTION
 */

int main() {

	// Variables
	unsigned int choosedOption; // stores option choosed from main menu
	unsigned int chosenOption; // stores option choosed from manage menu
	unsigned int loginOption; //  stores option choosed from welcome menu
	vector<Room> rooms; // vector for storing rooms data
	vector<Order> orders; // vector for strong orders data
	vector<Payment> payments;
	vector<User> users; //  vector for storing users data
	int userID;
	int returnFlag;
	HANDLE hOut;
	int roomsCounter = -1;
	int ordersCounter = -1; // 0 is first element in vector

	// setup handler
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN); // green color

	// display header
	cout << "----------------------------------------------------------------" << endl;
	cout << "Conference Room Manager ver. 0.1" << endl;
	cout << "Component 1/4, Bartosz Kubacki/Bartlomiej Urbanek/Beata Brymerska" << endl;
	cout << "----------------------------------------------------------------" << endl;

	SetConsoleTextAttribute(hOut, 15); // default color

	cout << endl;


	// load all data from files
	string roomsData = loadRoomsFile();
	string ordersData = loadOrdersFile();
	string usersData = loadUsersFile();


	// setup delimiters
	const string delimiter_1 = ";";
	const string delimiter_2 = ",";
	size_t pos = 0;

	/**
	 * users.txt to vectors
	 */

	// used to store tokens
	vector<string> userTokens;

	// explode string loaded from file into separate objects in vector
	while((pos = usersData.find(delimiter_1)) != string::npos) {

		userTokens.push_back(usersData.substr(0, pos));
		usersData.erase(0, pos + delimiter_1.length());
	}

	// used to store single user details

	vector<string> tempUserDetails;

	for(string s : userTokens) {

		while((pos = s.find(delimiter_2)) != string::npos) {

		tempUserDetails.push_back(s.substr(0, pos));
		s.erase(0, pos + delimiter_2.length());

		}

		users.push_back(User(stoi(tempUserDetails[0]), tempUserDetails[1], tempUserDetails[2], tempUserDetails[3], tempUserDetails[4], tempUserDetails[5]));
		tempUserDetails.clear();
	}



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
		roomsCounter++;
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
		orders.push_back(Order(stoi(tempOrderDetails[0]), stoi(tempOrderDetails[1]), stoi(tempOrderDetails[2]), tempOrderDetails[3], tempOrderDetails[4], stoi(tempOrderDetails[5])));
		tempOrderDetails.clear();
		ordersCounter++;
	}


	while(true){

		//show WelcomeMenu


		loginOption = showWelcomeMenu();
		returnFlag = 1;

		switch (loginOption){

		case 1:
		{
			userID = LogIn(users);
			if (userID > 0){
				returnFlag=0;}
			break;
		}
		case 2:
		{
			userID = Register(users);
			if (userID > 0){
				returnFlag=0;
						}
			break;
		}
		case 3:
		{
			userID = 0;
			returnFlag=0;
			cout << "----------------------------------------------------------------" << endl;
			cout<<"Welcome to the Guest Zone!"<<endl;
			cout << "----------------------------------------------------------------" << endl;
			break;
		}

		}

		if (returnFlag==0){
				break;}


	}

	// start loop, makes it possible to go back
	while(true) {

		label_2: // user choosed 0 at bookingLength menu and wanted to go back to Main Menu

		//show MainMenu
		choosedOption = showMainMenu();


		//handle choosedOption
		switch(choosedOption) {

			case 1:
			{
				// get date and time
				auto temp_time = chrono::system_clock::now();
				time_t actual_time = chrono::system_clock::to_time_t(temp_time);

				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN); // green color

				cout << "Room prices for: " << ctime(&actual_time) << endl;
				cout << endl;

				// list rooms with prices
				showRooms(rooms);

				SetConsoleTextAttribute(hOut, 15); // default color

				break;
			}
			case 2:
			{
				// vars
				unsigned int choosedRoom;
				unsigned int bookingLength;
				string startTime;
				string orderDate;

				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN); // green color

				cout << "Choose which room you would like to order:" << endl;
				cout << endl;

				// shows all rooms with already ordered dates
				showRooms(rooms);

				SetConsoleTextAttribute(hOut, 14); // yellow color

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

				label_1: // label to come back if room is not available at choosed time and date

				// show already booked dates for choosed room
				cout << endl;
				showRoomAvail(choosedRoom, orders);


				// get date from user, format: yyyy-m-dd hh:mm
				cout << endl;
				cout << "Enter date to book this room [YYYY-M(M)-D(D)] (0 -> go back to Main Menu): ";
				cin.ignore();
				getline(cin, orderDate);

				// handle going back to the main menu / invalid input
				try {
					if(stoi(orderDate) == 0)
						continue;
				}
				catch(exception& e) {

					//// do nothing
				}

				cout << endl;

				// setup regex
				regex date_match("[2][0][1][8-9]-([1][0-2]|[1-9])-([1-9]|[1-2][0-9]|[3][0-1])");

				// handle invalid input
				while(cin.fail() || !regex_match(orderDate, date_match)) {

					cout << endl;
					cout << "Invalid date format, please enter date in format [YYYY-M(M)-D(D)] (0 -> go back to Main Menu): ";

					getline(cin, orderDate);

					// handle going back to main menu
					if(stoi(orderDate) == 0)
						goto label_2;

				}

				// get start hour
				cout << endl;
				cout << "At what time would you like to book a room? (8 - 16) [:00, :15, :30, :45] (0 -> go back to Main Menu): ";
				cin >> startTime;

				// handle going back to main menu
				if(stoi(startTime) == 0)
					continue;

				regex startTime_match("([8-9]|[1][0-6]):([0][0]|[1][5]|[3][0]|[4][5])");

				while(cin.fail() || !regex_match(startTime, startTime_match)) {

					cout << endl;
					cout << "Invalid hour format, please try again (0 -> go back to Main Menu): ";
					cin >> startTime;

					// go back to the Main Menu
					if(stoi(startTime) == 0)
						goto label_2;
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
				cout << "Your choice (0 -> go back to Main Menu): ";
				cin >> bookingLength;

				while(cin.fail() || bookingLength > 5) {

					cout << "You choosed incorrectly, please try again (0 -> go back to Main Menu): ";
					cin >> bookingLength;
				}

				// handle going back to main menu
				if(bookingLength == 0)
					continue;

				switch(bookingLength) {

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
						cout << "Enter booking length in minutes (a multiply of 30, [30 - 480]) (0 -> go back to Main Menu): ";
						cin >> bookingLength;

						//handle going back to Main Menu
						if(bookingLength == 0)
							continue;

						while(cin.fail() || bookingLength < 30 || bookingLength > 480 || bookingLength % 30 != 0) {

							cout << endl;
							cout << "Incorrect value, please try again (0 -> go back to Main Menu): ";
							cin >> bookingLength;

							if(bookingLength == 0)
								goto label_2;
						}
						break;
					}

				}

				// merge start hour with duration
				string hour_delimiter = ":";
				unsigned int tempHour;
				unsigned int tempMinutes;

				// extract hour and minutes
				pos = startTime.find(hour_delimiter);
				tempHour = stoi(startTime.substr(0, pos));
				tempMinutes = stoi(startTime.substr(pos + hour_delimiter.length(), startTime.length()));

				// convert total minutes to actual time frame
				unsigned int totalMinutes = (tempHour * 60) + tempMinutes;

				unsigned int finalHour = (totalMinutes + bookingLength) / 60;
				unsigned int finalMinutes = (totalMinutes + bookingLength) % 60;


				// check avail of the room
				bool check = true;
				for(Order tempOrder : orders) {

					check = tempOrder.checkAvail(rooms, choosedRoom, orderDate, startTime, bookingLength);

					if(!check) {

						cout << "This room is not available at this time, please try again." << endl;
						goto label_1;
					}
				}


				cout << "========================================" << endl;
				cout << "ORDER SUMMARY" << endl;
				cout << "========================================" << endl;

				cout << endl;

				// order summary
				cout << "Room type: " << rooms.at(choosedRoom).getRoomType() << endl;
				cout << "Room size: " << rooms.at(choosedRoom).getRoomSpace() << endl;
				cout << "Room cost: " << rooms.at(choosedRoom).getRoomCost() << endl;
				cout << "Booking date: " << orderDate << endl;
				cout << "Booking time frame: " << startTime << " - " << finalHour << ":" << finalMinutes << endl;

				cout << endl;

				// add new order to existing orders vector
				orders.push_back(Order(ordersCounter + 1, userID, choosedRoom, orderDate, startTime, bookingLength));
				ordersCounter++;

				/*
				 * write to orders.txt
				 */

				saveOrder(orders, ordersCounter);

				int orderSummarySelectedOption;
				cout << "Press 0 to cancel booking or 1 to continue to payment" << endl;
				cin >> orderSummarySelectedOption;

				while(cin.fail() || orderSummarySelectedOption < 0 || orderSummarySelectedOption > 1) {
					cout << endl;
					cout << "Incorrect value, please try again: ";
					cin >> orderSummarySelectedOption;
				}

				if (orderSummarySelectedOption == 0) {
					continue;
				}

				int paymentSelectedOption = showPaymentMenu();
				int price = bookingLength * 50.0;

				// update file

				switch (paymentSelectedOption) {
					case 1:
						payments.push_back(payByCreditCard(price));
						break;

					case 2:
						payments.push_back(payByTransfer(price, "Name Surname - room booking"));
						break;

					case 0:
						continue;
				}


				cout << endl;

				break;
			}
			case 3:
			{
					chosenOption = ManageMyRooms();
					cout << chosenOption;
					if(chosenOption == 1){
						cout << "Dziala";
					}
				break;
			}
			default:
				break;
		}
	}

	return 0;
}
