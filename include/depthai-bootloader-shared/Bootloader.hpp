#pragma once

#include <cstdint>

namespace dai
{
namespace bootloader
{

struct Request {
    // Base request POD
    enum Command : uint32_t {
        USB_ROM_BOOT = 0,
        BOOT_APPLICATION, 
        UPDATE_SBR,
        UPDATE_BOOTLOADER,
        GET_BOOTLOADER_VERSION
    };
    Command command;

    // Specific request PODs
    struct UsbRomBoot{};
    struct BootApplication{};
    struct UpdateSbr{
        uint32_t totalSize;
        uint32_t numPackets;
    };
    struct UpdateBootloader{
        uint32_t totalSize;
        uint32_t numPackets;
    };
    struct GetBootloaderVersion{};
};


struct Response {
    // Base response POD
    enum Command : uint32_t {
        FLASH_COMPLETE = 0, 
        FLASH_STATUS_UPDATE,
        BOOTLOADER_VERSION
    };
    Command command;


    // Specific request PODs
    struct FlashComplete{
        uint32_t success;
        char errorMsg[64];
    };
    struct FlashStatusUpdate{
        float progress;
    };
    struct BootloaderVersion{
        uint32_t major, minor, patch;
    };

};


} // namespace bootloader
} // namespace dai


