#pragma once
#pragma warning(disable:warning)

#include <iostream>
#include "D:/Programming/Programming Advices/Course 10/Project2_MS/clsString.h";
#include <string> 
#include <vector>
#include <ctime>
using namespace std;

class clsDate {
private:
	short _Day;
	short _Month;
	short _Year;

public:
	clsDate() {
		time_t t = time(0);
		tm* now = localtime(&t);

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
	}

	clsDate(string DateString) {
		clsDate Date = StringToDate(DateString);

		this->Day = Date.Day;
		this->Month = Date.Month;
		this->Year = Date.Year;
	}

	clsDate(short Day, short Month, short Year) {
		this->Day = Day;
		this->Month = Month;
		this->Year = Year;
	}

	clsDate(short DateOrderInYear, short Year) {
		clsDate Date = GetDateFromDayOrderInYear(DateOrderInYear, Year);

		this->Day = Date.Day;
		this->Month = Date.Month;
		this->Year = Date.Year;
	}

	void SetDay(short Day) {
		_Day = Day;
	}
	short GetDay() {
		return _Day;
	}

	void SetMonth(short Month) {
		_Month = Month;
	}
	short GetMonth() {
		return _Month;
	}

	void SetYear(short Year) {
		_Year = Year;
	}
	short GetYear() {
		return _Year;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print() {
		cout << DateToString() << endl;
	}

	clsDate StringToDate(string DateString) {
		clsDate Date;
		vector <string> vDate;

		vDate = clsString::Split(DateString, "/");
		Date.Day = stoi(vDate[0]);
		Date.Month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);

		return Date;
	}
	
