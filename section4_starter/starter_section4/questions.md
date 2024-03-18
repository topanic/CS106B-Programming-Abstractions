## 3) Longest Common Subsequence (`lcs.cpp`)
_Topic: Recursive Backtracking_

Write a recursive function named longestCommonSubsequence that returns the longest common subsequence of two strings passed as arguments. Some
example function calls and return values are shown below.

Recall that if a string is a subsequence of another, each of its letters occurs in the longer string in the same order, but not necessarily consecutively.

Hint: In the recursive case, compare the first character of each string. What one recursive call can you make if they are the same? What two recursive calls do you try if they are different?
```c++
longestCommonSubsequence("cs106a", "cs106b") --> "cs106" 
longestCommonSubsequence("nick", "julie") --> "i" 
longestCommonSubsequence("karel", "c++") --> "" 
longestCommonSubsequence("she sells", "seashells") --> "sesells"
```
{% solution %}
```c++
string longestCommonSubsequence(string s1, string s2) {
	if (s1.length() == 0 || s2.length() == 0) {
		return "";
 	} else if (s1[0] == s2[0]) {
 		return s1[0] + longestCommonSubsequence(s1.substr(1), 
 							s2.substr(1));
 	} else {
 		string choice1 = longestCommonSubsequence(s1, s2.substr(1));
		string choice2 = longestCommonSubsequence(s1.substr(1), s2);
		if (choice1.length() >= choice2.length()) {
			return choice1;
		} else {
			return choice2;
		}
	}
}
```
{% endsolution %}

## 4) Cracking Passwords(`crack.cpp`)
_Topic: Recursive Backtracking_

Write a function `crack` that takes in the maximum length a site allows for a user's password and tries to find the password into an account by using recursive backtracking to attempt all possible passwords up to that length (inclusive). Assume you have access to the function `bool login(string password)` that returns true if a password is correct. You can also assume that the passwords are entirely alphabetic and case-sensitive. You should return the correct password you find, or the empty string if you cannot find the password. You should return the empty string if the maximum length passed is 0 and raise an error if the length is negative.

Security note: The ease with which computers can brute-force passwords is the reason why login systems usually permit only a certain number of login attempts at a time before timing out. It’s also why long passwords that contain a variety of different characters are better! Try experimenting with how long it takes to crack longer and more complex passwords. See the comic here for more information: <https://xkcd.com/936/>

{% solution %}
```c++
string crackHelper(string soFar, int maxLength) {
	if (login(soFar)) {
		return soFar;
	}
	if (soFar.size() == maxLength) {
		return "";
	}
	for (char c = 'a'; c <= 'z'; c++) {
		string password = crackHelper (soFar + c, maxLength);
		if (password != "") {
			return password;
		}
 		// Also check uppercase
 		char upperC = toupper(c);
 		password = crackHelper (soFar + upperC, maxLength);
		if (password != "") {
 			return password;
 		}
 	}
	return "";
}

string crack(int maxLength) {
	if (maxLength < 0) {
 		error("max length cannot be negative!);";
	}
 	return crackHelper("", maxLength);
}
```
{% endsolution %}

## 5) The Knapsack Problem (`knapsack.cpp`)

As a challenge problem, we encourage you to explore solving the quintessential optimization challenge of the knapsack problem. As a reminder from lecture, here is the problem setup. 

Imagine yourself in a new lifestyle as a professional wilderness survival expert. You are about to set off on a challenging expedition, and you need to pack your knapsack (or backpack) full of supplies. You have a list full of supplies (each of which has a survival value and a weight associated with it) to choose from. Your backpack is only sturdy enough to hold a certain amount of weight. The question is: How can you maximize the survival value of your backpack?

Assume each item in your backpack is modeled with the following struct:
```
struct BackpackItem {
    int survivalValue;  // You can assume this value will always >= 0
    int weight;         // You can assume this value will always >= 0
};
```

Your goal is to implement the following function:
```
int fillBackpack(Vector<BackpackItem>& items, int targetWeight);
```
which given a list of all possible items that you can take with you and the maximum weight that your backpack can hold, returns the maximum survival value that you can achieve by filling the backpack.

{% solution %}
```
int fillBackpackHelper(Vector<BackpackItem>& items, int capacityRemaining, int curValue, int index) {
    /* Base Case: If there is no more capacity in the backpack to hold things,
     * then we can no longer fit any more value in.
     */
    if (capacityRemaining < 0) {
        return 0;
    }
    /* Base Case: If we have run out of items to consider, then the best value we
     * can get is what we've built up so far.
     */
    else if (index == items.size()) {
        return curValue;
    }else {
        /* Choose: Select an item to decide whether to bring along or not.
         */
        BackpackItem curItem = items[index];

        /* Explore: Try including the item and not including it, and keep track
         * of the best possible value in each case. */
        int bestValueWithout = fillBackpackHelper(items,
                                                  capacityRemaining,
                                                  curValue,
                                                  index + 1);

        int bestValueWith = fillBackpackHelper(items,
                                               capacityRemaining - curItem.weight,
                                               curValue + curItem.survivalValue,
                                               index + 1);

        /* Unchoose: No explicit unchoose necessary since no changes to data
         * structures have been made.
         */

        /* The final value we return is the best of the two options we tried. */
        return max(bestValueWith, bestValueWithout);
    }
}

int fillBackpack(Vector<BackpackItem>& items, int targetWeight) {
    return fillBackpackHelper(items, targetWeight, 0, 0);
}
```
{% endsolution %}
