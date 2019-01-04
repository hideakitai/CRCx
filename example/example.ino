#include <CRC.h>

void setup()
{
    Serial.begin(115200);
    delay(2000);

    uint8_t arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Serial.println(CRC::crc8(arr, sizeof(arr)), HEX);
    Serial.println(CRC::crc16(arr, sizeof(arr)), HEX);
}

void loop()
{
}