	static string GetSystemDateToString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) 
			+ " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second);
	}

	static string DateToString(clsDate Date) {
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString() {
		return DateToString(*this);
	}

	static bool isLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool isLeapYear() {
		return isLeapYear(Year);
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
			return 0;

		int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
	}

	short NumberOfDaysInAMonth() {
		return NumberOfDaysInAMonth(Month, Year);
	}

	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return arrDayNames[DayOfWeekOrder];
	}

	static string MonthShortName(short MonthOrder)
	{
		string arrMonthNames[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul","Aug","Sep","Oct","Nov","Dec" };
		return arrMonthNames[MonthOrder - 1];
	}

	string MonthShortName() {
		return MonthShortName(Month);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;

		// Gregorian:
		// 0:sun, 1:Mon, 2:Tue...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder() {
		return DayOfWeekOrder(Day, Month, Year);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays = NumberOfDaysInAMonth(Month, Year);
		int current = DayOfWeekOrder(1, Month, Year); // Start day index

		// Print month header
		printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		// Print initial spacing
		int i;
		for (i = 0; i < current; i++)
			printf("     ");

		// Print days
		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n  _________________________________\n");
	}

	void PrintMonthCalendar() {
		PrintMonthCalendar(Month, Year);
	}

	static void PrintYearCalendar(int Year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", Year);
		printf("  _________________________________\n");

		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}

		return;
	}

	void PrintYearCalendar() {
		PrintYearCalendar(Year);
	}

	static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (int i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}

		TotalDays += Day;
		return TotalDays;
	}

	short NumberOfDaysFromTheBeginingOfTheYear() {
		return NumberOfDaysFromTheBeginingOfTheYear(Day, Month, Year);
	}

	static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{
		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	clsDate GetDateFromDayOrderInYear(short DateOrderInYear) {
		return GetDateFromDayOrderInYear(DateOrderInYear, Year);
	}

	static clsDate DateAddDays(int Days, clsDate Date)
	{
		int RemainingDays = Days + NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
		short MonthDays = 0;

		Date.Month = 1;

		while (true) {
			MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);

			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12) {
					Date.Month = 1;
					Date.Year++;
				}
			}
			else {
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	void DateAddDays(int Days) {
		*this = DateAddDays(Days, *this);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}

	bool IsDateBeforeDate2(clsDate Date2) {
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}

	bool IsDateEqualDate2(clsDate Date2) {
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
	}

	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool IsLastMonthInYear() {
		return IsLastMonthInYear(Month);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;

		return;
	}

	void SwapDates(clsDate& Date2) {
		SwapDates(*this, Date2);
	}

	static int CalculateMyAgeInDays(clsDate Date1, bool IncludeEndDay = true)
	{
		int Days = 0;
		short SwapFlagValue = 1;
		clsDate Date2 = GetSystemDate();

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}

	int CalculateMyAgeInDays() {
		return CalculateMyAgeInDays(*this);
	}

	static clsDate GetSystemDate()
	{
		clsDate Date;

		time_t t = time(0);
		tm* now = localtime(&t);

		Date.Year = now->tm_year + 1900;
		Date.Month = now->tm_mon + 1;
		Date.Day = now->tm_mday;

		return Date;
	}

	//Increase
	static clsDate IncreaseDateByOneDay(clsDate& Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	void IncreaseDateByOneDay() {
		IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(short Days, clsDate& Date)
	{
		for (short i = 1;i <= Days;i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByXDays(short Days) {
		IncreaseDateByXDays(Days, *this);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		return IncreaseDateByXDays(7, Date);
	}

	void IncreaseDateByOneWeek() {
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date)
	{
		for (short i = 1;i <= Weeks;i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks) {
		IncreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
		if (NumberOfDaysInCurrentMonth < Date.Day)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	void IncreaseDateByOneMonth() {
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(short Months, clsDate& Date)
	{
		for (short i = 1;i <= Months;i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void IncreaseDateByXMonths(short Months) {
		IncreaseDateByXMonths(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;
		return Date;
	}

	void IncreaseDateByOneYear() {
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(short Years, clsDate& Date)
	{
		for (short i = 1;i <= Years;i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	void IncreaseDateByXYears(short Years) {
		IncreaseDateByXYears(Years, *this);
	}

	static clsDate IncreaseDateByXYearsFaster(short Years, clsDate& Date)
	{
		Date.Year += Years;
		return Date;
	}

	void IncreaseDateByXYearsFaster(short Years) {
		IncreaseDateByXYearsFaster(Years, *this);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade() {
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(short Decades, clsDate& Date)
	{
		for (short i = 1; i <= Decades;i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}
		return Date;
	}

	void IncreaseDateByXDecades(short Decades) {
		IncreaseDateByXDecades(Decades, *this);
	}

	static clsDate IncreaseDateByXDecadesFaster(short Decades, clsDate& Date)
	{
		Date.Year += Decades * 10;
		return Date;
	}

	void IncreaseDateByXDecadesFaster(short Decades) {
		IncreaseDateByXDecadesFaster(Decades, *this);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury() {
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year += 1000;
		return Date;
	}

	void IncreaseDateByOneMillennium() {
		IncreaseDateByOneMillennium(*this);
	}

	//Decrease
	clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
			}
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}

	void DecreaseDateByOneDay() {
		DecreaseDateByOneDay(*this);
	}

	clsDate DecreaseDateByXDays(short Days, clsDate& Date)
	{
		for (short i = 1;i <= Days;i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDays(short Days) {
		DecreaseDateByXDays(Days, *this);
	}

	clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		return DecreaseDateByXDays(7, Date);
	}

	void DecreaseDateByOneWeek() {
		DecreaseDateByOneWeek(*this);
	}

	clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
	{
		for (short i = 1;i <= Weeks;i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks) {
		DecreaseDateByXWeeks(Weeks, *this);
	}

	clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
		{
			Date.Month--;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
		if (NumberOfDaysInCurrentMonth < Date.Day)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	void DecreaseDateByOneMonth() {
		DecreaseDateByOneMonth(*this);
	}

	clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
	{
		for (short i = 1;i <= Months;i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMonths(short Months) {
		DecreaseDateByXMonths(Months, *this);
	}

	clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date.Year--;
		return Date;
	}

	void DecreaseDateByOneYear() {
		DecreaseDateByOneYear(*this);
	}

	clsDate DecreaseDateByXYears(short Years, clsDate& Date)
	{
		for (short i = 1;i <= Years;i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	void DecreaseDateByXYears(short Years) {
		DecreaseDateByXYears(Years, *this);
	}

	clsDate DecreaseDateByXYearsFaster(short Years, clsDate& Date)
	{
		Date.Year -= Years;
		return Date;
	}

	void DecreaseDateByXYearsFaster(short Years) {
		DecreaseDateByXYearsFaster(Years, *this);
	}

	clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade() {
		DecreaseDateByOneDecade(*this);
	}

	clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
	{
		for (short i = 1; i <= Decades;i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}
		return Date;
	}

	void DecreaseDateByXDecades(short Decades) {
		DecreaseDateByXDecades(Decades, *this);
	}

	clsDate DecreaseDateByXDecadesFaster(short Decades, clsDate& Date)
	{
		Date.Year -= Decades * 10;
		return Date;
	}

	void DecreaseDateByXDecadesFaster(short Decades) {
		DecreaseDateByXDecadesFaster(Decades, *this);
	}

	clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury() {
		DecreaseDateByOneCentury(*this);
	}

	clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium() {
		DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate Date)
	{
		return (DayOfWeekOrder(Date.Day,Date.Month,Date.Year) == 6);
	}

	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		short DayIndex = DayOfWeekOrder(Date.Day,Date.Month,Date.Year);
		return (DayIndex == 5) || (DayIndex == 6);
	}

	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date.Day,Date.Month,Date.Year);
	}

	short DaysUntilTheEndOfWeek() {
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		short NumberOfDaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
		return NumberOfDaysInMonth - Date.Day;
	}

	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		short NumberOfDaysInYear = isLeapYear(Date.Year) ? 366 : 365;
		return NumberOfDaysInYear - NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
	}

	short DaysUntilTheEndOfYear() {
		return DaysUntilTheEndOfYear(*this);
	}

	static short ActualVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		short DaysCount = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				DaysCount++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return DaysCount;
	}

	short ActualVacationDays(clsDate DateTo) {
		return ActualVacationDays(*this, DateTo);
	}

	static clsDate CalculateVacationReturn(clsDate DateFrom, short VacationDays)
	{
		clsDate DateTo = DateFrom;

		while (VacationDays > 0)
		{
			if (IsBusinessDay(DateTo))
			{
				VacationDays--;
			}

			DateTo = IncreaseDateByOneDay(DateTo);
		}

		while (IsWeekEnd(DateTo))
		{
			DateTo = IncreaseDateByOneDay(DateTo);
		}

		return DateTo;
	}

	void CalculateVacationReturn(short VacationDays) {
		*this = CalculateVacationReturn(*this, VacationDays);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !(IsDate1BeforeDate2(Date1, Date2) || IsDate1EqualDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2) {
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		//if Date1 before Date2
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		//if Date1 Equals Date2
		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		//if Date1 After Date2
		/*if (MyDate::IsDate1AfterDate2(Date1, Date2))
			return enDateCompare::After;*/

			//this is faster
		return enDateCompare::After;
	}

	enDateCompare CompareDates(clsDate Date2) {
		return CompareDates(*this, Date2);
	}

	static bool IsValid(clsDate Date)
	{
		short NumberOfDaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
		return (Date.Month >= 1 && Date.Month <= 12) ? (Date.Day >= 1 && Date.Day <= NumberOfDaysInMonth) : false;
	}

	bool IsValid() {
		return IsValid(*this);
	}

	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormatDateString = "";

		FormatDateString = clsString::ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
		FormatDateString = clsString::ReplaceWordInString(FormatDateString, "mm", to_string(Date.Month));
		FormatDateString = clsString::ReplaceWordInString(FormatDateString, "yyyy", to_string(Date.Year));

		return FormatDateString;
	}

	string FormatDate(string DateFormat = "dd/mm/yyyy") {
		return FormatDate(*this, DateFormat);
	}
};