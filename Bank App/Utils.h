#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <vector>
#include<cmath>
#include "Prompting.h"

using namespace std;

struct stClient
{
	string accountNumber;
	string postalCode;
	string name;
	string phoneNum;
	unsigned int accountBalance;
};
enum class enClientOptions { showClients = 1, addNewClient=2, deleteClient=3, updateClient=4, findClient=5 };
namespace utils {
	stClient promptAClient() {
		stClient newClient;
		//enter client details
		newClient.accountNumber = prompting::prompt<string>("Please enter your account number");
		newClient.accountBalance = prompting::prompt<unsigned short>("Please enter your account balance");
		newClient.name = prompting::readText("Please enter your Name");
		newClient.phoneNum = "+2" + prompting::prompt<string>("Please enter your phone number");
		newClient.postalCode = prompting::prompt<string>("Please enter your postal code");
		return newClient;
	}
	void trimAll(string& text) {
		bool metFirstLetter = false;
		bool metLastLetter = false;
		unsigned short lastIndex = text.length();
		for (size_t i = 0; i < text.length(); i++)
		{
			lastIndex = text.length() - i;
			if (metFirstLetter && metLastLetter) return;

			if (text[i] == ' ' || text[i] == '\t') text[i] = 0;
			else metFirstLetter = true;

			if (text[lastIndex] == ' ' || text[i] == '\t') text[lastIndex] = 0;
			else metLastLetter = true;
		}
	}
	vector<string> splitBy(string& text, char character) {
		unsigned short currentIndex = 0;
		string newWord = "";
		vector<string> vSplittedWords = {};
		for (size_t i = 0; i < text.length(); i++)
		{
			if (text[i] == character)
			{
				newWord = (text.substr(currentIndex, i - currentIndex));
				trimAll(newWord);
				vSplittedWords.push_back(newWord);
				currentIndex = i + 1;
			}
		}
		newWord = (text.substr(currentIndex));
		trimAll(newWord);
		vSplittedWords.push_back(newWord);
		return vSplittedWords;
	}
	string oneline(stClient client, string separator) {
		string line = "";
		line.append(to_string(client.accountBalance) + separator);
		line.append(client.accountNumber + separator);
		line.append(client.name + separator);
		line.append(client.phoneNum + separator);
		line.append(client.postalCode);
		return line;
	}
	void readFile(string fileName, vector<stClient>& vClients) {
		stClient client;
		vector<string> vec = {};
		fstream file;
		file.open(fileName, ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{

				vec = splitBy(line, '/');
				client.accountBalance = stoi(vec[0]);
				client.accountNumber = vec[1];
				client.name = vec[2];
				client.phoneNum = vec[3];
				client.postalCode = vec[4];
				vClients.push_back(client);
			}
			file.close();
		}
	}
	stClient findClientById(vector<stClient> & vClients) {
		string accountNumber = prompting::prompt<string>("Please enter the account number you want to find");

		for (size_t i = 0; i < vClients.size(); i++)
		{
			if (vClients[i].accountNumber == accountNumber) {
				return vClients[i];
			}
		}
		throw exception();
	}
	void deleteClient(vector<stClient>& vClients) {
		string accountNumber = prompting::prompt<string>("Please enter the account number you want to delete");
		for (size_t i = 0; i < vClients.size(); i++)
		{
			if (vClients[i].accountNumber == accountNumber) {
				vClients.erase(vClients.begin() + i);
				cout << "Account deleted successfully" << endl;
				return;
			}
		}
		cerr << "Account not found!" << endl;
	}
	void updateClient(vector<stClient> & vClients) {
		string accountNumber = prompting::prompt<string>("Please enter the account number you want to update");
		for (size_t i = 0; i < vClients.size(); i++)
		{
			if (vClients[i].accountNumber == accountNumber) {
				vector<stClient>::iterator itClientNum = vClients.begin()+i;
				stClient updatedClient = promptAClient();
				vClients[i] = updatedClient;
			}
		}
	}
	void addClient(vector<stClient>& vClients) {
		stClient newClient;
		newClient = promptAClient();
		vClients.push_back(newClient);
	}
	void saveVectorToFile(string const& fileName, vector<stClient> const& vClients) {
		fstream file;
		file.open(fileName, ios::out);
		if (file.is_open())
		{
			for (size_t i = 0; i < vClients.size(); i++)
			{
				file << oneline(vClients[i], "/") << endl;
			}
			file.close();
		}
	}
	enClientOptions chooseOption() {
		string promptingTxt = "Please Choose an option:\n1) Show Clients\n2) Add Client\n3) Delete Client\n4) Update Client\n5) Find Client \n6) Exit";
		enClientOptions clientOption = static_cast<enClientOptions>(prompting::promptNumberBetween(1, 6,promptingTxt));
		return clientOption;
	}
}