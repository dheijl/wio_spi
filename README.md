
# WIO SPI

Proof of concept code for SPI communication between a Wio terminal and an Alchitry AU + Br Element.

The Wio is the SPI master, and the AU the SPI slave.

- cs = AU/Br A2 -> WIO pin 24
- sck = AU/Br A5 -> WIO pin 23
- miso = AU/Br A9 -> WIO pin 21
- mosi = AU/Br A6 -> WIO pin 19
- data_rdy = AU/Br A8 -> WIO pin 13 (D0)

D0 is asserted by the AU to indicate it has data to transmit. This makes the WIO start an SPI transfer.

Spi speed seems limited at 12 Mhz for Au -> Wio transfer, while Wio -> Au transfer is fine at 24 Mhz.

You can find the Lucid code for the Alchitry Au [here](https://github.com/dheijl/AlchitryAuTests/tree/main/WIO_SPIO).
