#pragma once
#include "unit.h"

class PrintOperatorUnit : public Unit {
public:
    explicit PrintOperatorUnit( const std::string& text ) : m_text( text ) { }

protected:
    const std::string& getText() const { return m_text; }

private:
    std::string m_text;
};

class CppPrintOperator : public PrintOperatorUnit {
public:
    CppPrintOperator( const std::string& text ) : PrintOperatorUnit( text ) { }

    std::string compile( unsigned int level = 0 ) const {
        return generateShift( level ) + "printf( \"" + getText() + "\" );\n";
    }
};

class JavaPrintOperator : public PrintOperatorUnit {
public:
    JavaPrintOperator( const std::string& text ) : PrintOperatorUnit( text ) { }

    std::string compile( unsigned int level = 0 ) const {
        return generateShift( level ) + "System.out.print( \"" + getText() + "\" );\n";
    }
};

class SharpPrintOperator : public PrintOperatorUnit {

public:
    SharpPrintOperator(const std::string& text) : PrintOperatorUnit( text ) { }
    std::string compile(unsigned int level = 0) const {
        return generateShift(level) + "Console.WriteLine(\"" + getText() + "\");\n";
    }
};
