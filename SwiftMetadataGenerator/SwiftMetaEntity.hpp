//
//  SwiftMetaEntity.hpp
//  EmbeddingSourceKitGuide
//
//  Created by Teodor Dermendzhiev on 15.03.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef SwiftMetaEntity_hpp
#define SwiftMetaEntity_hpp

#include <stdio.h>
#include <vector>
#include "TypeEntities.hpp"
#include <unordered_map>
#include <string>
#include "sourcekitd.h"

using namespace std;

enum MetaType {
    Undefined = 0,
    Interface,
    Function,
    Method
};

class Meta {
public:
    MetaType type = MetaType::Undefined;
    string name;
    string jsName;
    string mangledName;
    vector<Meta*> entities;
    const sourcekitd_variant_t* declaration = nullptr;
    
    string identificationString() const
    {
        return string("[Name: '") + name + "', Mangled name: '" + mangledName;
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
    
    Meta() = default;
    virtual ~Meta() = default;
    
    
    
};

class SwiftFunction: public Meta {
public:
    std::vector<Type*> signature;
    
};

class SwiftMethod: public SwiftFunction {
    
};

class SwiftClass: public Meta {
public:
    vector<SwiftMethod*> instanceMethods;
    vector<SwiftClass*> innerClasses;
};



#endif /* SwiftMetaEntity_hpp */
