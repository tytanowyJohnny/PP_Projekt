/*
 * User.h
 *
 *  Created on: 6 cze 2018
 *      Author: micha
 */

#ifndef USER_H_
#define USER_H_

#include <string>
#include <iostream>

using namespace std;

class User {

public:

User(unsigned int userID,
string userLogin,
string userPassword,
string userFullName,
string userPhoneNumber,
string userMail);
virtual ~User();

unsigned int userID;
string userLogin;
string userPassword;
string userFullName;
string userPhoneNumber;
string userMail;

	const string& getUserFullName() const;
	void setUserFullName(const string& userFullName);
	unsigned int getUserId() const;
	void setUserId(unsigned int userId);
	const string& getUserLogin() const;
	void setUserLogin(const string& userLogin);
	const string& getUserMail() const;
	void setUserMail(const string& userMail);
	const string& getUserPassword() const;
	void setUserPassword(const string& userPassword);
	const string& getUserPhoneNumber() const;
	void setUserPhoneNumber(const string& userPhoneNumber);
};

#endif /* USER_H_ */
