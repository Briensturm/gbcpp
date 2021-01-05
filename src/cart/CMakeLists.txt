include_directories(mbc)

add_library(cart
    ram_loader.hpp
    rom_loader.hpp
    mbc/mbc_factory.hpp
    mbc/mbc_factory.cpp
    mbc/mbc.hpp
    mbc/mbc0.hpp
)

target_link_libraries(cart ram)