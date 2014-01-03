/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "pqueue.h"
#include "random.h"
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start, Loc end, Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
             double heuristic(Loc start, Loc end, Grid<double>& world)) {
    Map<Loc, Node*> visited;
    TrailblazerPQueue<Loc> tpq;
    Node *startNode = new Node;
    startNode->parent = NULL;
    startNode->location = start;
    startNode->distance = 0;
    colorCell(world, start, YELLOW);
    visited.put(start, startNode);
    tpq.enqueue(start, heuristic(start, end, world));
    while (!tpq.isEmpty()) {
        Loc currLoc = tpq.dequeueMin();
        Node *currNode = visited.get(currLoc);
        colorCell(world, currLoc, GREEN);
        
        if (currNode->location == end) {
            Stack<Loc> pathStack;
            Vector<Loc> path;
            Node *step = currNode;
            pathStack.push(currLoc);
            while ((step = step->parent) != NULL) {
                pathStack.push(step->location);
            }
            while (!pathStack.isEmpty()) {
                path.add(pathStack.pop());
            }
            return path;
        }
        
        for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
            for (int colOffset = -1; colOffset <= 1; colOffset++) {
                Loc offset;
                offset.row = currLoc.row + rowOffset;
                offset.col = currLoc.col + colOffset;
                if (world.inBounds(offset.row, offset.col)) {
                    double length = costFn(currLoc, offset, world);
                    double candidateDistance = currNode->distance + length;
                    if (!visited.containsKey(offset)) {
                        colorCell(world, offset, YELLOW);
                        Node *v = new Node;
                        v->location = offset;
                        v->parent = currNode;                       
                        v->distance = candidateDistance;
                        visited.put(offset, v);
                        tpq.enqueue(offset, candidateDistance + heuristic(offset, end, world));
                    } else if (currNode->distance + length < visited.get(offset)->distance) {
                        Node *v = visited.get(offset);
                        v->location = offset;
                        v->parent = currNode;                       
                        v->distance = candidateDistance;
                        visited.put(offset, v);
                        tpq.decreaseKey(offset, candidateDistance + heuristic(offset, end, world));
                    }
                }
            }
        }
    }
}

Set<Edge> createMaze(int numRows, int numCols) {
    Vector<Loc> nodes;
    Grid<bool> world(numRows, numCols);
    PriorityQueue<Edge> pq;
    Set<Edge> edges;
    Map< Loc, Set<Loc> > clusterMap;
    
    /* Create Loc nodes */
    for (int col = 0; col < numCols; col++) {
        for (int row = 0; row < numRows; row++) {
            Loc node = makeLoc(row, col);
            Set<Loc> initSet;
            initSet.add(node);
            nodes.add(node);
            clusterMap.put(node, initSet);
        }
    }
    
    /* Enqueue edges with random priority */
    for (int i = 0; i < nodes.size(); i++) {
        Vector<Loc> neighbors;
        neighbors.add(makeLoc(nodes[i].row, nodes[i].col - 1)); // left offset
        neighbors.add(makeLoc(nodes[i].row, nodes[i].col + 1)); // right offset
        neighbors.add(makeLoc(nodes[i].row - 1, nodes[i].col)); // up offset
        neighbors.add(makeLoc(nodes[i].row + 1, nodes[i].col)); // down offset
        foreach (Loc offset in neighbors) {
            if (world.inBounds(offset.row, offset.col)) {
                Edge e = makeEdge(nodes[i], offset);
                pq.enqueue(e, randomReal(0, 1));
            }
        }
    }
    
    /* Create clusters */
    while (!pq.isEmpty()) {        
        Edge path = pq.dequeue();
        if (clusterMap[path.start] != clusterMap[path.end]) {
            clusterMap[path.start] += clusterMap[path.end];
            clusterMap[path.end] += clusterMap[path.start];
            foreach (Loc node in clusterMap[path.start]) {
                clusterMap[node] += clusterMap[path.end];
            }
            edges.add(path);
        }
    }
    return edges;    
}
