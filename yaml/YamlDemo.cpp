#include "YamlDemo.h"
#include "../FilePath.h"
#include <fstream>
namespace yaml
{
    namespace demo
    {
        YamlDemo::YamlDemo(/* args */)
        {
        }

        YamlDemo::~YamlDemo()
        {
        }

        void YamlDemo::ReadAndWriteYaml()
        {
            //fix bug
            std::string dir = "/home/li/map";
            if (!swr::util::FilePath::IsFileExisted(dir))
            {
                swr::util::FilePath::CreateDirR(dir.c_str());
            }
            std::string path = dir + "/info.yaml";
            if (!swr::util::FilePath::IsFileExisted(path))
            {
                std::ofstream fout(path);
                fout << "routeList:" << std::endl;
                fout.close();
            }
            YAML::Node localInfo = YAML::LoadFile(path);
            const auto& routeList = localInfo["routeList"];
            std::cout << "routeList type:" << routeList.Type() << std::endl;
            if(!routeList.IsSequence())
            {
                std::cout << "routeList Is not Sequence" << std::endl;
                return;
            }
            if(!routeList.size())
            {
                std::cout << "routeList size is 0" << std::endl;
                return;
            }
            for (const auto &info : localInfo["routeList"])
            {
                std::string routeName = info["routeName"].as<std::string>();
                std::cout << "routeName:" << routeName << std::endl;
                std::uint8_t routeState = info["routeState"].as<uint8_t>();
                std::cout << "routeState:" << (std::uint16_t)routeState << std::endl;
                std::uint8_t mapState = info["mapState"].as<uint8_t>();
                std::cout << "mapState:" << (std::uint16_t)mapState << std::endl;
            }
        }
        bool YamlDemo::SaveToYaml()
        {
            std::string dir = "/home/li/map";
            if (!swr::util::FilePath::IsFileExisted(dir))
            {
                swr::util::FilePath::CreateDirR(dir.c_str());
            }
            std::string path = dir + "/info.yaml";
            if (!swr::util::FilePath::IsFileExisted(path))
            {
                std::ofstream fout(path);
                fout << "routeList:" << std::endl;
                fout.close();
            }
            try
            {
                /* code */
                YAML::Node config = YAML::LoadFile(path);
                //create new node
                const auto& routeList = config["routeList"];
                std::cout << "routeList type:" << routeList.Type() << std::endl;
                if(!routeList.IsSequence())
                {
                    std::cout << "routeList Is not Sequence" << std::endl;
                    return false;
                }
                if(!routeList.size())
                {
                    std::cout << "routeList size is 0" << std::endl;
                    return false;
                }
                for (auto &&info : config["routeList"])
                {
                    info["routeState"] = (uint16_t)0x11;
                    info["mapState"] = (uint16_t)0x11;
                    info["pngState"] = (uint16_t)0x11;
                }
                //write conf
                std::ofstream fout(path);
                fout << config;
                fout.close();
            }
            catch(...)
            {
                std::cout << "ocuer error" << std::endl;
            }
            return true;
            
        }
        void YamlDemo::SimUpdateYaml()
        {
            std::string dir = "/home/li/map";
            if (!swr::util::FilePath::IsFileExisted(dir))
            {
                swr::util::FilePath::CreateDirR(dir.c_str());
            }
            std::string path = dir + "/info.yaml";
            if (!swr::util::FilePath::IsFileExisted(path))
            {
                std::ofstream fout(path);
                fout << "routeList:" << std::endl;
                fout.close();
            }
            try
            {
                std::vector<YAML::Node> routeVector;
                {
                    YAML::Node cacheInfo = YAML::LoadFile(path);
                    YAML::Node operationRecords = cacheInfo["routeList"];
                    for(auto&& node : operationRecords)
                    {
                        std::cout << "routeCode:" << node["routeCode"].as<std::string>() << std::endl;
                        routeVector.emplace_back(node);
                    }
                }
                for (size_t i = 0; i < routeVector.size(); i++)
                {
                    auto& node = routeVector[i];
                    node["flag"] = 'D';
                }
                //remove from yaml
                std::string newPath = dir + "info.back.yaml";
                if (!swr::util::FilePath::IsFileExisted(newPath))
                {
                    std::ofstream fout(newPath);
                    fout << "routeList:" << std::endl;
                    fout.close();
                }
                YAML::Node newConfig = YAML::LoadFile(newPath);
                for (size_t i = 0; i < routeVector.size(); i++)
                {
                    if (routeVector[i]["flag"].as<char>() != 'D')
                    {
                        newConfig["routeList"].push_back(routeVector[i]);
                    }
                }
                //write new conf
                std::ofstream fout(newPath);
                fout << newConfig;
                fout.close();
                //del old config
                bool isDel = swr::util::FilePath::DeleteFile(path.c_str());
                if(isDel)
                {
                    bool isRename = swr::util::FilePath::RenameFile(newPath.c_str(),path.c_str());
                    if(isRename)
                    {
                        std::cout << "update yaml success" << std::endl;
                    }
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
        void YamlDemo::DelYaml(){
            //fix bug
            std::string dir = "/home/li/workspaces/config";
            if (!swr::util::FilePath::IsFileExisted(dir))
            {
                swr::util::FilePath::CreateDirR(dir.c_str());
            }
            std::string path = dir + "/info.yaml";
            if (!swr::util::FilePath::IsFileExisted(path))
            {
                std::ofstream fout(path);
                fout << "routeList:" << std::endl;
                fout.close();
            }
            YAML::Node localInfo = YAML::LoadFile(path);
            YAML::Node routeList = localInfo["routeList"];
            std::cout << "routeList type:" << routeList.Type() << std::endl;
            if(!routeList.IsSequence())
            {
                std::cout << "routeList Is not Sequence" << std::endl;
                return;
            }
            std::cout << "routeList size is " << routeList.size()  << std::endl;
            if(!routeList.size())
            {
                std::cout << "routeList size is 0" << std::endl;
                return;
            }
            for (const auto &info : routeList)
            {
                std::string routeCode = info["routeName"].as<std::string>();
                std::cout << "routeName:" << routeCode << std::endl;
            }
            for (int i = routeList.size() - 1; i >= 0; i--){
                if(routeList[i]["bodyNum"].as<std::int16_t>()==1){
                    bool isDel = routeList.remove(i);
                    if(!isDel){
                        std::cout << "del failed" << std::endl;
                    }
                    else{
                        std::cout << "del success" << std::endl;
                    }
                }
            }
            //write conf
            std::ofstream fout(path);
            fout << localInfo;
            fout.close();
        }

        void YamlDemo::DelYaml2(){
            std::string dir = "/home/li/workspaces/config";
            if (!swr::util::FilePath::IsFileExisted(dir))
            {
                swr::util::FilePath::CreateDirR(dir.c_str());
            }
            std::string path = dir + "/info.yaml";
            if (!swr::util::FilePath::IsFileExisted(path))
            {
                std::ofstream fout(path);
                fout << "routeList:" << std::endl;
                fout.close();
            }
            YAML::Node localInfo = YAML::LoadFile(path);
            YAML::Node routeList = localInfo["routeList"];
            routeList.remove(2);
            routeList.remove(1);
            //write conf
            std::ofstream fout(path);
            fout << localInfo;
            fout.close();
        }
        void YamlDemo::DelYaml3()
        {
            try
            {
                std::string path = "/home/li/map/info.yaml";
                std::vector<YAML::Node> newConfigNodes;
                YAML::Node localInfo = YAML::LoadFile(path);
                YAML::Node routeList = localInfo["routeList"];
                for (size_t i = 0; i < routeList.size(); i++){
                    const auto& slotCode = routeList[i]["slotCode"].as<std::string>();
                    const auto& routeCode = routeList[i]["routeCode"].as<std::string>();
                    std::cout << "slotCode:" << slotCode << " routeCode:" << routeCode << std::endl;
                    if(slotCode.compare("K") == 0){
                        //del file
                        std::cout << "del " << routeCode << std::endl;
                    }
                    else{
                        newConfigNodes.emplace_back(routeList[i]);
                    }
                }
                std::string newPath = "/home/li/map/info.back.yaml";
                if (!swr::util::FilePath::IsFileExisted(newPath))
                {
                    std::ofstream fout(newPath);
                    fout << "routeList:" << std::endl;
                    fout.close();
                }
                YAML::Node newConfig = YAML::LoadFile(newPath);
                for (size_t i = 0; i < newConfigNodes.size(); i++)
                {
                    newConfig["routeList"].push_back(newConfigNodes[i]);
                }
                //write new conf
                std::ofstream fout(newPath);
                fout << newConfig;
                fout.close();
                //del old config
                bool isDel = swr::util::FilePath::DeleteFile(path.c_str());
                if(isDel)
                {
                    bool isRename = swr::util::FilePath::RenameFile(newPath.c_str(),path.c_str());
                    if(isRename)
                    {
                        std::cout << "update yaml success" << std::endl;
                    }
                }
            }
            catch(const YAML::Exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
    }
}