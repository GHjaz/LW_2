#pragma once
#include "unit.h"
#include "classunit.h"
#include "methodunit.h"
#include "printoperatorunit.h"

class IFactory
{
public:
    virtual std::shared_ptr<ClassUnit> createClassUnit(std::string name, ClassUnit::Flags modifier = 0, ClassUnit::Flags access_modifier = 0) = 0;
    virtual std::shared_ptr<MethodUnit> createMethodUnit(std::string name, std::string returnType, MethodUnit::Flags flags) = 0;
    virtual std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(std::string text) = 0;
    virtual ~IFactory() {}
};

class CPPFactory : public IFactory
{
public:
    explicit CPPFactory() {}
    ~CPPFactory() {}
    std::shared_ptr<ClassUnit> createClassUnit(std::string name, ClassUnit::Flags modifier = 0, ClassUnit::Flags access_modifier = 0) {
        return std::make_shared<CClassUnit>(name);
    }
    std::shared_ptr<MethodUnit> createMethodUnit(std::string name, std::string returnType, MethodUnit::Flags flags) {
        return std::make_shared<CMethodUnit>(name, returnType, flags);
    }
    std::shared_ptr<PrintOperatorUnit> createPrintOperatorUnit(std::string text) {
        return std::make_shared<CPrintOperatorUnit>(text);
    }
};

class SharpFactory : public IFactory
{

};

class JAVAFactory : public IFactory
{

};
