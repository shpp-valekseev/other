#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/**
 * This program has two methods stringToInt and intToString.
 * The first method converts the numeric value of type
 * string to type int, and the second method on the contrary,
 * converts the numeric value of type int in string.
 */
int stringToInt(string str);
string intToString(int n);

string resString;
int resInt;
int factor = 1;

int main() {
   // cout << stringToInt("-123") + 2;
   // cout << intToString(-1456);
   return 0;
}

/**
 * The method takes a value of type string.
 * Returns the value of the incoming transformed into a int type
 */
int stringToInt(string str){
    int last;
    bool minus = false;

    // If there is a minus value, it is clipped.
    if(str[0] == 45){
      str = str.erase(0, 1);
      minus = true;
    }

    // Each character converted to a int, forming a number of results.
    if(str.length() > 0){
        last = factor * (str[str.length()-1] - 48);
        str = str.erase(str.length()-1);
        factor *= 10;
        resInt = last + stringToInt(str);
    }

    // If the value was minus, it makes the results negative
    if(minus) resInt *= -1;

return resInt;
}

/**
 * The method takes a value of type int.
 * Returns the value of the incoming transformed into a string type
 */
string intToString(int n){
    char rest ;
    bool minus = false;

    // If the value of a minus, then converts it to the plus and a memory minus
    if (n < 0){
        n *= -1;
        minus = true;
    }

    // If the value consists of a single character, the process ends
    if(n < 10){
       rest = n + 48;
       resString = rest + resString;
       return resString;
    } else {
         rest = (n % 10) + 48;
         n = n / 10;
         resString = intToString(n) + rest;
    }

    // If the value was negative, it adds to the negative result
    if(minus) resString = "-" + resString;

    return resString;
}
