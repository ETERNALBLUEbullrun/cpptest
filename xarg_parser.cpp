#include <map>
#include <iostream>
#include <string>
#include "macros.h"
#include "xarg_parser.h"
int XargParser::parse(int c, const char **v) {
	int retval = 0;
	std::string vString;
	for(int i = 1; i < c; ++i) {
		XargsEmpty::const_iterator xargEmpty;
		vString = v[i];
		xargEmpty = xargsEmpty_.find(vString);
		if(xargsEmpty_.cend() != xargEmpty) {
			int ret;
			ret = xargEmpty->second();
			DEBUG1(CLOG << ret << " == xargs[\"" + vString + "\"]();" << ENDL;)
			if(0 != ret) {
				++retval;
				CERR << ret << " == xargs[\"" + vString + "\"]();" << ENDL;
			}
			continue;
		}
		DEBUG1(CLOG << "Xargs parsing \"" + vString + "\"";)
		for(int j = 0; ; ++j) {
			if('\0' == vString[j]) {
				DEBUG1(CLOG << " as one whole." << ENDL;)
				break;
			}
			if('=' == vString[j]) {
				const char *xarg2nd = &v[i][1 + j];
				int ret;
				XargsString::const_iterator xargString;
				vString[j] = '\0';
				DEBUG1(CLOG << " \"" + vString + "\" = \"" + xarg2nd + "\"" << ENDL;)
				xargString = xargsString_.find(vString);
				if(xargsString_.cend() != xargString) {
					ret = xargString->second(xarg2nd);
					DEBUG1(CLOG << ret << " == xargs[\"" + vString + "\"](\"" + xarg2nd + "\");" << ENDL;)
					if(0 != ret) {
						++retval;
						CERR << ret << " == xargs[\"" + vString + "\"](\"" + xarg2nd + "\");" << ENDL;
					}
				}
				break;
			}

		}
	}
	return retval;
}

