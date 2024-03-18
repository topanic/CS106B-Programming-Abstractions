/*
 * CS106B Section Handout Test Harness: Section 2
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include "SimpleTest.h"
#include "grid.h"
#include "gridlocation.h"

using namespace std;

/*
 * Max row (Code Write)
 * ----------------------------------
 * Write a function named maxRow that takes in a grid and an in 
 * bounds gridLocation and returns a the maximum value in that 
 * row of the grid.
 */

int maxRow(Grid<int>& grid, GridLocation loc) {
    int max = -1;
    for (int col = 0; col < grid.numCols(); col ++) {
        if (grid[loc.row][col] > max) {
            max = grid[loc.row][col];
        }
    }
    return max;
}

/*
 * Avg neighborhood (Code Write)
 * ----------------------------------
 * Write a function named avgNeighborhood that takes in a grid and an in 
 * bounds gridLocation and returns the average value in the neighborhood
 * of the gridLocation. A neighborhood is defined as the in bounds 
 * locations in North, South, East and West of loc.
 */
int avgNeighborhood(Grid<int>& grid, GridLocation loc) {
    Vector<GridLocation> possibleLocations = {
        {loc.row - 1, loc.col}, // north
        {loc.row + 1, loc.col}, // south
        {loc.row, loc.col + 1}, // east
        {loc.row, loc.col - 1}  // west
    };

    int sum = 0;
    int numValidLocations = 0;
    for (GridLocation dir : possibleLocations) {
        if (grid.inBounds(dir)) {
            sum += grid[dir];
            numValidLocations += 1;
        }
    }
    return sum / numValidLocations;
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Test max row") {
    Grid<int> grid = {{0, 9, 1}, {1, 3, 0}, {2, 3, 1}};
    EXPECT_EQUAL(maxRow(grid, {2, 1}), 3);
    EXPECT_EQUAL(maxRow(grid, {0, 1}), 9);
}

PROVIDED_TEST("Test average neighborhood") {
    Grid<int> grid = {{0, 9, 1}, {1, 3, 0}, {2, 3, 1}};
    EXPECT_EQUAL(avgNeighborhood(grid, {0,0}), 5);
    // average is 3.33*, but we truncate to 3
    EXPECT_EQUAL(avgNeighborhood(grid, {1,1}), 3); 
}
