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
	void operator_thing ();
	void expression();
	void parameter();
	void idList();
	void stringList();
	void parameterList();
	void predicateList();
	void predicate();
	void headPredicate();
	void query();
	void rule();
	void fact();
	void scheme();
	void queryList();
	void ruleList();
	void factList();
	void schemeList();
	void datalogProgram();

	//normal functions
	void parse_tokens();
	string to_string();
};

#endif
