/*
 * YamlDemo.h
 *
 *  Created on: Dec 03, 2021
 *      Author: liyanlong
 */
#ifndef YAML_DEMO_H_
#define YAML_DEMO_H_

#include <yaml-cpp/yaml.h>

namespace yaml
{
    namespace demo
    {
        class YamlDemo
        {
        public:
            YamlDemo(/* args */);
            ~YamlDemo();
            void ReadAndWriteYaml();
            bool SaveToYaml();
            void DelYaml();
            void DelYaml2();
        };
    }
}
#endif