/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <cctype>
#include <fstream>
#include <string>
#include <algorithm>
#include "console.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include "vector.h"
#include "SimpleTest.h"
#include "soundex.h"
using namespace std;

/* This function is intended to return a string which
 * includes only the letter characters from the original
 * (all non-letter characters are excluded)
 *
 * WARNING: The provided code is buggy!
 *
 * Add student test cases to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string lettersOnly(string s) {
    string result = "";
    // string result = charToString(s[0]);
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

string encode(char code) {
    code = toupper(code);
    if (code == 'A' || code == 'E' || code == 'I' || code == 'O' || code == 'U' || code == 'H' || code == 'W' || code == 'Y') {
        return "0";
    } else if (code == 'B' || code == 'F' || code == 'P' || code == 'V') {
        return "1";
    } else if (code == 'C' || code == 'G' || code == 'J' || code == 'K' || code == 'Q' || code == 'X' || code == 'S' || code == 'Z') {
        return "2";
    } else if (code == 'D' || code == 'T') {
        return "3";
    } else if (code == 'L') {
        return "4";
    } else if (code == 'M' || code == 'N') {
        return "5";
    } else if (code == 'R') {
        return "6";
    } else {
        return "";
    }
}



/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string soundex(string s) {
    /* TODO: Fill in this function. */

    // 1. Extract only the letters from the surname, discarding all non-letters (no dashes, spaces, apostrophes, …).
    s = lettersOnly(s);
    // 2. Encode each letter as a digit using the table below.
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        result += encode(s[i]);
    }
    // 3. Coalesce adjacent duplicate digits from the code (e.g. 222025 becomes 2025).
    result.erase(unique(result.begin(), result.end()), result.end());

    // 4. Replace the first digit of the code with the first letter of the original name, converting to uppercase.
    char firstName = s[0];
    firstName = toupper(firstName);
    result[0] = firstName;

    // 5. Discard any zeros from the code.
    result.erase(remove(result.begin(), result.end(), '0'), result.end());

    // 6. Make the code exactly length 4 by padding with zeros or truncating the excess.
    result.resize(4, '0');

    return result;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // This provided code opens the specified file
    // and reads the lines into a vector of strings
    ifstream in;
    Vector<string> allNames;

    if (openFile(in, filepath)) {
        allNames = readLines(in);
    }
    cout << "Read file " << filepath << ", "
         << allNames.size() << " names found." << endl;

    // The names read from file are now stored in Vector allNames

    /* TODO: Fill in the remainder of this function. */
}


/* * * * * * Test Cases * * * * * */

// TODO: add your STUDENT_TEST test cases here!
STUDENT_TEST("lettersOnly function") {
    string s = "O'Hara";
    string result = lettersOnly(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "tldr");
    s = "'hello";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "hello");
}


/* Please not add/modify/remove the PROVIDED_TEST entries below.
 * Place your student tests cases above the provided tests.
 */

PROVIDED_TEST("Test exclude of punctuation, digits, and spaces") {
    string s = "O'Hara";
    string result = lettersOnly(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "tldr");
}

PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}
