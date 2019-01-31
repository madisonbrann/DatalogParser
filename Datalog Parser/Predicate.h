#ifndef PREDICATE
#define PREDICATE

#include <string>
#include "Parameter.h"

using namespace std;


class Predicate
{
private:
	string name;
	vector<Parameter*> content;

public:
	Predicate(string name_in)
	{
		name = name_in;
	}
	virtual ~Predicate()
	{

	}

	void addParameter(Parameter* myParameter)
	{
		content.push_back(myParameter);
	}
	string to_string()
	{
		stringstream ss;
		ss << name << ":\n";
		for (unsigned int i = 0; i < content.size(); i++)
		{
			ss << content.at(i)->to_string();
			if (name != "Schemes") ss << ".";
			ss << endl;
		}
		return ss.str();
	}
};

#endif