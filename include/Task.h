 ///
 /// @file    Task.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-05-12 09:59:20
 ///
 
#ifndef __WD_TASK_H__
#define __WD_TASK_H__
#include "MyResult.h"
#include "TcpConnection.h"
#include "Mydict.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
using namespace std;
namespace wd{
class Task
{
public:
	Task(TcpConnectionPtr conn,string query);
	void execute();
	void queryIndexTable();
	void statistic(set<int> &iset);
	string  response();
	int distance(const string &rhs);
private:
	Mydict *myDict_;
	vector<pair<string,int> > &dict_;
	TcpConnectionPtr conn_;
	string query_;
	priority_queue<MyResult,vector<MyResult>,MyCompare> que_;
	set<int> word_idx_in_dict;
};
}
#endif
