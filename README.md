Proof of concept code for SPI communication between a Wio terminal and an Alchitry AU + Br Element.

The Wio is the SPI master, and the AU the SPI slave.

Spi speed seems limited at 12 Mhz for Au -> Wio transfer, while Wio -> Au transfer is fine at 24 Mhz.

For transmitting data, the Au SPI_peripheral component needs the master to toggle the chip select line for every byte.
For receiving the AU does not need this, the CS line can stay low between bytes.

You can find the Lucid code for the Alchitry Au [here](https://github.com/dheijl/AlchitryAuTests/tree/main/WIO_SPIO).
