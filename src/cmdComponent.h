#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
using namespace std;
class cmdBase{
    public:
        cmdBase(){}
        virtual ~cmdBase(){};
            
        virtual bool executeCommand(int fdin = 0, int fdout = 1) = 0;
        virtual bool ispipe() = 0;
        virtual string getfile() = 0;
};

#endif
