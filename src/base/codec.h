//
// Created by dylan liang on 2022/5/22.
//

#ifndef BASIC_RUN_CODEC_H
#define BASIC_RUN_CODEC_H

#include "loop/common.h"

struct Header{
    int32_t header[2];
    int16_t mode;
    FuncNoType funcNo;
    int64_t len;
};

class Codec {
    std::vector<uint8_t> buf_;
    int headerPos_ = -1;
public:
    void addData(std::vector<uint8_t> &data){
        //todo parse header
        buf_.insert(buf_.end(),data.begin(),data.end());
    }
    bool dataReady(){
        if((headerPos_ = findHeader()) == -1){
            return false;
        }
        Header *header = (Header*)(&buf_[headerPos_]);

        return buf_.size() > headerPos_ + sizeof(headerPos_) + header->len;
    }
    std::pair<FuncNoType,std::vector<uint8_t>> decode(){
        std::vector<uint8_t > content;
        Header *header = (Header*)(&buf_[headerPos_]);
        int start = headerPos_ + sizeof(header);
        content.insert(content.end(),buf_.begin()+start,buf_.begin()+start+header->len);
        return std::make_pair(header->funcNo,content);
    }
    static std::vector<uint8_t> encode(){

    }

    int findHeader(){
        int size = buf_.size()-1;
        for(int i = 1;i < size;i++){
            if(buf_[i] == 0xfe && buf_[i+1] == 0x55){
                return i;
            }
        }
        return -1;
    }

};


#endif //BASIC_RUN_CODEC_H
