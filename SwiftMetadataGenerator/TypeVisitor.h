//
//  TypeVisitor.h
//  EmbeddingSourceKitGuide
//
//  Created by Teodor Dermendzhiev on 18.03.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef TypeVisitor_h
#define TypeVisitor_h

template <typename T_RESULT>
class TypeVisitor {
public:
    virtual T_RESULT visitVoid() = 0;

//    virtual T_RESULT visitBool() = 0;
//
//    virtual T_RESULT visitInt() = 0;
//
//    virtual T_RESULT visitFloat() = 0;
//
//    virtual T_RESULT visitDouble() = 0;
};


#endif /* TypeVisitor_h */
