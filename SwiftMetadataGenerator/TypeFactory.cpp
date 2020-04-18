//
//  TypeFactory.c
//  EmbeddingSourceKitGuide
//
//  Created by Teodor Dermendzhiev on 19.03.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#include "TypeFactory.h"

shared_ptr<Type> TypeFactory::getInstanceType()
{
    static shared_ptr<Type> type(new Type(TypeType::TypeInstanceType));
    return type;
}


