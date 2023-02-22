#ifndef filer_h
#define filer_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <string.h>

#define fn 0x464D

namespace filer
{
    class Data{
    public:
    std::map<std::string, float> floats;
    std::map<std::string, int> ints;
    std::map<std::string, bool> flags;
    std::map<std::string, std::string> strings;
    };

    extern Data* data0;
    extern Data* data1;


    extern int activeData;



    extern void record(Data* data, std::string filename);
    extern Data* load(std::string filename);
    extern Data* getRandomData(int count);
    extern std::vector<std::string> splitstring(std::string s, std::string delimiter);
    extern Data* getDataBank(int number);
    extern unsigned short crc(const char *data, int size);



    constexpr unsigned int hash(const char *s, int off = 0) {                        
        return !s[off] ? 5381 : (hash(s, off+1)*33) ^ s[off];                           
    }


}







#endif