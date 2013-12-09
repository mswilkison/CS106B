/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: MacLane Wilkison
 * Section: SEE
 * This file is the starter project for the coin-flipping problem.
 * This program simulates flipping a coint repeatedly and continues
 * until three consecutive heads are tossed.
 */

#include <iostream>
#include <string>
#include "random.h"
using namespace std;

int main() {
    int consecutiveHeads = 0;
    int flips = 0;
    while (true) {
        flips++;
        if (randomChance(0.50)) {
            cout << "heads" << endl;
            consecutiveHeads++;
        } else {
            cout << "tails" << endl; consecutiveHeads = 0;
        }
        if (consecutiveHeads == 3) {
            cout << "It took " << flips << " flips to get 3 consecutive heads.";
            break;
        }
    }
    return 0;
}
