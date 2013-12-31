/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
    head = NULL;
    count = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    while (count > 0) {
        dequeueMin();
    }
}

int DoublyLinkedListPriorityQueue::size() {
    return count;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
    return count == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
    Cell *cp = new Cell;
    cp->str = value;
    cp->next = head;
    cp->prev = NULL;
    if (head != NULL) head->prev = cp;
    head = cp;
    count++;
}

string DoublyLinkedListPriorityQueue::peek() {
    if (isEmpty()) error("peek: Attmempting to peek into an empty list");
    string result = head->str;
    for (Cell *nextCell = head->next; nextCell != NULL; nextCell = nextCell->next) {
        if (nextCell->str < result) result = nextCell->str;
    }
    return result;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
    if (isEmpty()) error("dequeueMin: Attmempting to dequeue from an empty list");
    string result = head->str;
    for (Cell *nextCell = head->next; nextCell != NULL; nextCell = nextCell->next) {
        if (nextCell->str < result) result = nextCell->str;
    }

    Cell *removeCell = head;
    while (removeCell->str != result && removeCell->next != NULL) {
        removeCell = removeCell->next;
    }
    if (removeCell == head) {
        head = removeCell->next;
    } else {        
        Cell *prevCell = removeCell->prev;
        Cell *nextCell = removeCell->next;
        if (nextCell != NULL) {
            prevCell->next = nextCell;
            nextCell->prev = prevCell;
        } else {
            prevCell->next = NULL;
        }
    }
    delete removeCell;
    count--;
    return result;
}

