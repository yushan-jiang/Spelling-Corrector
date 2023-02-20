#pragma once

#include <string>
#include <vector>
#include <map>
using namespace std;

class SpellingCorrector
{
private:
	typedef vector<string> Vector;
	typedef map<string, int> Dictionary;

	Dictionary dictionary;
	void Edit(string word, Vector& result);
	void Known(Vector& result, Dictionary& candidates);

public:
	//用于加载词库，生成词频字典
	void Load(const std::string filename);
	string Correct(const string word);
};