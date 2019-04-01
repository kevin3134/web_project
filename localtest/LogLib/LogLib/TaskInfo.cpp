/* TaskInfo.cpp ver 1.0
   author: blacksea3

   Class: TaskInfo: deal with task, include outside files: Public.h for MFC import and
   Log.h for writing log
*/

#include "TaskInfo.h"

/* public function, split string with single interval
 * para const string& s, vector<string>& v, const string& c
 * return none
 */ 
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

/*************************************TaskInfo*************************************/
/*
 * TaskInfo* TaskInfo::set_instance  : for single instance design
 * no para
 * return _ptaskinfo = new TaskInfo();
 *
 * use example:
    TaskInfo* ti = TaskInfo::set_instance();
 */
TaskInfo* TaskInfo::set_instance()
{
	if (_ptaskinfo == NULL)
	{
		_ptaskinfo = new TaskInfo();
	}
	else
	{
		std::cout << "TaskInfo instance already ouucrs" << std::endl;
	}
	return _ptaskinfo;
}

/* void TaskInfo::self_destroy() for extern use, interface, destroy single instance of TaskInfo()
    note: You should call this function to destroy single instance of TaskInfo() if don't want to use it!
 * no para
 * retrun void
 *
 * use example:
	TaskInfo* ti = TaskInfo::set_instance();
	BALABALA
	ti->self_destroy();
 */
void TaskInfo::self_destroy()
{
	if (_ptaskinfo != NULL)
	{
		delete _ptaskinfo;
	}
	_ptaskinfo = NULL;
}

/* void TaskInfo::set_directory() for extern use, interface
 * para: filename
 * retrun void
 *
 * use example:
	taskinfo->set_directory("data.txt")
 */
void TaskInfo::set_directory(const std::string & filename)
{
	_filename = filename;
}

/* void TaskInfo::refresh_tasklist() for extern use, interface, refresh tasklist
    note: in this function, I will write infos in txt and/or display in log
 * no para
 * retrun void
 *
 * use example:
	TaskInfo* ti = TaskInfo::Instance();
	ti->refresh_tasklist();
 */
void TaskInfo::refresh_tasklist()
{
	write_string_to_txt(1, "=======", "=======\n");
	outdate_taskinfos();
	get_top_window();
	get_windows();
	remove_outdated_taskinfos();
	write_tasklist_to_txt(1);
}

/* TaskInfo::TaskInfo() init function
 * no para
 */
TaskInfo::TaskInfo()
{
	_mlog = Mlog::set_instance();
	_mlog->set_directory("log.txt");
	_mlog->write_log("TaskInfo created");
	//_p_structtaskinfo = new StructTaskInfo[50];	
	//_taskinfo_loc = 0;
	std::cout << "TaskInfo created" << std::endl;
}

/* TaskInfo::~TaskInfo() del function
 * no para
 */
TaskInfo::~TaskInfo()
{
	_mlog->self_destroy();
	//delete[] _p_structtaskinfo;
	std::cout << "TaskInfo deleted" << std::endl;
}

/* void TaskInfo::outdate_taskinfos() make StructTaskTimes.isupdated = false
 * no para
 * retrun void
 */
void TaskInfo::outdate_taskinfos()
{
	std::unordered_map<std::string, StructTaskTimes>::iterator it;
	it = _taskinfos.begin();
	
	StructTaskTimes taskinfo_value;

	while (it != _taskinfos.end())
	{
		taskinfo_value = it->second;
		taskinfo_value.isupdated = false;
		_taskinfos[it->first] = taskinfo_value;
		it++;
	}
}

/* void TaskInfo::update_taskinfos() operate structtaskinfo storation in object itself
 * para:const CString& classname, const CString& windowtext,
	const CString& processname, int type
 * retrun void
 */
void TaskInfo::update_taskinfos(const CString & classname, const CString & windowtext, 
	const CString & processname, const int & type)
{
	std::string str_classname = classname.GetString();
	std::string str_windowtext = windowtext.GetString();
	std::string str_processname = processname.GetString();
	std::string str_type = std::to_string(type);

	

	std::string str_taskinfokey = str_classname + INTERVAL + str_windowtext + INTERVAL +
		str_processname + INTERVAL + str_type;

	std::unordered_map<std::string, StructTaskTimes>::iterator it;
	it = _taskinfos.find(str_taskinfokey);

	if (it == _taskinfos.end()) {
		time_t t = time(NULL);
		StructTaskTimes stt;
		stt.present_time = t;
		stt.start_time = t;
		stt.running_time = stt.start_time - stt.present_time;
		stt.isupdated = true;
		_taskinfos.insert(std::pair<std::string, StructTaskTimes>(str_taskinfokey, stt));
		_mlog->write_log("add new key info:" + str_classname + str_windowtext + str_processname + str_type);
	}
	else {
		time_t t = time(NULL);
		StructTaskTimes stt = it->second;
		time_t start_time = stt.start_time;
		stt.present_time = t;
		stt.running_time = stt.present_time - stt.start_time;
		stt.isupdated = true;
		_taskinfos[str_taskinfokey] = stt;
		_mlog->write_log("update key info:" + str_classname + str_windowtext + str_processname + str_type);
	}
}

