#include <stdio.h>
#include "Task.h"
#include "CacheManager.h"
#include "Mydict.h"
#include <algorithm>
#include <iostream>
namespace wd{

Task::Task(wd::TcpConnectionPtr conn,string query)
:myDict_(Mydict::createInstance())
,dict_(myDict_->getDict())
,conn_(conn)
,query_(query)
{
}

void Task::execute()
{
	//线程的在缓存中查找query_，cache命中返回查找结果
	//否则，执行以下查询，返回查询结果的同时，写入缓存
	CacheManager *pCache_=CacheManager::createCacheManager();
	Cache &cache=pCache_->getCache(pthread_self());
	string send_back=cache.queryElement(query_);
	if(send_back.size())
	{
		std::cout<<"Cache hit success"<<std::endl;
		conn_->sendInLoop(send_back);
	}else{
		queryIndexTable();
		string query_result=response();
		cache.addElement(query_,query_result);
	}
}
void Task::queryIndexTable()
{
	map<string,set<int> > &index_table=myDict_->getIndexTable();
	for(size_t idx=0;idx<query_.size();++idx)
	{
		string key=string(1,query_[idx]);
		map<string,set<int> >::iterator imap=index_table.find(key);
		set<int> &query_set=imap->second;
		statistic(query_set);
	}
}
void Task::statistic(set<int> &query_set)
{
	set<int>::iterator iset=query_set.begin();
	for(;iset!=query_set.end();++iset)
	{
		pair<set<int>::iterator,bool> res=word_idx_in_dict.insert(*iset);
		if(!res.second)
			continue;
		string &word=dict_[*iset].first;
		int dis=distance(word);
		if(dis<3)
		{
			struct MyResult query_result;
			query_result.candidate_word_=dict_[*iset].first;
			query_result.frequence_=dict_[*iset].second;
			query_result.distance_=dis;
			que_.push(query_result);
		}
	}		

}
string Task::response()
{
	string send_back;
	int send_num=8;
	while(que_.size()&&(send_num--))
	{
		struct MyResult result=que_.top();
		string word(result.candidate_word_);
		send_back+=word+" ";
		que_.pop();
	}
	send_back.append("\n");
	conn_->sendInLoop(send_back);
	return send_back;
}
int Task::distance(const string &rhs)
{
    int max1 = query_.size();
    int max2 = rhs.size();

    int **ptr = new int*[max1 + 1];
    for(int i = 0; i < max1 + 1 ;i++)
    {
        ptr[i] = new int[max2 + 1];
    }

    for(int i = 0 ;i < max1 + 1 ;i++)
    {
        ptr[i][0] = i;
    }

    for(int i = 0 ;i < max2 + 1;i++)
    {
        ptr[0][i] = i;
    }

    for(int i = 1 ;i < max1 + 1 ;i++)
    {
        for(int j = 1 ;j< max2 + 1; j++)
        {
            int d;
            int temp = min(ptr[i-1][j] + 1, ptr[i][j-1] + 1);
            if(query_[i-1] == rhs[j-1])
            {
                d = 0 ;
            }
            else
            {
                d = 1 ;
            }
            ptr[i][j] = min(temp, ptr[i-1][j-1] + d);
        }
    }

    int dis = ptr[max1][max2];

    for(int i = 0; i < max1 + 1; i++)
    {
        delete[] ptr[i];
        ptr[i] = NULL;
    }

    delete[] ptr;
    ptr = NULL;

    return dis;
}
}
