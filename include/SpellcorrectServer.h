 ///
 /// @file    SpellcorrectServer.cpp
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-28 11:38:11
 ///
#ifndef __SPELLCORRECTSERVER_H__
#define __SPELLCORRECTSERVER_H__
#include "Myconf.h"
#include "Mydict.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include "TcpConnection.h"
namespace wd{
class SpellcorrectServer
{
	public:
		SpellcorrectServer();
		void start();
		void onConnection(const TcpConnectionPtr &conn);
		void onMessage(const TcpConnectionPtr &conn);
		void onClose(const TcpConnectionPtr &conn);
	private:
		Myconf     myConf_;		
		TcpServer  tcpServer_;
		Threadpool threadpool_;
};
}
#endif
