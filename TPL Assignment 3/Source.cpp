#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


//Declaring the Functions here so that calling isn't a problem
void match(string);
void program(string);
void stmt_list();
void stmt();
void expr();
void term_tail();
void term();
void factor_tail();
void factor();
void add_op();
void mult_op();

//Defining necessary global variables

string line;
string nextLine;
fstream file;
string symbol[] = { ":=", "(", ")", "$$", "*", "/", "+", "-"};
string rws[] = { "read", "write", "sum"};
string id[] = { "A", "B", "45.325", "80.777" };


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Reading in the file line by line
void scanFile(string fileName) {

	ifstream file;
	file.open(fileName);

	if (!file)
	{
		cerr << "Unable to open file." << endl;
		exit(1);
	}
	
	while (file)
	{
		getline(file, line);
		program(line);
	}
	cout << '\n';
};


//Function to check for token match
void match(string expectedToken) {

	if (line == expectedToken)
	{
		cout << "	Token: " << line << " Consumed" << endl;
	}
	else
	{
		cout << "This is Parse Error 1, match()" << endl;
		exit(1);
	}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to begin execution
void program(string) {
	
	if (line == rws[0] || line == rws[1] || line == rws[2])
	{
		stmt_list();
	}
	else if (line == id[0] || line == id[1] || line == id[2] || line == id[3])
	{
		stmt_list();
	}
	else if (line == symbol[0])
	{
		match(line);
	}
	else if (line == symbol[1]) 
	{
		factor();
	}
	else if (line == symbol[2])
	{
		factor_tail();
	}
	else if (line == symbol[3])
	{
		cout << "Executing: factor_tail() term_tail() stmt_list() stmt_list()" << endl;
		match(line);
	}
	else if (line == symbol[4] || line == symbol[5])
	{
		factor_tail();
	}
	else if (line == symbol[6] || line == symbol[7])
	{
		term_tail();
	}
	else
	{
		cout << "This is Parse Error 2, program()" << endl;
		exit(1);
	}


};

//Function to execute "stmt_list"
void stmt_list() {

	if (line == rws[0] || line == rws[1] || line == rws[2])
	{
		stmt();
	}
	else if (line == id[0] || line == id[1] || line == id[2] || line == id[3])
	{
		stmt();
	}
	else
	{
		cout << "This is Parse Error 3, stmt_list()" << endl;
		exit(1);
	}
	
	
};

//Function to execute "stmt"
void stmt() {


	if (line == id[0] || line == id[1] || line == id[2] || line == id[3])
	{
		expr();
	}
	else if (line == rws[0])
	{
		cout << "Executing: stmt_list() stmt()" << endl;
		match(line);
	}
	else if (line == rws[1])
	{
		cout << "Executing: factor_tail() term_tail() stmt_list()" << endl;
		match(line);
	}
	else if (line == rws[2])
	{
		factor();
	}
	else
	{
		cout << "This is Parse Error 4, stmt()" << endl;
		exit(1);
	}

};

//Function to execute "expr"
void expr() {

	if (line == id[0] || line == id[1] || line == id[2] || line == id[3] || line == symbol[2])
	{
		term();
	}
	else
	{
		cout << "This is Parse Error 5, expr()" << endl;
	}
};

//Function to execute "term_tail"
void term_tail() {

	if (line == symbol[6] || line == symbol[7])
	{
		add_op();
	}
	else if (line == rws[0] || line == rws[1] || line == rws[2] || line == symbol[3] || line == symbol[2])
	{

	}
	else
	{
		cout << "This is Parse Error 6, term_tail()" << endl;
	}
};

//Function to execute "term"
void term() {

	if (line == id[0] || line == id[1] || line == id[2] || line == id[3])
	{
		factor();
		factor_tail();
	}
	else
	{
		cout << "This is Parse Error 7, term()" << endl;
	}
};

//Function to execute "factor_tail"
void factor_tail() {

	if (line == symbol[4] || line == symbol[5])
	{
		mult_op();
	}
	else if (line == symbol[2])
	{
		cout << "Executing: factor_tail() term_tail()" << endl;
		match(line);
	}
	else if (line == symbol[6] || line == symbol[7] || line == rws[0] || line == rws[1] || line == rws[2] || line == symbol[3] || line == id[0] || line == id[1] || line == id[2] || line == id[3])
	{

	}
	else
	{
		cout << "This is Parse Error 8, factor_tail()" << endl;
	}
};

//Function to execute "factor"
void factor() {

	if (line == id[0] || line == id[1])
	{
		match(line);
	}
	else if (line == id[2] || line == id[3])
	{
		cout << "Executing: factor()" << endl;
		match(line);
	}
	else if (line == symbol[1])
	{
		cout << "Executing: expr() term() factor()" << endl;
		match(line);
		cout << "Executing: expr() term() factor()" << endl;
	}
	else if (line == rws[2])
	{
		cout << "Executing: stmt_list() stmt()" << endl;
		match(line);
	}
	else
	{
		cout << "This is Parse Error 9, factor()" << endl;
	}
};

//Function to execute "add_op"
void add_op() {

	if (line == symbol[6] || line == symbol[7])
	{
		cout << "Executing: factor_tail() term_tail() add_op()" << endl;
		match(line);
		cout << "Executing: term() factor()" << endl;
	}
	else
	{
		cout << "This is Parse Error 10, add_op()" << endl;
	}
};

//Function to execute "mult_op"
void mult_op() {

	if (line == symbol[4] || line == symbol[5])
	{
		cout << "Executing: factor_tail() mult_op()" << endl;
		match(line);
	}
	else
	{
		cout << "This is Parse Error 11, mult_op()" << endl;
	}
};




int main() {

	scanFile("data2.txt");

	return 0;
}

