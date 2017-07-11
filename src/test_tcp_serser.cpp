#include "TimerThread.h"
#include "SpellcorrectServer.h"
#include "CacheManager.h"
#include <functional>
using namespace wd;
int main(int argc, char const *argv[])
{
	CacheManager *pCache=CacheManager::createCacheManager();
	TimerThread update_cache(60,180,std::bind(&CacheManager::updateCache,pCache));
	update_cache.start();
	
	SpellcorrectServer server;
	server.start();
	return 0;

}
