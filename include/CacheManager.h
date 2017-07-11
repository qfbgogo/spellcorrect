 ///
 /// @file    CacheManager.h
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-06-03 15:39:01
 ///
#ifndef __CACHEMANAGER_H__
#define __CACHEMANAGER_H__
#include "Cache.h"
#include <pthread.h>
#include <map>
using std::map;
namespace wd
{
class CacheManager
{
	private:
		map<pthread_t,Cache> caches_;
		Cache cache_;
		CacheManager();
		~CacheManager();
	public:
		void createCache(pthread_t);
		Cache &getCache(pthread_t);
		void initCache();
		void updateCache();
		static CacheManager *createCacheManager();
		static void destroy();
		static CacheManager *pCache_;
};
}
#endif
