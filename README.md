# CRC
CRC calculation for Arduino

## Usage

``` C++
#include <CRC.h>

void setup()
{
    uint8_t arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    uint8_t c8 = CRC::crc8(arr, sizeof(arr));
    uint16_t c16 = CRC::crc16(arr, sizeof(arr));
}
```

## License

MIT
