#include "DatalogParser.h"
#include <iostream>
using namespace std;

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
}



void DatalogParser::match(string item)
{
	if (token_vector.at(token_number)->get_type() != item)
	{
		throw string("break");
	}
	token_number++;
}
void DatalogParser::operator_thing()
{
	if (token_vector.at(token_number)->get_type() == "ADD")
	{
		match("ADD");
	}
	else
	{
		match("MULTIPLY");
	}
}
void DatalogParser::expression()
{
	match("LEFT_PAREN");
	parameter();
	operator_thing();
	parameter();
	match("RIGHT_PAREN");
}
void DatalogParser::parameter()
{
	if (token_vector.at(token_number)->get_type() == "STRING")
	{
		match("STRING");
	}
	else if (token_vector.at(token_number)->get_type() == "ID")
	{
		match("ID");
	}
	else
	{
		expression();
	}
}
void DatalogParser::idList()
{
	if (token_vector.at(token_number)->get_type() == "RIGHT_PAREN")
	{
		//escape idList
	}
	else
	{
		match("COMMA");
		match("ID");
		idList();
	}
}
void DatalogParser::stringList()
{
	if (token_vector.at(token_number)->get_type() == "RIGHT_PAREN")
	{
		//escape stringList
	}
	else
	{
		match("COMMA");
		match("STRING");
		stringList();
	}
}
void DatalogParser::parameterList()
{
	if (token_vector.at(token_number)->get_type() == "RIGHT_PAREN")
	{
		//escape parameterList
	}
	else
	{
		match("COMMA");
		parameter();
		parameterList();
	}
}
void DatalogParser::predicateList()
{
	if (token_vector.at(token_number)->get_type() == "PERIOD")
	{
		//escape predicateList
	}
	else
	{
		match("COMMA");
		predicate();
		predicateList();
	}
}
void DatalogParser::predicate()
{
	match("ID");
	match("LEFT_PAREN");
	parameter();
	parameterList();
	match("RIGHT_PAREN");
}
void DatalogParser::headPredicate()
{
	match("ID");
	match("LEFT_PAREN");
	match("ID");
	idList();
	match("RIGHT_PAREN");
}
void DatalogParser::query()
{
	predicate();
	match("Q_MARK");
}
void DatalogParser::rule()
{
	headPredicate();
	match("COLON_DASH");
	predicate();
	predicateList();
	match("PERIOD");
}
void DatalogParser::fact()
{
	match("ID");
	match("LEFT_PAREN");
	match("STRING");
	stringList();
	match("RIGHT_PAREN");
	match("PERIOD");
}
void DatalogParser::scheme()
{
	match("ID");
	match("LEFT_PAREN");
	match("ID");
	idList();
	match("RIGHT_PAREN");
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
	return "hello world";
}