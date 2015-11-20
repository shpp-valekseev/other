#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
using namespace std;

/**
 * This program simulates a coin toss (heads and tails),
 * and continues to do, until when the fall heads three times by turns.
 */

// This variable indicates the desired number of consecutive victories.
const int COL_WIN = 3;

int main() {

int countFlip = 0;
int headsCount = 0;

    while(headsCount != COL_WIN){
        string sideCoin;
        if (randomBool()){
            sideCoin = "heads";
            headsCount++;
        } else {
            sideCoin = "tails";
            headsCount = 0;
        }
        countFlip++;
        cout << sideCoin << endl;
    }
    cout << "It took " << countFlip << " flips to get " << COL_WIN << " consecutive heads." << endl;
   return 0;
}
