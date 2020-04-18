#include <iostream>
#include "sourcekitd.h"
#include "SwiftMetaEntity.hpp"
#include <vector>
#include "MetaFactory.hpp"


std::vector<SwiftClass*> classes;
std::vector<SwiftFunction*> freeFunctions;
std::vector<Meta*> metaEntities;
MetaFactory* _metaFactory;

char* stringForKey(sourcekitd_variant_t* object, std::string key) {
    char* result = sourcekitd_variant_description_copy(sourcekitd_variant_dictionary_get_value(*object, sourcekitd_uid_get_from_cstr(key.c_str())));
    return result;
}

SwiftMethod* createMethod(sourcekitd_variant_t* obj) {
    
    SwiftMethod* newMethod = new SwiftMethod();
    newMethod->name = stringForKey(obj, "key.name");
    newMethod->mangledName = stringForKey(obj, "key.usr");
    
    return newMethod;
}

SwiftClass* createClass(sourcekitd_variant_t* obj) {
    
    SwiftClass* newClass = new SwiftClass();
    newClass->name = stringForKey(obj, "key.name");
    newClass->mangledName = stringForKey(obj, "key.usr");
    
    sourcekitd_variant_t entities = sourcekitd_variant_dictionary_get_value(*obj,
                                                                            sourcekitd_uid_get_from_cstr("key.entities"));
    
    size_t count = sourcekitd_variant_array_get_count(entities);
            for (size_t i = 0; i < count; i++) {
                sourcekitd_variant_t entity = sourcekitd_variant_array_get_value(entities, i);
                char* kindName = sourcekitd_variant_description_copy(sourcekitd_variant_dictionary_get_value(entity, sourcekitd_uid_get_from_cstr("key.kind")));
                
                if (strcmp(kindName, "source.lang.swift.decl.class") == 0) {
                    newClass->innerClasses.push_back(createClass(&entity));
                } else if (strcmp(kindName, "source.lang.swift.decl.function.free") == 0) {
                    //should throw - no free function are declared in classes
                } else if (strcmp(kindName, "source.lang.swift.decl.function.method.instance") == 0) {
                    newClass->instanceMethods.push_back(createMethod(&entity));
                    
                }
            }
    
    return newClass;
}

SwiftFunction* createFunction(sourcekitd_variant_t* obj) {
    return nullptr;
}

void checkObject(sourcekitd_variant_t* obj) {
    char* kindName = sourcekitd_variant_description_copy(sourcekitd_variant_dictionary_get_value(*obj, sourcekitd_uid_get_from_cstr("key.kind")));
    
    if (strcmp(kindName, "source.lang.swift.decl.class") == 0) {
        Meta* meta = createClass(obj);
        metaEntities.push_back(meta);
    } else if (strcmp(kindName, "source.lang.swift.decl.function.free") == 0) {
        freeFunctions.push_back(createFunction(obj));
    } else if (strcmp(kindName, "source.lang.swift.decl.function.method.instance") == 0) {
//        should throw
        
    }
}



sourcekitd_variant_dictionary_applier_t applier = ^(sourcekitd_uid_t key, sourcekitd_variant_t value) {
       const char* keyName = sourcekitd_uid_get_string_ptr(key);
       sourcekitd_variant_type_t type = sourcekitd_variant_get_type(value);
   // std::cout << keyName;
    if (type == SOURCEKITD_VARIANT_TYPE_DICTIONARY) {
        sourcekitd_variant_dictionary_apply(value, applier);
    } else if (type == SOURCEKITD_VARIANT_TYPE_ARRAY) {
        std::cout <<  "  array\n";
        size_t count = sourcekitd_variant_array_get_count(value);
        for (size_t i = 0; i < count; i++) {
            sourcekitd_variant_t value2 = sourcekitd_variant_array_get_value(value, i);
            sourcekitd_variant_type_t type2 = sourcekitd_variant_get_type(value2);
            if (type2 == SOURCEKITD_VARIANT_TYPE_DICTIONARY) {
                checkObject(&value2);
                Meta* meta = _metaFactory->create(value2);
                if (meta) {
                    metaEntities.push_back(meta);
                }
                
                
//                sourcekitd_variant_dictionary_apply(value2, applier);
            }
        }
        return true;
    }
//        std::cout << " value" << sourcekitd_variant_description_copy(value) << "\n";
       return true;
};

int main(int argc, const char * argv[]) {
    sourcekitd_initialize();
    
    _metaFactory = new MetaFactory();
    
    // 1. Construct the request dictionary
    const char* filePath = "/Users/teodordermendzhiev/workspace/ios-runtime/examples/Gameraww/SwiftClass.swift";
    sourcekitd_object_t request = sourcekitd_request_dictionary_create(nullptr, nullptr, 0);
    sourcekitd_uid_t reqValue = sourcekitd_uid_get_from_cstr("source.request.indexsource");
    sourcekitd_uid_t reqKey = sourcekitd_uid_get_from_cstr("key.request");
    sourcekitd_request_dictionary_set_uid(request, reqKey, reqValue);
    sourcekitd_request_dictionary_set_string(request, sourcekitd_uid_get_from_cstr("key.sourcefile"), filePath);
    
    // 2. Construct the arguments array
    const sourcekitd_object_t sdk = sourcekitd_request_string_create("-sdk");
    const sourcekitd_object_t sdkPath = sourcekitd_request_string_create("/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk");
    const sourcekitd_object_t j4 = sourcekitd_request_string_create("-j4");
    const sourcekitd_object_t j4Path = sourcekitd_request_string_create("/Users/teodordermendzhiev/workspace/ios-runtime/examples/Gameraww/SwiftClass.swift");
                      sourcekitd_object_t arguments[4] = {sdk, sdkPath, j4, j4Path};
    sourcekitd_object_t args = sourcekitd_request_array_create(arguments, 4);
    
    // 3. Send the request
    sourcekitd_request_dictionary_set_value(request, sourcekitd_uid_get_from_cstr("key.compilerargs"), args);
    sourcekitd_response_t reply = sourcekitd_send_request_sync(request);
    
    bool err = sourcekitd_response_is_error(reply);
    if (err) {
        sourcekitd_error_t errType = sourcekitd_response_error_get_kind(reply);
        const char * desc = sourcekitd_response_error_get_description(reply);
        std::cout << desc << "\n";

    } else {
         sourcekitd_variant_t value = sourcekitd_response_get_value(reply);
         sourcekitd_variant_dictionary_apply(value, applier);
         char* res = sourcekitd_response_description_copy(reply);
         std::cout << res << "\n";
    }
//    sourcekitd_response_description_dump(reply);
    return 0;
 }

    
