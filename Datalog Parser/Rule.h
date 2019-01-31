#ifndef RULE
#define RULE

#include <string>
#include <sstream>
#include <vector>
#include "Predicate.h"

using namespace std;

class Rule
{
private:
	vector<Parameter*> predicate_list;

public:
	Rule()
	{
		
	}
	virtual ~Rule()
	{
		for (unsigned int i = 0; i < predicate_list.size(); i++)
		{
			delete predicate_list.at(i);
		}
	}

	void addPredicate(Parameter* myPredicate)
	{
		predicate_list.push_back(myPredicate);
	}

	string to_string()
	{
		stringstream ss;
		ss << "Rules:\n" << predicate_list.at(0)->to_string() << " :- ";
		for (unsigned int i = 1; i < predicate_list.size(); i++)
		{
			ss << predicate_list.at(i)->to_string();
			if (i != predicate_list.size() - 1) ss << ",";
		}
		return ss.str();;
	}
};

#endif
