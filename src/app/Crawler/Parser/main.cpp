#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Headers/misc.h"
#include "Sources/misc.cpp"

using namespace std;

int main()
{
    vector<string> keywords;
    string test = "Malaysian military radar apparently lost contact with the plane as it flew over the Indian Ocean. (According to reports on March 19th, Thai military radar may also have tracked it turning off course.) That suggests it is somewhere on an arc hundreds of miles wide running from Kazakhstan almost to Antarctica (see map). Planes and ships from 26 countries have now joined the hunt. The northern part seems less plausible: it approaches land and passes through several countries with military radar primed to look for unidentified aircraft. But to the south, where the search is now focused, there is little coverage.The information age is taking to the skies only slowly. Planes far out at sea keep in touch using VHF radio, and the newer ones send ACARS data continuously via satellite. Many are also equipped with ADS-B, another system that uses satellites and GPS to pinpoint their location when they are out of radar range. But flight 370�s ADS-B seems to have stopped transmitting about the time its transponder went off.Clearer skiesAircraft-tracking websites use several of these newer sources of data. They will eventually replace radar when their safety and reliability are beyond dispute, a long process in the plodding world of aviation regulation. And the next generation of communications technology, due in around a decade, will relay all flight information at once, acting like a real-time version of the black box that all planes now carry. Adding internet connectivity, as many airlines are doing, will provide another way to get a message to the ground.Until parts of the plane are examined, how it came to grief will remain unknown. In the meantime, for the grieving relatives, there is little comfort to be taken from the fact that such mysteries should soon be a thing of the past.";
    keywords = splitString(test, ' ');
    int i = 0;
    int size = keywords.size();
    for (i = 0; i < size; i++)
        cout << keywords[i] << endl;
}
