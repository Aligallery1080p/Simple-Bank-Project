#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsUpdateUserScreen : protected clsScreen
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
	static void ShowUpdateUserScreen()
	{
		DrawScreenHeader("\t Update User Screen");

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
		cout << "\nAre you sure you want to update this user y/n? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			cout << "\n\nUpdate User Info:";
			cout << "\n____________________\n";

			_ReadUserInfo(User);

			clsUser::enSaveResults SaveResult;
			SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsUser::enSaveResults::svSucceeded:
				cout << "\nUser Updated Successfully :-)\n";
				_PrintUser(User);
				break;

			case clsUser::enSaveResults::svFaildEmptyObject:
				cout << "\nError User was not saved because it's Empty";
				break;
			}
		}
	}
};

