 ///
 /// @file    Mydict.cpp
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-28 17:34:35
 ///
#include "Mydict.h" 
#include "Myconf.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
using namespace std;
namespace wd
{
Mydict::Mydict()
{
	Myconf conf;
	map<string,string> &confMap=conf.getConfigMap();
	for(auto &elem:confMap)
	{
		if(!elem.first.compare("dict"))
			dict_path_=elem.second;
		else if(!elem.first.compare("index"))
			index_path_=elem.second;
	}
	initDict();
	initIndex();
}
Mydict *Mydict::createInstance()
{
	if(pdict_==NULL)
	{
		pdict_=new Mydict();
		atexit(destroy);
	}
	return pdict_;
}
Mydict *Mydict::pdict_=createInstance();
void Mydict::destroy()
{
	if(pdict_!=NULL)
		delete pdict_;
}
void Mydict::initDict()
{
	ifstream ifs(dict_path_);
	string line,word,sfreq;
	int freq;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		while(iss>>word)
		{
			iss>>sfreq;
			freq=stoi(sfreq);
			dict_.push_back(pair<string,int>(word,freq));
		}
	}
}
void Mydict::initIndex()
{
	ifstream ifs(index_path_);
	string line,key,sidx;
	int idx;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		set<int> set_idx;
		iss>>key;
		while(iss>>sidx)
		{
			idx=stoi(sidx);
			set_idx.insert(idx);
		}
		index_table_.insert(make_pair(key,set_idx));
	}
}
vector<pair<string,int> >& Mydict::getDict()
{
	return dict_;
}
map<string,set<int> >& Mydict::getIndexTable()
{
	return index_table_;
}

Mydict::~Mydict()
{

}
}
