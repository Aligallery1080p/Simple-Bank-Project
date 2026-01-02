#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "D:/Programming/Programming Advices/Course 10/Project3_MS/clsDate.h"
using namespace std;

class clsScreen
{
protected:
	static void DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\t\t\t\t\t______________________________________\n\n";
		cout << "\t\t\t\t\t  " << Title << endl;
		
		if (SubTitle != "")
		{
			cout << "\t\t\t\t\t  " << SubTitle << endl;
		}

		cout << "\t\t\t\t\t______________________________________\n\n";
		cout << "\t\t\t\t\tUser: " << CurrentUser.UserName << endl;
		cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n\n";
	}

	static bool	CheckAccessRights(clsUser::enPermissions Permission)
	{
		if (!CurrentUser.CheckAccessPermission(Permission))
		{
			cout << "\t\t\t\t\t______________________________________\n\n";
			cout << "\t\t\t\t\t  Access Denied! Contact your Admin.\n";
			cout << "\t\t\t\t\t______________________________________\n\n";
			return false;
		}
		else
			return true;
	}
};

