/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */

#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
    // Defer to underlying Vector class
}

VectorPriorityQueue::~VectorPriorityQueue() {
    // Defer to underlying Vector class
}

int VectorPriorityQueue::size() {	
	return vector.size();
}

bool VectorPriorityQueue::isEmpty() {
	return vector.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
    vector.add(value);
}

string VectorPriorityQueue::peek() {
    if (vector.isEmpty()) error("peek: Attempting to peek into empty pqueue");
    string min = vector[0];
    for (int i = 1; i < vector.size(); i++) {
        if (vector[i] < min) min = vector[i];
    }
    return min;
}

string VectorPriorityQueue::dequeueMin() {
    if (vector.isEmpty()) error("dequeueMin: Attempting to dequeue an empty pqueue");
    int index = 0;
    string min = vector[index];
    for (int i = 1; i < vector.size(); i++) {
        if (vector[i] < min) {
            min = vector[i];
            index = i;
        }
    }
    vector.remove(index);
    return min;
}

