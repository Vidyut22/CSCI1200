class Time {
public:
    Time();
    Time(int hour, int minute, int second);

    // Accessors
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    // Mutator
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);

    // Member Functions
    void PrintAMPM() const;

private:
    int hour;
    int minute;
    int second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);


