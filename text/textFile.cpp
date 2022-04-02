#include <iostream>
#include "textFile.h"
#include "../FilePath.h"

textFile::textFile(/* args */)
{
}

textFile::~textFile()
{
}

void textFile::ReadText2()
{
    std::string line = "101|0|65|0|a10fddcffb884aa4bc5fb701a471b430||||0|1648609849|0||||||1|1|1|0|11648609849|";
    std::vector<std::string> stringVector;
    SplitString(line,stringVector,'|');
    //bool isEnable = std::stoi(data[13]);
    //std::cout << "isEnable:" << isEnable << std::endl;
    for (size_t i = 0; i < stringVector.size(); i++)
    {
        std::cout << i << " " << stringVector[i] << std::endl;
    }
    std::string s1 = stringVector[0];
    std::cout << "s1:" << s1 << std::endl;
    std::string s2 = stringVector[1];
    std::cout << "s2:" << s2 << std::endl;
    std::uint8_t s3 = std::stoi(stringVector[2]);
    std::cout << "s3:" << s3 << std::endl;
    std::uint64_t mapId = std::stoul(stringVector[3]);
    std::string s4 = stringVector[4];
    std::cout << "s4:" << s4 << std::endl;
    std::string s5 = stringVector[5];
    std::cout << "s5:" << s5 << std::endl;
    std::string s6 = stringVector[6];
    std::cout << "s6:" << s6 << std::endl;
    std::string s7 = stringVector[7];
    std::cout << "s7:" << s7 << std::endl;
    int size = std::stoi(stringVector[8]);
    std::cout << "size:" << size << std::endl;
    int time = std::stoul(stringVector[9]);
    std::cout << "time:" << time << std::endl;
    std::uint8_t model = std::stoi(stringVector[10]);
    std::cout << "model:" << model << std::endl;
    std::uint8_t mapState = std::stoi(stringVector[16]);
    std::cout << "mapState:" << mapState << std::endl;
    std::uint8_t pngState = std::stoi(stringVector[17]);
    std::cout << "pngState:" << pngState << std::endl;
    std::uint8_t routeState = std::stoi(stringVector[18]);
    std::cout << "routeState:" << routeState << std::endl;
    std::uint8_t configState = std::stoi(stringVector[19]);
    std::cout << "configState:" << configState << std::endl;
    bool enableVirtualWall = std::stoi(stringVector[20]);
    std::cout << "enableVirtualWall:" << enableVirtualWall << std::endl;
    std::uint32_t useTime = std::stoul(stringVector[21]);
    std::cout << "useTime:" << useTime << std::endl;
}

void textFile::ReadText()
{
    std::string configPath = "/home/li/map/map.text";
    std::fstream fs;
    fs.open(configPath.c_str(),std::fstream::in| std::fstream::out);
    if (!swr::util::FilePath::IsFileExisted(configPath))
    {
        swr::util::FilePath::CreateFileR(configPath.c_str());
        std::cout << "new map.text" << std::endl;
    }
    if (fs.is_open())
    {
        std::string line;
        while (std::getline(fs, line))
        {
            std::cout << line << std::endl;
            ParseInfo(line);
        }
        fs.close();
    }
    else
    {
        std::cout << "Error opening file:" << configPath << std::endl;
    }
}
void textFile::WriteText()
{
    std::string configPath = "/home/li/map/map.text";
    std::fstream fs;
    fs.open(configPath.c_str(), std::fstream::in| std::fstream::out|std::fstream::app);
    if(fs.is_open())
    {
        fs << (std::uint16_t)0x01 << "|";
        fs << (std::uint16_t)0x01 << "|";
        fs << 101 << "|";
        fs << 0 << "|";
        fs << (std::uint16_t)'A' << "|";
        fs << "routeName" << "|";
        fs << 0 << "|";
        fs << (std::uint16_t)0x01 << "|";
        fs << "/root/info" << "|";
        fs << 123456 << "|";
        fs << "/root/info" << "|";
        fs << "/root/info" << "|";
        fs << "/root/info" << "|";
        fs << std::uint16_t(true) << "|";
        fs << "" << "|" << std::endl;
        fs.close();
    }
    else
    {
        std::cout << "Error opening file" << std::endl;
    }
}

void textFile::ParseInfo(const std::string& line)
{
    std::vector<std::string> data;
    SplitString(line,data,'|');
    //bool isEnable = std::stoi(data[13]);
    //std::cout << "isEnable:" << isEnable << std::endl;
    for (size_t i = 0; i < data.size(); i++)
    {
        std::cout << i << " " << data[i] << std::endl;
    }
}

void textFile::SplitString(const std::string& s, std::vector<std::string>& v, const char& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + 1;
        pos2 = s.find(c, pos1);
    }

    if(pos1 != s.length())
    {
        v.push_back(s.substr(pos1));
    }
}

void textFile::DeleteText()
{
    //filter
    
    //rewrite

}

void textFile::UpdateText()
{
    std::string configPath = "/home/li/map/map.text";
    std::ifstream ifs(configPath);
    if (ifs.is_open())
    {
        std::string line;
        while (std::getline(ifs, line))
        {
            std::cout << line << std::endl;
            ParseInfo(line);
        }
        ifs.close();
    }
    else
    {
        std::cout << "Error opening file:" << configPath << std::endl;
        return;
    }
    //update

    //rewrite
}
