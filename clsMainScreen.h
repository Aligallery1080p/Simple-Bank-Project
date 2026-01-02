#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "Global.h"
#include "clsClientsListScreen.h" //1
#include "clsAddNewClientScreen.h" //2
#include "clsDeleteClientScreen.h" //3
#include "clsUpdateClientScreen.h" //4
#include "clsFindClientScreen.h" //5
#include "clsTransactionsScreen.h" //6
#include "clsManageUsersScreen.h" //7
#include "clsLoginRegisterScreen.h" //8
#include "clsCurrencyExchangeMainScreen.h" //9
#include "D:/Programming/Programming Advices/Course 11/Project2_MS/clsInputValidate.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenueOptions {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4,eFindClient = 5,
		eTransactionsMenue = 6, eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eLogout = 10
	};

	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		short Choice = clsInputValidate::ReadNumberBetween<int>(1, 10,"Enter Number between 1 to 10? ");
		return Choice;
	}

	static void _GoBackToMainMenue()
	{
		cout << "\n\tPress any key to go back to Main Menue...\n";
		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowAllClientsScreen()
	{
		clsClientsListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUserMenue()
	{
		clsManageUsersScreen::ShowManageUsersMenue();
	}

	static void _ShowLoginRegisterMenue()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeMainScreen()
	{
		clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("","");
	}

	static void _PerformMainMenueOption(enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enMainMenueOptions::eListClients:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eAddNewClient:
		{
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eDeleteClient:
		{
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eUpdateClient:
		{
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eFindClient:
		{
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eTransactionsMenue:
		{
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eManageUsers:
		{
			system("cls");
			_ShowManageUserMenue();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eLoginRegister:
		{
			system("cls");
			_ShowLoginRegisterMenue();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eCurrencyExchange:
		{
			system("cls");
			_ShowCurrencyExchangeMainScreen();
			_GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eLogout:
		{
			system("cls");
			_Logout();
			break;
		}
		}
	}

public:
	static void ShowMainMenue()
	{
		system("cls");
		DrawScreenHeader("\t\tMain Menue");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Clients List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
	};
};

