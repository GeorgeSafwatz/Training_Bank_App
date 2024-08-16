#pragma once

#include<iostream>
#include<string>
#include"Utils.h"

using namespace std;

namespace loggers {
	void logInfo(stClient const& client) {
		cout << "Client Name:" << client.name << endl;
		cout << "Client Account Name:" << client.accountNumber << endl;
		cout << "Client Account Balance:" << to_string(client.accountBalance) << endl;
		cout << "Client Phone Number and Postal Code:" << client.phoneNum
			<< '\t' << client.postalCode
			<< endl;
	}
	void printClients(vector<stClient> const & vClients) {
		for (size_t i = 0; i < vClients.size(); i++)
		{
			logInfo(vClients[i]);
			cout << "#########################" << endl;
		}
	}
}