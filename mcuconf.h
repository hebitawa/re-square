#pragma once

#undef RP2040_SPI_USE_SPI0
#define RP2040_SPI_USE_SPI0 TRUE

#undef RP2040_SPI_USE_SPI1
#define RP2040_SPI_USE_SPI1 FALSE

#include_next <mcuconf.h>