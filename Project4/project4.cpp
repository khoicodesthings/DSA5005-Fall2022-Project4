// Project 4
// Fall 2022
// Computing Structures
// Khoi Trinh

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
	for (int i = 1; i < l.length() - 1; i++) {
		if (l[i] == '(') {
			// if the character is a (
			// start building the substring from ( to the )
			// then recursively call buildGL on that substring
			node* tempNode = new node();
			GL* tempGL = new GL();
			string subString;
			// keep track of the open (
			int paraCounter = 1;

			for (int j = i + 1; j < l.length(); j++) {
				// if char is (, increase counter by 1
				if (l[j] == '(') {
					subString += l[j];
					paraCounter++;
				}
				// if char is ), decrease counter by 1
				else if (l[j] == ')') {
					subString += l[j];
					paraCounter--;
				}
				// if paraCounter is 0
				// that means all the parentheses
				// have been accounted for
				if (paraCounter == 0) {
					// build the substring, j - i is in between
					// the ( and ); add 1 for the last )
					// due to the outter for loop condition
					
					// visual studio suggested this casting operation
					// to prevent overflow
					subString = l.substr(i, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(j) - i + 1);
					//subString += l[j];
					// recursion here
					tempGL->buildGL(subString);
					tempNode->setDown(tempGL);
					head.push_back(*tempNode);
					i = j; // set i = j to skip parenthesis
					break;
				}
			}
		}
		else { // base case for recursion
			node* tempNode = new node();
			tempNode->setCharVariable(l[i]);
			head.push_back(*tempNode);
		}
	}
}

bool GL::findCharInExpression(char findThisChar) {
	list<node>::iterator iter;
	for (iter = head.begin(); iter != head.end(); iter++) {
		if (iter->getDown() != NULL) {
			//return true;
			iter->getDown()->findCharInExpression(findThisChar); // recursion
		}
		else if (*iter->getChar() == findThisChar) {
			return true;
		}
		//else if (iter->getDown() != NULL) {
			//iter->getDown()->findCharInExpression(findThisChar); // recursion
		//}
		else {
			continue;
		}
	}
	return false;
}

int GL::LCAdistance(char char1, char char2) {
	return 0;
}

int GL::heightOfGL() { // apparently only 4 lines
	list<node>::iterator iter;
	for (iter = head.begin(); iter != head.end(); iter++) {
		if (iter->getDown() != NULL) {
			heightCount++;
			iter->getDown()->heightOfGL();
		}
	}
	return heightCount;
}

void GL::searchDuplicates() {
	list<node>::iterator iter;
	//int dupesCount = 0;
	for (iter = head.begin(); iter != head.end(); iter++) {
		char thisChar = *iter->getChar();
		bool findThis = findCharInExpression(thisChar);
		if (findThis = true) {
			cout << thisChar << endl;
			break;
		}
		else {
			searchDuplicates();
		}

	}
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
		switch (option) {
			case 'D': {
				cout << "Displaying all expressions: " << endl;
				for (int i = 0; i < numExpressions; i++) {
					cout << "Expression " << i << ": ";
					expressions[i].display();
					cout << endl;
				}
				break;
			}
			case 'F': {
				int expressionNo;
				char findThis;
				cin >> expressionNo >> findThis;
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
			case 'H': {
				int expressionNo;
				cin >> expressionNo;
				int height = expressions[expressionNo].heightOfGL();
				cout << "Height of expression " << expressionNo << ": " << height << endl;
				break;
			}
			case 'U': {
				int expressionNo;
				cin >> expressionNo;
				cout << "Duplicates in " << expressionNo << ": ";
				expressions[expressionNo].searchDuplicates();
				break;
			}
			default: cout << "It broke" << endl;
		}
		cin >> option;
	}
	return 0;
}