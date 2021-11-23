#ifndef __DB_H
#define __DB_H
enum UbStatus {
	UB_OCCURED 		= 1 << 0,
	UB_LIKELY_IF_WRITE	= 1 << 1,
	UB_LIKELY_IF_READ	= 1 << 2
};
#ifdef __cplusplus
#include <string>
#include <iostream>
#include <cstdio>
class sqlite3;//#include "sqlite3.h"
#include "macros.h"
//using namespace std;
class Sqlite3 {
	private:
	sqlite3 *sqlite3Ptr_ = NULL;
	int lastErr_ = 0;
	const std::string &dbName_;
	public:
	int lastErr() {return lastErr_;}	//Last error number

	int undefinedBehaviour();		//Has UB occured
	Sqlite3(const std::string &dbName = ":memory");	//const ref can have default
	~Sqlite3();
};
#else //__cplusplus
struct Sqlite {
	struct Sqlite3 *sqlite3Ptr_;
	const char *lastErr_;
	const char *dbName_;
}
struct Sqlite *sqliteInit(struct Sqlite *, const char *);
#endif //__cplusplus
#endif

