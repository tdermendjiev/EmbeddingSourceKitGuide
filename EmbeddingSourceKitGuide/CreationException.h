//
//  CreationException.h
//  EmbeddingSourceKitGuide
//
//  Created by Teodor Dermendzhiev on 19.03.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef CreationException_h
#define CreationException_h

#include "SwiftMetaEntity.hpp"
#include <string>

class CreationException {
public:
    static std::string constructMessage(std::string outerMessage, std::string innerMessage)
    {
        return outerMessage + " --> " + innerMessage;
    }

    CreationException(std::string message, bool isError)
        : _message(message)
        , _isError(isError)
    {
    }
    
    virtual ~CreationException() { }

    virtual void polymorhicThrow() = 0;
    
    std::string getMessage() const
    {
        return _message;
    }

    virtual std::string getDetailedMessage() const
    {
        return getMessage();
    }

    bool isError() const
    {
        return _isError;
    }

private:
    std::string _message;
    bool _isError;
};

class MetaCreationException : public CreationException {
public:
    MetaCreationException(const Meta* meta, std::string message, bool isError)
        : CreationException(message, isError)
        , _meta(meta)
    {
    }

    std::string getDetailedMessage() const override
    {
        return _meta->identificationString() + " : " + this->getMessage();
    }

    const Meta* getMeta()
    {
        return _meta;
    }

//    DEFINE_POLYMORPHIC_THROW;

private:
    const Meta* _meta;
};

#endif /* CreationException_h */
