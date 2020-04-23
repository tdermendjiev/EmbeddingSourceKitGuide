//
//  binarySerializer.hpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 22.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef binarySerializer_hpp
#define binarySerializer_hpp

#include <stdio.h>
#include "SwiftMetaEntity.hpp"
#include "metaFile.hpp"
#include "binaryTypeEncodingSerializer.hpp"
#include "MetaVisitor.h"
#include "binaryWriter.hpp"
#include <map>

namespace binary {
/*
     * \class BinarySerializer
     * \brief Applies the Visitor pattern for serializing \c Meta::Meta objects in binary format.
     */
class BinarySerializer : public ::Meta::MetaVisitor {
private:
    MetaFile* file;
    BinaryWriter heapWriter;
    BinaryTypeEncodingSerializer typeEncodingSerializer;


    void serializeBase(::Meta::Meta* Meta, binary::Meta& binaryMetaStruct);


public:
    BinarySerializer(MetaFile* file)
        : heapWriter(file->heap_writer())
        , typeEncodingSerializer(heapWriter)
    {
        this->file = file;
    }

    void serializeContainer(std::vector<::Meta::Meta*>& container);

    void start(std::vector<::Meta::Meta*>& container);

    void finish(std::vector<::Meta::Meta*>& container);
    virtual void visit(::Meta::SwiftFunction* Meta) override;

//    virtual void visit(::Meta::InterfaceMeta* Meta) override;
//
//    virtual void visit(::Meta::ProtocolMeta* Meta) override;
//
//    virtual void visit(::Meta::CategoryMeta* Meta) override;
//
//    virtual void visit(::Meta::FunctionMeta* Meta) override;
//
//    virtual void visit(::Meta::StructMeta* Meta) override;
//
//    virtual void visit(::Meta::UnionMeta* Meta) override;
//
//    virtual void visit(::Meta::EnumMeta* Meta) override;
//
//    virtual void visit(::Meta::VarMeta* Meta) override;
//
//    virtual void visit(::Meta::EnumConstantMeta* Meta) override;
//
//    virtual void visit(::Meta::PropertyMeta* Meta) override;
//
//    virtual void visit(::Meta::MethodMeta* Meta) override;
};
}


#endif /* binarySerializer_hpp */
