#pragma once

#include <cstdint>
#include <chrono>

#include "Bootloader.hpp"

namespace dai
{
namespace bootloader
{

// Config
// TODO(themarpe)
struct EthernetBootloaderConfig {
    char ip[16];
    char subnetMask[16];
    char gateway[16];
};


// Structure
struct EthernetBootloaderStructure : Structure {

    constexpr static long HEADER_OFFSET = 0;
    constexpr static long HEADER_SIZE = 128;
    constexpr static long CONFIG_SIZE = 16 * 1024;
    constexpr static long BOOTLOADER_OFFSET = 0 + HEADER_SIZE;
    constexpr static long BOOTLOADER_SIZE = 8 * 1024 * 1024 - CONFIG_SIZE;
    constexpr static long CONFIG_OFFSET = BOOTLOADER_OFFSET + BOOTLOADER_SIZE;
    constexpr static long APPLICATION_OFFSET = CONFIG_OFFSET + CONFIG_SIZE;

    EthernetBootloaderStructure() : Structure({
        {Section::HEADER, HEADER_OFFSET},
        {Section::BOOTLOADER_CONFIG, CONFIG_OFFSET},
        {Section::BOOTLOADER, BOOTLOADER_OFFSET},
        {Section::APPLICATION, APPLICATION_OFFSET},
    }, {
        {Section::HEADER, HEADER_SIZE},
        {Section::BOOTLOADER_CONFIG, CONFIG_SIZE},
        {Section::BOOTLOADER, BOOTLOADER_SIZE},
        {Section::APPLICATION, 0},
    }) {}

};

} // namespace bootloader
} // namespace dai


