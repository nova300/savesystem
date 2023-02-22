#include <iostream>
#include <string.h>
#include <set>


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

    int count = atoi(argv[1]);
    std::set<unsigned short> checked;
    int duplicates = 0;


    for (int i = 0; i < count; i++)
    {
        int value = i;
        unsigned short crcval = crc((char*)&value, sizeof(int));

        std::cout << value << "    " << crcval << std::endl;
        auto ret = checked.emplace(crcval);
        if (!ret.second) duplicates++;
    }



    std::cout << duplicates << " collisions detected\n";

}

