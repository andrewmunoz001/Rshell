#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
using namespace std;
class cmdBase{
    public:
        cmdBase(){}
        virtual ~cmdBase(){};
            
        virtual bool executeCommand() = 0;
};

#endif
