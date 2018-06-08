/*
 * User.cpp
 *
 *  Created on: 6 cze 2018
 *      Author: micha
 */

#include "User.h"

User::User(unsigned int userID,
string userLogin,
string userPassword,
string userFullName,
string userPhoneNumber,
string userMail)
{
	this -> userID = userID;
	this -> userLogin = userLogin;
	this -> userPassword = userPassword;
	this -> userFullName = userFullName;
	this -> userPhoneNumber = userPhoneNumber;
	this -> userMail = userMail;
}

User::~User(){

}



const string& User::getUserFullName() const {
	return userFullName;
}

void User::setUserFullName(const string& userFullName) {
	this->userFullName = userFullName;
}

unsigned int User::getUserId() const {
	return userID;
}

void User::setUserId(unsigned int userId) {
	userID = userId;
}

const string& User::getUserLogin() const {
	return userLogin;
}

void User::setUserLogin(const string& userLogin) {
	this->userLogin = userLogin;
}

const string& User::getUserMail() const {
	return userMail;
}

void User::setUserMail(const string& userMail) {
	this->userMail = userMail;
}

const string& User::getUserPassword() const {
	return userPassword;
}

void User::setUserPassword(const string& userPassword) {
	this->userPassword = userPassword;
}

const string& User::getUserPhoneNumber() const {
	return userPhoneNumber;
}

void User::setUserPhoneNumber(const string& userPhoneNumber) {
	this->userPhoneNumber = userPhoneNumber;
}
