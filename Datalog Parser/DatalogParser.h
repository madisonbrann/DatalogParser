#ifndef DATALOGPARSER
#define DATALOGPARSER

#include <string>
#include <vector>
#include <sstream>
#include "Token.h"

using namespace std;

class DatalogParser
{
private:
	vector<Token*> token_vector;
	int token_number;
public:
	DatalogParser(vector<Token*> token_vector_in);
	virtual ~DatalogParser();
	// grammar functions
	void match(string item);
	void operator_thing (Token* token);
	void expression(Token* token);
	void parameter(Token* token);
	void idList(Token* token);
	void stringList(Token* token);
	void parameterList(Token* token);
	void predicateList(Token* token);
	void predicate(Token* token);
	void headPredicate(Token* token);
	void query(Token* token);
	void rule(Token* token);
	void fact(Token* token);
	void scheme(Token* token);
	void queryList(Token* token);
	void ruleList(Token* token);
	void factList(Token* token);
	void schemeList(Token* token);
	void datalogProgram(Token* token);

	//normal functions
	void parse_tokens();
	string to_string();
};

#endif
