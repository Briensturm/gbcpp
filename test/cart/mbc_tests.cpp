#include "test.hpp"

#include <vector>
#include <memory>

#include "gbcpp.hpp"
#include "cart/mbc/mbc0.hpp"

TEST_FIXTURE_BEGIN("MBC_Tests")
{
    TEST("Creating_an_MBC0_does_not_throw_an_exception")
    {
        auto rom = std::vector<byte>();
        rom.resize(0x0150);

        rom[0x0149] = 0x00;
        rom[0x0148] = 0x00;
        rom[0x0147] = 0x00;

        ASSERT_DOES_NOT_THROW([&rom](){ auto mbc0 = std::make_shared<MBC0>(rom); });
    }
}
TEST_FIXTURE_END