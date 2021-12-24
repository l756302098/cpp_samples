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
    }
}