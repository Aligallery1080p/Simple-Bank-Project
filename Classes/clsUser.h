#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsPerson.h"
#include "D:/Programming/Programming Advices/Course 10/Project2_MS/clsString.h"
#include "D:/Programming/Programming Advices/Course 11/Project1_MS/clsUtil.h"
#include "D:/Programming/Programming Advices/Course 10/Project3_MS/clsDate.h"
using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _UserName;
	string _PassWord;
	int _Permissions;
	bool _MarkedForDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Sperator = "#//#")
	{
		vector <string> vUserData;
		vUserData = clsString::Split(Line, Sperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5],2), stoi(vUserData[6]));
	}

	static string _ConvertUserObjectToLine(clsUser& User, string Sperator = "#//#")
	{
		string stUserObject = "";

		stUserObject += User.FirstName + Sperator;
		stUserObject += User.LastName + Sperator;
		stUserObject += User.Email + Sperator;
		stUserObject += User.Phone + Sperator;
		stUserObject += User.UserName + Sperator;
		stUserObject += clsUtil::EncryptText(User.PassWord, 2) + Sperator;
		stUserObject += to_string(User.Permissions);

		return stUserObject;
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> vUsers;
		fstream MyFile("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}

			MyFile.close();
		}

		return vUsers;
	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{
		string DataLine;

		fstream MyFile("Users.txt", ios::out);//overwrite

		if (MyFile.is_open())
		{
			for (clsUser& User : vUsers)
			{
				if (User._MarkedForDelete == false)
				{
					//we only write records that are not marked for delete.
					DataLine = _ConvertUserObjectToLine(User);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	static void _AddDataLineToFile(string Line)
	{
		fstream MyFile("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == _UserName)
			{
				User = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	string _PrepareLogInRecord(string Sperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateToString() + Sperator;
		LoginRecord += UserName + Sperator;
		LoginRecord += clsUtil::EncryptText(PassWord,2) + Sperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Sperator = "#//#")
	{
		vector <string> LoginRegisterDataLine = clsString::Split(Line, Sperator);

		stLoginRegisterRecord LoginRegisterRecord;
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.Username = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2], 2);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);
		return LoginRegisterRecord;
	}

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,pUpdateClient = 8, pFindClient = 16,
		pTransactions = 32, pManageUsers = 64, pLoginRegister = 128, pCurrencyExchange = 256
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string Username;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string UserName, string PassWord, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_PassWord = PassWord;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	string GetUserName() {
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassWord(string PassWord) {
		_PassWord = PassWord;
	}
	string GetPassWord() {
		return _PassWord;
	}
	__declspec(property(get = GetPassWord, put = SetPassWord)) string PassWord;

	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	int GetPermissions() {
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		fstream MyFile("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string PassWord)
	{
		fstream MyFile("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.PassWord == PassWord)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
			break;

		case enMode::UpdateMode:
			_Update();

			return enSaveResults::svSucceeded;
			break;

		case enMode::AddNewMode:
			if (IsUserExist(UserName))
				return enSaveResults::svFaildUserNameExists;

			_AddNew();
			_Mode = enMode::UpdateMode;
			return enSaveResults::svSucceeded;
			break;
		}
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = Find(UserName);
		return (!User.IsEmpty());
	}

	bool Delete()
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == _UserName)
			{
				User._MarkedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList() {
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	void RegisterLogIn()
	{
		string LoginRecord = _PrepareLogInRecord();

		fstream MyFile("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << LoginRecord << endl;
			MyFile.close();
		}
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecord;
		fstream MyFile("LoginRegister.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				stLoginRegisterRecord LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}

			MyFile.close();
		}

		return vLoginRegisterRecord;
	}
};
