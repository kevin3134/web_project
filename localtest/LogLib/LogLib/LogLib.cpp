/* LogLib.cpp ver 1.0
   author: blacksea3

   LogLib.cpp. main interface
*/

//#include "pch.h"
#include "TaskInfo.h"

int main()
{
	TaskInfo* ti = TaskInfo::set_instance();
	ti->set_directory("data.txt");

	//run some mins, every 5s run onetime
	int i = 0;
	while (i++ < 100)
	{
		ti->refresh_tasklist();
		Sleep(5 * 1000); //延时5秒
	}
	ti->self_destroy();
}
