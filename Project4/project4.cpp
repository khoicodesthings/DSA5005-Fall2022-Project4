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
	cout << charVariable << endl;
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
	// recursively build the generalized list
	// Take in the string char by char
	// Build the list, if run into any '(' char
	// after the first '(' char then 
	// Build another list using recursion
	int stringLength = l.length();
	for (int i = 0; i < stringLength; i++) {
		if (l[i] == '(') { // recursion here
			// call buildGL(subString)
			node* temp = new node();
			int j = i+1;
			string subString;
			while (l[j] != ')') {
				// need to figure out how to generate this substring
				subString = subString + l[j];
				j++;
			}
			cout << subString;
			GL* tempGL = new GL();
			tempGL->buildGL(subString); // recursion here
			temp->setDown(tempGL);
			head.push_back(*temp);
		}
		else if (l[i] == ')') {
			break; 
		}
		else { // if it's a letter or numeric char, build a node object
			node* temp = new node();
			temp->setCharVariable(l[i]);
			head.push_back(*temp);
			temp->displayChar();
		}
	}
}

bool GL::findCharInExpression(char findThisChar) {
	return false;
}

int GL::LCAdistance(char char1, char char2) {
	return 0;
}

int GL::heightOfGL() {
	return 0;
}

void GL::searchDuplicates() {

}

void GL::display() {

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
	cout << endl;
	expressions[0].buildGL(second);
	cout << endl;
	expressions[0].buildGL(third);
	cout << endl;
	return 0;
} // main