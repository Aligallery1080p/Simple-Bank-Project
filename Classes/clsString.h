#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class clsString {
private:
	string _Value;

public:
	clsString() {
		_Value = "";
	}

	clsString(string Value) {
		_Value = Value;
	}

	void SetValue(string Value) {
		_Value = Value;
	}
	string GetValue() {
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static void PrintFirstLetterOfEachWord(string S1) {
		bool isFirstLetter = true;

		for (short i = 0;i < S1.length();i++)
		{
			if (S1[i] != ' ' && isFirstLetter)
			{
				cout << S1[i] << endl;
			}

			isFirstLetter = (S1[i] == ' ' ? true : false);
		}
	}

	void PrintFirstLetterOfEachWord() {
		PrintFirstLetterOfEachWord(_Value);
	}

	static string UpperFirstLetterOfEachWord(string S1) {
		bool isFirstLetter = true;

		for (short i = 0;i < S1.length();i++)
		{
			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = toupper(S1[i]);
			}

			isFirstLetter = (S1[i] == ' ' ? true : false);
		}

		return S1;
	}

	void UpperFirstLetterOfEachWord() {
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string S1) {
		bool isFirstLetter = true;

		for (short i = 0;i < S1.length();i++)
		{
			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = tolower(S1[i]);
			}

			isFirstLetter = (S1[i] == ' ' ? true : false);
		}

		return S1;
	}

	void LowerFirstLetterOfEachWord() {
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(string S1) {
		for (short i = 0;i < S1.length();i++)
		{
			S1[i] = toupper(S1[i]);
		}

		return S1;
	}

	void UpperAllString() {
		_Value = UpperAllString(_Value);
	}

	static string LowerAllString(string S1) {
		for (short i = 0;i < S1.length();i++)
		{
			S1[i] = tolower(S1[i]);
		}

		return S1;
	}

	void LowerAllString() {
		_Value = LowerAllString(_Value);
	}

	static char InvertLetterCase(char Char1) {
		return isupper(Char1) ? tolower(Char1) : toupper(Char1);
	}

	static string InvertAllString(string S1) {
		for (short i = 0;i < S1.length();i++)
		{
			S1[i] = InvertLetterCase(S1[i]);
		}

		return S1;
	}

	void InvertAllString() {
		_Value = InvertAllString(_Value);
	}

	enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };

	static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All) {
		if (WhatToCount == enWhatToCount::All)
		{
			return S1.length();
		}

		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
				Counter++;
			if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
				Counter++;
		}

		return Counter;
	}

	short CountLetters() {
		return CountLetters(_Value);
	}

	static short CountCapitalLetters(string S1) {
		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (isupper(S1[i]))
				Counter++;
		}

		return Counter;
	}
	 
	short CountCapitalLetters() {
		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetters(string S1) {
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (islower(S1[i]))
				Counter++;
		}

		return Counter;
	}

	short CountSmallLetters() {
		return CountSmallLetters(_Value);
	}

	static short CountLetter(string S1, char Letter, bool MatchCase = true) {
		short Counter = 0;

		for (short i = 0;i < S1.length();i++)
		{
			if (MatchCase)
			{
				if (S1[i] == Letter)
					Counter++;
			}
			else
			{
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}
		}

		return Counter;
	}

	short CountLetter(char Letter) {
		return CountLetter(_Value, Letter);
	}

	static bool isVowel(char Ch1) {
		Ch1 = tolower(Ch1);

		return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
	}

	static short CountVowels(string S1) {
		short Counter = 0;
		for (short i = 0;i < S1.length();i++)
		{
			if (isVowel(S1[i]))
				Counter++;
		}
		return Counter;
	}

	short CountVowels() {
		return CountVowels(_Value);
	}

	static void PrintVowels(string S1) {
		cout << "\nVowels in string are: ";
		for (short i = 0;i < S1.length();i++)
		{
			if (isVowel(S1[i]))
				cout << S1[i] << "    ";
		}
	}

	void PrintVowels() {
		PrintVowels(_Value);
	}

	static void PrintEachWordInString(string S1) {
		string delim = " ";

		cout << "\nYour string words are: \n\n";
		short pos = 0;
		string sWord;

		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != "")
			{
				cout << sWord << endl;
			}
			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
		{
			cout << S1 << endl;
		}
	}

	void PrintEachWordInString() {
		PrintEachWordInString(_Value);
	}

	static short CountWords(string S1) {
		string delim = " ";
		short Counter = 0;
		short pos = 0;
		string sWord;

		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);

			if (sWord != "")
			{
				Counter++;
			}

			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
		{
			Counter++;
		}

		return Counter;
	}

	short CountWords() {
		return CountWords(_Value);
	}

	static vector <string> Split(string S1, string Delim) {
		vector <string> vString;

		short pos = 0;
		string sWord;

		while ((pos = S1.find(Delim)) != S1.npos)
		{
			sWord = S1.substr(0, pos);

			if (sWord != "")
			{
				vString.push_back(sWord);
			}

			S1.erase(0, pos + Delim.length());
		}

		if (S1 != "")
		{
			vString.push_back(S1);
		}

		return vString;
	}

	vector <string> Split(string Delim) {
		return Split(_Value, Delim);
	}

	static string TrimLeft(string S1) {
		for (short i = 0;i < S1.length();i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length() - 1);
			}
		}
		return "";
	}

	void TrimLeft() {
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string S1) {
		for (short i = S1.length() - 1;i >= 0;i--)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(0, i + 1);
			}
		}
		return "";
	}

	void TrimRight() {
		_Value = TrimRight(_Value);
	}

	static string Trim(string S1) {
		return (TrimLeft(TrimRight(S1)));
	}

	void Trim() {
		_Value = Trim(_Value);
	}

	static string JoinString(vector<string> vString, string Delim) {
		string S1 = "";

		for (string& s : vString)
		{
			S1 += s + Delim;
		}

		return S1.substr(0, S1.length() - Delim.length());
	}

	static string JoinString(string arrString[], short Length, string Delim) {
		string S1 = "";

		for (short i = 0;i < Length;i++)
		{
			S1 = S1 + arrString[i] + Delim;
		}

		return S1.substr(0, S1.length() - Delim.length());
	}

	static string ReverseWordsInString(string S1) {
		vector <string> vString;
		string S2 = "";

		vString = Split(S1, " ");

		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			iter--;

			S2 = S2 + *iter + " ";
		}

		S2 = S2.substr(0, S2.length() - 1);

		return S2;
	}

	void ReverseWordsInString() {
		_Value = ReverseWordsInString(_Value);
	}

	static string ReplaceWordInString(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
	{
		vector<string> vString = Split(S1, " ");

		for (string& s : vString)
		{
			if (MatchCase)
			{
				if (s == StringToReplace)
				{
					s = sRepalceTo;
				}
			}
			else
			{
				if (LowerAllString(s) ==
					LowerAllString(StringToReplace))
				{
					s = sRepalceTo;
				}
			}
		}

		return JoinString(vString, " ");
	}

	void ReplaceWordInString(string StringToReplace, string sRepalceTo) {
		_Value = ReplaceWordInString(_Value, StringToReplace, sRepalceTo);
	}
};