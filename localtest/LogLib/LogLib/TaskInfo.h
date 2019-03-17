#pragma once

#include "Public.h"

struct StructTaskInfo
{
	CString classname;
	CString windowtext;
	CString processname;
	int type;
};

class TaskInfo
{
public:
	static TaskInfo* Instance();
	void debug_print();
	void self_destroy();
	void refresh_tasklist();
private:
	TaskInfo();
	~TaskInfo();

	void get_top_window();
	void get_windows();
	void print_tasklist(const int& type);
	
	void append_structtaskinfo(const CString & classname, const CString & windowtext, 
		const CString & processname, int type);

	void print_chinese(const int& printtype, const CString& inputpre, const CString& inputstr);
	void get_process_name(CString& nProcessName, const DWORD& nPid);

	static TaskInfo* _ptaskinfo;
	StructTaskInfo* _p_structtaskinfo;
	int _taskinfo_loc;

	static int _MAX_TASKINFO_LENGTH;
	
	std::ofstream _file;
};
