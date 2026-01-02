#pragma once
#include <iostream>
#include <string>
#include "D:/Programming/Programming Advices/Course 10/Project3_MS/clsDate.h"

class clsUtil
{
public:
    enum enCharType {
        SamallLetter = 1, CapitalLetter = 2,
        Digit = 3, MixChars = 4, SpecialCharacter = 5
    };

	static void Srand() {
		srand((unsigned)time(NULL));;
	}

    static void Pause() {
        system("pause>0");
    }

	static int RandomNumber(int From, int To)
	{
		int randNum = rand() % (To - From + 1) + From;
		return randNum;
	}

	static string NumberToText(int Number)
    {
        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = { "","One","Two","Three","Four","Five","Six","Seven",
                "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
                "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

            return arr[Number] + " ";
        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy", "Eighty", "Ninety" };

            return arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return NumberToText(Number / 100) + "Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return NumberToText(Number / 1000) + "Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return NumberToText(Number / 1000000) + "Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return NumberToText(Number / 1000000000) + "Billion " + NumberToText(Number % 1000000000);
        }
    }

    static int ReadPositiveNumber(string Message)
    {
        int Number = 0;
        do
        {
            cout << Message << endl;
            cin >> Number;
        } while (Number <= 0);

        return Number;
    }

    static char GetRandomCharacter(enCharType CharType)
    {
        if (CharType == enCharType::MixChars)
        {
            CharType = enCharType(RandomNumber(1, 3));
        }

        switch (CharType)
        {
        case enCharType::SamallLetter:
        {
            return char(RandomNumber(97, 122));
            break;
        }
        case enCharType::CapitalLetter:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        case enCharType::Digit:
        {
            return char(RandomNumber(48, 57));
            break;
        }
        }

        return '\0';
    }

    static string GenerateWord(enCharType CharType, short Length)
    {
        string Word = "";

        for (int i = 1; i <= Length; i++)
        {
            Word = Word + GetRandomCharacter(CharType);
        }

        return Word;
    }

    static int ReverseNumber(int Number)
    {
        int Remainder = 0;
        int Number2 = 0;

        while (Number > 0)
        {
            Remainder = Number % 10;
            Number = Number / 10;
            Number2 = Number2 * 10 + Remainder;
        }

        return Number2;
    }

    static string GenerateKey(enCharType CharType)
    {
        string Key = "";

        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);

        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {
        for (int i = 1;i <= NumberOfKeys;i++)
        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }
    }

    static void Swap(int& x, int& y)
    {
        int Temp = x;
        x = y;
        y = Temp;
    }

    static void Swap(double& a, double& b) 
    {
        double Temp = a;
        a = b;
        b = Temp;
    }

    static void Swap(string& s1, string& s2)
    {
        string Temp = s1;
        s1 = s2;
        s2 = Temp;
    }

    static void Swap(clsDate& Date1, clsDate& Date2)
    {
        clsDate::SwapDates(Date1, Date2);
    }

    static void ShuffleArray(int arr[], int arrLength)
    {
        for (int i = 0;i < arrLength;i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    static void ShuffleArray(string arr[], int arrLength)
    {
        for (int i = 0;i < arrLength;i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    static void FillArrayWithRandomNumbers(int arr[], int arrLength, int From, int To)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = RandomNumber(From, To);
    }

    static void FillArrayWithRandomWords(string arr[], int arrLength, enCharType CharType, short Length)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateWord(CharType, Length);
    }

    static void FillArrayWithRandomKeys(string arr[], int arrLength, enCharType CharType) 
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateKey(CharType);
    }

    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1;i < NumberOfTabs;i++)
        {
            t = t + "\t";
            cout << t;
        }

        return t;
    }

    static string EncryptText(string Text, short EncryptionKey)
    {
        for (int i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncryptionKey);
        }

        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey)
    {
        for (int i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - EncryptionKey);
        }

        return Text;
    }

    static bool IsPrime(int Number)
    {
        int M = round(Number / 2);

        for (int Counter = 2; Counter <= M; Counter++)
        {
            if (Number % Counter == 0)
                return false;
        }

        return true;
    }

    static void ResetScreen()
    {
        system("cls");
        system("color 0F");
    }
};

