#ifndef _TonyTFTH_
#define _TonyTFTH_

#include "TonyTFT.h"

#define TFT_240_240		0 
#define TFT_240_320		1
 


/// Subclass of ST77XX type display for ST7789 TFT Driver
class TonyTFT : public TonyTFT {
  public:
    TonyTFT(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk,
      int8_t rst = -1);
    TonyTFT(int8_t cs, int8_t dc, int8_t rst);
	TonyTFT(int8_t slot);
	TonyTFT(int8_t slot,uint8_t tfttype);
#if !defined(ESP8266)
    TonyTFT(SPIClass *spiClass, int8_t cs, int8_t dc, int8_t rst);
#endif // end !ESP8266

    void setRotation(uint8_t m);
    void init(uint16_t width, uint16_t height, uint8_t spiMode = SPI_MODE0);
	uint8_t _tfttype;
};

#endif // _TonyTFTH_
