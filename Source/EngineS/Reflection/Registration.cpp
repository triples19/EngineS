#include "Reflection/Registration.hpp"

namespace EngineS::Registration {

void RegisterPrimitiveTypes() {
#define REG(name) Class<name>(#name)
    REG(void);

    REG(signed char);
    REG(unsigned char);
    REG(short int);
    REG(unsigned short int);
    REG(int);
    REG(long int);
    REG(unsigned long int);
    REG(long long int);
    REG(unsigned long long int);

    REG(bool);

    REG(float);
    REG(double);
    REG(long double);
#undef REG
}

void DoRegistration() {
    RegisterPrimitiveTypes();

    Class<VariantVector>("EngineS::VariantVector");
    Class<VariantMap>("EngineS::VariantMap");
}

} // namespace EngineS::Registration