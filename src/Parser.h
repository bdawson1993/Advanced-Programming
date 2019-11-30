#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

class Parser
{
public:
	Parser() {};
	~Parser() {};

	void Parse(string data);
	vector<string> Get(string name);

private:
	map<string, vector<string>> data;
	vector<string> Split(const string& s, char delimiter);
};


