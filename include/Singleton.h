 ///
 /// @file    template_singleton.cc
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-04-23 11:20:13
 ///
#ifndef __SINGLETON_H__
#define __SINGLETON_H__
namespace wd
{
template<typename T>
class Singleton
{
	public:
		static T *getinstance()
		{
			if(_psingleton==NULL)
			{
				_psingleton=new T;
				atexit(destroy);
			}
			return _psingleton;
		}
		static void destroy()
		{
			if(_psingleton)
				delete _psingleton;
		}
	private:
		static T *_psingleton;
		Singleton(){};
		~Singleton(){};
};
template<typename T>
T *Singleton<T>::_psingleton=getinstance();
}
#endif
