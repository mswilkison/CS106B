/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: MacLane Wilkison
 * Section: SEE
 * This program determines whether a string is a subsequence of another string.
 * If 'S' and 'T' are strings, we say that 'S' is a subsequence of 'T' if all
 * of the letters of 'S' appear in 'T' in the same relative order that they
 * appear in 'S'. The empty string is a subsequence of every string, since
 * all 0 characters of the empty string appear in the same relative order in
 * any arbitrary string.
 */

#include <iostream>
#include <string>
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    cout << "PIN is a subsequence of the string ProgrammINg: ";
    cout << isSubsequence("programming", "pin") << endl;
    cout << "SINGE is a subsequence of the string SprINGtimE: ";
    cout << isSubsequence("springtime", "singe") << endl;
    cout << "STEAL is not a subsequence of the string LEAST (wrong order): ";
    cout << isSubsequence("least", "steal") << endl;
    cout << "I is a subsequence of the string team: ";
    cout << isSubsequence("team", "I") << endl;
    return 0;
}

bool isSubsequence(string text, string subsequence) {
    if (subsequence == "" || subsequence == text) return true;
    int pos = text.find(subsequence[0]);
    if (pos != string::npos) return isSubsequence(text.substr(pos + 1),
                                        subsequence.substr(1));
    return false;
}
