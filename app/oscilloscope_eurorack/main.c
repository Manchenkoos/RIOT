/**
 * @ingroup     app
 * @{
 *
 * @file
 * @brief       oscilloscope_eurorack
 *
 * @author      Manchenko Oleg <man4enkoos@gmail.com>
 *
 * @}
 */

#include <stdio.h>
#include "xtimer.h"
#include "board.h"
#include "ili9341.h"
#include "ili9341_params.h"

// Pinout display
// CS  - PA4
// DC  - PA0
// RST - PA1
// SDA - PA7
// SCK - PA5
// VCC - 3.3v
// GND - GND

// Pinout console
// TX - PA2
// RX - PA3

void display_oscilloscope(ili9341_t *dev) {
    printf("[Display] Oscilloscope");

    // TFT display filling map
    ili9341_fill(dev, 0, 319, 0, 239, 0xFFFF);

    // Draw vertical lines
    for (uint16_t i = 20; i < 320; i += 20) {
        ili9341_fill(dev, i, i, 20, 220, 0x0000);
    }

    // Draw horizontal lines
    for (uint16_t i = 20; i < 240; i += 20) {
        ili9341_fill(dev, 20, 300, i, i, 0x0000);
    }

    // Draw axis
    // Vertikal
    for (uint16_t i = 20; i < 220; i += 4) {
        ili9341_fill(dev, 159, 161, i, i, 0x0000);
    }

    // Horizontal
    for (uint16_t i = 20; i < 300; i += 4) {
        ili9341_fill(dev, i, i, 119, 121, 0x0000);
    }
}

void display_measurements(ili9341_t *dev, uint16_t *measurements) {
    printf("[Display] Measurements");

    display_oscilloscope(dev);

    for (uint16_t i = 0; i < 280; i++) {
        if (i == 279) {
            break;
        }

        uint16_t measurement_start = measurements[i];
        uint16_t measurement_end   = measurements[i+1];

        if (measurement_start > measurement_end) {
            ili9341_fill(dev, i + 21, i + 21, measurement_end + 1, measurement_start, 0x0000);
        } else {
            ili9341_fill(dev, i + 21, i + 21, measurement_start, measurement_end - 1, 0x0000);
        }
    }
}

int main(void)
{
    ili9341_t dev;

    puts("ili9341 TFT display test application");

    /* initialize the sensor */
    printf("Initializing display...");

    /* Enable backlight if macro is defined */
#ifdef BACKLIGHT_ON
    BACKLIGHT_ON;
#endif

    static const ili9341_params_t display_params = {
        .spi      = SPI_DEV(0),          \
        .spi_clk  = SPI_CLK_10MHZ,       \
        .spi_mode = SPI_MODE_0,          \
        .cs_pin   = GPIO_PIN(PORT_A, 4), \
        .dcx_pin  = GPIO_PIN(PORT_A, 0), \
        .rst_pin  = GPIO_PIN(PORT_A, 1), \
        .rgb      = 0,                   \
        .inverted = 0,                   \
        .lines    = 320U,                \
    };

    if (ili9341_init(&dev, &display_params) == 0) {
        puts("[OK]");
    }
    else {
        puts("[Failed]");
        return 1;
    }    

    uint16_t measurements[280] = {120, 125, 131, 136, 142, 147, 152, 157, 162, 167, 172, 177, 181, 186, 190, 194, 197, 201, 204, 207, 209, 211, 213, 215, 217, 218, 219, 219, 219, 219, 219, 218, 217, 216, 214, 213, 210, 208, 205, 202, 199, 196, 192, 188, 184, 179, 175, 170, 165, 160, 155, 150, 145, 139, 134, 128, 123, 117, 111, 106, 100, 95, 90, 84, 79, 74, 69, 65, 60, 56, 52, 48, 44, 40, 37, 34, 31, 29, 27, 25, 23, 22, 21, 20, 20, 20, 20, 20, 21, 22, 24, 25, 27, 30, 32, 35, 38, 42, 45, 49, 53, 57, 62, 66, 71, 76, 81, 86, 92, 97, 102, 108, 113, 119, 125, 130, 136, 141, 146, 152, 157, 162, 167, 172, 176, 181, 185, 189, 193, 197, 200, 203, 206, 209, 211, 213, 215, 217, 218, 219, 219, 219, 219, 219, 218, 217, 216, 215, 213, 211, 208, 206, 203, 199, 196, 192, 188, 184, 180, 175, 171, 166, 161, 156, 150, 145, 140, 134, 129, 123, 118, 112, 106, 101, 96, 90, 85, 80, 75, 70, 65, 61, 56, 52, 48, 44, 41, 37, 34, 32, 29, 27, 25, 23, 22, 21, 20, 20, 20, 20, 20, 21, 22, 23, 25, 27, 29, 32, 35, 38, 41, 45, 49, 53, 57, 61, 66, 71, 76, 81, 86, 91, 96, 102, 107, 113, 118, 124, 130, 135, 140, 146, 151, 156, 162, 166, 171, 176, 180, 185, 189, 193, 196, 200, 203, 206, 209, 211, 213, 215, 216, 218, 219, 219, 219, 219, 219, 219, 218, 216, 215, 213, 211, 208, 206, 203, 200, 196, 193, 189, 185, 180, 176, 171, 166, 161, 156, 151, 146, 140};
    display_measurements(&dev, measurements);

    while (1) {
    }

    return 0;
}
