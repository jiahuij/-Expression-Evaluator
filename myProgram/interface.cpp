
#include <iostream>     //including I/O support
#include <fstream>      //including file I/O support
#include <map>
#include <vector>		//including support of vector container
#include <string>		//including the new C++ string class support
#include <cstring>		//including old C character array support
#include <conio.h>		//including support to use _getch()
#include "lexScanner.h"	
#include "interface.h"	
#include "expEvaluator.h"
using namespace std;

// 1. Read in a program (lines of statements) from a file
void Interface::loadProgramFromFile()
{
	char fileName[MaxLengthFileName];	
	// this char array stores the name of the file the program reads from.

	cout<<"Name of file to upload program from (ex. file.txt): ";
	cin >> fileName;
	while( strlen(fileName) == 0 )
	{
		cin >> fileName;
	}

	ifstream inFile;
	inFile.open( fileName );
	if ( inFile.fail() )
	{ cout << endl << "Cannot open this file!" << endl;
	return;
	}

	lines.clear();  //Delete all the lines of statements
	string inputBuffer;
	while( !inFile.eof() )
	{
		getline(inFile, inputBuffer);
		while( !inFile.eof() && inputBuffer.size() == 0 )
		{
			getline(inFile, inputBuffer);
		}

		if (!inFile.eof())
		{
  			cout<< "Line["
				<< lines.size()
				<< "] read:"
				<< inputBuffer << endl;
			lines.push_back(inputBuffer);
		}

	}

	inFile.close();
}



// 2. Display the lines of statements
void Interface::displayProgram()
{
	int count = 0;//use to count the line number

	// use vector iterator to display all elements in the lines vector
	for (vector<string>::iterator it = lines.begin(); it != lines.end(); it++,count++){
		cout<< "Line[" << count<<"]  read: " <<*it << endl;
	}
}



// 3. Enter new lines of code to the end of the program
void Interface::appendLines()
{
	string newLine;// to store user inputs
	bool flag = true;

	cout << "Enter . to end" << endl;

	while (flag){
		
		cout << "Enter your new line: ";
		getline(cin,newLine);// to get lines from user input ans save it into newLine
		

		while (newLine.empty()) //Check and skip empty line.
		{
			getline(cin, newLine);
		}

		// check if the user input is . or not. If the user input is == . end the loop, otherwise add newLine to the end of vector
		newLine == "." ? flag = false : lines.push_back(newLine);
	}
}


// 4. Insert new lines before an existing line
void Interface::insertLines()
{	
	string newLine;// to store user inputs for new line
	int index;// to store user inputs for the  index of the vector
	bool flag = true;

	
	cout << "Enter . to end." << endl;
	cout << "Enter the line number after your new line: ";
		cin >> index;


	while (flag){

		cout << "Enter your new line: ";
		getline(cin, newLine);// to get lines from user input ans save it into newLine

		

		if (newLine == ".")
			flag = false;

		else{

			while (newLine.empty()) //Check and skip empty line.
			{
				getline(cin, newLine); // if the user input is empty, ask user to enter new line
			}

			// call insert funtion to insert newLine to the line number of index.Add one to the iterator after every line is entered
			// so the lines entered will follow next to each other
			lines.insert(lines.begin() + index++, newLine );
		}
	}

}


// 5. Delete a range of existing line
void Interface::deleteLines()
{
	int deleteLineBegin;// to store the beginning line number to be deleted
	int deletLineEnd;// to store the last line number to be deleted 

	cout << "Line number to be deleted: from ";
	cin >> deleteLineBegin;
	cout << " to ";
		cin >> deletLineEnd;

		//call erase funtion to delete the lines from deleteLineBegin to deletLineEnd +1
		lines.erase(lines.begin() + deleteLineBegin, lines.begin() + deletLineEnd+1);
}


// 6. Replace the contents of an existing line
void Interface::replaceOneLine()
{
	int index; // to store user inputs for vector index
	string newLine;// to store user inputs for new line

	cout << "Enter the line number to be replaced: ";
	cin >> index;
	cout << "Line" << index << ": ";
		getline(cin, newLine);// to get line from user input and store into newLine

		while (newLine.empty()) //Check and skip empty line.
		{
			getline(cin, newLine);// if the user input is empty, ask user to enter new line
		}

	lines.erase(lines.begin() + index);// call erase function to erase line number index
	lines.insert(lines.begin() + index, newLine);// call insert function to insert newLine to line number index
}


