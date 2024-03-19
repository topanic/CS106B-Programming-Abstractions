/*
 * CS106B Section Handout Test Harness: Section 8
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "SimpleTest.h"
#include "utility.h"
#include "error.h"
#include "stack.h"
using namespace std;

/*
 * Decode Sequence (Code Writing)
 * --------------------------------------------------------
 * Write a function that accepts a ternary tree and string representing
 * a sequence of directions and returns the decoded string.
 */

string decodeSequence(TernaryTreeNode* tree, string sequence) {
    string message;
    for (char direction: sequence) {
        if (direction == 'L') {
            tree = tree->left;
        } else if (direction == 'M') {
            tree = tree->middle;
        } else {
            tree = tree->right;
        }

        if (!tree) {
            break;
        }
        message += tree->ch;
    }
    return message;
}


/*
 * Print All Paths (Code Writing)
 * --------------------------------------------------------
 * Write a function that accepts a ternary tree prints all the valid
 * paths that lead to a leaf in the ternary tree.
 */
void printAllPaths(TernaryTreeNode* tree) {
    if (!tree) {
        return ;
    }

}




PROVIDED_TEST("Simple set of test cases for decodeSequence") {
    TernaryTreeNode* node1L = new TernaryTreeNode('D');
    TernaryTreeNode* node1M = new TernaryTreeNode('E');
    TernaryTreeNode* node1R = new TernaryTreeNode('F');

    TernaryTreeNode* node2L = new TernaryTreeNode('G');
    TernaryTreeNode* node2M = new TernaryTreeNode('H');
    TernaryTreeNode* node2R = new TernaryTreeNode('I');

    TernaryTreeNode* node1 = new TernaryTreeNode('A', node1L, node1M, node1R);
    TernaryTreeNode* node2 = new TernaryTreeNode('B', node2L, node2M, node2R);
    TernaryTreeNode* node3 = new TernaryTreeNode('C');

    node3->middle = new TernaryTreeNode('J');

    TernaryTreeNode* root = new TernaryTreeNode('-', node1, node2, node3);

    EXPECT_EQUAL(decodeSequence(root, "LR"), "AF");
    EXPECT_EQUAL(decodeSequence(root, "RMR"), "CJ");
}
