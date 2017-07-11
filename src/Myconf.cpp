 ///
 /// @file    Myconf.cpp
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-17 14:54:41
 ///
#include "Myconf.h"
using namespace std;
namespace wd{
Myconf::Myconf()
:filepath_("./conf/myconf.conf")
{
	init();
}
Myconf::Myconf(const string &conf_path)
{
	filepath_=conf_path;
	init();
}
map<string,string> &Myconf::getConfigMap()
{
	return configMap_;
}
void Myconf::init()
{
	ifstream ifs(filepath_);
	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		pair<string,string> p;
		iss>>p.first;
		iss>>p.second;
		configMap_.insert(p);
		if(!p.first.compare("ip"))
			ip_=p.second;
		else if(!p.first.compare("port"))
			port_=static_cast<unsigned short> (stoi(p.second));
		else if(!p.first.compare("buffer"))
			buf_size_=stoi(p.second);
		else if(!p.first.compare("thread"))
			thread_num_=stoi(p.second);
	}
		
}
}