// 7. Save program to a file
void Interface::saveProgramIntoFile()
{
	char fileName[MaxLengthFileName];//to store the name of file  and set the max length of the file name  to MaxLengthFileName
	

	cout << "Name of file to save the program (ex. file.txt): ";
	cin >> fileName;


	while (strlen(fileName) == 0)// if user input is empty, ask user to input new file name
	{
		cout << "ERROR: Empty line entered. Please enter new file name:  ";
		cin >> fileName;
	}

	ofstream inFile;
	inFile.open(fileName);// open the file

	if (inFile.fail())// if the file fail to open, display error message and return.
	{
		cout << endl << "Cannot open this file!" << endl;
		return;
	}
    

	//user vector iterator to access all elements in the lines vector and save them into the file
	for (vector<string>::iterator it = lines.begin(); it != lines.end(); it++){
		inFile << *it << endl;
	}

	inFile.close();// close the file.
	
}

// 8. Lexical analysis of the program line by line.
void Interface::lexialAnalysis(){

	
	vectOfTokenVects vectorOfTokenVectors;// a vector that stores  vectors of tokens from every line in the program
	vectOfCategoryVects vectorOfCategoryVectors;// a vector that stores  vectors of vecotor categorys  from every line in the program

	cout << endl << "" << endl;

	// display all the lines of the program with line numbers beside
	for (size_t i = 0; i< lines.size(); i++)
		cout << "Line["
		<< i
		<< "].\t"
		<< lines[i]
		<< endl;

	cout << endl << "Lexical analysis of the program line by line." << endl << endl;


	//Get the lexical information 
	LexicalScanner::getLexicalInfo(
		lines,
		vectorOfTokenVectors,
		vectorOfCategoryVectors);

	//Display the lexical information 
	LexicalScanner::displayLexicalInfo(
		vectorOfTokenVectors,
		vectorOfCategoryVectors);

	// release all memories of vectorOfTokenVectors and vectorOfCategoryVectors to prepare for next call
	vectorOfTokenVectors.clear();
	vectorOfCategoryVectors.clear();
}


void Interface::calculator() {

	perLineTokenVector infixExp, postfixExp;// two vector of string to store tokens
	map <string, float> table;// useless, declared because the function postfixEvaluator need a table to be passed in as an argument.
	string expression;// variable that will be used to store user  expression
	float expValue;// variable that will be used to store the value of the expression

	cout << "Please enter the arithmetic or logic expression to be evaluated." << endl;
	cout << "Only numeral constants, parenthesis, arithmeric or logical operators are allow." << endl;

		getline(cin, expression);

		// call getPerLineTokenVectFromOneStringObject to get every token in the expression that user entered and store the tokens into infixExp
		LexicalScanner::getPerLineTokenVectFromOneStringObject(expression,infixExp);

		// according to the assignment requirements, only numeral constant, arithmetic operator, logical operator, and parenthesis are allowed.
		for ( int i = 0; i < infixExp.size(); i++) {
			if (!LexicalScanner::isNUMERICAL_LITERAL(infixExp[i]) && !LexicalScanner::isLOGICAL_OP(infixExp[i]) &&
				!LexicalScanner::isNUMERICAL_OP(infixExp[i]) && !LexicalScanner::isLEFT_PARENTHESIS(infixExp[i]) &&
				!LexicalScanner::isRIGHT_PARENTHESIS(infixExp[i])) {
				cout << "ERROR: Invalid key entered." << endl;
				cout << "Valid keys are:  Numerical Literals, Logical Operators, Numerical Operators, Parenthesis" << endl;
				return;
			}
		}
		// call infixToPostfixConversion to convert the infix expression entered by the user into a postfix expression and it in postfixExp
		ExpressionEvaluator::infixToPostfixConversion(infixExp, postfixExp);

	// call postfixEvaluator to get the value of the postfixExp 
		if (ExpressionEvaluator::postfixEvaluator(postfixExp, table, expValue)) {

			for (int i = 0; i < infixExp.size(); i++) 
				cout << infixExp[i];
		
			cout << " = " << expValue << endl;
		}
		
	}




//An auxilliary message displaying function
void Interface::endOfService(const string service)
{
	cout<<endl << service << " done." << endl << "Press any key to continue.";
	_getch();
	cout << endl;
	cout << "****************************************************" <<endl<< endl;

}

