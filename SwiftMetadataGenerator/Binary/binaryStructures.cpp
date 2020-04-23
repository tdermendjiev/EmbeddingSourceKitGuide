//
//  binaryStructures.cpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 18.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#include "binaryStructures.hpp"
#include "binaryWriter.hpp"

binary::MetaFileOffset binary::FunctionMeta::save(BinaryWriter& writer)
{
    binary::MetaFileOffset offset = Meta::save(writer);
    writer.push_pointer(this->_encoding);
    return offset;
}

binary::MetaFileOffset binary::FunctionEncoding::save(binary::BinaryWriter& writer)
{
    binary::MetaFileOffset offset = TypeEncoding::save(writer);
    writer.push_byte(this->_encodingsCount);
    for (int i = 0; i < this->_encodingsCount; i++) {
        this->_encodings[i]->save(writer);
    }
    return offset;
}

binary::MetaFileOffset binary::TypeEncoding::save(binary::BinaryWriter& writer)
{
    binary::MetaFileOffset offset = TypeEncoding::save(writer);
    return offset;
}

binary::MetaFileOffset binary::Meta::save(binary::BinaryWriter& writer)
{
    binary::MetaFileOffset offset = Meta::save(writer);
    return offset;
}
