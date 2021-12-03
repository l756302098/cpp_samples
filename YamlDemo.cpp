#include "YamlDemo.h"
#include "FilePath.h"
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
            std::string dir = "/home/indemind/workspces/config";
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
                std::string routeCode = info["routeName"].as<std::string>();
                std::cout << "routeName:" << routeCode << std::endl;
            }
        }
        bool YamlDemo::SaveToYaml()
        {
            std::string dir = "/home/indemind/workspces/config";
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
                YAML::Node node;
                node["siteCode"] = "n101";
                node["hlcCode"] = "1";
                node["slotCode"] = 1;
                node["bodyNum"] = 0;
                node["machineName"] = "m18";
                node["routeName"] = "r18";
                node["size"] = 0;
                node["time"] = 0;

                config["routeList"].push_back(node);
                //write conf
                std::ofstream fout(path);
                fout << config;
                fout.close();
            }
            catch(...)
            {
                std::cout << "ocuer error" << std::endl;
            }
            
        }
    }
}