#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <locale>   
#include <vector>

#include "Tokenizer.h"
#include "Token.h"
#include "DatalogParser.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"

using namespace std;

int main(int argc, char *argv[])
{
	vector<Token*> token_vector;
	if (argc < 2)
	{
		cerr << "Please provide name of input and output files" << endl;
		return 0;
	}

	ifstream in(argv[1]);
	Tokenizer* myTokenizer = new Tokenizer();
	Rule* myRule = new Rule();
	Parameter* myParameter = new Parameter("HasSameAddress");
	Parameter* myParameter1 = new Parameter("SNAP");
	Parameter* myParameter2 = new Parameter("SNAP");
	token_vector = myTokenizer->herewego(in);
	DatalogParser* myDatalogParser = new DatalogParser(token_vector);
	myDatalogParser->parse_tokens();

	myParameter->addString("x");
	myParameter->addString("y");
	myParameter->addString("12 Apple");
	myParameter->addString("555-1234");
	myParameter1->addString("12345");
	myParameter1->addString("C. Brown");
	myParameter2->addString("A");
	myParameter2->addString("X");
	myParameter2->addString("B");
	myParameter2->addString("C");
	
	myRule->addPredicate(myParameter);
	myRule->addPredicate(myParameter1);
	myRule->addPredicate(myParameter2);
	cout << myRule->to_string();

	delete myParameter;
	delete myTokenizer;
	// delete myPredicate;
	delete myDatalogParser;
	system("pause");

	return 0;
}