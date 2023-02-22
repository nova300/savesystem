#include "filer.h"



filer::Data* filer::load(std::string filename)
{
    std::fstream fs;
    fs.open(filename); 
    fs.seekg(1);
    short check;
    fs.read((char*)&check, 2);
    if (check == fn)
    {
        std::cout << "check ok!" << std::endl;
    }
    else std::cout << "check fail!" << check << fn << std::endl;

    unsigned int size;
    unsigned short crc;

    fs.read((char*)&size, sizeof(int));
    fs.read((char*)&crc, sizeof(short));

    std::cout << size <<  std::endl;

    char * buffer = (char*)malloc(size);
    fs.seekg(24);
    fs.read(buffer, size);
    unsigned short newcrc = filer::crc(buffer, size);
    free(buffer);
    fs.seekg(24);

    std::cout << crc << "   " << newcrc << std::endl;

    if (newcrc != crc)
    {
        std::cout << "bad crc!\n";
        return new Data();
    }
    std::cout << "crc ok!\n";
    
    filer::Data *data = new filer::Data();

    std::vector<std::string> keys;
    std::vector<float> values;
    std::vector<int> values1;
    std::vector<bool> values2;
    std::vector<std::string> values3;

    int count;
    fs.read((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        short bytes;
        fs.read((char*)&bytes, sizeof(short));
        char* kdata = (char*)malloc(bytes);
        fs.read(kdata, bytes);
        std::string key = std::string(kdata, bytes);
        std::cout << key << std::endl;
        keys.push_back(key);
    }


    fs.read((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        float value;
        fs.read((char*)&value, sizeof(float));
        values.push_back(value);
    }


    fs.read((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        int value;
        fs.read((char*)&value, sizeof(int));
        values1.push_back(value);
    }

    fs.read((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        bool value;
        fs.read((char*)&value, sizeof(bool));
        values2.push_back(value);
    }

    fs.read((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        long bytes;
        fs.read((char*)&bytes, sizeof(long));
        char* kdata = (char*)malloc(bytes);
        fs.read(kdata, bytes);
        std::string value = std::string(kdata, bytes);
        values3.push_back(value);
    }



    int read = fs.tellg();
    fs.close();

    int keypos = 0;
    for (int i = 0; i < values.size(); i++)
    {
        data->floats.emplace(keys[keypos], values[i]);
        keypos++;
    }
    for (int i = 0; i < values1.size(); i++)
    {
        data->ints.emplace(keys[keypos], values1[i]);
        keypos++;
    }
    for (int i = 0; i < values2.size(); i++)
    {
        data->flags.emplace(keys[keypos], values2[i]);
        keypos++;
    }
    for (int i = 0; i < values3.size(); i++)
    {
        data->strings.emplace(keys[keypos], values3[i]);
        keypos++;
    }

    std::cout << std::endl << keys.size() << " elements"<< std::endl;
    std::cout << read << " bytes" << std::endl;
    //std::cout << "crc: " << data->crc << std::endl;
    return data;
}




