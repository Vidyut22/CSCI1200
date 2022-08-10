#include <iostream>
#include "Time.h"
using namespace std;
// Constructors
Time::Time()
{
    hour = 23;
    minute = 59;
    second = 59;
}

Time::Time(int hour, int minute, int second)
{
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}
string leadZero(int num)
{
    if (num < 10)
    {
        std::string str = "0" + to_string(num);
        return str;
    }
    return to_string(num);
}

//Accessors
int Time::getHour() const
{
    return hour;
}

int Time::getMinute() const
{
    return minute;
}

int Time::getSecond() const
{
    return second;
}

// Mutator
void Time::setHour(int hour)
{
    this->hour = hour;
}

void Time::setMinute(int minute)
{
    this->minute = minute;
}

void Time::setSecond(int second)
{
    this->second = second;
}

// Member Functions
void Time::PrintAMPM() const
{
    if (getHour() == 0) {
        std::cout << 12 << ':'
            << leadZero(getMinute()) << ':'
            << leadZero(getSecond()) << ' '
            << "am" << std::endl;
    }
    else if (getHour() > 12)
    {
        std::cout << getHour() - 12 << ':'
            << leadZero(getMinute()) << ':'
            << leadZero(getSecond()) << ' '
            << "pm" << std::endl;
    }
    else if (getHour() == 12)
    {
        std::cout << getHour() << ':'
            << leadZero(getMinute()) << ':'
            << leadZero(getSecond()) << ' '
            << "pm" << std::endl;
    }
    else {
        std::cout << getHour() << ':'
            << leadZero(getMinute()) << ':'
            << leadZero(getSecond()) << ' '
            << "am" << std::endl;
    }
}

bool IsEarlierThan(const Time& t1, const Time& t2)
{
    return t1.getHour() * 3600 + t1.getMinute() * 60 + t1.getSecond() < t2.getHour() * 3600 + t2.getMinute() * 60 + t2.getSecond();
    
}