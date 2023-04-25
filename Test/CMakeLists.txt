set(SOURCES
        main.cpp
        Reflection/Constructors.cpp
        Reflection/Enum.cpp
        Reflection/Fields.cpp
        Reflection/Instance.cpp
        Reflection/Methods.cpp
        Reflection/Type.cpp
        Reflection/Variant.cpp
        Container/String.cpp)

add_executable(EngineS-Test ${SOURCES})
target_link_libraries(EngineS-Test PRIVATE EngineS Catch2::Catch2)
