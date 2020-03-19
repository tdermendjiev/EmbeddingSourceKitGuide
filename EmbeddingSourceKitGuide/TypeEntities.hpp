//
//  TypeEntities.hpp
//  EmbeddingSourceKitGuide
//
//  Created by Teodor Dermendzhiev on 18.03.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef TypeEntities_hpp
#define TypeEntities_hpp

#include <stdio.h>
#include "Noncopyable.h"
#include "TypeVisitor.h"

enum TypeType {
    TypeVoid,
    TypeBool,
    TypeInt,
    TypeFloat,
    TypeDouble,
    TypeProtocol,
    TypeClass,
    TypeArray,
    TypePointer,
    TypeBlock,
    TypeFunctionPointer,
    TypeInterface,
    TypeStruct,
    TypeEnum,
    TypeTypeArgument
};

class Type {
    MAKE_NONCOPYABLE(Type);

public:
    Type(TypeType type)
        : type(type)
    {
    }

    TypeType getType() const
    {
        return type;
    }

    template <class T>
    const T& as() const
    {
        return *static_cast<const T*>(this);
    }

    template <class T>
    T& as()
    {
        return *static_cast<T*>(this);
    }

    bool is(TypeType type) const
    {
        return this->type == type;
    }
    
    template <class T>
    T visit(TypeVisitor<T>& visitor) const
    {
        switch (this->type) {
        case TypeVoid:
            return visitor.visitVoid();
        case TypeBool:
            return visitor.visitBool();
        case TypeInt:
            return visitor.visitInt();
        case TypeFloat:
            return visitor.visitFloat();
        case TypeDouble:
            return visitor.visitDouble();
        default:
                return nullptr;
                
        }
    }


protected:
    TypeType type;
};

#endif /* TypeEntities_hpp */
