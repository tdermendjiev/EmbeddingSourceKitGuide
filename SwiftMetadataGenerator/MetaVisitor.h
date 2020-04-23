//
//  MetaVisitor.h
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 22.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef MetaVisitor_h
#define MetaVisitor_h

namespace Meta {

class InterfaceMeta;
class ProtocolMeta;
class CategoryMeta;
class FunctionMeta;
class StructMeta;
class UnionMeta;
class EnumMeta;
class VarMeta;
class MethodMeta;
class PropertyMeta;
class EnumConstantMeta;

class MetaVisitor {
public:

    virtual void visit(SwiftFunction* meta) = 0;

};
}


#endif /* MetaVisitor_h */
