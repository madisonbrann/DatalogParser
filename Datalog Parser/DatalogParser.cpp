#include "DatalogParser.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include <iostream>
using namespace std;

vector<Predicate*> SchemePredicates;
vector<Predicate*> FactPredicates;
vector<Rule*> RulePredicates;
vector<Predicate*> QueriePredicates;

DatalogParser::DatalogParser(vector<Token*> token_vector_in)
{
	token_vector = token_vector_in;
	token_number = 0;
	
}
DatalogParser::~DatalogParser()
{
	for (unsigned int i = 0; i < token_vector.size(); i++)
	{
		delete token_vector.at(i);
	}
	for (unsigned int i = 0; i < FactPredicates.size(); i++)
	{
		delete FactPredicates.at(i);
	}
	for (unsigned int i = 0; i < RulePredicates.size(); i++)
	{
		delete RulePredicates.at(i);
	}
	for (unsigned int i = 0; i < SchemePredicates.size(); i++)
	{
//		delete SchemePredicates.at(i);
	}
	for (unsigned int i = 0; i < QueriePredicates.size(); i++)
	{
		delete QueriePredicates.at(i);
	}
	delete SchemePredicates[0];
}



void DatalogParser::match(string item)
{
	if (token_vector.at(token_number)->get_type() != item)
	{
		throw string("break");
	}
	token_number++;
}
void DatalogParser::operator_thing(Parameter* myParameter)
{
	if (token_vector.at(token_number)->get_type() == "ADD")
	{
		myParameter->addString(token_vector.at(token_number)->get_output());
		match("ADD");
	}
	else
	{
		myParameter->addString(token_vector.at(token_number)->get_output());
		match("MULTIPLY");
	}
}
void DatalogParser::expression(Parameter* myParameter)
{
	match("LEFT_PAREN");
	parameter(myParameter);
	operator_thing(myParameter);
	parameter(myParameter);
	match("RIGHT_PAREN");
}
void DatalogParser::parameter(Parameter* myParameter)
{
	if (token_vector.at(token_number)->get_type() == "STRING")
	{
		myParameter->addString(token_vector.at(token_number)->get_output());
		match("STRING");
	}
	else if (token_vector.at(token_number)->get_type() == "ID")
	{
		myParameter->addString(token_vector.at(token_number)->get_output());
		match("ID");
	}
	else
	{
		expression(myParameter);
	}
}
void DatalogParser::idList(Parameter* myParameter)
{
	if (token_vector.at(token_number)->get_type() == "RIGHT_PAREN")
	{
		//escape idList
	}
	else
	{
		match("COMMA");
		myParameter->addString(token_vector.at(token_number)->get_output());
		match("ID");
		idList(myParameter);
	}
}
void DatalogParser::stringList(Parameter* myParameter)
{
	if (token_vector.at(token_number)->get_type() == "RIGHT_PAREN")
	{
		//escape stringList
	}
	else
	{
		match("COMMA");
		myParameter->addString(token_vector.at(token_number)->get_output());
		match("STRING");
		stringList(myParameter);
	}
}
void DatalogParser::parameterList(Parameter* myParameter)
{
	if (token_vector.at(token_number)->get_type() == "RIGHT_PAREN")
	{
		//escape parameterList
	}
	else
	{
		match("COMMA");
		parameter(myParameter);
		parameterList(myParameter);
	}
}
void DatalogParser::predicateList(Rule* myRule)
{
	if (token_vector.at(token_number)->get_type() == "PERIOD")
	{
		//escape predicateList
	}
	else
	{
		match("COMMA");
		predicate(myRule);
		predicateList(myRule);
	}
}
void DatalogParser::predicate(Rule* myRule)
{
	Predicate* myPredicate = new Predicate(token_vector.at(token_number)->get_output());
	match("ID");
	match("LEFT_PAREN");
	Parameter* myParameter = new Parameter(token_vector.at(token_number)->get_output());
	myPredicate->addParameter(myParameter);
	parameter(myParameter);
	parameterList(myParameter);
	match("RIGHT_PAREN");
	myParameter->removeFirstString();
	myRule->addPredicate(myPredicate);
}
void DatalogParser::headPredicate(Rule* myRule)
{
	Predicate* myPredicate = new Predicate(token_vector.at(token_number)->get_output());
	match("ID");
	match("LEFT_PAREN");
	Parameter* myParameter = new Parameter(token_vector.at(token_number)->get_output());
	myPredicate->addParameter(myParameter);
	match("ID");
	idList(myParameter);
	myRule->addPredicate(myPredicate);
	match("RIGHT_PAREN");
}
void DatalogParser::query()
{
	Rule* myRule = new Rule();
	 predicate(myRule);
	match("Q_MARK");
}
void DatalogParser::rule()
{
	Rule* myRule = new Rule();
	headPredicate(myRule);
	match("COLON_DASH");
	predicate(myRule);
	predicateList(myRule);
	match("PERIOD");
	RulePredicates.push_back(myRule);
}
void DatalogParser::fact()
{
	Predicate* myFactPredicate = new Predicate(token_vector.at(token_number)->get_output());
	match("ID");
	match("LEFT_PAREN");
	Parameter* myParameter = new Parameter(token_vector.at(token_number)->get_output());
	myFactPredicate->addParameter(myParameter);
	match("STRING");
	stringList(myParameter);
	match("RIGHT_PAREN");
	match("PERIOD");
	FactPredicates.push_back(myFactPredicate);
}
void DatalogParser::scheme()
{
	Predicate* mySchemePredicate = new Predicate(token_vector.at(token_number)->get_output());
	match("ID");
	match("LEFT_PAREN");
	Parameter* myParameter = new Parameter(token_vector.at(token_number)->get_output());
	mySchemePredicate->addParameter(myParameter);
	match("ID");
	idList(myParameter);
	match("RIGHT_PAREN");
	SchemePredicates.push_back(mySchemePredicate);
}
void DatalogParser::queryList()
{
	if (token_vector.at(token_number)->get_type() == "EOF")
	{
		//escape queryList
	}
	else
	{
		query();
		queryList();
	}
}
void DatalogParser::ruleList()
{
	if (token_vector.at(token_number)->get_type() == "QUERIES")
	{
		//escape schemeList
	}
	else
	{
		rule();
		ruleList();
	}
}
void DatalogParser::factList()
{
	if (token_vector.at(token_number)->get_type() == "RULES")
	{
		//escape factList
	}
	else
	{
		fact();
		factList();
	}
}
void DatalogParser::schemeList()
{
	if (token_vector.at(token_number)->get_type() == "FACTS")
	{
		//escape schemeList
	}
	else
	{
		scheme();
		schemeList();
	}
}
void DatalogParser::datalogProgram()
{
	match("SCHEMES");
	match("COLON");
	scheme();
	schemeList();
	match("FACTS");
	match("COLON");
	factList();
	match("RULES");
	match("COLON");
	ruleList();
	match("QUERIES");
	match("COLON");
	query();
	queryList();
}

//normal functions
void DatalogParser::parse_tokens()
{
	try
	{
		datalogProgram();
		cout << "Success!" << endl;
	}
	catch (string e)
	{
		cout << "Failure!\n  (" << token_vector.at(token_number)->get_type() << ",\""<< token_vector.at(token_number)->get_output() << "\"," << token_vector.at(token_number)->get_line() << ")" << endl;
	}
}

void DatalogParser::get_domain()
{

}

string DatalogParser::to_string()
{
	stringstream ss;
	for (unsigned int i = 0; i < RulePredicates.size(); i++)
	{
		ss << RulePredicates.at(i)->to_string() << endl;
	}
	return ss.str();
}