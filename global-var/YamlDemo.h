/*
 * YamlDemo.h
 *
 *  Created on: Dec 03, 2021
 *      Author: liyanlong
 */
#ifndef YAML_DEMO_H_
#define YAML_DEMO_H_

#include <yaml-cpp/yaml.h>
#include "DDSConfig.h"

namespace yaml
{
    namespace demo
    {
        class YamlDemo
        {
        public:
            YamlDemo(/* args */);
            ~YamlDemo();
            long GetAddress();
            void ReadAndWriteYaml();
            bool SaveToYaml();
            void SimUpdateYaml();
            void DelYaml();
            void DelYaml2();
            void DelYaml3();
            bool ParseRouteInfo(const YAML::Node& info);
            void TestRead();
            void TestAdd();
            bool TestRouteInfo(const YAML::Node& info);
        };
    }
}
#endif