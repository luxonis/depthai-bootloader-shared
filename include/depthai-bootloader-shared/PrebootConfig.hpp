#pragma once

#include <cstdint>
#include <chrono>

namespace dai
{
namespace bootloader
{

struct PrebootConfig {
    /**
     * If timeout < 0 - waits forever
     * if timeout == 0 - no timeout
     * if timeout > 0 - waits timeout milliseconds
     */
    std::int32_t timeoutMs = -1;
};

} // namespace bootloader
} // namespace dai


