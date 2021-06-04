#pragma once


#include "factory.h"

class CodeGenerator
{
private:
    IFactory* p;
public:
    CodeGenerator(IFactory* factory) : p(factory) {}
    std::string generateProgram() {
        auto myclass = p->createClassUnit("MyClass", 0, CClassUnit::PUBLIC);

        auto methodUnit1 = p->createMethodUnit("testFunc1", "void", 0);
        myclass->add(methodUnit1, CClassUnit::PUBLIC);

        auto methodUnit2 = p->createMethodUnit("testFunc2", "void", CMethodUnit::STATIC);
        myclass->add(methodUnit2, CClassUnit::PRIVATE);

        auto methodUnit3 = p->createMethodUnit("testFunc3", "void", CMethodUnit::VIRTUAL | CMethodUnit::CONST);
        myclass->add(methodUnit3, CClassUnit::PUBLIC);

        auto methodUnit4 = p->createMethodUnit("testFunc4", "void", CMethodUnit::STATIC);
        auto printUnit = p->createPrintOperatorUnit(R"(Hello, World!\n)");

        methodUnit4->add(printUnit);

        myclass->add(methodUnit4, CClassUnit::PROTECTED);

        return myclass->compile();
    }
};
