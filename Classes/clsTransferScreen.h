#pragma once
#include <iostream>
#include "clsScreen.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient& Client)
	{
		cout << "\nClient Card:\n";
		cout << "___________________\n";
		cout << "FirstName   : " << Client.FirstName << endl;
		cout << "Acc. Number : " << Client.AccountNumber() << endl;
		cout << "Balance     : " << Client.AccountBalance << endl;
		cout << "___________________\n";
	}

	static string _ReadAccountNumberForSource()
	{
		string AccountNumber;
		cout << "\nPlease Enter Account Number to Transfer From: ";
		cin >> AccountNumber;

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			cout << "\nPlease Enter Account Number to Transfer From: ";
			cin >> AccountNumber;
		}

		return AccountNumber;
	}

	static string _ReadAccountNumberForDestination()
	{
		string AccountNumber;
		cout << "\nPlease Enter Account Number to Transfer To: ";
		cin >> AccountNumber;

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			cout << "\nPlease Enter Account Number to Transfer To: ";
			cin >> AccountNumber;
		}

		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient Client)
	{
		double Amount = 0;
		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadNumber<double>();

		while (Client.AccountBalance < Amount)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount? ";
			Amount = clsInputValidate::ReadNumber<double>();
		}

		return Amount;
	}

public:
	static void ShowTransferScreen()
	{
		DrawScreenHeader("\tTranfser Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumberForSource());
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumberForDestination());
		_PrintClient(DestinationClient);

		double Amount = _ReadAmount(SourceClient);
		
		char Answer = 'n';
		cout << "\nAre you sure you want to perform this transaction? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if(SourceClient.Transfer(Amount,DestinationClient,CurrentUser.UserName))
			{
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer Faild\n";
			}

			_PrintClient(SourceClient);
			_PrintClient(DestinationClient);
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}

	}
};

