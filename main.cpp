#include "unit.h"
#include "codegen.h"

int main(int argc, char *argv[])
{
    IFactory *icd = new CPPFactory();
    CodeGenerator* cd = new CodeGenerator(icd);
    std::cout << cd->generateProgram() << std::endl;
    delete icd;
    delete cd;
    return 0;
}
