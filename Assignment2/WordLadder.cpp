/*
 * File: WordLadder.cpp
 * --------------------
 * Name: MacLane Wilkison
 * Section: SEE
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

// Function prototypes
Vector<string> findLadder(string startWord, string destinationWord);

int main() {
    while (true) {
        string startWord = getLine("Enter start word (RETURN to quit): ");
        if (startWord == "") break;
        string destinationWord = getLine("Enter destination word: ");
        Vector<string> ladder = findLadder(startWord, destinationWord);
        if (ladder.isEmpty()) {
            cout << "No ladder found." << endl;
        } else {
            cout << "Ladder found!" << endl;
            for (int i = 0; i < ladder.size(); i++) {
                cout << ladder[i] << " -> ";
            }
            cout << endl;
        }
    }
    return 0;
}

/*
 * Function: findLadder
 * Usage: Vector<string> ladder = findLadder(startWord, destinationWord)
 * This function takes a startWord and destinationWord as parameters and
 * returns the word ladder, if one exists.
 */
Vector<string> findLadder(string startWord, string destinationWord) {
    Lexicon english("EnglishWords.dat");
    Lexicon wordsTried("EnglishWords.dat");
    wordsTried.clear();
    Queue< Vector<string> > ladderQueue;
    Vector<string> ladderVector;
    ladderVector.add(startWord);
    ladderQueue.enqueue(ladderVector);
    while (!ladderQueue.isEmpty()) {
        ladderVector = ladderQueue.dequeue();
        string lastWordInLadder = ladderVector.get(ladderVector.size() - 1);
        if (lastWordInLadder == destinationWord) return ladderVector;
        for (int i = 0; i < lastWordInLadder.length(); i++) {
            for (char ch = 'a'; ch <= 'z'; ch++) {
                string possibleWord = lastWordInLadder;
                possibleWord[i] = ch;
                if (english.contains(possibleWord) && !wordsTried.contains(possibleWord)) {
                    wordsTried.add(possibleWord);
                    Vector<string> newLadder = ladderVector;
                    newLadder.add(possibleWord);
                    ladderQueue.enqueue(newLadder);
                }
            }
        }
    }
    Vector<string> emptyVec;
    return emptyVec;
    /*
     * while (the queue is not empty) {
     *     Dequeue the first ladder from the queue.
     *     if (the final word in this ladder is the destination word) {
     *         Return this ladder as the solution.
     *     }
     *     for (each word in the lexicon of English words that differs by one letter) {
     *         if (that word has not already been used in a ladder) {
     *             Create a copy of the current ladder.
     *             Add the new word to the end of the copy.
     *             Add the new ladder to the end of the queue.
     *         }
     *     }
     * }
     * Report that no word ladder exists.
     */
}
