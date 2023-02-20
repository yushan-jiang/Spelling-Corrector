#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "SpellingCorrector.h"

using namespace std;

char FilterNoAlpha(char& letter)
{
	//过滤掉不是字母的字符并转为小写
	if (letter < 0)
	{
		return '-';
	}
	if (isalpha(letter))
	{
		return tolower(letter);
	}
	return '-';
}
void SpellingCorrector::Edit(string word, Vector& result)
{
	for (char j = 'a'; j <= 'z'; ++j)
	{
		for (string::size_type i = 0; i < word.size(); ++i)
			result.push_back(word.substr(0, i) + j + word.substr(i+1));//将位置i替换
		for (string::size_type i = 0; i < word.size() + 1; ++i)
			result.push_back(word.substr(0, i) + j + word.substr(i));//在位置i添加
	}
	for (string::size_type i = 0; i < word.size(); ++i)
		result.push_back(word.substr(0, i) + word.substr(i+1));//删除位置i元素
	for (string::size_type i = 0; i < word.size() - 1; ++i)
		result.push_back(word.substr(0, i) + word[i + 1] + word[i] + word.substr(i+2));//位置i与i+1交换
		
}

void SpellingCorrector::Known(Vector& result, Dictionary& candidates)
{
	for (int i = 0; i < result.size(); ++i)
	{
		Dictionary::iterator value = dictionary.find(result[i]);
		if (value != dictionary.end())
		{
			candidates[value->first] = value->second;
		}
	}
}

void SpellingCorrector::Load(const string filename)
{
	ifstream file;
	file.open(filename.c_str(), ios::binary | ios::in);

	file.seekg(0, ios::end);
	streampos length = file.tellg();
	//length = streamsize
	file.seekg(0, ios::beg);

	//cout << len << endl;

	string data(static_cast<size_t>(length), '\0');

	file.read(&data[0], length);
	//将文件内容读取到data中

	transform(data.begin(), data.end(), data.begin(), FilterNoAlpha);

	for (string::size_type i = 0; i != string::npos;)
	{
		const string::size_type firstNonFiltered =
			data.find_first_not_of('-', i + 1);
		if (firstNonFiltered == string::npos)break;
		const string::size_type end = 
			data.find('-', firstNonFiltered);
		dictionary[data.substr(firstNonFiltered,end-firstNonFiltered)]++;

		i = end;
	}



}

bool SortBySecond(const pair<string, int>& left, const pair<string, int>& right)
{
	return left.second < right.second;
}

string SpellingCorrector::Correct(const string word)
{
	Vector result;
	Dictionary candidates;
	
	
	if (dictionary.find(word) != dictionary.end()) 
		return word;

	Edit(word, result);
	Known(result, candidates);

	if (candidates.size() > 0)
		return max_element(candidates.begin(), candidates.end(), SortBySecond)->first;

	for (int i = 0; i < result.size(); ++i)
	{
		Vector subResult;

		Edit(result[i], subResult);
		Known(subResult, candidates);
	}
	if (candidates.size() > 0)
		return max_element(candidates.begin(), candidates.end(), SortBySecond)->first;

	return "";
}

