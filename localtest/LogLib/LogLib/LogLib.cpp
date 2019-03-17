// LogLib.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include "pch.h"

#include "Log.h"
#include "TaskInfo.h"

void test1()
{
	Mlog* m1 = Mlog::Instance();
	m1->debug_print();
	m1->destroy();

	//int* a = new int[5];
	//delete a;

	//Mlog* pm1 = &m1;
	//delete m1;
	std::cout << "After delete Mlog object" << std::endl;
}

int main()
{
	TaskInfo* ti = TaskInfo::Instance();
	ti->refresh_tasklist();
	ti->self_destroy();
}
