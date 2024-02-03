#include "BootTarget.hpp"

#include <iostream>
#include "com.h"

BootTarget::BootTarget(const char* port) {
    ComInit();
}

BootTarget::~BootTarget() {
    ComDeInit();
}

void BootTarget::Connect() {
  
}