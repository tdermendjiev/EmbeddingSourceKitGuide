//
//  memoryStream.cpp
//  SwiftMetadataGenerator
//
//  Created by Teodor Dermendzhiev on 18.04.20.
//  Copyright © 2020 Teodor Dermendzhiev. All rights reserved.
//

#include "memoryStream.hpp"
#include <vector>

unsigned long utils::MemoryStream::size() {
    return this->_heap.size();
}

uint8_t utils::MemoryStream::read_byte() {
    return this->_heap[this->_position++];
}

void utils::MemoryStream::push_byte(uint8_t b) {
    this->_heap.insert(this->_heap.begin() + this->_position, b);
    this->_position++;
}

std::vector<uint8_t>::iterator utils::MemoryStream::begin() {
    return this->_heap.begin();
}

std::vector<uint8_t>::iterator utils::MemoryStream::end() {
    return this->_heap.end();
}
