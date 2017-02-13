#ifndef __MYACTOR_H
#define __MYACTOR_H
#include <iostream>

class MyActor {
    protected:

    std::string _name;

    public:

    int _age;

    public:

    MyActor( std::string name, int age ) : _name(name), _age(age)
    {
    }

    void walk() {
    }

    void setName( std::string name )
    {
        _name = name;
    }

    ~MyActor()
    {
    }
};

#endif // __MYACTOR_H
