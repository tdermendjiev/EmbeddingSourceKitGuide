//
//  stream.h
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 18.04.20.


#ifndef stream_h
#define stream_h

#include <stdint.h>
#include <vector>

namespace utils {

class Stream {
protected:
    unsigned long _position;
    
public:
    virtual unsigned long position() {
        return this->_position;
    }
    
    virtual void set_position(unsigned long p) {
        this->_position = p;
    }
    
    virtual unsigned long size() = 0;
    
    virtual uint8_t read_byte() = 0;
    
    virtual void push_byte(uint8_t b) = 0;
    
    virtual void operator<<(uint8_t b) {
        this->push_byte(b);
    }
};


}


#endif /* stream_h */
