/*
 * File: InverseGenetics.cpp
 * ----------------------
 * Name: MacLane Wilkison
 * Section: SEE
 * This program accepts the amino acid sequence of a protein and returns the
 * set of all possible RNA strands that it could encode.
 */
#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
Set<string> listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
	/* Load the codon map. */
	Map<char, Set<string> > codons = loadCodonMap();
	
        cout << "RNA strands for sequence KWS: " << endl;
	foreach (string s in listAllRNAStrandsFor("KWS", codons)) {
            cout << s << endl;
        }
	return 0;
}

Set<string> listAllRNAStrandsFor(string protein, Map< char, Set<string> > & codons) {
    Set<string> result;
    if (protein == "") {
        result += "";
    } else {
        foreach (string encoding in codons.get(protein[0])) {
            foreach (string nextEncoding in listAllRNAStrandsFor(protein.substr(1), codons)) {
                result += encoding + nextEncoding;
            }
        }
    }
    return result;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
	ifstream input("codons.txt");
	Map<char, Set<string> > result;
    
	/* The current codon / protein combination. */
	string codon;
	char protein;
	
	/* Continuously pull data from the file until all data has been
	 * read.
	 */
	while (input >> codon >> protein) {
		result[protein] += codon;
	}
	
	return result;
}

