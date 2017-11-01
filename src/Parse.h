#ifndef PARSE_H
#define PARSE_H
#include <sstream>
#include <string>
#include <vector>

class Parse {
    private:
        vector<char*> argList;
    public:
        Parse();
        Parse(vector<string> &vStr);
};



#endif
