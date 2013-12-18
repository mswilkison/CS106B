/*
 * File: Boggle.cpp
 * ----------------
 * Name: MacLane Wilkison
 * Section: SEE
 * This file implements a PvC version of Boggle, the classic word search game.
 */
 
#include <iostream>
#include <cmath>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "grid.h"
#include "strlib.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const Lexicon english("EnglishWords.dat");

const string STANDARD_CUBES[16]  = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void play(int boardSize);
Vector<string> shakeCubes(const string array[], int numCubes);
Vector<string> copyArrayIntoVector(const string array[], int numCubes);
void shuffleVector(Vector<string> & vec);
void selectCubeFace(Vector<string> & cubes);
Grid<char> placeCubes(Vector<string> & cubes);
void humanPlayerTurn(Lexicon & boardLexicon);
void computerPlayerTurn(Lexicon & boardLexicon);
bool checkWord(string guess, Lexicon & humanGuesses, Lexicon & boardLexicon);
void findWordsOnBoard(Grid<char> & boardGrid, Lexicon & boardLexicon);
void findAllDirections(string current, Grid<char> & boardGird, int row,
                      int col, Lexicon & boardLexicon);
void findInDirection(string current, Grid<char> & boardGrid, int row,
                     int col, Lexicon & boardLexicon, int rowInc, int colInc);

/* Main program */

int main() {
   GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
   initGBoggle(gw);
   welcome();
   giveInstructions();
   while (true) {
       cout << "---BOARD CONFIGURATION---" << endl;
       cout << "Board size (Press 'B' for Big/any other key for Standard): ";
       string size;
       getline(cin, size);
       int boardSize;
       (size == "B") ? boardSize = 5 : boardSize = 4;                
       play(boardSize);
   }
   cin.get();
   return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}

void play(int boardSize) {
    drawBoard(boardSize, boardSize);
    cout << "Press 'C' for custom board/any other key for Random board): ";
    string custom;
    getline(cin, custom);
    string customBoard;
    Vector<string> cubes;
    if (custom == "C") {
        while (customBoard.length() < boardSize * boardSize) {
            cout << "Please enter string of cube faces (characters must be"
                 << "greater than or equal to the number of cubes on the board): ";
            getline(cin, customBoard);
        }
        for (int i = 0; i < boardSize * boardSize; i++) {
            cubes.add(customBoard.substr(i, i + 1));
        }
    } else if (boardSize == 4) {
        cubes = shakeCubes(STANDARD_CUBES, boardSize * boardSize);
        selectCubeFace(cubes);
    } else {
        cubes = shakeCubes(BIG_BOGGLE_CUBES, boardSize * boardSize);
        selectCubeFace(cubes);
    }        
    Grid<char> boardGrid = placeCubes(cubes);
    Lexicon boardLexicon;
    findWordsOnBoard(boardGrid, boardLexicon);
    humanPlayerTurn(boardLexicon);
    computerPlayerTurn(boardLexicon);
}

Vector<string> shakeCubes(const string array[], int numCubes) {
    Vector<string> shakenVec = copyArrayIntoVector(array, numCubes);
    shuffleVector(shakenVec);
    return shakenVec;
}

Vector<string> copyArrayIntoVector(const string array[], int numCubes) {
    Vector<string> vecCopy;
    for (int i = 0; i < numCubes; i++) {
        vecCopy.add(array[i]);
    }
    return vecCopy;
}

void shuffleVector(Vector<string> & vec) {
    for (int i = 0; i < vec.size(); i++) {
        int index = randomInteger(i, vec.size() - 1);
        string tmp = vec[i];
        vec[i] = vec[index];
        vec[index] = tmp;
    }
}

void selectCubeFace(Vector<string> & cubes) {
    for (int i = 0; i < cubes.size(); i++) {
        string cube = cubes[i];
        int index = randomInteger(0, cube.length() - 1);
        string cubeFace = cube.substr(index, index + 1);
        cubes[i] = cubeFace;
    }
}

Grid<char> placeCubes(Vector<string> & cubes) {
    int index = 0;
    Grid<char> boardGrid(sqrt(cubes.size()), sqrt(cubes.size()));
    for (int row = 0; row < sqrt(cubes.size()); row++) {
        for (int col = 0; col < sqrt(cubes.size()); col++) {
            //string cube = cubes[index++];            
            //char cubeFace = cube[randomInteger(0, cube.length() - 1)];
            char cubeFace = cubes[index++][0];
            labelCube(row, col, cubeFace);
            boardGrid[row][col] = cubeFace;
        }
    }
    return boardGrid;
}

void humanPlayerTurn(Lexicon & boardLexicon) {
    cout << "Enter word (RETURN to end): ";
    Lexicon humanGuesses;
    while (true) {
        string guess;
        getline(cin, guess);
        guess = toLowerCase(guess);
        if (guess == "") break;
        if (checkWord(guess, humanGuesses, boardLexicon)) recordWordForPlayer(guess, HUMAN);
        cout << "  >> ";
    }
}

void computerPlayerTurn(Lexicon & boardLexicon) {
    foreach (string word in boardLexicon) {
        if (word.length() > 3) recordWordForPlayer(word, COMPUTER);
    }
}

bool checkWord(string guess, Lexicon & humanGuesses, Lexicon & boardLexicon) {
    if (guess.length() > 3 && !humanGuesses.contains(guess) && english.contains(guess)) {
        humanGuesses.add(guess);
        return boardLexicon.contains(guess);
    }
    return false;
}

void findWordsOnBoard(Grid<char> & boardGrid, Lexicon & boardLexicon) {
    for (int row = 0; row < boardGrid.numRows(); row++) {
        for (int col = 0; col < boardGrid.numCols(); col++) {
            string current;
            findAllDirections(current, boardGrid, row, col, boardLexicon);
        }
    }

}

void findAllDirections(string current, Grid<char> & boardGrid, int row,
                      int col, Lexicon & boardLexicon) {
    Vector<int> rowDir;
    Vector<int> colDir;
    rowDir.add(-1);
    colDir.add(-1);
    rowDir.add(0);
    colDir.add(0);
    rowDir.add(1);
    colDir.add(1);
    foreach (int rowInc in rowDir) {
        foreach (int colInc in colDir) {
            if (boardGrid.inBounds(row + rowInc, col + colInc)) {
                findInDirection(current, boardGrid, row, col, boardLexicon,
                                rowInc, colInc);
            }
        }
    }
    
}

void findInDirection(string current, Grid<char> & boardGrid, int row,
                     int col, Lexicon & boardLexicon, int rowInc, int colInc) {
    current += boardGrid[row][col];
    if (english.contains(current)) boardLexicon.add(current);
    if (english.containsPrefix(current)) {
        if (boardGrid.inBounds(row + rowInc, col + colInc)) {
            findInDirection(current, boardGrid, row + rowInc, col + colInc,
                        boardLexicon, rowInc, colInc);
        }
    }
}