
#include "Log.h"
#include <iostream>

Mlog::Mlog(const std::string &name)
{
	_name = name;
	std::cout << "This class Mlog, Mlog: object name:" << _name.c_str() << std::endl;
}

Mlog::~Mlog()
{
	std::cout << "This class Mlog, ~Mlog: object name:" << _name.c_str() << std::endl;
}

//我不能找到Instance的函数定义,猜测为
//无输入
//返回Mlog的引用
Mlog* Mlog::Instance()
{
	if (pMlog == NULL)
	{
		pMlog = new Mlog(std::string("111"));
	}
	return pMlog;
}

//debug输出
void Mlog::debug_print()
{
	std::cout << "This class Mlog, debug_print: object name:" << _name.c_str() << std::endl;
}

//销毁
void Mlog::destroy()
{
	if (pMlog != NULL)
	{
		delete pMlog;
		pMlog = NULL;
	}
}

Mlog *Mlog::pMlog = NULL;
