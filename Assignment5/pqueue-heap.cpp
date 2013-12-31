/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
    capacity = INITIAL_CAPACITY;
    count = 0;
    array = new string[capacity];
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] array;
}

int HeapPriorityQueue::size() {
    return count;
}

bool HeapPriorityQueue::isEmpty() {
    return count == 0;
}

void HeapPriorityQueue::enqueue(string value) {
    if (count == capacity) expandCapacity();
    array[count] = value;
    count++;
    if (count > 1) bubbleup(count);
}

string HeapPriorityQueue::peek() {
    if (isEmpty()) error("peek: Attempting to peek into an empty pqueue");
    return array[0];
}

string HeapPriorityQueue::dequeueMin() {
    if (isEmpty()) error("dequeueMin: Attempting to dequeue and empty pqueue");
    string first = array[0];
    array[0] = array[count - 1];
    count--;
    if (count > 1) bubbledown(1); // bubbledown first element
    return first;
}

void HeapPriorityQueue::expandCapacity() {
    string *oldArray = array;
    capacity *= 2;
    array = new string[capacity];
    for (int i = 0; i < count; i++) {
        array[i] = oldArray[i];
    }
    delete[] oldArray;    
}

void HeapPriorityQueue::bubbleup(int index) {
    if (array[index - 1] < array[(index / 2) - 1]) {
        string temp = array[index - 1];
        array[index - 1] = array[(index / 2) - 1];
        array[(index / 2) - 1] = temp;
        if (index / 2 - 1 >= 1) bubbleup(index / 2);
    }
}

void HeapPriorityQueue::bubbledown(int index) {
    if (count > (2 * index) - 1 && array[index - 1] > array[(2 * index) - 1]) {
        string temp = array[index - 1];
        array[index - 1] = array[(2 * index) - 1];
        array[(2 * index) - 1] = temp;
        bubbledown(2 * index);
    }
    
    if (count > 2 * index && array[index - 1] > array[2 * index]) {
        string temp = array[index - 1];
        array[index - 1] = array[2 * index];
        array[2 * index] = temp;
        bubbledown(2 * index + 1);
    }
}