#ifndef COMPONENT_H
#define COMPONENT_H

class cmdBase{
    public:
        cmdBase(){}
        virtual bool executeCommand() = 0;
};

#endif
