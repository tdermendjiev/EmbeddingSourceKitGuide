//
//  MetaFactory.cpp
//  EmbeddingSourceKitGuide
//
//  Created by Teodor Dermendzhiev on 19.03.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#include "MetaFactory.hpp"
#include <iostream>
#include <stack>

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
//    if (!resetCached && cachedMetaIt != _cache.end()) {
//        Meta* meta = cachedMetaIt->second.first.get();
//        if (auto creationException = cachedMetaIt->second.second.get()) {
////            POLYMORPHIC_THROW(creationException);
//        }
//
//        /* TODO: The meta object is not guaranteed to be fully initialized. If the meta object is in the creation stack
//             * it will appear in cache, but will not be fully initialized. This may cause some inconsistent results.
//             * */
//
//        return meta;
//    }

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
        populateIdentificationFields(decl, insertedMetaPtrRef.get());
        createFromFunction(decl, insertedMetaPtrRef.get()->as<SwiftFunction>());
        return insertedMetaPtrRef.get();
    } else if (strcmp(kindName, "source.lang.swift.decl.function.method.instance") == 0) {
//        should throw
        
    }
    return nullptr;
};

void MetaFactory::createFromFunction(const sourcekitd_variant_t function, SwiftFunction& functionMeta) {
    populateMetaFields(function, &functionMeta);
//    functionMeta.signature.push_back(_typeFactory.create(getFunctionReturnType(function)).get());
}

void MetaFactory::populateIdentificationFields(const sourcekitd_variant_t& decl, Meta* meta) {
    meta->declaration = &decl;
    std::cout << stringForKey(&decl, "key.name");
    meta->name = stringForKey(&decl, "key.name");
    meta->jsName = stringForKey(&decl, "key.name");
    string mangled = stringForKey(&decl, "key.usr").replace(0,3, "$s");
    meta->mangledName = mangled.substr(0, mangled.size() - 1);
}

void MetaFactory::pushReturnType(SwiftFunction* meta, std::string returnTypeString) {
    if ( returnTypeString.compare("Swift.String") == 0) {
        meta->signature.push_back(_typeFactory.getInstanceType().get());
    }
}

bool MetaFactory::populateSignature(SwiftFunction* meta, const char* demangledName) {
    std::stack<char> s;
    char x;
    std::string expr;
    expr = demangledName;
    int start = 0;
    int end = 0;
    std::string returnTypeString = "";
    std::string paramsString = "";
    for (int i=0; i<expr.length(); i++){
        if (expr[i]=='(') {
            s.push(expr[i]);
            if (start == 0) {
                start = i;
            }
            
            continue;
        }
        
              switch (expr[i])
              {
              case ')':
        
                  x = s.top();
                  s.pop();
                  if (x!= '(')
                      return false;
                  if(s.empty()) {
                      end = i;
                      paramsString = expr.substr (start, end - start +1);
                      int returnStart = end+5;
                      returnTypeString = expr.substr(returnStart, expr.length() - returnStart);
                      std::cout <<"\n" << paramsString << "\n";
                  }
                      
                  break;
        
              default:
                  break;
              }
    }
    
    pushReturnType(meta, returnTypeString);
    //pushParamTypes
    
    return true;
}

void MetaFactory::populateMetaFields(const sourcekitd_variant_t& decl, Meta* meta) {
    char* output = new char;
    if (_demangler.demangleFunction(meta->mangledName.c_str(), output)) {
        if (SwiftFunction* func = dynamic_cast<SwiftFunction*>(meta)) {
            populateSignature(func, output);
        }

    }
    delete output;
    
}

std::string getFunctionReturnType(const sourcekitd_variant_t& function) {
    return "";
}






