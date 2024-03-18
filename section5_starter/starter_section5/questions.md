## 4) Cleaning Up Your Messes

_Topics: Dynamic allocation and freeing_

Whenever you allocate an array with `new[]`, you need to deallocate it using `delete[]`. It's important when you do so that you only deallocate the array exactly once – deallocating an array zero times causes a memory leak, and deallocating an array multiple times usually causes the program to crash. (Fun fact – deallocating memory twice is called a double free and can lead to security vulnerabilities in your code! Take CS155 for details.)

Below are three code snippets. Trace through each snippet and determine whether all memory allocated with `new[]` is correctly deallocated exactly once. If there are any other errors in the program, make sure to report them as well.

Snippet 1
```c++
int main() {
	int* arya = new int[3];
	int* jon = new int[5];

	arya = jon;
	jon = arya;

	delete[] arya;
	delete[] jon;
	
	return 0;
} 
```
Snippet 2
```c++
int main() {
	int* stark = new int[6];
	int* lannister = new int[3];
	
	delete[] stark;
	stark = lannister;
	
	delete[] stark;
	return 0;
} 
```
Snippet 3
```c++
int main() {
	int* tyrell = new int[137];
	int* arryn = tyrell;
	
	delete[] tyrell;
	delete[] arryn;
	
	return 0;
}
```

{% solution %}
The first piece of code has two errors in it. First, the line

`arya = jon`;

causes a memory leak, because there is no longer a way to deallocate the array of three elements allocated in the first line. Second, since both arya and jon point to the same array, the last two lines will cause an error.

The second piece of code is perfectly fine. Even though we execute

`delete[] stark`;

twice, the array referred to each time is different. Remember that you delete arrays, not pointers.

Finally, the last piece of code has a double-delete in it, because the pointers referred to in the last two lines point to the same array.
{% endsolution %}

## 5) Creative Destruction

_Topics: Constructors and Destructors_

Constructors and destructors are unusual functions in that they're called automatically in many contexts and usually aren't written explicitly. To help build an intuition for when constructors and destructors are called, trace through the execution of this program and list all times when a constructor or destructor is called.
```c++
/* Prints the elements of a stack from the bottom of the stack up to the top
 * of the stack. To do this, we transfer the elements from the stack to a
 * second stack (reversing the order of the elements), then print out the
 * contents of that stack.
*/
void printStack(Stack<int> toPrint) {
	Stack<int> temp;
	while (!toPrint.isEmpty()) {
		temp.push(toPrint.pop());
	}

	while (!temp.isEmpty()) {
		cout << temp.pop() << endl;
	}
}

int main() {
	Stack<int> elems;
	for (int i = 0; i < 10; i++) {
		elems.push(i);
	}
 
	printStack(elems);
	return 0;
}
```
{% solution %}
The ordering is as follows:

* A constructor is called when elem is declared in main.
* A constructor is then called to set `toPrint` equal to a copy of `elem`.
* A constructor is then called to initialize the `temp` variable in `printStack`.
* When `printStack` exits, a destructor is called to clean up the `temp` variable.
* Also when `printStack` exits, a destructor is called to clean up the `toPrint` variable.
* When `main` exits, a destructor is called to clean up the `elem` variable.
{% endsolution %}

___Content for the following two questions is covered in the lecture on Friday, October 29th___

## 6) Min Heap
_Topics: Heaps_

We have implemented the Priority Queue ADT using a binary min-heap. Draw a diagram of the heap’s tree structure that results from inserting the following priority values in the order given: `25, 37, 28, 12, 30, 3`

<div align="center" markdown="1">
![This image contains a table with 2 rows and three columns, for a total of 6 entries. These entries read as follows (left to right, top to bottm): 1) Diagram after inserting 25 2) Diagram after inserting 37 3) Diagram after inserting 28 4) Diagram after inserting 12 5) Diagram after inserting 30 6) Diagram after inserting 3](img/minheaptable.png){: width="100%"}
</div>

{% solution %}
<div align="center" markdown="1">
![This image has six parts that diagram insertion of ints into a min heap. The parts show insertion of the following elements in order: 25, 37, 28, 12, 30, and 3. 25 is inserted first, and is the only node in the heap, with no children. 37 is inserted next, and is inserted at the ‘end’ of the heap, as the left-most empty spot as the left child of 25. Becuase its parent, 25, is less than 37, no movement is necessary. 28 is inserted next, and is inserted at the ‘end’ of the heap, as the right child of 25. Because it’s parent, 25, is less than 28, no movement is necessary. 12 is inserted next, and is inserted at the ‘end’ of the heap, as the left child of 37. Because its parent, 37, is greater than 12, the 12 ‘bubbles up’ by swapping with 37 so that is new parent is 25. Because 25 is greater than 12, the 12 bubbles up again by swapping with the 25. At this point, the heap has 12 as the root with left child 25 and right child 28. The 25 has a left child, 37. The ‘end’ of the heap is now the right-child of 25. 30 is inserted at the ‘end’ of the heap as the right child of 25. Because 25 is less than 30, no movement is necessary. The ‘end’ of the heap is now the left-child of 28. Finally, 3 is inserted into the heap at the ‘end’, as the left child of 28. Because 28 is greater than 3, the 3 swaps position with the 28 to bubble up to become the right child of 12. Because 12 is greater than 3, the 3 swaps with 12 to bubble up to become the root of the heap. The final position of all the elements is 3 at the root, with left child 25 and right child 12. The 25 has a left child of 37 and a right child of 30. The 12 has a left child of 28.](img/minheap.png){: width="80%"}
</div>

