//
//  Demangler.hpp
//  EmbeddingSourceKitGuide
//
//  Created by Teodor Dermendzhiev on 19.03.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#ifndef Demangler_hpp
#define Demangler_hpp

#include <stdio.h>
#include <dlfcn.h>

class Demangler {
public:
    bool demangleFunction(const char* input, char* output) {
        size_t result = demangle(input, output,
                         256);
        return result > 0;
    }
    
    
    
    Demangler() {
        handle = dlopen(DemangleLibPath, RTLD_NOW);
        demangle = (size_t(*)(const char*, char*, size_t))dlsym(handle, "swift_demangle_getDemangledName");
//        const char* input = "$s10SwiftClass7aMethod6param16param2S2S_SitF";
    }
private:
    char* DemangleLibPath = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/libswiftDemangle.dylib";
    void* handle;
    size_t (*demangle) (const char*, char*, size_t) ;
};

#endif /* Demangler_hpp */
