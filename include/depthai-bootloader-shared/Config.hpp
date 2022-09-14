#pragma once

#include "Memory.hpp"

// std
#include <array>
#include <chrono>
#include <cstdint>

// libraries
#include "NlohmannJsonCompat.hpp"

#define DEPTHAI_BOOTLOADER_NLOHMANN_JSON_OPTIONAL_TO(v1) nlohmann::to_json(nlohmann_json_j[#v1], nlohmann_json_t.v1);
#define DEPTHAI_BOOTLOADER_NLOHMANN_JSON_OPTIONAL_FROM(v1) if(nlohmann_json_j.contains(#v1)) nlohmann_json_j[#v1].get_to(nlohmann_json_t.v1);

#define DEPTHAI_BOOTLOADER_NLOHMANN_DEFINE_TYPE_OPTIONAL_NON_INTRUSIVE(Type, ...)  \
    inline void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) { DEPTHAI_BOOTLOADER_NLOHMANN_JSON_EXPAND(DEPTHAI_BOOTLOADER_NLOHMANN_JSON_PASTE(DEPTHAI_BOOTLOADER_NLOHMANN_JSON_OPTIONAL_TO, __VA_ARGS__)) } \
    inline void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { DEPTHAI_BOOTLOADER_NLOHMANN_JSON_EXPAND(DEPTHAI_BOOTLOADER_NLOHMANN_JSON_PASTE(DEPTHAI_BOOTLOADER_NLOHMANN_JSON_OPTIONAL_FROM, __VA_ARGS__)) }

namespace dai
{
namespace bootloader
{


// Config
struct NetworkConfig {
    /**
     * If timeout < 0 - waits forever
     * if timeout == 0 - no timeout
     * if timeout > 0 - waits timeout milliseconds
     */
    int timeoutMs = 30000;
    // Network configuration options
    // IPv4
    std::uint32_t ipv4 = 0;
    std::uint32_t ipv4Mask = 0;
    std::uint32_t ipv4Gateway = 0;
    std::uint32_t ipv4Dns = 0;
    std::uint32_t ipv4DnsAlt = 0;
    bool staticIpv4 = false;
    // TODO(themarpe) - IPv6
    std::array<uint32_t, 4> ipv6 = {};
    std::uint32_t ipv6Prefix = 0;
    std::array<uint32_t, 4> ipv6Gateway = {};
    std::array<uint32_t, 4> ipv6Dns = {};
    std::array<uint32_t, 4> ipv6DnsAlt = {};
    bool staticIpv6 = false;
    // MAC address - if not flashed, overwrites autogenerated one
    std::array<uint8_t, 6> mac = {};
};
DEPTHAI_BOOTLOADER_NLOHMANN_DEFINE_TYPE_OPTIONAL_NON_INTRUSIVE(NetworkConfig, timeoutMs, ipv4, ipv4Mask, ipv4Gateway, ipv4Dns, ipv4DnsAlt, staticIpv4, ipv6, ipv6Prefix, ipv6Gateway, ipv6Dns, ipv6DnsAlt, staticIpv6, mac);

// Config
struct UsbConfig {
    /**
     * If timeout < 0 - waits forever
     * if timeout == 0 - no timeout
     * if timeout > 0 - waits timeout milliseconds
     */
    int timeoutMs = 3000;

    /**
     * UNKNOWN = 0, LOW, FULL, HIGH, SUPER, SUPER_PLUS
     */
    int maxUsbSpeed = 3;

    /// VID/PID pair used by bootloader
    uint16_t vid = 0x03E7, pid = 0xF63C;
};
DEPTHAI_BOOTLOADER_NLOHMANN_DEFINE_TYPE_OPTIONAL_NON_INTRUSIVE(UsbConfig, timeoutMs, maxUsbSpeed, vid, pid);

struct Config {
    Memory appMem = Memory::AUTO;
    UsbConfig usb;
    NetworkConfig network;
    uint32_t userBlSize = 0;
    uint32_t userBlChecksum = 0;
};
DEPTHAI_BOOTLOADER_NLOHMANN_DEFINE_TYPE_OPTIONAL_NON_INTRUSIVE(Config, appMem, usb, network);

} // namespace bootloader
} // namespace dai

