/*
 * File: Sierpinski.cpp
 * ----------------------
 * Name: MacLane Wilkison
 * Section: SEE
 * This program asks the user for an edge length and a fractal order and draws
 * the resulting Sierpinski Triangle in the center of the graphics window.
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

// Function prototypes
void drawTriangle(GWindow & gw, int length, GPoint p0);
void drawSierpinskiTriangle(GWindow & gw, int length, int order, GPoint p0);

// Main program
int main() {
    GWindow gw;
    int length = getInteger("Edge length: ");
    int order = getInteger("Fractal order: ");
    double cx = (gw.getWidth() - length) / 2;
    double cy = (gw.getHeight() + length) / 2;
    GPoint p0 = GPoint(cx, cy); // starting point
    drawSierpinskiTriangle(gw, length, order, p0);
    cin.get();
    return 0;
}

/*
 * Function: drawSierpinskiTriangle
 * Usage: drawSierpinskiTriangle(gw, length, order);
 * This function recursively draws a Sierpinski Triangle of a specified
 * length and order.
 */
void drawSierpinskiTriangle(GWindow & gw, int length, int order, GPoint p0) {
    drawTriangle(gw, length, p0);
    if (order == 0) return;
    else {
        GPoint p1 = gw.drawPolarLine(p0, length / 2, 60);
        GPoint p2 = gw.drawPolarLine(p0, length / 2, 0);
        gw.drawLine(p1, p2);
        drawSierpinskiTriangle(gw, length / 2, order - 1, p0);
        drawSierpinskiTriangle(gw, length / 2, order - 1, p1);
        drawSierpinskiTriangle(gw, length / 2, order - 1, p2);
    }
    
}

/*
 * Function: drawTriangle
 * Usage: drawTriangle(gw, length, startPoint);
 * This function draws an equilateral triangle in the graphics window.
 */
void drawTriangle(GWindow & gw, int length, GPoint p0) {
    GPoint p1 = gw.drawPolarLine(p0, length, 60);
    GPoint p2 = gw.drawPolarLine(p1, length, -60);
    GPoint p3 = gw.drawPolarLine(p2, length, 180);
}
