//
//  metaFile.hpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 18.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef metaFile_hpp
#define metaFile_hpp

#include <stdio.h>
#include "binaryHashtable.hpp"
#include "memoryStream.hpp"
#include "binaryReader.hpp"
#include "binaryWriter.hpp"

namespace binary {

class MetaFile {
private:
    std::unique_ptr<BinaryHashtable> _globalTableSymbolsJs;
    std::shared_ptr<utils::MemoryStream> _heap;
    
public:
    MetaFile(int size) {
        size = std::max(size, 100);
        this->_globalTableSymbolsJs = std::unique_ptr<BinaryHashtable>(new BinaryHashtable(size));
        this->_heap = std::shared_ptr<utils::MemoryStream>(new utils::MemoryStream());
        this->_heap->push_byte(0);
    }
    
    MetaFile() : MetaFile(10) { }
    
    unsigned int size();
    
    BinaryWriter heap_writer();
    /*
         * \brief Creates a \c BinaryReader for this file heap
         */
    BinaryReader heap_reader();

    /// I/O
    /*
         * \brief Writes this file to the filesystem with the specified name.
         * \param filename The filename of the output file
         */
    void save(std::string filename);
    /*
         * \brief Writes this file to a stream.
         * \param stream
         */
    void save(std::shared_ptr<utils::Stream> stream);
    
    
};


}

#endif /* metaFile_hpp */
