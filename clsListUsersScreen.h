#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsListUsersScreen : protected clsScreen
{
private:
	static void _PrintUserRecordLine(clsUser User)
	{
		cout << setw(8) << left << "" << "| " << left << setw(12) << User.UserName;
		cout << "| " << left << setw(25) << User.FullName();
		cout << "| " << left << setw(12) << User.Phone;
		cout << "| " << left << setw(20) << User.Email;
		cout << "| " << left << setw(10) << User.PassWord;
		cout << "| " << left << setw(12) << User.Permissions;
	}

public:
	static void ShowUsersList()
	{
		vector <clsUser> vUsers = clsUser::GetUsersList();
		string Title = "\t  Users List Screen";
		string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

		DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "________________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
		cout << "| " << left << setw(25) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "PassWord";
		cout << "| " << left << setw(12) << "Permissions";

		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "________________________________________________\n" << endl;

		if (vUsers.size() == 0)
		{
			cout << "\t\t\tNo Users Available in the System!\n";
		}

		for (clsUser& User : vUsers)
		{
			_PrintUserRecordLine(User);
			cout << endl;
		}

		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "________________________________________________\n" << endl;
	}
};