{% endsolution %}

## 7) Max Heap
_Topics: Heaps_

You have a PriorityQueue class which treats higher (larger integer value) priority elements as frontmost. The internal implementation of the class is a binary max-heap stored in an unfilled array. The initial allocation of the array is for capacity 5 and the array capacity is doubled when asked to enqueue to a queue which is full. You are going to trace the operation of enqueuing and dequeuing elements from the priority queue. You can sketch as a tree if you prefer when working it out, but your final answer should be based on a representation of the underlying array that supports the heap.

__(a)__ Show the contents of the internal array after these elements are enqueued to an empty priority queue in this order. Each element has a string value and a priority in parenthesis.

`Red(8), Blue(33), Green(29), Purple(42), Orange(20), Yellow(22), Indigo(10), Teal(21)`

__(b)__ Dequeue is called twice on the priority queue. Which two values are
removed?

__(c)__ Show the contents of the internal array after the above two elements
have been dequeued

{% solution %}
<style>
.array {
    font-size: 100%;
}
.array td {
    border-style: solid;
    text-align: center;
    padding: 8px;
}
tr.noborder td {
    border: 0;
    font-size:80%;
}
tr.indexes td {
    font-size:80%;
}

td.noborder {
    border: 0;
    font-size:80%;
}
td.arrow {
    font-size:300%;
    vertical-align:top;
}

</style>
(a) Color names are abbreviated
<pre>
<table class="array" style="width: 70%">
    <tr>
        <td class="noborder">elements:</td>
        <td>P(42)</td>
        <td>B(33)</td>
        <td>G(29)</td>
        <td>T(21)</td>
        <td>O(20)</td>
        <td>Y(22)</td>
        <td>I(10)</td>
        <td>R(8)</td>
        <td>?</td>
        <td>?</td>
    </tr>
    <tr class="indexes">
        <td class="noborder">index:</td>
        <td>&nbsp;0&nbsp;</td>
        <td>&nbsp;1&nbsp;</td>
        <td>&nbsp;2&nbsp;</td>
        <td>&nbsp;3&nbsp;</td>
        <td>&nbsp;4&nbsp;</td>
        <td>&nbsp;5&nbsp;</td>
        <td>&nbsp;6&nbsp;</td>
        <td>&nbsp;7&nbsp;</td>
        <td>&nbsp;8&nbsp;</td>
        <td>&nbsp;9&nbsp;</td>
    </tr>
</table></pre>
(b) Purple(42) and Blue(33)

(c) 
<pre>
<table class="array" style="width: 70%">
    <tr>
        <td class="noborder">elements:</td>
        <td>G(29)</td>
        <td>T(21)</td>
        <td>Y(22)</td>
        <td>R(8)</td>
        <td>O(20)</td>
        <td>I(10)</td>
        <td>?</td>
        <td>?</td>
        <td>?</td>
        <td>?</td>
    </tr>
    <tr class="indexes">
        <td class="noborder">index:</td>
        <td>&nbsp;0&nbsp;</td>
        <td>&nbsp;1&nbsp;</td>
        <td>&nbsp;2&nbsp;</td>
        <td>&nbsp;3&nbsp;</td>
        <td>&nbsp;4&nbsp;</td>
        <td>&nbsp;5&nbsp;</td>
        <td>&nbsp;6&nbsp;</td>
        <td>&nbsp;7&nbsp;</td>
        <td>&nbsp;8&nbsp;</td>
        <td>&nbsp;9&nbsp;</td>
    </tr>
</table></pre>
{% endsolution %}

## 2) Reciprocate and Divide (`Fraction.h/.cpp`)

_Topic: Classes_

Consider the following partially-implemented `Fraction` class which can be used to model rational numbers in C++, functionality that is not built-in to the language. If you're interested in the actual source code of the public and private helper methods, feel free to refer to the section starter code.
```c++
class Fraction {
public:
	Fraction();
	Fraction(int num, int denom);
	void add(Fraction f);
	void multiply(Fraction f);
	double decimal();
	int getNumer();
	int getDenom();
	friend ostream& operator<<(ostream &out, Fraction &frac);
private:
	int numer; // stores the numerator of the fraction
	int denom; // stores the denominator of the fraction
	void reduce(); // simplifies fraction to reduced form 
	int gcd(int u, int v); // calculates and returns Greatest Common Divisor (GCD) of the two inputs
}
```

We're going to expand the interface with two additional methods.

Add a public method named `reciprocal` to the `Fraction` class which converts the fraction to its reciprocal (note that by definition the reciprocal of a number `x` is a number `y` such that `xy == 1` holds). You can assume the numerator and denominator will always be non-zero.

Add a public method named `divide` to the `Fraction` class that takes in a `Fraction f` and divides the original `Fraction` by `f`. You can assume the numerator and denominator will always be non-zero.

{% solution %}
```c++
void Fraction::reciprocal() {
	int tempDenom = denom;
	denom = numer;
	numer = tempDenom;
}

void Fraction::divide(Fraction other) {
	multiply(Fraction(other.getDenom(), other.getNumer()));
}
```
{% endsolution %}