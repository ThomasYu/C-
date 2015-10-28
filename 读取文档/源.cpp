#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<fstream>
using namespace std;
const string& transform(const string& s, map<string, string>& m)
{
	auto map_it = m.find(s);
	if (map_it != m.cend())
	return map_it->second;
	else
		return s;
}

map<string, string> buildMap(ifstream& map_file)
{
	string key, value;
	map<string, string> trans_map;
	//ifstream输入是一个字符串的输入
	while (map_file >> key&&getline(map_file,value))
	{
		if (value.size() > 1)
			trans_map[key] = value.substr(1);
		else
			throw runtime_error("no rule for " + key);
	}
	return trans_map;
}

void word_transform(ifstream& map_file, ifstream& input)
{
	map<string, string> trans_map = buildMap(map_file);
	string text;
	while (getline(input, text))
	{
		istringstream stream(text);
		string word;
		bool firstword = true;
		while (stream >> word)
		{

			if (firstword)
				firstword = false;
			else
				cout << " ";
			cout << transform(word, trans_map);
		}
		cout << endl;
	}
}
void main()
{
	ifstream map_file("规则.txt");
	ifstream input("待转换的文本.txt");
	word_transform(map_file, input);
	cout << endl;
	ofstream out("保存文本.txt");
}