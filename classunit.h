#pragma once

#include "unit.h"

class ClassUnit : public Unit
{
public:
    virtual void add(const std::shared_ptr< Unit > &unit, Flags flags) = 0;
    virtual std::string compile(unsigned int level = 0) const = 0;
protected:
    std::string m_name;
    using Fields = std::vector< std::shared_ptr< Unit >>;
    std::vector< Fields > m_fields;
};

class CClassUnit : public ClassUnit
{
public:
    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };
    static const std::vector< std::string > ACCESS_MODIFIERS;
public:

    explicit CClassUnit(const std::string &name) : m_name(name) {
        m_fields.resize(ACCESS_MODIFIERS.size());
    }
    void add(const std::shared_ptr< Unit > &unit, Flags flags) {
        int accessModifier = PRIVATE;
        if (flags < ACCESS_MODIFIERS.size()) {
            accessModifier = flags;
        }
        m_fields[accessModifier].push_back(unit);
    }
    std::string compile(unsigned int level = 0) const {
        std::string result = generateShift(level) + "class " + m_name
                + " \n{\n";
        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (m_fields[i].empty()) {
                continue;
            }
            result += ACCESS_MODIFIERS[i] + ":\n";
            for (const auto &f : m_fields[i]) {
                result += f->compile(level + 1);
            }
            result += "\n";
        }
        result += generateShift(level) + "};\n";
        return result;
    }
private:
    std::string m_name;
    using Fields = std::vector< std::shared_ptr< Unit >>;
    std::vector< Fields > m_fields;
};

class SClassUnit : public ClassUnit
{
public:
    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE,
        INTERNAl,
        ABSTRACT,
        INTERFACE
    };
    static const std::vector< std::string > ACCESS_MODIFIERS;
public:

    explicit SClassUnit(const std::string &name) : m_name(name) {
        m_fields.resize(ACCESS_MODIFIERS.size());
    }
    void add(const std::shared_ptr< Unit > &unit, Flags flags) {
        int accessModifier = PRIVATE;
        if (flags < ACCESS_MODIFIERS.size()) {
            accessModifier = flags;
        }
        m_fields[accessModifier].push_back(unit);
    }
    std::string compile(unsigned int level = 0) const {
        std::string result = generateShift(level) + "class " + m_name
                + " \n{\n";
        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (m_fields[i].empty()) {
                continue;
            }

            for (const auto &f : m_fields[i]) {
                result += generateShift(level + 1) + ACCESS_MODIFIERS[i];
                result += f->compile(level + 1);
                result += "\n";
            }

        }
        result += generateShift(level) + "};\n";
        return result;
    }
private:
    std::string m_name;
    using Fields = std::vector< std::shared_ptr< Unit >>;
    std::vector< Fields > m_fields;
};
