add_library(cpu
    cpu_core.cpp 
    cpu_core.hpp 
    cpu_registers.cpp 
    cpu_registers.hpp
    cpu_state.cpp
    cpu_state.hpp
    instructions/instruction_decoder.cpp
    instructions/instruction_decoder.hpp
    instructions/instruction.cpp
    instructions/instruction.hpp
    reg_16bit.hpp
)

target_link_libraries(cpu ram)