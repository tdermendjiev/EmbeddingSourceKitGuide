//
//  MetaFactory.hpp
//  EmbeddingSourceKitGuide
//
//  Created by Teodor Dermendzhiev on 19.03.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef MetaFactory_hpp
#define MetaFactory_hpp

#include <stdio.h>
#include "SwiftMetaEntity.hpp"
//#include "TypeFactory.h"
#include "Noncopyable.h"
#include "sourcekitd.h"
#include "CreationException.h"
#include "TypeFactory.h"
#include "Demangler.hpp"

typedef std::unordered_map<const sourcekitd_variant_t*, std::pair<std::unique_ptr<Meta>, std::unique_ptr<CreationException>> > Cache;
typedef std::unordered_map<const Meta*, const sourcekitd_variant_t*> MetaToDeclMap;

class MetaFactory {
public:
    MetaFactory():
        _typeFactory(this)
    {
        _demangler = Demangler();
    }

    Meta* create(const sourcekitd_variant_t& decl, bool resetCached = false);
    
    Cache& getCache()
    {
        return this->_cache;
    }

//    bool tryCreate(const sourcekitd_variant_t decl, Meta** meta);

//    TypeFactory& getTypeFactory()
//    {
//        return this->_typeFactory;
//    }

private:
    void createFromFunction(const sourcekitd_variant_t decl, SwiftFunction& functionMeta);
//
//    void createFromVar(const clang::VarDecl& var, VarMeta& varMeta);
//
//    void createFromEnum(const clang::EnumDecl& enumeration, EnumMeta& enumMeta);
//
//    void createFromEnumConstant(const clang::EnumConstantDecl& enumConstant, EnumConstantMeta& enumMeta);
//
//    void createFromInterface(const clang::ObjCInterfaceDecl& interface, InterfaceMeta& interfaceMeta);
//
//    void createFromProtocol(const clang::ObjCProtocolDecl& protocol, ProtocolMeta& protocolMeta);
//
//    void createFromCategory(const clang::ObjCCategoryDecl& category, CategoryMeta& categoryMeta);
//
//    void createFromMethod(const clang::ObjCMethodDecl& method, MethodMeta& methodMeta);
//
//    void createFromProperty(const clang::ObjCPropertyDecl& property, PropertyMeta& propertyMeta);
//
    void populateIdentificationFields(const sourcekitd_variant_t& decl, Meta* meta);
//
    void populateMetaFields(const sourcekitd_variant_t& decl, Meta* meta);
//
//    void populateBaseClassMetaFields(const clang::ObjCContainerDecl& decl, BaseClassMeta& baseClassMeta);
    
    void pushReturnType(SwiftFunction* meta, std::string returnTypeString);
    
    bool populateSignature(SwiftFunction* meta, const char* demangledName);

    TypeFactory _typeFactory;
    Cache _cache;
    MetaToDeclMap _metaToDecl;
    Demangler _demangler;
};

#endif /* MetaFactory_hpp */
