 ///
 /// @file    CacheManager.cpp
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-06-03 16:33:21
 ///
#include "CacheManager.h"
#include <stdlib.h>
#include <iostream>
namespace wd
{
CacheManager::CacheManager()
{
	initCache();	
}
CacheManager::~CacheManager()
{
	cache_.writeToFile();
}
CacheManager *CacheManager::pCache_=createCacheManager();
CacheManager *CacheManager::createCacheManager()
{
	if(pCache_==NULL)
	{
		pCache_=new CacheManager();
		atexit(destroy);
	}
	return pCache_;
}
void CacheManager::destroy()
{
	if(pCache_!=NULL)
		delete pCache_;
}
void CacheManager::createCache(pthread_t pthID) 
{
	caches_.insert(make_pair(pthID,cache_));
}
Cache &CacheManager::getCache(pthread_t pthID)
{
	map<pthread_t,Cache>::iterator it=caches_.find(pthID);
	return it->second;
}
void CacheManager::initCache()
{
	cache_.readFromFile();
}
void CacheManager::updateCache()
{
	for(auto &elem_cache:caches_)
	{
		cache_.update(elem_cache.second);
	}
	for(auto &elem_cache:caches_)
	{
		elem_cache.second.update(cache_);
	}
	cache_.writeToFile();
	std::cout<<"updateCache success"<<std::endl;	
}
}
