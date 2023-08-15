#include <bits/stdc++.h>
using namespace std;
#include "string_util.h"

// Function to convert unix time to
// Human readable format
string unixTimeToHumanReadable(long int seconds)
{

    // Save the time in Human
    // readable format
    string ans = "";

    // Number of days in month
    // in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };

    int currYear, daysTillNow, extraTime, extraDays,
        index, date, month, hours, minutes, secondss,
        flag = 0;

    // Calculate total days unix time T
    daysTillNow = seconds / (24 * 60 * 60);
    extraTime = seconds % (24 * 60 * 60);
    currYear = 1970;

    // Calculating current year
    while (true) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0 && currYear % 100 != 0)) {
            if (daysTillNow < 366) {
                break;
            }
            daysTillNow -= 366;
        }
        else {
            if (daysTillNow < 365) {
                break;
            }
            daysTillNow -= 365;
        }
        currYear += 1;
    }
    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;

    if (currYear % 400 == 0
        || (currYear % 4 == 0 && currYear % 100 != 0))
        flag = 1;

    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {

            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays - daysOfMonth[index] < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {

            if (extraDays - daysOfMonth[index] < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }

    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }

    // Calculating HH:MM:YYYY
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;

    char *buff = new char[128];
    sprintf(buff,"%4i-%02i-%02i %02i:%02i:%02i",currYear,month,date,hours,minutes,secondss);
    ans = std::string(buff);
    // Return the time
    return ans;
}

long toTimestamp(const std::string& date){
    std::vector<std::string> splits = abby::StringUtil::Split(date,' ');
    for (size_t i = 0; i < splits.size(); i++)
    {
        std::cout << "index:" << i << " " << splits[i] << std::endl;
    }
    std::string d = splits[0];
    std::string s = splits[1];
    
    std::vector<std::string> dSplits = abby::StringUtil::Split(d,'-');
    // for (size_t i = 0; i < dSplits.size(); i++)
    // {
    //     std::cout << "year index:" << i << " " << dSplits[i] << std::endl;
    // }

    std::vector<std::string> sSplits = abby::StringUtil::Split(s,':');
    // for (size_t i = 0; i < sSplits.size(); i++)
    // {
    //     std::cout << "time index:" << i << " " << sSplits[i] << std::endl;
    // }
    int years = stoi(dSplits[0]);
    int tempy = 1970;
    int otherDay = 0;
    while (tempy < years)
    {
        if (tempy % 400 == 0
        || (tempy % 4 == 0 && tempy % 100 != 0)){
            otherDay += 1;
        }
        tempy += 1;
    }

    int year = years - 1970;
    int month = stoi(dSplits[1]);
    int days = stoi(dSplits[2]) - 1;

    if(month>2)
    {
        if (years % 400 == 0
        || (years % 4 == 0 && years % 100 != 0)){
            otherDay += 1;
        }
    }
    std::cout << "year:" << year << " month:" << month << " days:" << days << std::endl;
    
    int hours = stoi(sSplits[0]);
    int minent = stoi(sSplits[1]);
    int seconds = stoi(sSplits[2]);
    std::cout << "hours:" << hours << " minent:" << minent << " seconds:" << seconds << std::endl;


    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
    long dayTime = 3600 * 24;
    long day = year * 365;
    std::cout << "day:" << day << std::endl;
    for (size_t i = 0; i < month - 1; i++)
    {
        day += daysOfMonth[i];
    }
    std::cout << "day:" << day << std::endl;
    day += days;
    std::cout << "day:" << day << std::endl;
    day += otherDay;
    long timestamp = day * dayTime  + hours * 3600 + minent * 60 + seconds;

    return timestamp;
} 

// Driver Code
int main()
{

    std::shared_ptr<std::vector<float>> ptr = make_shared<std::vector<float>>();;
    ptr->push_back(0.1);
    ptr->push_back(0.2);
    std::cout << ptr.get()->size() << std::endl;
    std::cout << (*ptr).size() << std::endl;
    // Given unix time
    long int T = 1685418244;

    // Function call to convert unix
    // time to human read able
    string ans = unixTimeToHumanReadable(T);

    // Print time in format
    // DD:MM:YYYY:HH:MM:SS
    cout << ans << "\n";


    //std::string date = "2023-05-30 11:09:45";
    long timestamp = toTimestamp(ans);
    cout << "timestamp:" << timestamp << "\n";
    return 0;
}