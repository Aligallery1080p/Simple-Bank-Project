#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
	static void PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord& Record)
	{
		cout << setw(8) << left << "" << "| " << left << setw(35) << Record.DateTime;
		cout << "| " << left << setw(20) << Record.Username;
		cout << "| " << left << setw(20) << Record.Password;
		cout << "| " << left << setw(10) << Record.Permissions;
	}

public:
	static void ShowLoginRegisterScreen()
	{ 
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pLoginRegister))
		{
			return;
		}

		vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();
		string Title = "\tLogin Register List Screen";
		string SubTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";
	
		DrawScreenHeader(Title, SubTitle);
	
		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;
	
		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "PassWord";
		cout << "| " << left << setw(10) << "Permissions";
	
		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;
	
		if (vLoginRegisterRecord.size() == 0)
		{
			cout << "\t\t\tNo Records Available in the System!\n";
		}
	
		for (clsUser::stLoginRegisterRecord Record : vLoginRegisterRecord)
		{
			PrintLoginRegisterRecordLine(Record);
			cout << endl;
		}
	
		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;
	}

};

