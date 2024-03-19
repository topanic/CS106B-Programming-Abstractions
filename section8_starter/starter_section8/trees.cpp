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
 * Pruning Tree Leaves (Code Writing)
 * --------------------------------------------------------
 * Write a function that accepts a reference to a pointer
 * to a TreeNode and removes the leaf nodes from a tree. A
 * leaf is a node that has empty left and right subtrees.
 * If your function is called on an empty tree, it does not
 * change the tree because there are no nodes of any kind
 * (leaf or not). You must free the memory for any removed
 * nodes.
 */

bool isPalindromicTree(TreeNode* root) {
    /* TODO: Your code goes here! */
    (void) root;
    return false;
}



PROVIDED_TEST("Simple set of test cases for isPalindromicTree function") {
    TreeNode *tree = nullptr;
    EXPECT(isPalindromicTree(tree));

    tree = createTreeFromVector({1});
    EXPECT(isPalindromicTree(tree));
    freeTree(tree);

    tree = createTreeFromVector({/* Level 1 */3, /* Level 2*/ 2, 2, /* Level 3 */ 5, 4, 4, 5, /* Level 4 */ EMPTY, EMPTY, 1, 2, 2, 1, EMPTY, EMPTY});
    EXPECT(isPalindromicTree(tree));
    freeTree(tree);

    tree = createTreeFromVector({/* Level 1 */3, /* Level 2*/ 1, 1, /* Level 3 */ 1, 2, 1, 2});
    EXPECT(!isPalindromicTree(tree));
    freeTree(tree);
}
