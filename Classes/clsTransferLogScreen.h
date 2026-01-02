#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;
class clsTransferLogScreen : protected clsScreen
{
private:
	static void PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord& Record)
	{
		cout << setw(8) << left << "" << "| " << left << setw(23) << Record.DateTime;
		cout << "| " << left << setw(8) << Record.SourceAccountNumber;
		cout << "| " << left << setw(8) << Record.DestinationAccountNumber;
		cout << "| " << left << setw(8) << Record.Amount;
		cout << "| " << left << setw(10) << Record.SourceBalance;
		cout << "| " << left << setw(10) << Record.DestinationBalance;
		cout << "| " << left << setw(15) << Record.UserName;
	}

public:
	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransfersLogList();
		string Title = "\tTransfer Log List Screen";
		string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

		DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(15) << "UserName";

		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;

		if (vTransferLogRecord.size() == 0)
		{
			cout << "\t\t\tNo Records Available in the System!\n";
		}

		for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord)
		{
			PrintTransferLogRecordLine(Record);
			cout << endl;
		}

		cout << setw(8) << left << "\n\t______________________________________________________";
		cout << "__________________________________________\n" << endl;
	}
};

