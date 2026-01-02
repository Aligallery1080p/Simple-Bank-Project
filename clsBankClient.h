#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsPerson.h"
#include "D:/Programming/Programming Advices/Course 10/Project3_MS/clsDate.h"
#include "D:/Programming/Programming Advices/Course 10/Project2_MS/clsString.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode; 


	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Sperator = "#//#")
	{
		vector <string> vClientData;
		vClientData = clsString::Split(Line, Sperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient& Client, string Sperator = "#//#")
	{
		string stClientObject = "";

		stClientObject += Client.FirstName + Sperator;
		stClientObject += Client.LastName + Sperator;
		stClientObject += Client.Email + Sperator;
		stClientObject += Client.Phone + Sperator;
		stClientObject += Client.AccountNumber() + Sperator;
		stClientObject += Client.PinCode + Sperator;
		stClientObject += to_string(Client.AccountBalance);

		return stClientObject;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;
		fstream MyFile("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			
			while (getline(MyFile, Line))
			{	
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		string DataLine;

		fstream MyFile("Clients.txt", ios::out);//overwrite

		if (MyFile.is_open())
		{
			for (clsBankClient& Client : vClients)
			{
				if (Client._MarkedForDelete == false)
				{
					//we only write records that are not marked for delete.
					DataLine = _ConvertClientObjectToLine(Client);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	static void _AddDataLineToFile(string Line)
	{
		fstream MyFile("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& Client : vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRecord(double Amount, clsBankClient& DestinationClient, string Username, string Sperator = "#//#")
	{
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateToString() + Sperator;
		TransferLogRecord += this->AccountNumber() + Sperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Sperator;
		TransferLogRecord += to_string(Amount) + Sperator;
		TransferLogRecord += to_string(this->AccountBalance) + Sperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Sperator;
		TransferLogRecord += Username;
		return TransferLogRecord;
	}

	void _RegisterTransferLog(double Amount, clsBankClient& DestinationClient,string Username)
	{
		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, Username);

		fstream MyFile("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Sperator = "#//#")
	{
		vector <string> vTransferLog = clsString::Split(Line, Sperator);
		
		stTransferLogRecord TransferLogRecord;
		TransferLogRecord.DateTime = vTransferLog[0];
		TransferLogRecord.SourceAccountNumber = vTransferLog[1];
		TransferLogRecord.DestinationAccountNumber = vTransferLog[2];
		TransferLogRecord.Amount = stod(vTransferLog[3]);
		TransferLogRecord.SourceBalance = stod(vTransferLog[4]);
		TransferLogRecord.DestinationBalance = stod(vTransferLog[5]);
		TransferLogRecord.UserName = vTransferLog[6];
		return TransferLogRecord;
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, 
		string Phone,string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount;
		double SourceBalance;
		double DestinationBalance;
		string UserName;
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber() {
		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	string GetPinCode() {
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance() {
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

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
			if (IsClientExist(AccountNumber()))
				return enSaveResults::svFaildAccountNumberExists;

			_AddNew();
			_Mode = enMode::UpdateMode;
			return enSaveResults::svSucceeded;
			break;
		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector <clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& Client : vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();
		return true;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}

		_AccountBalance -= Amount;
		Save();
		return true;
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient,string Username)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient,Username);
		return true;
	}

	static vector <stTransferLogRecord> GetTransfersLogList()
	{
		vector <stTransferLogRecord> vTransferLogRecord;
		fstream MyFile("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				stTransferLogRecord TransferRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLogRecord.push_back(TransferRecord);
			}

			MyFile.close();
		}

		return vTransferLogRecord;
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
	}
};

