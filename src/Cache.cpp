 ///
 /// @file    Cache.cpp
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-06-03 14:45:41
 ///
#include "Cache.h"
#include <sstream>
#include <fstream>
#include <iostream>
namespace wd
{
Cache::Cache()
:filePath_("./MyCache.cache")
{

}
Cache::Cache(const Cache &cache)
{
	hashMap_=cache.hashMap_;
}
string Cache::queryElement(const string &query)
{
	unordered_map<string,string>::iterator it=hashMap_.find(query);
	if(it!=hashMap_.end())
		return it->second;
	else
		return string();
}
void Cache::addElement(const string &key,const string &value)
{
	hashMap_.insert(make_pair(key,value));
}
void Cache::readFromFile()
{
	ifstream ifs(filePath_);
	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		string key,value,candidate_word;
		iss>>key;
		while(iss>>candidate_word)
		{
			value+=candidate_word+" ";
		}
		value.append("\n");
		hashMap_.insert(make_pair(key,value));
	}
}
void Cache::writeToFile()
{
	ofstream ofs(filePath_);
	for(auto &elem:hashMap_)
	{
		ofs<<elem.first<<" "<<elem.second;
	}
}
void Cache::update(Cache &rhs)
{
	for(auto &elem:rhs.hashMap_)
	{
		hashMap_.insert(elem);
	}
}
}
