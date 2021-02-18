/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     app
 * @{
 *
 * @file
 * @brief       SPI test
 *
 * @author      Oleg Manchenko <man4enkoos@gmail.com>
 *
 * @}
 */

#include <stdio.h>
#include "periph/spi.h"

int main(void)
{
    puts("SPI test");

    // SPI init step 1
    spi_init(SPI_DEV(1));

    // SPI init step 2
    int res = spi_init_cs(SPI_DEV(1), GPIO_PIN(PORT_B, 12));
    if (res != SPI_OK) {
        printf("[SPI test] init: error initializing the CS pin [%i]\n", res);
        return -1;
    }

    // SPI init step 3
    spi_acquire(SPI_DEV(1), GPIO_PIN(PORT_B, 12), SPI_MODE_0, SPI_CLK_5MHZ);

    // Send data
    uint8_t buffer_for_send[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F}; 
    spi_transfer_bytes(SPI_DEV(1), GPIO_PIN(PORT_B, 12), false, buffer_for_send, NULL, sizeof(buffer_for_send));

    // SPI release
    spi_release(SPI_DEV(1));

    return 0;
}
