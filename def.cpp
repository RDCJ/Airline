#include "def.h"

string var[11] = {"Flight ID", "Departure date", "Intl/Dome", "Flight NO.", "Departure airport",
                          "Arrival airport", "Departure Time", "Arrival Time", "Airplane ID", "Airplane Model", "Air fares"};

const int maxR = 2346, maxC = 11, aptNum = 79;
const string EarlistT = "5/4/2017 0:00", LatestT = "5/9/2017 12:00";

int deltaTime(string t1, string t2)
{
    int ans;
    int day1, hour1 = 0, min1 = 0,
         day2, hour2 = 0, min2 = 0;
    day1 = t1[2] - '0'; day2 = t2[2] - '0';
    int p = 9;
    while (t1[p] != ':') hour1 = hour1 * 10 + t1[p++] - '0';
    p++;
    while (p < t1.size()) min1 = min1 * 10 + t1[p++] - '0';
    p = 9;
    while (t2[p] != ':') hour2 = hour2 * 10 + t2[p++] - '0';
    p++;
    while (p < t2.size()) min2 = min2 * 10 + t2[p++] - '0';
    ans = (day1 - day2) * 24 * 60 + (hour1 - hour2) * 60 + (min1 - min2);
    return ans;
}