/* void TaskInfo::remove_outdated_taskinfos() remove taskinfo with StructTaskTimes.isupdated == false
 * no para
 * retrun void
 */
void TaskInfo::remove_outdated_taskinfos()
{
	std::unordered_map<std::string, StructTaskTimes>::iterator it;
	it = _taskinfos.begin();

	std::string taskinfo_key;
	StructTaskTimes taskinfo_value;

	while (it != _taskinfos.end())
	{
		taskinfo_key = it->first;
		taskinfo_value = it->second;
		if (taskinfo_value.isupdated == false)
		{
			_taskinfos.erase(it++);    //note: must it = it +1 before erase it!, so I use it++
		}
		else
		{
			it++;
		}
	}
}

/* void TaskInfo::get_top_window() this function will call append_structtaskinfo()
 * no para
 * retrun void
 */
void TaskInfo::get_top_window()
{
	//get window
	HWND tophwnd;
	tophwnd = GetForegroundWindow();
	CString strTopClassName = _T("");
	GetClassName(tophwnd, strTopClassName.GetBuffer(256), 256);
	CString strTopWindowText = _T("");
	GetWindowText(tophwnd, strTopWindowText.GetBuffer(256), 256);

	//get process
	DWORD dwProcessID;
	DWORD dwXianChenID;
	dwXianChenID = GetWindowThreadProcessId(tophwnd, &dwProcessID);
	CString processName;
	get_process_name(processName, dwProcessID);

	//add window infos in structtaskinfo in object itself
	update_taskinfos(strTopClassName, strTopWindowText, processName, 0);
}

/* void TaskInfo::get_windows() this function will call append_structtaskinfo()
    note: get all windows, not just topwindow
 * no para
 * retrun void
 */
