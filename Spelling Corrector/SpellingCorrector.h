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
	//���ڼ��شʿ⣬���ɴ�Ƶ�ֵ�
	void Load(const std::string filename);
	string Correct(const string word);
};