/* TaskInfo.h ver 1.0
   author: blacksea3

   Class: TaskInfo: deal with task, include outside files: Public.h for MFC import and
   Log.h for writing log
*/
#pragma once

#include "Public.h"
#include "Log.h"
#include <unordered_map>

//describe Single task time storation
struct StructTaskTimes
{
	time_t start_time;       // is a timestamp from 1970.1.1 00:00:00
	time_t present_time;     // is a timestamp from 1970.1.1 00:00:00
	time_t running_time;     // running_time = present_time - start_time
	bool isupdated;          // isupdated in all times, false:not(then will be removed) true:is
};

/*Class TaskInfo, need include struct StructTaskInfo, MFC and Class Log supporting
  deal with task
*/
class TaskInfo
{
public:
	static TaskInfo* set_instance();     // for single instance design

	void self_destroy();                 // for extern use, interface
	void set_directory(const std::string& filename);
	void refresh_tasklist();             // for extern use, interface
private:
	TaskInfo();
	~TaskInfo();

	void outdate_taskinfos();            // make StructTaskTimes.isupdated = false
	void update_taskinfos(const CString & classname, const CString & windowtext,
		const CString & processname, const int& type);
	void remove_outdated_taskinfos();    // remove taskinfo with StructTaskTimes.isupdated == false

	void get_top_window();
	void get_windows();
	void get_process_name(CString& nProcessName, const DWORD& nPid);

	void write_tasklist_to_txt(const int& type);
	void write_string_to_txt(const int& printtype, const std::string& inputpre, const std::string& inputstr);
	
	static TaskInfo* _ptaskinfo;        // for single instance design
	Mlog* _mlog;                        // for Mlog Class use, point to Mlog instance

	static char INTERVAL[1];
	std::unordered_map<std::string, StructTaskTimes> _taskinfos;   //unordered_map
	//note _taskinfos use classname + (char)1->string + windowtext + (char)1->string
	// + processname + (char)1->string + type

	std::string _filename;
	std::ofstream _file;                //for file operation
};
