 ///
 /// @file    Myconf.h
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-28 18:19:12
 ///
#ifndef __MYCONF_H__
#define __MYCONF_H__
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using std::map;
using std::string;
namespace wd
{
class Myconf
{
	private:
		string filepath_;
		map<string,string> configMap_;
	public:
		Myconf();
		Myconf(const string &conf_path);
		void init();
		map<string,string> &getConfigMap();
	public:
		size_t buf_size_;
		size_t thread_num_;
		string ip_;
		unsigned short port_;
};
}
#endif
