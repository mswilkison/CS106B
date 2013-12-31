/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
    head = NULL;                 // Initialize emptylist
    count = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
    while (count > 0) {
        dequeueMin();
    }
}

int LinkedListPriorityQueue::size() {
    return count;
}

bool LinkedListPriorityQueue::isEmpty() {
    return count == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
    Cell *cp = new Cell;
    cp->str = value;
    cp->link = NULL;
    if (head == NULL) {
        head = cp;
    } else if (value <= head->str) {
        cp->link = head;
        head = cp;
    } else {
        for (Cell *prevCell = head; prevCell != NULL; prevCell = prevCell->link) {
            Cell *nextCell = prevCell->link;
            if (nextCell == NULL) {
                prevCell->link = cp;
                break;
            } else if (value < nextCell->str) {
                cp->link = nextCell;
                prevCell->link = cp;
                break;
            }
        }
    }
    count++;
}

string LinkedListPriorityQueue::peek() {
    if (isEmpty()) error("peek: Attempting to peek into an empty pqueue");
    return head->str;
}

string LinkedListPriorityQueue::dequeueMin() {
    if (isEmpty()) error("dequeueMin: Attempting to dequeue an empty pqueue");
    Cell *cp = head;
    string result = cp->str;
    if (count > 1) head = cp->link;
    else head = NULL;
    delete cp;
    count--;
    return result;
}

