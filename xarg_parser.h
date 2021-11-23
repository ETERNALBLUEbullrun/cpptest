#ifndef __XARG_PARSER_H
#define __XARG_PARSER_H
#include <map>
#include <utility> /*make_pair*/
#include <string>
typedef int(*XargEmpty)();
typedef int(*XargInt)(int);
typedef int(*XargBool)(bool);
typedef int(*XargString)(std::string);
typedef std::map<const std::string, XargEmpty> XargsEmpty;
typedef std::map<const std::string, XargInt> XargsInt;
typedef std::map<const std::string, XargBool> XargsBool;
typedef std::map<const std::string, XargString> XargsString;
/*typedef std::pair<const std::string, XargEmpty> std::make_pair;
typedef std::pair<const std::string, XargInt> std::make_pair;
typedef std::pair<const std::string, XargBool> std::make_pair;
typedef std::pair<const std::string, XargString> std::make_pair;
*/
class XargParser {
	XargsEmpty xargsEmpty_;
	XargsInt xargsInt_;
	XargsBool xargsBool_;
	XargsString xargsString_;
	public:
	int push_back(std::string arg, XargEmpty func) {return !xargsEmpty_.insert(std::make_pair(arg, func)).second;}
	int push_back(std::string arg, XargInt func) {return !xargsInt_.insert(std::make_pair(arg, func)).second;}
	int push_back(std::string arg, XargBool func) {return !xargsBool_.insert(std::make_pair(arg, func)).second;}
	int push_back(std::string arg, XargString func) {return !xargsString_.insert(std::make_pair(arg, func)).second;}
	int parse(int c, const char **v);
};
#endif

