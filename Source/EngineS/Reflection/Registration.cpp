#include "Reflection/Registration.hpp"
#include "Generated/Refl.hpp"

namespace EngineS::Registration {

void RegisterPrimitiveTypes() {
    Class<void>("void", nullptr);
    Class<int>("int", nullptr);
    Class<bool>("bool", nullptr);
    Class<float>("float", nullptr);
    Class<double>("double", nullptr);
}

void DoRegistration() {
    RegisterPrimitiveTypes();
    RegisterEngineObjects();
}

} // namespace EngineS::Registration