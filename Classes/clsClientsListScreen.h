#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUser.h"

class clsClientsListScreen : protected clsScreen
{
private:
	static void _PrintClientRecordLine(clsBankClient Client)
	{
		cout << setw(8) << left << "" << "| " << left << setw(15) << Client.AccountNumber();
		cout << "| " << left << setw(20) << Client.FullName();
		cout << "| " << left << setw(12) << Client.Phone;
		cout << "| " << left << setw(20) << Client.Email;
		cout << "| " << left << setw(10) << Client.PinCode;
		cout << "| " << left << setw(12) << Client.AccountBalance;
	}

public:
	static void ShowClientsList()
	{
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pListClients))
		{
			return;
		}

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string Title = "\t  Clients List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;
		
		cout << setw(8) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		
		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;

		if (vClients.size() == 0)
		{
			cout << "\t\t\tNo Clients Available in the System!\n";
		}

		for (clsBankClient& Client : vClients)
		{
			_PrintClientRecordLine(Client);
			cout << endl;
		}

		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;
	}
};

