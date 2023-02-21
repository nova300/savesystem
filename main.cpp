#include "filer.h"


filer::Data* filer::data0 = new Data();
filer::Data* filer::data1 = new Data();

int filer::activeData;


filer::Data* filer::getDataBank(int number)
{
    switch (number)
    {
    case (0):
        return filer::data0;
        break;
    case (1):
        return filer::data1;
        break;
    default:
        return filer::data0;
        break;
    }
}


bool process(std::string const & line)
{
    bool exit;
    
    std::vector<std::string> args = filer::splitstring(line, " ");
    switch(filer::hash(args[0].c_str()))
    {
        case filer::hash("exit"):
        {
            return true;
            break;
        }
        case filer::hash("stat"):
        {
            std::cout << "file: " << filer::activeData << std::endl;
            filer::Data* data = filer::getDataBank(filer::activeData);
            std::cout << "floats: " << data->floats.size() << std::endl;
            break;
        }
        case filer::hash("rand"):
        {
            if (args.size() < 2) break;
            if (!args[1].empty())
            {
                int size = atoi(args[1].c_str());
                std::cout << size << std::endl;
                if (size < 1) break;
                delete(filer::getDataBank(filer::activeData));
                *filer::getDataBank(filer::activeData) = *filer::getRandomData(size);
            }
            break;
        }
        case filer::hash("fs"):
        {
            if (args.size() < 2) break;
            if (!args[1].empty())
            {
                int arg = atoi(args[1].c_str());
                if (arg < 0 || arg > 1)
                {
                    std::cout << "cannot select file " << arg << std::endl;
                    break;
                }
                filer::activeData = arg;
                std::cout << "file " << arg << " selected" << std::endl;
            }
            break;
        }
        case filer::hash("float"):
        {
            if (args.size() < 3) break;
            if ((!args[1].empty()) && (!args[2].empty()))
            {
                std::string key = args[1];
                float value  = atof(args[2].c_str());
                filer::Data* data = filer::getDataBank(filer::activeData);
                data->floats.emplace(key, value);
            }
            break;
        }
        case filer::hash("lsfp"):
        {
            std::cout << "floats in current file:" << std::endl;
            filer::Data* data = filer::getDataBank(filer::activeData);
            for (std::map<std::string,float>::iterator it=data->floats.begin(); it!=data->floats.end(); ++it)
            {
                std::cout << it->first << " => " << it->second << '\n';
            }
            break;
        }
        case filer::hash("save"):
        {
            if (args.size() < 2) break;
            if (!args[1].empty())
            {

                filer::record(filer::getDataBank(filer::activeData), args[1]);
            }
            break;
        }
        case filer::hash("load"):
        {
            if (args.size() < 2) break;
            if (!args[1].empty())
            {

                *filer::getDataBank(filer::activeData) = *filer::load(args[1]);
            }
            break;
        }
        case filer::hash("int"):
        {
            if (args.size() < 3) break;
            if ((!args[1].empty()) && (!args[2].empty()))
            {
                std::string key = args[1];
                int value  = atoi(args[2].c_str());
                filer::Data* data = filer::getDataBank(filer::activeData);
                data->ints.emplace(key, value);
            }
            break;
        }
        case filer::hash("lsi"):
        {
            std::cout << "integers in current file:" << std::endl;
            filer::Data* data = filer::getDataBank(filer::activeData);
            for (std::map<std::string,int>::iterator it=data->ints.begin(); it!=data->ints.end(); ++it)
            {
                std::cout << it->first << " => " << it->second << '\n';
            }
            break;
        }
        case filer::hash("flag"):
        {
            if (args.size() < 3) break;
            if ((!args[1].empty()) && (!args[2].empty()))
            {
                std::string key = args[1];
                int value  = atoi(args[2].c_str());
                bool value1 = false;
                if (value != 0) value1 = true;
                filer::Data* data = filer::getDataBank(filer::activeData);
                data->flags.emplace(key, value1);
            }
            break;
        }
        case filer::hash("lsfl"):
        {
            std::cout << "flags in current file:" << std::endl;
            filer::Data* data = filer::getDataBank(filer::activeData);
            for (std::map<std::string,bool>::iterator it=data->flags.begin(); it!=data->flags.end(); ++it)
            {
                std::cout << it->first << " => " << it->second << '\n';
            }
            break;
        }
        case filer::hash("string"):
        {
            if (args.size() < 3) break;
            if ((!args[1].empty()) && (!args[2].empty()))
            {
                std::string key = args[1];
                std::string value  = args[2].c_str();
                filer::Data* data = filer::getDataBank(filer::activeData);
                data->strings.emplace(key, value);
            }
            break;
        }
        case filer::hash("lss"):
        {
            std::cout << "strings in current file:" << std::endl;
            filer::Data* data = filer::getDataBank(filer::activeData);
            for (std::map<std::string,std::string>::iterator it=data->strings.begin(); it!=data->strings.end(); ++it)
            {
                std::cout << it->first << " => " << it->second << '\n';
            }
            break;
        }
        case filer::hash("clear"):
        {
            delete(filer::getDataBank(filer::activeData));
            *filer::getDataBank(filer::activeData) = *new filer::Data();
            std::cout << "data cleared" << std::endl;
            break;
        }
        case filer::hash("ls"):
        {
            std::cout << "values in current file:" << std::endl << std::endl;
            filer::Data* data = filer::getDataBank(filer::activeData);
            std::cout << "flags:" << std::endl;
            for (std::map<std::string,bool>::iterator it=data->flags.begin(); it!=data->flags.end(); ++it)
            {
                std::cout << it->first << " => " << it->second << '\n';
            }
            std::cout << "integers:" << std::endl;
            for (std::map<std::string,int>::iterator it=data->ints.begin(); it!=data->ints.end(); ++it)
            {
                std::cout << it->first << " => " << it->second << '\n';
            }
            std::cout << "floats:" << std::endl;
            for (std::map<std::string,float>::iterator it=data->floats.begin(); it!=data->floats.end(); ++it)
            {
                std::cout << it->first << " => " << it->second << '\n';
            }
            std::cout << "strings:" << std::endl;
            for (std::map<std::string,std::string>::iterator it=data->strings.begin(); it!=data->strings.end(); ++it)
            {
                std::cout << it->first << " => " << it->second << '\n';
            }
            break;
        }
        default:
        {
            std::cout << "command not found\n";
            break;
        }
    }

    return false;
}

int main()
{
    bool exit;
    std::cout << "Operations Control Terminal\n\nREADY\n";
    for (std::string line; std::cout << "> " && std::getline(std::cin, line); )
    {
        if (!line.empty()) { 
            exit = process(line); 
        }
        if (exit) break;
    }

    delete(filer::data0);
    delete(filer::data1);

    std::cout << "Goodbye.\n";
}
