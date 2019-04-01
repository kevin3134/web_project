/* Log.cpp ver 1.0
   author: blacksea3

   Class: MLog

   need include #include <iostream>
*/

#pragma once

#include <iostream>
#include <fstream>

/*Class Mlog, write log on disk
*/
class Mlog
{
public:
	static Mlog* set_instance();
	void self_destroy();
	void set_directory(const std::string& filename);
	void write_log(const std::string& logdata);

private:
	Mlog(const std::string &name);
	~Mlog();
	static Mlog *_pMlog;

	std::string _filename;
	std::ofstream _file;                //for file operation
};
