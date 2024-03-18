/*
 * CS106B Section Handout Test Harness: Section 3
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Chase Davis for CS106B
 * Fall 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "SimpleTest.h"
#include "vector.h"
using namespace std;

/*
 * Win some, lose sum (Code Writing)
 * --------------------------------------------------------
 * Write a recursive function named canMakeSum that takes a
 * reference to a Vector<int> and an int target value and
 * returns true if it is possible to have some selection of
 * values from the Vector that sum to the target value.
 */

bool canMakeSumHelper(Vector<int>& v, int target, int sumSoFar) {
    if (v.isEmpty()) {
        return sumSoFar == target;
    }
    int choice = v[v.size() - 1];
    v.remove(v.size() - 1);
    bool with = canMakeSumHelper(v, target, sumSoFar + choice);
    bool without = canMakeSumHelper(v, target, sumSoFar);
    v.add(choice);
    return with || without;
}

bool canMakeSum(Vector<int>& values, int target) {
    // TODO: Your code here
    return canMakeSumHelper(values, target, 0);
}



/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Positive example from handout.") {
    Vector<int> nums = {1,1,2,3,5};
    EXPECT(canMakeSum(nums, 9));
}

PROVIDED_TEST("Provided Test: Negative example from handout") {
    Vector<int> nums = {1,4,5,6};
    EXPECT(!canMakeSum(nums, 8));
}
