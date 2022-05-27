//
// Created by dylan liang on 2022/5/20.
//

#ifndef BASIC_RUN_CONFIG_H
#define BASIC_RUN_CONFIG_H


#include <string>

class Config {
    std::string conf_path_;
public:
    Config(){

    }

    void init()
    {

    }

    static std::string get(std::string key){
        if(key == "port"){
            return "9980";
        }

    }

    static void set(std::string key,std::string value){

    }
};


#endif //BASIC_RUN_CONFIG_H
