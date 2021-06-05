#pragma once
#include "unit.h"

class MethodUnit : public Unit {
public:
    enum Modifier {
        PUBLIC      = 1,
        PROTECTED   = 1 << 1,
        PRIVATE     = 1 << 2,
        STATIC      = 1 << 3,
        CONST       = 1 << 4,
        VIRTUAL     = 1 << 5,
        ABSTRACT    = 1 << 6,
        OVERRIDE    = 1 << 7,
        SEALED      = 1 << 8
    };

public:
    MethodUnit( const std::string& name, const std::string& returnType, Flags flags ) :
        m_name( name ), m_returnType( returnType ), m_flags( flags ) { }

    void add( const std::shared_ptr< Unit >& unit) {
        m_body.push_back( unit );
    }

protected:
    const std::string& getName() const { return m_name; }
    const std::string& getReturnType() const { return m_returnType; }
    Flags getFlags() const { return m_flags; }
    const std::vector< std::shared_ptr< Unit > >& getBody() const { return m_body; }

private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;

    std::vector< std::shared_ptr< Unit > > m_body;
};


class CppMethod : public MethodUnit {
public:
    CppMethod( const std::string& name, const std::string& returnType, Flags flags ) :
        MethodUnit( name, returnType, flags ) { }

    std::string compile( unsigned int level = 0 ) const {
        std::string result = generateShift( level );
        if( getFlags() & STATIC ) {
            result += "static ";
        } else if( getFlags() & VIRTUAL ) {
            result += "virtual ";
        }

        result += getReturnType() + " ";
        result += getName() + "()";

        if( getFlags() & CONST ) {
            result += " const";
        }

        result += " {\n";

        for( const auto& b : getBody() ) {
            result += b->compile( level + 1 );
        }

        result += generateShift( level ) + "}\n";

        return result;
    }
};

class JavaMethod : public MethodUnit {
public:
    JavaMethod( const std::string& name, const std::string& returnType, Flags flags ) :
        MethodUnit( name, returnType, flags ) { }

    std::string compile( unsigned int level = 0 ) const {
        std::string result = generateShift( level );

        // Учитываем флаг модификатора доступа
        if( getFlags() & PUBLIC ) {
            result += "public ";
        } else if( getFlags() & PROTECTED ) {
            result += "protected ";
        } else {
            result += "private ";
        }

        if( getFlags() & STATIC ) {
            result += "static ";
        } else if( !( getFlags() & VIRTUAL ) ) {
            result += "final ";
        }

        result += getReturnType() + " ";
        result += getName() + "()";

        result += " {\n";

        for( const auto& b : getBody() ) {
            result += b->compile( level + 1 );
        }

        result += generateShift( level ) + "}\n";

        return result;
    }
};

class SharpMethod : public MethodUnit
{
public:
    SharpMethod(const std::string& name, const std::string& returnType, Flags flags) : MethodUnit( name, returnType, flags ){ }
    std::string compile(unsigned int level = 0) const {
        std::string result;
        if (getFlags() & STATIC) {
            result += "static ";
        }
        else if (getFlags() & VIRTUAL) {
            result += "virtual ";
        }
        else if (getFlags() & ABSTRACT) {
            result += "abstract ";
        }
        if (getFlags() & OVERRIDE) {
            result += "override ";
        }
        else if (getFlags() & SEALED) {
            result += "sealed ";
        }
        result += getReturnType() + " ";
        result += getName() + "()";
        result += " {\n";
        for (const auto& b : getBody()) {
            result += b->compile(level + 1);
        }
        result += generateShift(level) + "}\n";
        return result;
    }
};

