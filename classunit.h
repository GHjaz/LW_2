#pragma once

#include "unit.h"
#include "methodunit.h"

class ClassUnit : public Unit {
public:
    enum AccessModifier {
        DEFAULT,
        PUBLIC,
        PROTECTED,
        PRIVATE,
        INTERNAL,
        PROTECTED_PRIVATE,
        PROTECTED_INTERNAL
    };

    static const std::vector< std::string > ACCESS_MODIFIERS;

    using Fields = std::vector< std::shared_ptr< Unit > >;

public:
    explicit ClassUnit( const std::string& name ) : m_name( name ) {
        m_fields.resize( ACCESS_MODIFIERS.size() );
    }

    void add( const std::shared_ptr< Unit >& unit /* flags - больше этот параметр не нужен */) {
        int accessModifier = PRIVATE;
        if( unit->getFlags() & MethodUnit::PUBLIC ) {
            accessModifier = PUBLIC;
        } else if( unit->getFlags() & MethodUnit::PROTECTED ) {
            accessModifier = PROTECTED;
        }

        m_fields[ accessModifier ].push_back( unit );
    }

protected:
    const std::string& getName() const { return m_name; }

    const Fields& getFields( unsigned int accessGroup ) const {
        if( ACCESS_MODIFIERS.size() <= accessGroup ) {
            throw std::out_of_range( "Invalid access group index" );
        }
        return m_fields[ accessGroup ];
    }

private:
    std::string m_name;
    std::vector< Fields > m_fields;

};

class CppClass : public ClassUnit {
public:
    CppClass( const std::string& name ) : ClassUnit( name ) { }

    std::string compile( unsigned int level = 0 ) const {
        std::string result = generateShift( level ) + "class " + getName() + " {\n";
        for( size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i ) {
            if( getFields( i ).empty() ) {
                continue;
            }

            result += ACCESS_MODIFIERS[ i ] + ":\n";
            for( const auto& f : getFields( i ) ) {
                result += f->compile( level + 1 );
            }

            result += "\n";
        }
        result += generateShift( level ) + "};\n";

        return result;
    }
};

class JavaClass : public ClassUnit {
public:
    JavaClass( const std::string& name ) : ClassUnit( name ) { }

    std::string compile( unsigned int level = 0 ) const {
        std::string result = generateShift( level ) + "class " + getName() + " {\n";
        for( size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i ) {
            for( const auto& f : getFields( i ) ) {
                result += f->compile( level + 1 );
                result += "\n";
            }
        }
        result += generateShift( level ) + "}\n";

        return result;
    }
};


class SharpClass : public ClassUnit
{
public:
    SharpClass( const std::string& name ) : ClassUnit( name ) { }
    std::string compile( unsigned int level = 0 ) const {
        std::string result = generateShift( level ) + "class " + getName() + " {\n";
        for( size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i ) {
            for( const auto& f : getFields( i ) ) {
                result += f->compile( level + 1 );
                result += "\n";
            }
        }
        result += generateShift( level ) + "}\n";

        return result;
    }
};
