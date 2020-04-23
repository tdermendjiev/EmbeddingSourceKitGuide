//
//  binaryTypeEncodingSerializer.hpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 22.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef binaryTypeEncodingSerializer_hpp
#define binaryTypeEncodingSerializer_hpp

#include "SwiftMetaEntity.hpp"
#include "binaryStructures.hpp"
#include "binaryWriter.hpp"
#include <vector>

using namespace std;

namespace binary {
/*
     * \class BinaryTypeEncodingSerializer
     * \brief Applies the Visitor pattern for serializing \c typeEncoding::TypeEncoding objects in binary format.
     */
class BinaryTypeEncodingSerializer : public TypeVisitor<unique_ptr<binary::TypeEncoding> > {
private:
    BinaryWriter _heapWriter;


public:
    BinaryTypeEncodingSerializer(BinaryWriter& heapWriter)
        : _heapWriter(heapWriter)
    {
    }

    MetaFileOffset visit(std::vector<::Meta::Type*>& types);
    
    virtual unique_ptr<TypeEncoding> visitVoid() override;
};
}


#endif /* binaryTypeEncodingSerializer_hpp */
