//
//  binarySerializer.cpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 22.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#include "binarySerializer.hpp"

void binary::BinarySerializer::serializeBase(::Meta::Meta* meta, binary::Meta& binaryMetaStruct)
{

}

void binary::BinarySerializer::start(std::vector< ::Meta::Meta*>& container) {
}

void binary::BinarySerializer::finish(std::vector< ::Meta::Meta*>& containerr) {
}

void binary::BinarySerializer::serializeContainer(std::vector<::Meta::Meta*>& container) {
//    this->start(container);
//    for (std::pair<clang::Module*, std::vector< ::Meta::Meta*> >& module : container) {
//        for (::Meta::Meta* meta : module.second) {
//            meta->visit(this);
//        }
//    }
//    this->finish(container);
}

void binary::BinarySerializer::visit(::Meta::SwiftFunction* Meta) {
    
}
