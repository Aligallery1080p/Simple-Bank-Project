#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PassWord: ";
		User.PassWord = clsInputValidate::ReadString();

		cout << "\nEnter Permissions: ";
		User.Permissions = _ReadPermissionsToSet();
	}

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

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Answer = 'n';

		cout << "\nDo you want to give full access? y/n? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			return -1;
		}
		else
		{
			cout << "\nDo you want to give access to : \n";

			cout << "\nShow Clients List? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{ 
				Permissions += clsUser::enPermissions::pListClients;
			}

			cout << "\nAdd New Client? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += clsUser::enPermissions::pAddNewClient;
			}

			cout << "\nDelete Client? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += clsUser::enPermissions::pDeleteClient;
			}

			cout << "\nUpdate Client? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{ 
				Permissions += clsUser::enPermissions::pUpdateClient;
			}

			cout << "\nFind Client? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += clsUser::enPermissions::pFindClient;
			}

			cout << "\nTransactions? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += clsUser::enPermissions::pTransactions;
			}

			cout << "\nManage Users? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += clsUser::enPermissions::pManageUsers;
			}

			cout << "\nLogin Register? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += clsUser::enPermissions::pLoginRegister;
			}

			cout << "\nCurrency Exchange? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				Permissions += clsUser::enPermissions::pCurrencyExchange;
			}

			return Permissions;
		}
	}

public:
	static void ShowAddNewUserScreen()
	{
		DrawScreenHeader("\t  Add New User Screen");

		cout << "\nPlease Enter UserName: ";
		string UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName is already used, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case clsUser::enSaveResults::svSucceeded:
			cout << "\nUser Added Successfully :-)\n";
			_PrintUser(NewUser);
			break;

		case clsUser::enSaveResults::svFaildEmptyObject:
			cout << "\nError User was not saved because it's Empty";
			break;

		case clsUser::enSaveResults::svFaildUserNameExists:
			cout << "\nError User was not save becuase UserName already in used";
			break;
		};
	}
};

