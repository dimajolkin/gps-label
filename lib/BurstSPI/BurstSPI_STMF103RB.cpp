#if defined(TARGET_STM32F103RB)
#include "BurstSPI.h"

void BurstSPI::fastWrite(int data)
{
    SPI_TypeDef *spi = (SPI_TypeDef *)(_peripheral->spi.spi.handle.Instance);
    // Check if data is transmitted
    while ((spi->SR & SPI_SR_TXE) == 0);
    spi->DR = data;
}

void BurstSPI::clearRX(void)
{
    const SPI_TypeDef *spi =
        (SPI_TypeDef *)(_peripheral->spi.spi.handle.Instance);
    while (spi->SR & SPI_SR_BSY) {
        // Check RX buffer readable
        while ((spi->SR & SPI_SR_RXNE) == 0)
            ;
        int dummy = spi->DR;
        (void)dummy; // suppress UNUSED warning
    }
}

#endif