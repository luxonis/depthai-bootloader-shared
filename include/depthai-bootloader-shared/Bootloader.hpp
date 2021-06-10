#pragma once

#include <cstdint>
#include <map>

namespace dai
{
namespace bootloader
{

enum class Type : std::int32_t {
    USB, ETHERNET
};

enum class Memory : std::int32_t {
    FLASH, EMMC
};

enum class Section : std::int32_t {
    HEADER, BOOTLOADER, BOOTLOADER_CONFIG, APPLICATION
};

struct Structure {
    Structure() = default;
    std::map<Section, long> offset, size;
protected:
    Structure(decltype(offset) a, decltype(size) b) : offset(a), size(b) {}
};

namespace request {

    enum Command {
        USB_ROM_BOOT = 0,
        BOOT_APPLICATION,
        UPDATE_FLASH,
        GET_BOOTLOADER_VERSION,
        UPDATE_FLASH_EX,
        UPDATE_FLASH_EX_2
    };

    struct ARequest {
        ARequest() = delete;
        Command cmd;
    protected:
        ARequest(Command command) : cmd(command){}
    };

    // Specific request PODs
    struct UsbRomBoot : ARequest {
        // Common
        UsbRomBoot() : ARequest(USB_ROM_BOOT) {}
    };
    struct BootApplication : ARequest {
        // Common
        BootApplication() : ARequest(BOOT_APPLICATION) {}

        // Data
    };

    struct UpdateFlash : ARequest {
        // Common
        UpdateFlash() : ARequest(UPDATE_FLASH) {}

        // Data
        enum Storage : uint32_t { SBR, BOOTLOADER };
        Storage storage;
        uint32_t totalSize;
        uint32_t numPackets;
    };


    struct GetBootloaderVersion : ARequest {
        // Common
        GetBootloaderVersion() : ARequest(GET_BOOTLOADER_VERSION) {}

        // Data
    };

    // UpdateFlashEx - Additional options
    struct UpdateFlashEx : ARequest {
        // Common
        UpdateFlashEx() : ARequest(UPDATE_FLASH_EX) {}

        // Data
        Memory memory;
        Section section;
        uint32_t totalSize;
        uint32_t numPackets;
    };

    // UpdateFlashEx2 - Additional options
    struct UpdateFlashEx2 : ARequest {
        // Common
        UpdateFlashEx2() : ARequest(UPDATE_FLASH_EX_2) {}

        // Data
        Memory memory;
        uint32_t offset;
        uint32_t totalSize;
        uint32_t numPackets;
    };

}


namespace response {

    enum Command : uint32_t {
        FLASH_COMPLETE = 0,
        FLASH_STATUS_UPDATE,
        BOOTLOADER_VERSION,
        BOOTLOADER_TYPE
    };

    struct AResponse {
        AResponse() = delete;
        Command cmd;
    protected:
        AResponse(Command command) : cmd(command){}
    };

    // Specific request PODs
    struct FlashComplete : AResponse {
        // Common
        FlashComplete() : AResponse(FLASH_COMPLETE) {}

        // Data
        uint32_t success;
        char errorMsg[64];
    };
    struct FlashStatusUpdate : AResponse {
        // Common
        FlashStatusUpdate() : AResponse(FLASH_STATUS_UPDATE) {}

        // Data
        float progress;
    };
    struct BootloaderVersion : AResponse {
        // Common
        BootloaderVersion() : AResponse(BOOTLOADER_VERSION) {}

        // Data
        uint32_t major, minor, patch;
    };

    struct BootloaderType : AResponse {
        // Common
        BootloaderType() : AResponse(BOOTLOADER_TYPE) {}

        // Data
        Type type;
    };

}

} // namespace bootloader
} // namespace dai


