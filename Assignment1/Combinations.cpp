/*
 * File: Combinations.cpp
 * ----------------------
 * Name: MacLane Wilkison
 * Section: SEE
 * This file is the starter project for the recursive combinations problem.
 * This program implements a recursive definition of mathematical Combinations
 */

#include <iostream>
#include "simpio.h"
using namespace std;

// Prototype
int combination(int n, int k);

int main() {
    cout << combination(6, 2) << endl;
    
    return 0;
}

int combination(int n, int k) {
    if (n == k) return 1;
    if (n == 0 || k == 0) return 1;
    return (combination(n - 1, k - 1) + combination(n - 1, k));
}