// This menu() function is the interface
void Interface::startInterface() {

	// "Then I suppose now is the time for me to say something profound....
	// Nothing comes to mind. Let's do it."

	bool inMenu = true;	// while the user is using the program this var is set to true and the menu keeps looping.
						// when the user wants to quit, it is set to false and the loop ends.
	char keyPressed;	// This var stores which menu selection the user picks.

	while ( inMenu )
	{
		cout<< endl << endl << endl;
		cout << "****************************************************" << endl;
		cout  <<"**  MENU:(press a character to select an option)  **" << endl;
 		cout << "****************************************************" << endl;
		cout<<"Q. [QUIT]     Quit."<<endl;
		cout<<"L. [LOAD}     Read in a program (lines of statements) from a file"<<endl;
  		cout<<"S. [SAVE]     Save lines of statement as a program into a file"<<endl;
		cout << endl;

		cout<<"D. [DISPLAY]  Display the source code as lines of statements"<<endl;
		cout<<"U. [ANALYSIS] Lexical analysis of all lines of statements currently in the program." << endl;
		cout<<"C. [CALCULATOR]  Evaluate an arithmetic or logic expression." << endl;
		cout << endl;

		cout<<"A. [APPEND]   Append new lines to the end of the program"<<endl;
		cout<<"I. [INSERT}   Insert new lines before an existent line"<<endl;
		cout<<"X. [DELETE]   Delete a range of existent lines"<<endl;
		cout<<"R. [REPLACE]  Replace the contents of an existent line"<<endl;
		cout << endl;

		cout<<"P. [PARSE]    Parse and ident the code" << endl;
		cout<<"E. [EXECUTE]  Execute (run) the program"<<endl;
		cout<<"T. [TOGGLE]   Toggle the execution debug mode"<<endl;

		cout << "****************************************************" <<endl<< endl;

		cout<<"Your choice is: ";
		keyPressed = _getch();
		cout<<keyPressed << endl;

		switch(keyPressed) {
		case 'Q': case 'q'://Quit
			cout << "[QUIT]:" << endl;
			inMenu = false;
			break;

		case 'L': case 'l':// 1. Read in a program (lines of statements) from a file
 			cout << "[LOAD PROGRAM]:" << endl;
			loadProgramFromFile();
			endOfService("[LOAD PROGRAM]");
			break;

		case 'D': case 'd':// 2. Display the lines of statements
			cout << "[DISPLAY PROGRAM]:" << endl;
			displayProgram();
			endOfService("[DISPLAY PROGRAM]");
			break;

		case 'U': case 'u':// 6. Replace the contents of an existing line
			cout << "[ANALYSIS]:" << endl;
			lexialAnalysis();
			endOfService("[LEXICAL ANALYSIS]");
			break;

		case 'A': case 'a':// 3. Append new lines of code to the end
			cout << "[APPEND]:" << endl;
			appendLines();
			endOfService("[APPEND LINES]");
			break;

		case 'I': case 'i':// 4. Insert a new line after an existing line
			cout << "[INSERT LINES]:" << endl;
			insertLines();
			endOfService("[INSERT LINES]");
			break;

		case 'C': case 'c':// 1. Read in a program (lines of statements) from a file
			cout <<"[CALCULATOR]" << endl;
			calculator();
			endOfService("[CALCULATION]");
			break;

		case 'X': case 'x':// 5. Delete an existing line
			cout << "[DELETE LINES]:" << endl;
			deleteLines();
			endOfService("[DELETE LINES]");
			break;

		case 'R': case 'r':// 6. Replace the contents of an existing line
			cout << "[REPLACE]:" << endl;
			replaceOneLine();
			endOfService("[REPLACE ONE LINE]");
			break;

		case 'S': case 's':// 7. Save program to a file
			cout << "[SAVE]:" << endl;
			saveProgramIntoFile();
			endOfService("[SAVE CODE INTO A FILE]");
			break;

		case 'P': case 'p':// 8. Parse and Indent the program
			cout << "[PARSE AND INDENT SOURCE CODE]:" << endl;
			endOfService("[PARSE AND INDENT SOURCE CODE]");
			break;

		case 'E': case 'e':// 9. Run program
			cout << "[EXECUTE TO RUN PROGRAM]:" << endl;
			endOfService("[EXECUTE TO RUN PROGRAM]");
			break;

		case 'T': case 't':// Toggle the debug mode
			cout << "[TOGGLE the debug mode]:" << endl;
			break;


		default:
			cout << "[?? UNKNOWN COMMAND]:" << endl;
			// Unrecognized key, do nothing
			break;
		}

	} // End of while loop.
}
