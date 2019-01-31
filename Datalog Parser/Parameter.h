#ifndef PARAMETER
#define PARAMETER

#include <string>

using namespace std;

class Parameter
{
private:
	string ID;
	vector<string> parameter_contents;

public:
	Parameter(string ID_in)
	{
		ID = ID_in;
	}
	virtual ~Parameter()
	{

	}

	string getID()
	{
		return ID;
	}

	void addString(string content)
	{
		parameter_contents.push_back(content);
	}

	string to_string()
	{
		stringstream ss;
		ss << "(" << ID << ",";
		for (unsigned int i = 0; i < parameter_contents.size(); i++)
		{
			ss << parameter_contents.at(i);
			if (i != parameter_contents.size() - 1) ss << ",";
		}
		ss << ")";
		return ss.str();
	}

	void removeFirstString()
	{
		parameter_contents.erase(parameter_contents.begin());
	}
};

#endif
