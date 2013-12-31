/*******************************************************
 * File: pqueue-doublylinkedlist.h
 *
 * A priority queue class backed by an unsorted, doubly-linked
 * list.
 */
#ifndef PQueue_DoublyLinkedList_Included
#define PQueue_DoublyLinkedList_Included

#include <string>
using namespace std;

/* A class representing a priority queue backed by an unsorted,
 * doubly-linked list.
 */
class DoublyLinkedListPriorityQueue {
public:
	/* Constructs a new, empty priority queue backed by a doubly-linked list. */
	DoublyLinkedListPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~DoublyLinkedListPriorityQueue();
	
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
    // Type for doubly linked list
    struct Cell {
        string str;                     // The string to store
        Cell *next;                     // Link to next Cell
        Cell *prev;                     // Link to previous Cell
    };
    
    // Instance variables
    Cell *head;                         // Pointer to head Cell
    Cell *tail;                         // Pointer to tail Cell
    int count;                          // Number of elements in list
};

#endif
