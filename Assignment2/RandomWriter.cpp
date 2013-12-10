/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: MacLane Wilkison
 * Section: SEE
 * This program implements a random text writer based on the Markov model.
 * A Markov model is a statistical model that describes the future state of
 * a system based on the current state and the conditional probabilities of
 * the possible transitions. In the case of English text, it is used to
 * describe the possibility of a particular character appearing given the
 * sequence of characters seen so far. An order-0 Markov model predicts
 * that each character occurs with a fixed probability independent of previous
 * characters. An oder-K Markov model predicts each character based on the
 * conditional probability of it following the K characters preceding it.
 * The string of characters preceding the current point is called the seed.
 */

#include <fstream>
#include <iostream>
#include <string>
#include "map.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
using namespace std;

// Function prototypes
void promptUserForFile(ifstream & infile, string prompt = "");
void generateText(Map< string, Vector<char> > & map, string initSeed);
char getRandomChar(Map< string, Vector<char> > & map, string seed);

// Main program
int main() {
    ifstream infile;
    string prompt = "Input file: ";
    promptUserForFile(infile, prompt);
    int order = 0;
    while (true) {
        order = getInteger("Enter the Markov order [1-10]: ");
        if (order >= 1 && order <= 10) break;
        cout << "That value is out of range." << endl;
    }
    
    /*
     * This data structure is a Map with a string key that represents all of
     * the unique seeds (of length K as dictated by the user) in the source
     * file. The values are the individual characters that follow each occurence
     * of the seed. The frequency of the seed can be determined by examining
     * the length of its corresponding Vector value.
     */
    Map<string, Vector<char> > frequencyMap;
    
    /* Read file character-by-character, adding unique seeds (keys) and
     * the characters that follow (values) to our data structure along the way.
     * Also, keeps track of most frequent seed which will be used as the
     * initial seed.
    */
    
    string longest;
    while(true) {
        Vector<char> seedChars(order);
        for (int i = 0; i < order; i++) {
            if (infile.eof()) break;
            seedChars[i] = infile.get();
        }
        string seed;
        for(int i = 0; i < order; i++) {
            seed += seedChars[i];
        }
        Vector<char> vecValue = frequencyMap.get(seed);
        vecValue.add(infile.get());
        if (infile.eof()) break;
        if (vecValue.size() > frequencyMap.get(longest).size()) longest = seed;
        frequencyMap.put(seed, vecValue);
        for (int i = 0; i < order; i++) {
            infile.unget();
        }
    }
    generateText(frequencyMap, longest);
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
 * Function: generateText
 * Usage: generateText(map);
 */
void generateText(Map< string, Vector<char> > & map, string initSeed) {
    string seed = initSeed;
    for (int i = 0; i < 2000 - initSeed.length(); i++) {
        char randChar = getRandomChar(map, seed);
        cout << randChar;
        seed.erase(0, 1);
        seed += randChar;
    }
}

char getRandomChar(Map< string, Vector<char> > & map, string seed) {
    Vector<char> vec = map.get(seed);
    int index = randomInteger(0, vec.size() - 1);
    if (index < 0) index = 0;
    char result = vec[index];
    return result;
}