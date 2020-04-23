//
//  binaryStructures.hpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 18.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef binaryStructures_hpp
#define binaryStructures_hpp

#include <stdint.h>
#include <vector>

namespace binary {
typedef int32_t MetaFileOffset;
typedef int32_t MetaArrayCount;

class MetaFile;
class BinaryWriter;

enum BinaryTypeEncodingType : uint8_t {
    Void,
    FunctionPointer
};

// BinaryMetaType values must not exceed
enum BinaryMetaType : uint8_t {
    Undefined = 0,
    Function
};

#pragma pack(push, 1)
struct Meta {
public:
    Meta(BinaryMetaType type)
        : _flags(type & 0x7) // 7 = 111 -> get only the first 3 bits of the type
    {
    }

    MetaFileOffset _names = 0;
    MetaFileOffset _topLevelModule = 0;
    uint16_t _flags = 0;
    uint8_t _introduced = 0;

    virtual MetaFileOffset save(BinaryWriter& writer) = 0;
};


struct FunctionMeta : Meta {
public:
    FunctionMeta()
        : Meta(BinaryMetaType::Function)
    {
    }

    MetaFileOffset _encoding = 0;

    virtual MetaFileOffset save(BinaryWriter& writer) override;
};

#pragma pack(pop)

// type encoding

struct TypeEncoding {
public:
    TypeEncoding(BinaryTypeEncodingType t)
        : _type(t)
    {
    }

    BinaryTypeEncodingType _type;

    virtual MetaFileOffset save(BinaryWriter& writer);
    virtual ~TypeEncoding() { }
};

struct FunctionEncoding : public TypeEncoding {
public:
    FunctionEncoding()
        : TypeEncoding(BinaryTypeEncodingType::FunctionPointer)
    {
    }

    uint8_t _encodingsCount;
    std::vector<std::unique_ptr<TypeEncoding>> _encodings;

    virtual MetaFileOffset save(BinaryWriter& writer) override; //https://stackoverflow.com/questions/44413478/abstract-class-and-unique-pointer
};

}



#endif /* binaryStructures_hpp */
