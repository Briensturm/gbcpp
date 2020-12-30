include_directories(instructions)

add_library(cpu
    cpu_core.cpp 
    cpu_core.hpp 
    cpu_registers.cpp 
    cpu_registers.hpp
    cpu_state.cpp
    cpu_state.hpp
    reg_16bit.hpp
    instructions/instruction_decoder.cpp
    instructions/instruction_decoder.hpp
    instructions/instruction.cpp
    instructions/instruction.hpp
    
    instructions/controlflow/call.hpp
    instructions/bit/bitn_hl_.hpp
    instructions/bit/bitnr8.hpp
    instructions/bit/resn_hl_.hpp
    instructions/bit/resnr8.hpp
    instructions/bit/setn_hl_.hpp
    instructions/bit/setnr8.hpp
    instructions/misc/ccf.hpp
    instructions/misc/cpl.hpp
    instructions/misc/daa.hpp
    instructions/misc/di.hpp
    instructions/misc/ei.hpp
    instructions/misc/halt.hpp
    instructions/misc/nop.hpp
    instructions/misc/pop.hpp
    instructions/misc/prefix.hpp
    instructions/misc/push.hpp
    instructions/misc/scf.hpp
    instructions/misc/stop.hpp
    instructions/rotateshift/rrr8.hpp
)

target_link_libraries(cpu ram)