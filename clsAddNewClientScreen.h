#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsBankClient.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadNumber<float>();
	}

	static void _PrintClient(clsBankClient& Client)
	{
		cout << "\nClient Card:\n";
		cout << "___________________\n";
		cout << "FirstName   : " << Client.FirstName<< endl;
		cout << "LastName    : " << Client.LastName << endl;
		cout << "Full Name   : " << Client.FullName() << endl;
		cout << "Email       : " << Client.Email << endl;
		cout << "Phone       : " << Client.Phone << endl;
		cout << "Acc. Number : " << Client.AccountNumber() << endl;
		cout << "PinCode     : " << Client.PinCode << endl;
		cout << "Balance     : " << Client.AccountBalance << endl;
		cout << "___________________\n";
	}

public:
	static void ShowAddNewClientScreen()
	{
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}

		DrawScreenHeader("\t  Add New Client Screen");
	
		cout << "\nPlease Enter Account Number: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is already used, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Added Successfully :-)\n";
			_PrintClient(NewClient);
			break;

		case clsBankClient::enSaveResults::svFaildEmptyObject:
			cout << "\nError account was not saved because it's Empty";
			break;

		case clsBankClient::enSaveResults::svFaildAccountNumberExists:
			cout << "\nError account was not save becuase Account Number already in used";
			break;
		};
	}
};

