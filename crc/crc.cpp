#include <iostream>
#include <string.h>



unsigned short crc(const char *data, int size = 24)
{
    unsigned short crc = 0;
    for (int i = 0; i < size; i++)
    {
        char b = data[i];
        crc ^= (b << 8);
        for (int j = 0; j < 8; j++)
        {
            if((crc & 0x8000) != 0)
            {
                crc = ((crc << 1) ^ 0x9909);
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "no argument\n";
        return 0; 
    }

    const char *value = argv[1];
    int size = strlen(value);
    unsigned short crcval = crc(value, size);

    std::cout << "bytes:    " << size << std::endl;
    std::cout << "crc:  " << crcval << std::endl;


}

