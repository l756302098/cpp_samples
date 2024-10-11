#include "YamlDemo.h"
#include "../FilePath.h"
#include <fstream>

namespace yaml
{
    namespace demo
    {
        YamlDemo::YamlDemo(/* args */)
        {
            std::cout << "id:" << this << std::endl;
        }

        YamlDemo::~YamlDemo()
        {
        }

        long GetAddress()
        {
            
            //return long(&this);
            return 0;
        }

        void YamlDemo::ReadAndWriteYaml()
        {
            //fix bug
            std::string dir = "/home/li/log";
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
                ParseRouteInfo(info);
                // std::string routeName = info["routeName"].as<std::string>();
                // std::cout << "routeName:" << routeName << std::endl;
                // std::uint8_t routeState = info["routeState"].as<uint8_t>();
                // std::cout << "routeState:" << (std::uint16_t)routeState << std::endl;
                // std::uint8_t mapState = info["mapState"].as<uint8_t>();
                // std::cout << "mapState:" << (std::uint16_t)mapState << std::endl;
            }
        }

        bool YamlDemo::ParseRouteInfo(const YAML::Node& info)
        {
            try {
                std::string siteCode = info["siteCode"].as<std::string>();
                std::string hlcCode = info["hlcCode"].as<std::string>();
                char slotCode = info["slotCode"].as<char>();
                uint64_t mapId = info["mapId"].as<uint64_t>();
                std::string routeCode = info["routeCode"].as<std::string>();
                std::string bodyNum = info["bodyNum"].as<std::string>();
                std::string machineName = info["machineName"].as<std::string>();
                std::string routeName = info["routeName"].as<std::string>();
                int size = info["size"].as<int>();
                int time = info["time"].as<int>();
                int model = info["model"].as<int>();
                std::string mapPath = "/" + siteCode + "/" + hlcCode + "/" + routeCode + "/" + routeCode + ".map";
                std::string pngPath = "/" + siteCode + "/" + hlcCode + "/" + routeCode + "/" + routeCode + ".png";
                std::string routePath = "/" + siteCode + "/" + hlcCode + "/" + routeCode + "/" + routeCode + ".route";
                std::string configPath = "/" + siteCode + "/" + hlcCode + "/" + routeCode + "/" + routeCode + ".yaml";
                std::string semanticPath = info["semanticPath"].as<std::string>();
                uint8_t mapState = info["mapState"].as<uint8_t>();
                uint8_t pngState = info["pngState"].as<uint8_t>();
                uint8_t routeState = info["routeState"].as<uint8_t>();
                uint8_t configState = info["configState"].as<uint8_t>();
                bool enableVirtualWall = info["enableVirtualWall"].as<bool>();
                std::cout << "ParseRouteInfo success." << siteCode << " mapId:" << mapId;
                return true;
            }
            catch(const YAML::Exception& e)
            {
                std::cout << e.what();
            }
            catch (...) {
                std::cout << "ParseRouteInfo failed";
            }

            return false;
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
            std::cout << "ROS_DOMAIN_ID:" << wk::ROS_DOMAIN_ID << std::endl;
            wk::ROS_DOMAIN_ID  = 3;
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

        void YamlDemo::TestRead()
        {
            std::cout << "ROS_DOMAIN_ID:" << wk::ROS_DOMAIN_ID << std::endl;
            wk::ROS_DOMAIN_ID  = 2;
            std::string dir = "/home/li";
            if (!swr::util::FilePath::IsFileExisted(dir))
            {
                swr::util::FilePath::CreateDirR(dir.c_str());
            }
            std::string path = dir + "/info.yaml";
            if (!swr::util::FilePath::IsFileExisted(path))
            {
                std::ofstream fout(path);
                fout << "name:" << std::endl;
                fout.close();
            }
            YAML::Node localInfo = YAML::LoadFile(path);
            //const auto& routeList = localInfo["taskList"];
            //std::cout << "taskList type:" << routeList.Type() << std::endl;
            // if(!routeList.IsSequence())
            // {
            //     std::cout << "routeList Is not Sequence" << std::endl;
            //     return;
            // }
            for (const auto &info : localInfo["taskList"])
            {
                TestRouteInfo(info);
            }
        }

        void YamlDemo::TestAdd()
        {
            std::string dir = "/home/li";
            if (!swr::util::FilePath::IsFileExisted(dir))
            {
                swr::util::FilePath::CreateDirR(dir.c_str());
            }
            std::string path = dir + "/info.yaml";
            if (!swr::util::FilePath::IsFileExisted(path))
            {
                std::ofstream fout(path);
                fout << "name:" << std::endl;
                fout.close();
            }
            //YAML::Node localInfo = YAML::LoadFile(path);
            //const auto& routeList = localInfo["taskList"];
            //std::cout << "taskList type:" << routeList.Type() << std::endl;
            // if(!routeList.IsSequence())
            // {
            //     std::cout << "routeList Is not Sequence" << std::endl;
            //     return;
            // }
            YAML::Node config = YAML::LoadFile(path);
            YAML::Node node;
            node["operation"] = (std::uint16_t)0x01;
            node["resourceType"] = (std::uint16_t)0x01;
            node["siteCode"] = 101;
            node["hlcCode"] = 0;
            node["slotCode"] = (std::uint16_t)'A';
            node["routeName"] = "routeName";
            node["time"] = 0;
            node["model"] = (std::uint16_t)0x01;
            node["mapPath"] = "/root/info";
            node["mapId"] = 123456;
            node["routePath"] = "/root/info";
            node["pngPath"] = "/root/info";
            node["semanticPath"] = "/root/info";
            node["routeCode"] = "fcbsa123";
            config["taskList"].push_back(node);
            std::ofstream fout(path);
            fout << config;
            fout.close();
            std::cout << "update taskQueue yaml success" << std::endl;
        }

        bool YamlDemo::TestRouteInfo(const YAML::Node& node)
        {
            std::uint16_t operation = node["operation"].as<std::uint16_t>();
            std::uint16_t resType = node["resourceType"].as<std::uint16_t>();
            std::string siteCode = node["siteCode"].as<std::string>();
            std::string hlcCode = node["hlcCode"].as<std::string>();
            std::uint16_t slotCode = node["slotCode"].as<std::uint16_t>();
            std::uint64_t mapId = node["mapId"].as<uint64_t>();
            std::string  routeCode = node["routeCode"].as<std::string>();
            std::string routeName = node["routeName"].as<std::string>();
            int time = node["time"].as<int>();
            std::uint16_t model = node["model"].as<std::uint16_t>();
            std::string mapPath = node["mapPath"].as<std::string>();
            std::string pngPath = node["pngPath"].as<std::string>();
            std::string routePath = node["routePath"].as<std::string>();
            std::string semanticPath = node["semanticPath"].as<std::string>();
            if(node["configState"])
            {
                uint16_t configState = node["configState"].as<uint16_t>();
            }
            std::cout << "ParseItem success." << siteCode;
            return true;
        }

    }
}