void TaskInfo::get_windows()
{
	//get desktop window
	CWnd* pDesktopWnd = CWnd::GetDesktopWindow();
	//get a son window
	CWnd* pWnd = pDesktopWnd->GetWindow(GW_CHILD);

	HWND hwnd;
	//get all son windows of desktop window iteraly
	while (pWnd != NULL)
	{
		hwnd = pWnd->GetSafeHwnd();

		//Shell_TrayWnd 任务栏本身
		//Progman 桌面
		if (!GetWindow(hwnd, GW_OWNER) && IsWindowVisible(hwnd))
		{
			CString strClassName = _T("");
			GetClassName(hwnd, strClassName.GetBuffer(256), 256);
			CString strWindowText = _T("");
			GetWindowText(hwnd, strWindowText.GetBuffer(256), 256);

			strClassName.ReleaseBuffer();
			strWindowText.ReleaseBuffer();

			//get procss
			DWORD dwProcessID;
			DWORD dwXianChenID;
			dwXianChenID = GetWindowThreadProcessId(hwnd, &dwProcessID);

			CString processName;

			get_process_name(processName, dwProcessID);

			//add window infos in structtaskinfo in object itself
			update_taskinfos(strClassName, strWindowText, processName, 1);
		}
		//get another sonwindow
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
}

/* void TaskInfo::get_process_name()
 * para: CString& nProcessName, const DWORD& nPid
 * retrun void
 */
void TaskInfo::get_process_name(CString& nProcessName, const DWORD& nPid)
{
	PROCESSENTRY32 nPT;
	nPT.dwSize = sizeof(nPT);
	HANDLE nSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	BOOL nRet = Process32First(nSnapShot, &nPT);
	while (nRet)
	{
		if (nPid == nPT.th32ProcessID)
		{
			nProcessName = nPT.szExeFile;
			return;
		}
		nRet = Process32Next(nSnapShot, &nPT);
	}
}

/* void TaskInfo::write_tasklist_to_txt() this function will call wtire_string_to_txt()
 * para type: 0 all information, 1: useful information(remove some dump infos)
 * retrun void
 */
void TaskInfo::write_tasklist_to_txt(const int& type)
{
	std::unordered_map<std::string, StructTaskTimes>::iterator it;
	it = _taskinfos.begin();

	StructTaskTimes taskinfo_value;
	std::string str_classname;
	std::string str_windowtext;
	std::string str_processname;
	std::string str_type;
	time_t start_time;
	time_t running_time;
	time_t present_time;
	char str_start_time[32];
	char str_running_time[32];
	char str_present_time[32];

	while (it != _taskinfos.end())
	{
		std::vector<std::string> res;
		SplitString(it->first, res, INTERVAL); //可按多个字符来分隔;
		if(res.size()!=4)
		{
			throw "write_tasklist_to_txt ERROR";
		}
		str_classname = res[0];
		str_windowtext = res[1];
		str_processname = res[2];
		str_type = res[3];

		taskinfo_value = it->second;
		start_time = taskinfo_value.start_time;
		running_time = taskinfo_value.running_time;
		present_time = taskinfo_value.present_time;

		it++;
		if (type == 1) //useful information
		{
			//if useless information, continue this iteration
			if ((str_processname.compare("SynTPEnh.exe") == 0) ||   //小新V1000触摸板...
				(
				(str_processname.compare("explorer.exe") == 0) && //explorer.exe some fucking things
					(
					(str_classname.compare("Shell_TrayWnd") == 0) ||
						(str_classname.compare("Shell_SecondaryTrayWnd") == 0) ||
						(str_classname.compare("ApplicationFrameWindow") == 0) ||
						(str_classname.compare("EdgeUiInputTopWndClass") == 0) ||
						(str_classname.compare("DummyDWMListenerWindow") == 0) ||
						(str_classname.compare("Progman") == 0)
						)
					) ||
					(str_processname.compare("SystemSettings.exe") == 0) ||
				(str_processname.compare("ApplicationFrameHost.exe") == 0) ||
				(str_processname.compare("newssvc.exe") == 0) ||
				(
				(str_processname.compare("MicrosoftEdgeCP.exe") == 0) &&
					(str_classname.compare("Windows.UI.Core.CoreWindow") == 0)
					) ||
					(
				(str_processname.compare("MicrosoftEdge.exe") == 0) &&
						(str_classname.compare("Windows.UI.Core.CoreWindow") == 0)
						)
				)
				continue;
		}
		write_string_to_txt(1, "ClassName:", str_classname + "\n");
		write_string_to_txt(1, "WindowText:", str_windowtext + "\n");
		write_string_to_txt(1, "ProcessName:", str_processname + "\n");
		if (str_type.compare("0")) write_string_to_txt(1, "type:", "topWindow\n");
		else write_string_to_txt(1, "type:", "common\n");

		//the fucking get time procedure!
		struct tm newtime;
		errno_t errNum;

		const time_t cstart_time = start_time;
		errNum = _gmtime64_s(&newtime, &cstart_time);
		if (errNum)
		{
			printf("Invalid Argument to _gmtime64_s.");
			throw "write_tasklist_to_txt";
		}
		errNum = asctime_s(str_start_time, 32, &newtime);
		if (errNum)
		{
			printf("Error code: %d", (int)errNum);
			throw "write_tasklist_to_txt";
		}

		const time_t crunning_time = running_time;
		errNum = _gmtime64_s(&newtime, &crunning_time);
		if (errNum)
		{
			printf("Invalid Argument to _gmtime64_s.");
			throw "write_tasklist_to_txt";
		}
		errNum = asctime_s(str_running_time, 32, &newtime);
		if (errNum)
		{
			printf("Error code: %d", (int)errNum);
			throw "write_tasklist_to_txt";
		}

		const time_t cpresent_time = present_time;
		errNum = _gmtime64_s(&newtime, &cpresent_time);
		if (errNum)
		{
			printf("Invalid Argument to _gmtime64_s.");
			throw "write_tasklist_to_txt";
		}

		errNum = asctime_s(str_present_time, 32, &newtime);
		if (errNum)
		{
			printf("Error code: %d", (int)errNum);
			throw "write_tasklist_to_txt";
		}

		write_string_to_txt(1, "StartTime:", str_start_time);
		write_string_to_txt(1, "RunningTime:", str_running_time);
		write_string_to_txt(1, "PresentTime:", str_present_time);	
	}
}

/* void TaskInfo::write_string_to_txt() this function will call wtire_string_to_txt()
 * para type: 0:cmd display, 1:txt
 * retrun void
 */
void TaskInfo::write_string_to_txt(const int& printtype, const std::string& inputpre, const std::string& inputstr)
{
	char* char_inputpre = (char*)inputpre.c_str();
	char* char_inputstr = (char*)inputstr.c_str();

	if( printtype == 0) std::cout << char_inputpre << char_inputstr << std::endl;
	else
	{
		_file.open(_filename, std::ios_base::out | std::ios_base::app);
		_file << char_inputpre << char_inputstr;
		_file.close();
	}
}

TaskInfo* TaskInfo::_ptaskinfo = NULL;       //static TaskInfo* TaskInfo::_ptaskinfo init
char TaskInfo::INTERVAL[1] = { 1 };          //static char TaskInfo::INTERVAL[1] init
/*********************************End TaskInfo*************************************/
