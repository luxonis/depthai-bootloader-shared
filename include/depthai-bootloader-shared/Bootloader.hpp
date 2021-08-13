#pragma once

// std
#include <cstdint>
#include <map>

// project
#include "Type.hpp"
#include "Section.hpp"
#include "Memory.hpp"

namespace dai
{
namespace bootloader
{

namespace request {

    enum Command : uint32_t {
        USB_ROM_BOOT = 0,
        BOOT_APPLICATION,
        UPDATE_FLASH,
        GET_BOOTLOADER_VERSION,
        BOOT_MEMORY,
        UPDATE_FLASH_EX,
        UPDATE_FLASH_EX_2,
        NO_OP,
        GET_BOOTLOADER_TYPE,
        SET_BOOTLOADER_CONFIG,
        GET_BOOTLOADER_CONFIG,
        BOOTLOADER_MEMORY,
    };

    struct BaseRequest {
        BaseRequest(Command command) : cmd(command){}
        Command cmd;
    };

    // Specific request PODs
    struct UsbRomBoot : BaseRequest {
        // Common
        UsbRomBoot() : BaseRequest(USB_ROM_BOOT) {}
    };
    struct BootApplication : BaseRequest {
        // Common
        BootApplication() : BaseRequest(BOOT_APPLICATION) {}

        // Data
    };

    struct UpdateFlash : BaseRequest {
        // Common
        UpdateFlash() : BaseRequest(UPDATE_FLASH) {}

        // Data
        enum Storage : uint32_t { SBR, BOOTLOADER };
        Storage storage;
        uint32_t totalSize;
        uint32_t numPackets;
    };


    struct GetBootloaderVersion : BaseRequest {
        // Common
        GetBootloaderVersion() : BaseRequest(GET_BOOTLOADER_VERSION) {}

        // Data
    };

    // 0.0.12 or higher
    struct BootMemory : BaseRequest {
        // Common
        BootMemory() : BaseRequest(BOOT_MEMORY) {}

        // Data
        uint32_t totalSize;
        uint32_t numPackets;
    };

    // UpdateFlashEx - Additional options
    struct UpdateFlashEx : BaseRequest {
        // Common
        UpdateFlashEx() : BaseRequest(UPDATE_FLASH_EX) {}

        // Data
        Memory memory;
        Section section;
        uint32_t totalSize;
        uint32_t numPackets;
    };

    // UpdateFlashEx2 - Additional options
    struct UpdateFlashEx2 : BaseRequest {
        // Common
        UpdateFlashEx2() : BaseRequest(UPDATE_FLASH_EX_2) {}

        // Data
        Memory memory;
        uint32_t offset;
        uint32_t totalSize;
        uint32_t numPackets;
    };


    struct GetBootloaderType : BaseRequest {
        // Common
        GetBootloaderType() : BaseRequest(GET_BOOTLOADER_TYPE) {}

        // Data
    };


    // 0.0.14 or higher
    struct SetBootloaderConfig : BaseRequest {
        // Common
        SetBootloaderConfig() : BaseRequest(SET_BOOTLOADER_CONFIG) {}

        // Data
        Memory memory;
        uint32_t totalSize;
        uint32_t numPackets;
    };

    struct GetBootloaderConfig : BaseRequest {
        // Common
        GetBootloaderConfig() : BaseRequest(GET_BOOTLOADER_CONFIG) {}

        // Data
        Memory memory;
    };
    struct BootloaderMemory : BaseRequest {
        // Common
        BootloaderMemory() : BaseRequest(BOOTLOADER_MEMORY) {}

        // Data
    };

}


namespace response {

    enum Command : uint32_t {
        FLASH_COMPLETE = 0,
        FLASH_STATUS_UPDATE,
        BOOTLOADER_VERSION,
        BOOTLOADER_TYPE,
        GET_BOOTLOADER_CONFIG,
        BOOTLOADER_MEMORY,
    };

    struct BaseResponse {
        BaseResponse(Command command) : cmd(command){}
        Command cmd;
    };

    // Specific request PODs
    struct FlashComplete : BaseResponse {
        // Common
        FlashComplete() : BaseResponse(FLASH_COMPLETE) {}

        // Data
        uint32_t success;
        char errorMsg[64];
    };
    struct FlashStatusUpdate : BaseResponse {
        // Common
        FlashStatusUpdate() : BaseResponse(FLASH_STATUS_UPDATE) {}

        // Data
        float progress;
    };
    struct BootloaderVersion : BaseResponse {
        // Common
        BootloaderVersion() : BaseResponse(BOOTLOADER_VERSION) {}

        // Data
        uint32_t major, minor, patch;
    };

    struct BootloaderType : BaseResponse {
        // Common
        BootloaderType() : BaseResponse(BOOTLOADER_TYPE) {}

        // Data
        Type type;
    };


    // 0.0.14
    struct GetBootloaderConfig : BaseResponse {
        // Common
        GetBootloaderConfig() : BaseResponse(GET_BOOTLOADER_CONFIG) {}

        // Data
        uint32_t success;
        char errorMsg[64];
        uint32_t totalSize;
        uint32_t numPackets;
    };

    struct BootloaderMemory : BaseResponse {
        // Common
        BootloaderMemory() : BaseResponse(BOOTLOADER_MEMORY) {}

        // Data
        Memory memory;
    };
}

} // namespace bootloader
} // namespace dai
