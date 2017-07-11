 ///
 /// @file    Mydict.h
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-28 16:31:07
 ///
#ifndef __MYDICT_H__
#define __MYDICT_H__
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;
namespace wd
{
class Mydict
{
	private:
		vector<pair<string,int> > dict_;
		map<string,set<int> > index_table_;
		Mydict();
		~Mydict();
		string dict_path_;
		string index_path_;
	public:
		static Mydict *createInstance();
		void initDict();
		void initIndex();
		vector<pair<string,int> > &getDict();
		map<string,set<int> > &getIndexTable();
		static Mydict *pdict_;
		static void destroy();
};
}
#endif
