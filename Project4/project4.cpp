// Project 4
// Fall 2022
// Computing Structures
#include <iostream>
#include <list>     // stl list library
#include <iterator> // to iterate through the list
using namespace std;
int heightCount = 1;
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
	for (int i = 0; i < l.length(); i++) {
		// start building substring
		string substr;
		if (l[i] == '(') {
			node* tempNode = new node();
			GL* temp = new GL();
			// if first char is (, count begins at 0
			int count = 0;
			tempNode->setCharVariable(NULL);
			for (int j = i + 1; j < l.length(); j++) {
				if (l[j] == '(') {
					// for every subsequent (
					// add to substring, and increase count
					substr += l[j];
					count++;
				}
				if (l[j] == ')' && count > 0) {
					// if there is ), and count is positive
					// add to substring, decrease count
					substr += l[j];
					count--;
				}
				if (l[j] == ')' && count == 0) {
					// should be the last ) of the epxpression
					// break the loop
					break;
				}
			}
			head.push_back(*tempNode);
			// recursion here
			temp->buildGL(substr);
			tempNode->setDown(temp);
		}
		else if (l[i] == ')') {
			// add the last ) into substring
			substr += l[i];
		}
		else { // base case for recursion
			node* tempNode = new node();
			tempNode->setCharVariable(l[i]);
			head.push_back(*tempNode);
			tempNode->setDown(NULL);
		}
	}
	
}

bool GL::findCharInExpression(char findThisChar) {
	list<node>::iterator iter;
	for (iter = head.begin(); iter != head.end(); iter++) {
		if (iter->getChar() != NULL) {
			if (iter->getChar() == &findThisChar) {
				return true;
			}
			else {
				return false;
			}
		}
		if (iter->getDown() != NULL) {
			iter->getDown()->findCharInExpression(findThisChar); // recursion
		}
	}
}

int GL::LCAdistance(char char1, char char2) {
	return 0;
}

int GL::heightOfGL() { // apparently only 4 lines
	list<node>::iterator iter;
	for (iter = head.begin(); iter != head.end(); iter++) {
		//if (iter->getDown() == NULL) {
			//heightOfGL();
		//}
		if (iter->getDown() != NULL) {
			heightCount++;
			//heightCount++;
			heightCount = heightOfGL();
		}
	}
	int height = heightCount;
	return height;
}

void GL::searchDuplicates() {
	list<node>::iterator iter = head.begin();
}

void GL::display() {
	list<node>::iterator iter;
	for (iter = head.begin(); iter != head.end(); iter++) {
		if (iter->getChar() != NULL) {
			iter->displayChar();
		}
		/*if (iter->getChar() != NULL && *iter->getChar() == ')') {
			continue;
		}*/
		if (iter->getChar() == NULL) {
			iter->getDown()->display(); // recursion
		}
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
	for (int i = 0; i < numExpressions; i++) {
		string expression;
		cin >> expression;
		expressions[i].buildGL(expression);
	}
	cout << "Displaying all expressions: " << endl;
	for (int i = 0; i < numExpressions; i++) {
		cout << "Expression " << i << ": ";
		expressions[i].display();
		cout << endl;
	}

	/*bool find = expressions[0].findCharInExpression('b');
	if (find == true) {
		cout << "Find b in 0: " << "found" << endl;
	}
	else {
		cout << "Find b in 0: " << "not found" << endl;
	}*/

	int height = expressions[2].heightOfGL();
	cout << "Height of expression 2: " << height << endl;
	return 0;
} // main