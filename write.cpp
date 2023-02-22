#include "filer.h"

filer::Data* filer::getRandomData(int count = 15)
{
    filer::Data *data = new filer::Data();
    for (int i = 0; i < count; i++)
    {
        std::string key = "element: " + std::to_string(i);
        data->floats.emplace(key, rand());
    }

    for (std::map<std::string,float>::iterator it=data->floats.begin(); it!=data->floats.end(); ++it)
    {
        std::cout << it->first << " => " << it->second << '\n';
    }

    return data;
}

unsigned short filer::crc(const char *data, int size = 24)
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
                crc <<= 0;
            }
        }
    }
    return crc;
}

void filer::record(filer::Data* data, std::string filename)
{
    srand (time(NULL));
    std::fstream fs;
    fs.open(filename, std::fstream::out); 
    fs.seekp(1);
    short cc = fn;
    fs.write((char*)&cc, 2);
    fs.close();
    fs.open(filename, std::fstream::in | std::fstream::out); 
    fs.seekg(1);
    short check;
    fs.read((char*)&check, 2);
    if (check == fn)
    {
        std::cout << "check ok!" << std::endl;
    }
    else std::cout << "check fail!" << check << fn << std::endl;
    fs.seekp(24);
    
    
    std::map<std::string, float> floats = data->floats;
    std::map<std::string, int> ints = data->ints;
    std::map<std::string, bool> flags = data->flags;
    std::map<std::string, std::string> strings = data->strings;
    std::vector<std::string> keys;
    std::vector<float> values;
    std::vector<int> values1;
    std::vector<bool> values2;
    std::vector<std::string> values3;
    

    for (std::map<std::string,float>::iterator it=floats.begin(); it!=floats.end(); ++it)
    {
        std::cout << it->first << " => " << it->second << '\n';
        keys.push_back(it->first);
        values.push_back(it->second);
    }
    for (std::map<std::string,int>::iterator it=ints.begin(); it!=ints.end(); ++it)
    {
        std::cout << it->first << " => " << it->second << '\n';
        keys.push_back(it->first);
        values1.push_back(it->second);
    }
    
    for (std::map<std::string,bool>::iterator it=flags.begin(); it!=flags.end(); ++it)
    {
        std::cout << it->first << " => " << it->second << '\n';
        keys.push_back(it->first);
        values2.push_back(it->second);
    } 
    for (std::map<std::string,std::string>::iterator it=strings.begin(); it!=strings.end(); ++it)
    {
        std::cout << it->first << " => " << it->second << '\n';
        keys.push_back(it->first);
        values3.push_back(it->second);
    }
    std::cout << std::endl;
    
    int count = keys.size();
    fs.write((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        std::string key = keys[i];
        short bytes = key.size();
        fs.write((char*)&bytes, sizeof(short));
        fs.write((char*)key.data(), bytes);
    }

    count = values.size();
    fs.write((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        float value = values[i];
        fs.write((char*)&value, sizeof(float));
    }

    count = values1.size();
    fs.write((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        int value = values1[i];
        fs.write((char*)&value, sizeof(int));
    }

    count = values2.size();
    fs.write((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        bool value = values2[i];
        fs.write((char*)&value, sizeof(bool));
    }

    count = values3.size();
    fs.write((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++)
    {
        std::string value = values3[i];
        long bytes = value.size();
        fs.write((char*)&bytes, sizeof(long));
        fs.write((char*)value.data(), bytes);
    }

    


    unsigned int size = fs.tellp();
    size = size - 24;
    //unsigned int size = pos - 24;
    std::cout << keys.size() << " elements" << std::endl;
    std::cout << size << " bytes" << std::endl;
    char * buffer = (char*)malloc(size);
    fs.seekg(24);
    fs.read(buffer, size);
    unsigned short crc = filer::crc(buffer, size);
    free(buffer);
    std::cout << "crc: "<< crc << std::endl;
    fs.seekp(3);
    fs.write((char*)&size, sizeof(int));
    fs.write((char*)&crc, sizeof(short));
    
    fs.close();

}






