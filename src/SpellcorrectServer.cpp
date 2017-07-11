 ///
 /// @file    SpellcorrectServer.cpp
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-28 11:47:39
 ///
#include "SpellcorrectServer.h"
#include "TcpConnection.h"
#include "Task.h"
#include "MyLog.h"
#include <functional>
using namespace std::placeholders;
namespace wd{
SpellcorrectServer::SpellcorrectServer()
:tcpServer_(myConf_.ip_.c_str(),myConf_.port_)
,threadpool_(myConf_.buf_size_,myConf_.thread_num_)
{
}
void SpellcorrectServer::start()
{
	threadpool_.start();
    tcpServer_.setConnectionCallback(std::bind(&SpellcorrectServer::onConnection,this,_1));
    tcpServer_.setMessageCallback(std::bind(&SpellcorrectServer::onMessage,this,_1));
    tcpServer_.setCloseCallback(std::bind(&SpellcorrectServer::onClose,this,_1));
	tcpServer_.start();
}
void SpellcorrectServer::onConnection(const TcpConnectionPtr &conn)
{
	char log_info[100]={0};
    sprintf(log_info,"> %s has connected!", conn->toString().c_str());
	LogInfo(log_info);
	conn->send("hello, welcome to SpellcorrectServer.\n");
}
void SpellcorrectServer::onMessage(const TcpConnectionPtr &conn)
{
	string line(conn->receive()),query;
	istringstream iss(line);
    iss>>query;
	Task task(conn,query);
	threadpool_.addTask(std::bind(&Task::execute,task));
}
void SpellcorrectServer::onClose(const TcpConnectionPtr &conn)
{
	char log_info[100]={0};
    sprintf(log_info,"> %s has closed.", conn->toString().c_str());
	LogInfo(log_info);
}
}

