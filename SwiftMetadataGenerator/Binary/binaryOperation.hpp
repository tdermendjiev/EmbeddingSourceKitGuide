//
//  binaryOperation.hpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 22.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef binaryOperation_hpp
#define binaryOperation_hpp

#include "stream.h"

namespace binary {
class BinaryOperation {
protected:
    std::shared_ptr<utils::Stream> _stream;

public:
    BinaryOperation(std::shared_ptr<utils::Stream> stream)
    {
        this->_stream = stream;
    }

    utils::Stream* baseStream()
    {
        return this->_stream.get();
    }
};
}


#endif /* binaryOperation_hpp */
