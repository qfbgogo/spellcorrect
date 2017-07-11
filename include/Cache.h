 ///
 /// @file    Cache.h
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-29 16:15:22
 ///
#ifndef __CACHE_H__ 
#define __CACHE_H__
#include <unordered_map>
#include <string>
using namespace std;
namespace wd
{
	class Cache
	{
		private:
			string filePath_;
			unordered_map<string,string> hashMap_;
		public:
			Cache();
			Cache(const Cache& cache);
			string queryElement(const string &query);
			void addElement(const string &key,const string &value);
			void readFromFile();
			void writeToFile();
			void update(Cache &rhs);
	};
}
#endif
