#include <string> /**/
#include <locale> /*isalnum*/
#include <iostream> /*cerr cloga endl*/
#include <cctype> /*isalnum*/
#include <cstdio>
#include <sqlite3.h> /*sqlite3 sqlite3_open sqlite3_close*/
#include "macros.h" /*CERR CLOG ENDL*/
#include "db.h"
//using namespace std;
//	sqlite3 *sqlite3Ptr_ = NULL;
/*
Sqlite3:Sqlite3() {
	this = Sqlite3(":memory");
}
*/
Sqlite3::Sqlite3(const std::string &dbName) : dbName_(dbName) {
	for(auto & ch : dbName) {
		if(!std::isalnum(ch) && '.' != ch) {
			lastErr_ = SQLITE_CANTOPEN;
			CERR << "DB name !(a-zA-Z0-9\\.*): " << dbName << ENDL;
			return;
		}
	}
	lastErr_ = sqlite3_open(dbName.c_str(), &sqlite3Ptr_);
	if(SQLITE_OK != lastErr_) {
		CERR << lastErr_ << " == sqlite3_open(" << dbName << ", ...)" << ENDL;
		if(NULL != sqlite3Ptr_) {
		        CERR << "free(" << sqlite3Ptr_ << ")" << ENDL;
			free(sqlite3Ptr_);
			sqlite3Ptr_ = NULL;
		}
		DEBUG1(CLOG << lastErr_ << " == sqlite3_open(" << dbName << ", ...)" << ENDL;)
	}
}
Sqlite3::~Sqlite3() {
	DEINIT_ASSERT(SQLITE_OK == lastErr_);
/*	if(undefinedBehaviour()) {
		CERR << "~Sqlite3() called after UB! lastErr = " << lastErr_ << ENDL;
	}*/
	DEBUG1(if(lastErr_) {
		CLOG << "~Sqlite3() called when lastErr = " << lastErr_ << ENDL;
	})
	if(NULL != sqlite3Ptr_) {
		lastErr_ = sqlite3_close(sqlite3Ptr_);
		DEINIT_ASSERT(SQLITE_OK == lastErr_);
		DEBUG1(CLOG << lastErr_ << " == sqlite3_close(" << dbName_ << ")" << ENDL;)
	}
}

