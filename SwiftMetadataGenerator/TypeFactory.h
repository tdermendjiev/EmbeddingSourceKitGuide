//
//  TypeFactory.h
//  EmbeddingSourceKitGuide
//
//  Created by Teodor Dermendzhiev on 19.03.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef TypeFactory_h
#define TypeFactory_h

#include <stdio.h>
#include "CreationException.h"
#include "SwiftMetaEntity.hpp"
#include "TypeEntities.hpp"

class MetaFactory;

class TypeFactory {
public:
    TypeFactory(MetaFactory* metaFactory)
        : _metaFactory(metaFactory)
        , _cache()
    {
    }

    static std::shared_ptr<Type> getVoid();

    static std::shared_ptr<Type> getBool();
    
    static std::shared_ptr<Type> getInstanceType();

    std::shared_ptr<Type> create(const std::string type);

private:
    MetaFactory* _metaFactory;
    typedef std::unordered_map<std::string, std::pair<std::shared_ptr<Type>, std::unique_ptr<CreationException> > > Cache;
    Cache _cache;
};

#endif /* TypeFactory_h */
