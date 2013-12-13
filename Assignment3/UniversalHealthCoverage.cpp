/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: MacLane Wilkison
 * Section: SEE
 * This program determines whether, given a limit on the number of hospitals that
 * can be constructed, the potential hospital locations can be chosen in such
 * a way so that each city in a given Set can be covered.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> > & locations,
                               int numHospitals,
                               Vector< Set<string> > & result);


int main() {
    // Test variables
    Set<string> cities;
    Vector< Set<string> > locations;
    cities += "A", "B", "C", "D", "E", "F";
    Set<string> hospital0;
    hospital0 += "A", "B", "C";
    Set<string> hospital1;
    hospital1 += "A", "C", "D";
    Set<string> hospital2;
    hospital2 += "B", "F";
    Set<string> hospital3;
    hospital3 += "C", "E", "F";
    locations += hospital0, hospital1, hospital2, hospital3;
    cout << "Need to cover: " << cities << endl;
    Vector< Set<string> > result;
    
    if (canOfferUniversalCoverage(cities, locations, 3, result)) cout << "yes!" << endl;
    return 0;
}

bool canOfferUniversalCoverage(Set<string> & cities,
                               Vector< Set<string> > & locations,
                               int numHospitals,
                               Vector< Set<string> > & result) {
    Set<string> covered;
    if (result.size() == numHospitals) {
        foreach (Set<string> loc in result) {
            covered += loc;
        }
        cout << covered << endl;
        return cities.isSubsetOf(covered);
    } else {
        Vector< Set<string> > origResult = result;
        cout << "adding" << locations[0] << endl;
        result += locations[0];
        Vector< Set<string> > remaining = locations;
        remaining.remove(0);
        return canOfferUniversalCoverage(cities, remaining, numHospitals, result)
            || canOfferUniversalCoverage(cities, remaining, numHospitals, origResult);
    }
}

