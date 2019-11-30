#include "Parser.h"

void Parser::Parse(string data)
{
	this->data.clear();
	//cout << data << endl;
	bool isName = false;
	bool isData = false;
	string name;

	//buffers
	string nameBuffer;
	string dataBuffer;

	vector<string> splitString = Split(data, ':');

	if (splitString.size() > 0)
	{
		vector<string> posData = Split(splitString[1], ',');
		this->data.insert(std::pair<string, vector<string>>(splitString[0], posData));
	}
}

vector<string> Parser::Get(string name)
{
	return data[name];
}

vector<string> Parser::Split(const string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	istringstream tokenStream(s);
	
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

