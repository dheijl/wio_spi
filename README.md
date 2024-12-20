Proof of concept code for SPI communication between a Wio terminal and an Alchitry AU + Br Element.

The Wio is the SPI master, and the AU the SPI slave.

D0 is asserted by the AU to indicate it has data to transmit. This makes the WIO start an SPI transfer.

Spi speed seems limited at 12 Mhz for Au -> Wio transfer, while Wio -> Au transfer is fine at 24 Mhz.

You can find the Lucid code for the Alchitry Au [here](https://github.com/dheijl/AlchitryAuTests/tree/main/WIO_SPIO).
