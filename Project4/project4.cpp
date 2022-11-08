// Project 4
// Fall 2022
// Computing Structures
// Khoi Trinh

#include <iostream>
#include <list>     // stl list library
#include <iterator> // to iterate through the list
using namespace std;
// global variable to keep track of GL height
int heightCount = 1;
// global array of char to for search duplicates
char charlist[20] = { };
// global search index for search duplicates
int search = 0;
// global flag for duplicates
bool duplicates = false;
class GL; // prototype for class GL
// node class to store char and generalized linked list called down
class node
{
protected:
	char* charVariable; // single char variable pointer (not an array)
	GL* down;           // going down to the next level
public:
	node(); // default constructor
	// setters
	void setCharVariable(char var);
	void setDown(GL* d);
	// getters
	char* getChar();
	GL* getDown();
	// display
	void displayChar();
};

// default constructor
node::node() {
	charVariable = NULL;
	down = NULL;
}

// setters
void node::setCharVariable(char var) {
	char* newvar = new char(var);
	charVariable = newvar;
}

void node::setDown(GL* d) {
	down = d;
}

// getters
char* node::getChar() {
	return charVariable;
}

GL* node::getDown() {
	return down;
}

// display
void node::displayChar() {
	cout << *charVariable << " ";
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// class Generalized List
class GL
{
protected:
	list<node> head; // head of the list - each object is of type node class
public:
	GL();                                         // default constructor
	void buildGL(string l);                       // to build the generalized list
	bool findCharInExpression(char findThisChar); // given a char, find it in a given expression
	int LCAdistance(char char1, char char2);      // find the LCA distance of two char in the expression
	int heightOfGL();                             // return the height of the GL using the GL
	void searchDuplicates();                      // print all the duplicates in the GL
	void display();                               // display list
};

// constructor
GL::GL() {
	// List is already initalized so I shouldn't need to 
	// do anything in the default constructor
}

// operators
void GL::buildGL(string l) {
	// starts i at 1 to skip the first (
	// ends at length - 1 to skip the last )
	for (int i = 1; i < l.length() - 1; i++) {
		if (l[i] == '(') {
			// if the character is a (
			// start building the substring from ( to the )
			// then recursively call buildGL on that substring
			node* tempNode = new node();
			GL* tempGL = new GL();
			string subString;
			// keep track of the open (
			// right now, starts at 1
			int count = 1;
			// inner loop starts from the next index of the string
			for (int j = i + 1; j < l.length(); j++) {
				if (l[j] == '(') {
					// if char is (
					// add to substring
					// increase counter by 1
					//cout << "Found (, increasing counter" << endl;
					subString += l[j];
					count++;
				}
				if (l[j] == ')' && count > 0) {
					// if char is ) and count is positive
					// add to substring
					// decrease counter by 1
					//cout << "Found ), decreasing counter" << endl;
					subString += l[j];
					count--;
				}
				if (l[j] == ')' && count == 0) {
					// if char is ) and count is 0
					// this is the last ) of the expression
					// build the substring, j - i is in between the ( and )
					//cout << "Found ), counter is 0" << endl;
					// trying substr instead of the + operation to add multiple characters
					subString = l.substr(i, j - i + 1); // + 1 to add the last ) to complete the pair
					i = j; // set i = j to "catch" i up to j
					break; // substring is done, break the inner for loop to start recursion
				}
			}
			// recursion here
			//cout << "substring is: " << subString << endl;
			tempGL->buildGL(subString);
			//tempNode->setCharVariable(NULL);
			tempNode->setDown(tempGL);
			head.push_back(*tempNode);
		}
		else { // base case for recursion
			//cout << "Base case here" << endl;
			node* tempNode = new node();
			tempNode->setCharVariable(l[i]);
			head.push_back(*tempNode);
		}
	}
}

bool GL::findCharInExpression(char findThisChar) {
	list<node>::iterator iter;
	bool returnThis = false;
	for (iter = head.begin(); iter != head.end(); iter++) {
		if (iter->getDown() != NULL) {
			GL* temp = iter->getDown();
			// update return value
			returnThis = temp->findCharInExpression(findThisChar); // recursion
			// use this to break out of recursion
			// as soon as the char is found
			if (returnThis == true) {
				return returnThis;
			}
		}
		else if (iter->getDown() == NULL) {
			char thisChar = *iter->getChar();
			if (thisChar == findThisChar) {
				returnThis = true;
				break;
			}
		}
	}
	return returnThis;
}

int GL::LCAdistance(char char1, char char2) {
	return 0;
}

int GL::heightOfGL() { // apparently only 4 lines
	list<node>::iterator iter;
	// loop through head, if any down pointer is null, then increase
	// heightCount and recursively call the method again
	for (iter = head.begin(); iter != head.end(); iter++) {
		if (iter->getDown() != NULL) {
			heightCount++;
			// recursion here
			iter->getDown()->heightOfGL();
		}
	}
	return heightCount;
}

void GL::searchDuplicates() {
	// loop through head of the expression
	for (list<node>::iterator iter = head.begin(); iter != head.end(); iter++) {	
		// if any down pointer is not NULL
		// recursion case
		if (iter->getDown() != NULL) {
			iter->getDown()->searchDuplicates();
		}
		// base case
		else {	
			// get the current character and
			// insert it into the global char array
			charlist[search] = *iter->getChar();
			// increment index
			search++;
			// loop through the char array
			for (int i = 0; i < search - 1; i++) {
				// if any pair matches, print it out
				if (charlist[search - 1] == charlist[i]) {
					duplicates = true;
					cout << charlist[i] << " ";
				}
			}
		}
		if (duplicates = false) {
			cout << "None" << endl;
		}
	}
	
}

void GL::display() {
	list<node>::iterator iter;
	for (iter = head.begin(); iter != head.end(); iter++) {
		// don't print )
		// don't need this condition anymore since buildGL
		// skipped the last )
		/*if (iter->getChar() != NULL && *iter->getChar() == ')') {
			continue;
		}*/
		// base case, if there is char
		// print it
		if (iter->getChar() != NULL) {
			iter->displayChar();
		}
		// recursion if char is null
		// use method on down pointer
		if (iter->getChar() == NULL) {
			iter->getDown()->display(); // recursion
		}
	}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{
	int numExpressions; // number of expressions
	cin >> numExpressions;
	cout << "Number of expressions: " << numExpressions << endl;
	GL* expressions = new GL[numExpressions]; // an array of expressions / an array of GL objects
		// read one line/expression at a time and call the buildGL method for each expression[i]
		// read in and process all the options using switch case
	for (int i = 0; i < numExpressions; i++) {
		string expression;
		cin >> expression;
		expressions[i].buildGL(expression);
	}
	char option;        // command from the input file
	// read the number of expressions given
	cin >> option;
	while (!cin.eof()) {
		// switch case to cover all the options
		switch (option) {
			case 'D': { // display the lists
				cout << "Displaying all expressions: " << endl;
				for (int i = 0; i < numExpressions; i++) {
					cout << "Expression " << i << ": ";
					expressions[i].display();
					cout << endl;
				}
				break;
			}
			case 'F': { // find a particular char in a list
				int expressionNo;
				char findThis;
				cin >> expressionNo >> findThis;
				// call the method
				bool exist = expressions[expressionNo].findCharInExpression(findThis);
				if (exist == true) {
					cout << "Find " << findThis << " in " << expressionNo << ": found" << endl;
					break;
				}
				else {
					cout << "Find " << findThis << " in " << expressionNo << ": not found" << endl;
					break;
				}
			}
			case 'H': { // find the height of a list
				int expressionNo;
				cin >> expressionNo;
				// call the method
				int height = expressions[expressionNo].heightOfGL();
				cout << "Height of expression " << expressionNo << ": " << height << endl;
				// reset global heightCount variable back to 1 for the next run
				heightCount = 1;
				break;
			}
			case 'U': { // find duplicates characters in a list
				int expressionNo;
				cin >> expressionNo;
				cout << "Duplicates in " << expressionNo << ": ";
				// call the method
				expressions[expressionNo].searchDuplicates();
				// reset search index and char list for the next run
				search = 0;
				for (int i = 0; i < 20; i++) {
					charlist[i] = '\0';
				}
				// reset global flag for the next run
				duplicates = false;
				cout << endl;
				break;
			}
			default: cout << "It broke :(" << endl;
		}
		cin >> option;
	}
	return 0;
}