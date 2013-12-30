/**********************************************
 * File: pqueue-vector.h
 *
 * A priority queue class backed by an unsorted
 * vector.
 */
#ifndef PQueue_Vector_Included
#define PQueue_Vector_Included

#include <string>
#include "vector.h"
using namespace std;

/* A class representing a priority queue backed by an
 * unsorted Vector.
 */
class VectorPriorityQueue {
public:
	/* Constructs a new, empty priority queue backed by a vector. */
	VectorPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~VectorPriorityQueue();
	
	/* Returns the number of elements in the priority queue. */
	int size();
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();
	
	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek();
	
	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();

private:
    static const int INITIAL_CAPACITY = 10;
    
    // Instance variables
    Vector<string> vector;                     // A Vector of elements
};

#endif
