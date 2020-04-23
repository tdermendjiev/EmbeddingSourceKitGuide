//
//  metaFile.cpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 18.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#include "metaFile.hpp"

binary::BinaryWriter binary::MetaFile::heap_writer()
{
    return binary::BinaryWriter(this->_heap);
}

binary::BinaryReader binary::MetaFile::heap_reader()
{
    return binary::BinaryReader(this->_heap);
}
