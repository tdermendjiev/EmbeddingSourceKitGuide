//
//  MetaFactory.cpp
//  EmbeddingSourceKitGuide
//
//  Created by Teodor Dermendzhiev on 19.03.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#include "MetaFactory.hpp"
#include <iostream>

std::string stringForKey(const sourcekitd_variant_t* object, std::string key) {
    char* result = sourcekitd_variant_description_copy(sourcekitd_variant_dictionary_get_value(*object, sourcekitd_uid_get_from_cstr(key.c_str())));
    return string(result);
}

template<class T>
void resetMetaAndAddToMap(std::unique_ptr<Meta>& metaPtrRef, MetaToDeclMap& metaToDecl, const sourcekitd_variant_t& decl) {
    if (metaPtrRef.get()) {
        // The pointer has been previously allocated. Reset it's value and assert that it's already present in the map
        static_cast<T&>(*metaPtrRef) = T();
        assert(metaToDecl[metaPtrRef.get()] == &decl);
    } else {
        // Allocate memory and add to map
        metaPtrRef.reset(new T());
        metaToDecl[metaPtrRef.get()] = &decl;
    }

//    if (decl.isInvalidDecl()) {
//        std::string declDump;
//        llvm::raw_string_ostream os(declDump);
//        decl.dump(os);
//        throw MetaCreationException(metaPtrRef.get(), CreationException::constructMessage("Invalid decl.", os.str()), true);
//    }
}

Meta* MetaFactory::create(const sourcekitd_variant_t& decl, bool resetCached) {
    char* kindName = sourcekitd_variant_description_copy(sourcekitd_variant_dictionary_get_value(decl, sourcekitd_uid_get_from_cstr("key.kind")));
    
    // Check for cached Meta
    Cache::iterator cachedMetaIt = _cache.find(&decl);
    if (!resetCached && cachedMetaIt != _cache.end()) {
        Meta* meta = cachedMetaIt->second.first.get();
        if (auto creationException = cachedMetaIt->second.second.get()) {
//            POLYMORPHIC_THROW(creationException);
        }

        /* TODO: The meta object is not guaranteed to be fully initialized. If the meta object is in the creation stack
             * it will appear in cache, but will not be fully initialized. This may cause some inconsistent results.
             * */

        return meta;
    }

    if (cachedMetaIt == _cache.end()) {
        std::pair<Cache::iterator, bool> insertionResult = _cache.insert(std::make_pair(&decl, std::make_pair(nullptr, nullptr)));
        assert(insertionResult.second);
        cachedMetaIt = insertionResult.first;
    }
    std::unique_ptr<Meta>& insertedMetaPtrRef = cachedMetaIt->second.first;
    std::unique_ptr<CreationException>& insertedException = cachedMetaIt->second.second;
        
    if (strcmp(kindName, "source.lang.swift.decl.class") == 0) {
//        SwiftMetaEntity* meta = createClass(obj);
//        metaEntities.push_back(meta);
    } else if (strcmp(kindName, "source.lang.swift.decl.function.free") == 0) {
        resetMetaAndAddToMap<SwiftFunction>(insertedMetaPtrRef, this->_metaToDecl, decl);
        populateIdentificationFields(decl, *insertedMetaPtrRef.get());
        createFromFunction(decl, insertedMetaPtrRef.get()->as<SwiftFunction>());
//        freeFunctions.push_back(createFunction(obj));
    } else if (strcmp(kindName, "source.lang.swift.decl.function.method.instance") == 0) {
//        should throw
        
    }
    return nullptr;
};

void MetaFactory::createFromFunction(const sourcekitd_variant_t function, SwiftFunction& functionMeta) {
    populateMetaFields(function, functionMeta);
//    functionMeta.signature.push_back(_typeFactory.create(getFunctionReturnType(function)).get());
}

void MetaFactory::populateIdentificationFields(const sourcekitd_variant_t& decl, Meta& meta) {
    meta.declaration = &decl;
    std::cout << stringForKey(&decl, "key.name");
    meta.name = stringForKey(&decl, "key.name");
    meta.jsName = stringForKey(&decl, "key.name");
    meta.mangledName = stringForKey(&decl, "key.usr");
}

void MetaFactory::populateMetaFields(const sourcekitd_variant_t& decl, Meta& meta) {
    
}

std::string getFunctionReturnType(const sourcekitd_variant_t& function) {
    return "";
}




