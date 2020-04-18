//
//  memoryStream.hpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 18.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef memoryStream_hpp
#define memoryStream_hpp

#include <stdio.h>
#include "stream.h"

namespace utils {

class MemoryStream: public Stream {
private:
    std::vector<uint8_t> _heap;
    
public:
    virtual ~MemoryStream() { }
    
    virtual unsigned long size() override;
    
    virtual uint8_t read_byte() override;
    
    virtual void push_byte(uint8_t b) override;
    
    std::vector<uint8_t>::iterator begin();
    
    std::vector<uint8_t>::iterator end();
};

}

#endif /* memoryStream_hpp */
