/*
 * YamlDemo.h
 *
 *  Created on: Dec 03, 2021
 *      Author: liyanlong
 */
#ifndef YAML_IST_H_
#define YAML_IST_H_

#include <yaml-cpp/yaml.h>

namespace yaml
{
    namespace demo
    {
        class ISTDemo
        {
        public:
            ISTDemo(/* args */);
            ~ISTDemo();
            void ReadAndWriteYaml();
            bool SaveToYaml();
        };
    }
}
#endif