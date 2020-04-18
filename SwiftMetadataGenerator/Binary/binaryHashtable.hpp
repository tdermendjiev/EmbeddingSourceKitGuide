//
//  binaryHashtable.hpp
//  SwiftMetadataGenerator
//


#ifndef binaryHashtable_hpp
#define binaryHashtable_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "binaryStructures.hpp"

namespace binary {

class BinaryHashtable {
private:
    std::vector<std::vector<std::tuple<std::string, MetaFileOffset>>> elements;
    
    unsigned int hash(std::string value);
    
public:
    BinaryHashtable(int size) {
        this->elements = std::vector<std::vector<std::tuple<std::string, MetaFileOffset>>> (size);
    }
    
    
};


}

#endif /* binaryHashtable_hpp */
