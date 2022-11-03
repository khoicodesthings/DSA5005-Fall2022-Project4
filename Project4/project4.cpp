// Project 4
// Fall 2022
// Computing Structures

#include <iostream>
#include <list>     // stl list library
#include <iterator> // to iterate through the list
using namespace std;

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
	charVariable = &var;
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
	cout << charVariable << " ";
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
	int paraCount = 0; // int var to keep track of how many open (
	int stringLength = l.length();
	// i starts at 1 since index 0 is (
	for (int i = 1; i < stringLength; i++) {
		if (l[i] == '(') { // recursion here
			// count is still 0 here
			node* temp = new node();
			//int j = i+1;
			string subString;
			for (int j = i + 1; j < stringLength; j++) {
				if (l[j] != '(' && l[j] != ')') {
					subString = subString + l[j];
				}
				if (l[j] == '(') {
					subString = subString + l[j];
					paraCount++;
				}
				// if paraCount >0 then push ) into subString
				if (l[j] == ')' && paraCount != 0) {
					subString = subString + l[j];
					paraCount--;
				}
				if (l[j] == ')' && paraCount == 0) {
					break;
				}
			}
			cout << "This sub string is: " << subString << endl; // for debugging
			GL* tempGL = new GL();
			tempGL->buildGL(subString); // recursion here, once called, should go to else block
			temp->setDown(tempGL);
			head.push_back(*temp);
		}
		else { // if it's a letter or numeric char, build a node object
			node* temp = new node();
			char* tempChar = new char(l[i]);
			temp->setCharVariable(*tempChar);
			temp->displayChar();
			head.push_back(*temp);	
		}
	}
}

bool GL::findCharInExpression(char findThisChar) {
	for (int i = 0; i < head.size(); i++) {
		list<node>::iterator iter = head.begin();
		advance(iter, i);
		node thisNode = *iter;
		if (thisNode.getChar() == &findThisChar) {
			return true;
		}
	}
	return false;
}

int GL::LCAdistance(char char1, char char2) {
	return 0;
}

int GL::heightOfGL() { // apparently only 4 lines
	list<node>::iterator iter = head.begin();
	return 0;
}

void GL::searchDuplicates() {
	list<node>::iterator iter = head.begin();
}

void GL::display() {
	cout << "Displaying all expressions:" << endl;
	list<node>::iterator iter = head.begin();
	for (int i = 0; i < head.size(); i++) {
		node thisNode = *iter;
		char* tempChar = thisNode.getChar();
		node* display = new node();
		display->setCharVariable(*tempChar);
		display->displayChar();
	}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{
	int numExpressions; // number of expressions
	//char option;        // command from the input file
	// read the number of expressions given
	cin >> numExpressions;
	cout << "Number of expressions: " << numExpressions << endl;
	GL* expressions = new GL[numExpressions]; // an array of expressions / an array of GL objects
		// read one line/expression at a time and call the buildGL method for each expression[i]
		// read in and process all the options using switch case
	string first, second, third;
	cin >> first >> second >> third;
	expressions[0].buildGL(first);

	expressions[0].display();

	//expressions[1].buildGL(second);
	
	//expressions[2].buildGL(third);
	
	return 0;
} // main