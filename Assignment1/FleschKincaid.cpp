/*******************************************************************
 * File: FleschKincaid.cpp
 *
 * A program that approximates the Flesch-Kincaid grade level of a
 * piece of text.
 * 
 * The Flesh-Kincaid test assigns a number to a piece of text indicating what
 * grade level is necessary to understand the text. The test counts up the total
 * number of words and sentences within the text, along with the total number
 * of syllables within each of those words. Given these numbers, the grade
 * level score is then computed using the following formula:
 * 
 *      Grade = C0 + C1(num words / num sentences) + C2(num syllables / num words)
 * 
 * Where C0, C1, and C2 are constants:
 *  C0 = 15.59          C1 = 0.39          C2 = 11.8
 */

#include <iostream>
#include <fstream>
#include <string>
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

// Constants
const double C0 = -15.59;
const double C1 = 0.39;
const double C2 = 11.8;

// Function prototypes
void promptUserForFile(ifstream & infile, string prompt = "");
bool isVowel(char ch);
double calcFkScore(int syllableCount, int wordCount, int sentenceCount);

// Main program
int main() {
    ifstream infile;
    promptUserForFile(infile, "Input file: ");
    
    TokenScanner scanner(infile);
    scanner.ignoreWhitespace();
    scanner.addWordCharacters("\'");
    
    // REFACTOR THIS INTO FUNCTION; TWEAK SYLLABLE COUNTING
    // Process file and count sentences and words using "tokenscanner"
    int syllableCount = 0;
    int wordCount = 0;
    int sentenceCount = 0;
    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        if (scanner.getTokenType(token) == WORD) {
            wordCount++;            
            for (int i = 0; i < token.length(); i++) {
                if (isVowel(token[i])) syllableCount++;
            }
        } else if (token == ".") sentenceCount++;        
    }
    
    if (sentenceCount == 0) sentenceCount = 1; // Avoid DIV by 0 error if empty file
    if (wordCount == 0) wordCount = 1; // Avoid DIV by 0 error if empty file
    int fkScore = calcFkScore(syllableCount, wordCount, sentenceCount);
    
    cout << "Sentence Count: " << sentenceCount << endl;
    cout << "Word Count: " << wordCount << endl;
    cout << "Syllables: " << syllableCount << endl;
    cout << "Flesh-Kincaid Score: " << fkScore << endl;
    
    infile.close();
    return 0;
}


/*
 * Function: promptUserForFile
 * Usage: promptUserForFile(infile, prompt);
 * Asks the user for the name of an input file and opens the reference
 * parameter infile using that name, which is returned as the result of 
 * the function. If the requested file does not exist, the user is given
 * additional chances to enter a valid file name. The optional prompt
 * argument is used to give the user more information about the desired input
 * file.
 */
void promptUserForFile(ifstream & infile, string prompt) {
    while (true) {
        cout << prompt;
        string filename;
        getline(cin, filename);
        infile.open(filename.c_str());
        if (!infile.fail()) break;
        infile.clear();
        cout << "Unable to open that file. Try again." << endl;
        if (prompt == "") prompt = "Input file: ";
    }
}

/*
 * Function: isVowel
 * Usage: bool flag = isVowel(ch);
 * Predicate function that returns true if the char passed as a parameter
 * is a vowel.
 */
bool isVowel(char ch) {
    string vowels = "aeiouy";
    for (int i = 0; i < vowels.length(); i++) {
        if (ch == vowels[i]) return true;
    }
    return false;
}

/*
 * Function: calcFkScore
 * Usage: double score = calcFkScore(syllableCount, wordCount, sentenceCount);
 * This function returns the Flesh-Kincaid score, given the syllable, word,
 * and sentence counts for the string that is to be analyzed.
 */
double calcFkScore(int syllableCount, int wordCount, int sentenceCount) {
    return C0 + C1 * (wordCount / sentenceCount) + C2 * (syllableCount / wordCount);
}