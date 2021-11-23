#include <string> /*string*/
#include <iostream> /*cout endl*/
#include <cassert> /*assert*/
#include "macros.h" /*CERR COUT ENDL*/
#include "db.h" /*Sqlite3*/
#include "xarg_parser.h" /*XargsParser*/
int verboseMode = 0;
int inMemoryMode = 0;
int xargs_v() {
	COUT << "Verbose mode set.";
	verboseMode = 1;
	return 0;
}
int xargs_in_memory() {
	COUT << "In-memory mode set.";
	inMemoryMode = 1;
	return 0;
}
int main(int c, const char **v) {
	int ret = 0;
	XargParser xargParser;
	const char *v1 = v[1];
	ret |= xargParser.push_back("-v", xargs_v);
	ret |= xargParser.push_back("-in-memory", xargs_in_memory);
	ret |= xargParser.parse(c, v);
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

