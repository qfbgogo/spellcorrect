 ///
 /// @file    MyResult.h
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-28 16:23:34
 ///
#ifndef __RESULT_H__
#define __RESULT_H__

#include <string>
namespace wd
{
struct MyResult
{
	std::string candidate_word_;
	int frequence_;
	int distance_;
};
struct MyCompare
{
	bool operator()(const MyResult &lhs,const MyResult &rhs)
	{
		if(lhs.distance_>rhs.distance_)
		{
			return true;
		}
		else if(lhs.distance_==rhs.distance_)
		{
			if(lhs.frequence_<rhs.frequence_)
				return true;
			else if(lhs.frequence_==rhs.frequence_&&lhs.candidate_word_.compare(rhs.candidate_word_)>0)
				return true;
			else
				return false;
		}else{
			return false;
		}
	}
};
}
#endif
