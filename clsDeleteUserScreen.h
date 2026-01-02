#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
	static void _PrintUser(clsUser& User)
	{
		cout << "\nUser Card:\n";
		cout << "___________________\n";
		cout << "FirstName   : " << User.FirstName << endl;
		cout << "LastName    : " << User.LastName << endl;
		cout << "Full Name   : " << User.FullName() << endl;
		cout << "Email       : " << User.Email << endl;
		cout << "Phone       : " << User.Phone << endl;
		cout << "UserName    : " << User.UserName << endl;
		cout << "PassWord    : " << User.PassWord << endl;
		cout << "Permissions : " << User.Permissions << endl;
		cout << "___________________\n";
	}

public:
	static void ShowDeleteUserScreen()
	{
		DrawScreenHeader("\tDelete User Screen");

		cout << "\nPlease Enter UserName: ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer;
		cout << "\nAre you sure you want to delete this user? y/n? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\nUser Delete Successfully :-)\n";
				_PrintUser(User);
			}
			else
			{
				cout << "\nError User was not Deleted\n";
			}
		}
	}
};

