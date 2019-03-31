/* Log.cpp ver 1.0
   author: blacksea3

   Class: Log
*/

#include "Log.h"

/*************************************MLog*************************************/
/*
 * Mlog* Mlog::set_instance  : for single instance design
 * no para
 * return pMlog = new Mlog();
 *
 * use example:
	Mlog* ti = Mlog::set_instance();
 */
Mlog* Mlog::set_instance()
{
	if (_pMlog == NULL)
	{
		_pMlog = new Mlog(std::string("111"));
	}
	return _pMlog;
}

Mlog::Mlog(const std::string &name)
{
	std::cout << "Mlog created" << std::endl;
}

Mlog::~Mlog()
{
	std::cout << "Mlog destoryed"<< std::endl;
}

/* void Mlog::self_destroy() for extern use, interface, destroy single instance of Mlog()
	note: You should call this function to destroy single instance of Mlog() if don't want to use it!
 * no para
 * retrun void
 *
 * use example:
	Mlog* ti = Mlog::set_instance();
	BALABALA
	ti->self_destroy();
 */
void Mlog::self_destroy()
{
	if (_pMlog != NULL)
	{
		delete _pMlog;
		_pMlog = NULL;
	}
}

/* void Mlog::set_directory() for extern use, interface
 * para: filename
 * retrun void
 *
 * use example:
	mlog->set_directory("log.txt")
 */
void Mlog::set_directory(const std::string& filename)
{
	_filename = filename;
}

/* void Mlog::write_log() for extern use, interface
     note:I will automatically write down __FILE__, __LINE__, __FUNCTION__, 
	 and \n will also be automatically written
 * para: string
 * retrun void
 *
 * use example:
	mlog->write_log("HELLO WORLD\n")
 */
void Mlog::write_log(const std::string& logdata)
{
	_file.open(_filename, std::ios_base::out | std::ios_base::app);
	char* char_logdata = (char*)logdata.c_str();
	_file << "In file:"<< __FILE__ << " line:" << __LINE__ << " function:" << __FUNCTION__ << "  " << char_logdata << "\n";
	_file.close();
}

Mlog *Mlog::_pMlog = NULL; //static Mlog* Mlog::pMlog init
