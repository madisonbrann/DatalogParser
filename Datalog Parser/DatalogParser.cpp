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

}



void DatalogParser::match(string item)
{

}
void DatalogParser::operator_thing(Token* token)
{

}
void DatalogParser::expression(Token* token)
{

}
void DatalogParser::parameter(Token* token)
{

}
void DatalogParser::idList(Token* token)
{

}
void DatalogParser::stringList(Token* token)
{

}
void DatalogParser::parameterList(Token* token)
{

}
void DatalogParser::predicateList(Token* token)
{

}
void DatalogParser::predicate(Token* token)
{

}
void DatalogParser::headPredicate(Token* token)
{

}
void DatalogParser::query(Token* token)
{

}
void DatalogParser::rule(Token* token)
{

}
void DatalogParser::fact(Token* token)
{

}
void DatalogParser::scheme(Token* token)
{

}
void DatalogParser::queryList(Token* token)
{

}
void DatalogParser::ruleList(Token* token)
{

}
void DatalogParser::factList(Token* token)
{

}
void DatalogParser::schemeList(Token* token)
{

}
void DatalogParser::datalogProgram(Token* token)
{

}

//normal functions
void DatalogParser::parse_tokens()
{
	try
	{

	}
	catch (string e)
	{
		cout << "Failure!\n";
	}
}
string DatalogParser::to_string()
{

}