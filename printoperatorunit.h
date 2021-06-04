#pragma once
#include "unit.h"

class PrintOperatorUnit : public Unit
{
public:

    virtual std::string compile(unsigned int level = 0) const = 0;

};

class CPrintOperatorUnit : public PrintOperatorUnit
{
public:
    explicit CPrintOperatorUnit(const std::string &text) : m_text(text) { }
    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "printf( \"" + m_text + "\" );\n";
    }
private:
    std::string m_text;
};

class SPrintOperatorUnit : public PrintOperatorUnit
{
public:
    explicit SPrintOperatorUnit(const std::string &text) : m_text(text) { }
    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "Console.WriteLine( \"" + m_text + "\" );\n";
    }
private:
    std::string m_text;
};
