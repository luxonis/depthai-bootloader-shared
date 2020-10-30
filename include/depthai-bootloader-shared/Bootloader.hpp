#pragma once

namespace dai
{
namespace bootloader
{

struct Request {
    enum class Command : uint32_t {
        USB_ROM_BOOT = 0, BOOT_APPLICATION = 1, UPDATE_SBR = 2, UPDATE_BOOTLOADER = 3, GET_BOOTLOADER_VERSION = 4
    };
    Command command;
    uint32_t totalSize;
    uint32_t numPackets;
};

struct Response {
    enum class Command : uint32_t {
        FLASH_COMPLETE = 0, FLASH_STATUS_UPDATE = 1, BOOTLOADER_VERSION
    };
    Command command;
    uint32_t success;
    float progress;
    uint32_t major, minor, patch;
    char errorMsg[64];
};


} // namespace bootloader
} // namespace dai


