#pragma once
#include "utility.h"

#define max_log_len  1024 * 8

class log{

private:
	log();
	log(const log &);  
    log & operator = (const log &);
	
public:
	static log * instance();
	virtual~ log();
	int init(const char* path, const char * prefix, 
	int max_size = 8<<20, bool immediate_flush = true); 
	
	int write_log(const char * msg);
	int close_log();

protected:
	int run();
	int open_log();
	int write_log(const char * msg, int len);
	static void * log_task(void * param);

private:
	FILE * m_file;
	char m_pathname[max_path_len];
	char m_filename[max_path_len];
	int m_max_size;

	struct tm m_logbegin;
	struct tm m_logend;

	ring_buffer m_ring_buf;
	auto_mutex m_task_mutex;
	auto_mutex m_w_mutex;
	bool m_brun;
	bool m_immediate_flush;
};

