#include <string> /*string*/
#include <iostream> /*cout endl*/
#include <cassert> /*assert*/
#include "macros.h" /*CERR COUT ENDL*/
#include "db.h" /*Sqlite3*/
int main(int c, const char **v) {
	int ret = 0;
	const char *v1 = v[1];
	assert(NULL != v);
	assert(NULL != v[0]);
	if(NULL != v[1]) {
		COUT << "First arg = " << std::string(v1) << ENDL;
		Sqlite3 sqlite3Ob = Sqlite3(v1);
		ret |= sqlite3Ob.lastErr();
		DEBUG1(assert(0 == sqlite3Ob.lastErr());)
	} else {
		assert(NULL == v1);
		CERR << "No arguments passed" << ENDL;
	}
	return ret;
}

