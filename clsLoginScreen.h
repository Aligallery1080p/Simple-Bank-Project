#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsMainScreen.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		bool LoginFailed = false;
		short Trials = 3;

		do
		{
			if (LoginFailed)
			{
				Trials--;
				cout << "\nInvalid Username/Password!";
				cout << "\nYou have " << Trials << " Trials to login.\n\n";

				if (Trials == 0)
				{
					cout << "\nYou are Locked after 3 failed trials\n\n";
					return false;
				}
			}

			cout << "Enter Username? ";
			string Username = clsInputValidate::ReadString();

			cout << "Enter Password? ";
			string Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();

		return true;
	}

public:
	static bool ShowLoginScreen()
	{
		system("cls");
		DrawScreenHeader("\t   Login Screen");
		return _Login();

	}
};

