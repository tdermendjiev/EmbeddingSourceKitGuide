//
//  binaryTypeEncodingSerializer.cpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 22.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#include "binaryTypeEncodingSerializer.hpp"
#include "SwiftMetaEntity.hpp"

binary::MetaFileOffset binary::BinaryTypeEncodingSerializer::visit(std::vector< ::Meta::Type*>& types)
{
    vector<unique_ptr<binary::TypeEncoding> > binaryEncodings;
    for (::Meta::Type* type : types) {
        unique_ptr<binary::TypeEncoding> binaryEncoding = type->visit(*this);
        binaryEncodings.push_back(std::move(binaryEncoding));
    }

    binary::MetaFileOffset offset = this->_heapWriter.push_arrayCount(types.size());
    for (unique_ptr<binary::TypeEncoding>& binaryEncoding : binaryEncodings) {
        binaryEncoding->save(this->_heapWriter);
    }
    return offset;
}

unique_ptr<binary::TypeEncoding> binary::BinaryTypeEncodingSerializer::visitVoid()
{
    return std::make_unique<binary::TypeEncoding>(binary::BinaryTypeEncodingType::Void);
}
