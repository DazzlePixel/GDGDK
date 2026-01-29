#include "gdgdk_xasyncblock.h"

using namespace godot;

void GDGDK_XAsyncBlock::_bind_methods() {
    
}

void GDGDK_XAsyncBlock::_notification(int p_what) {
    if (p_what == NOTIFICATION_PREDELETE && _native_object) {
        delete _native_object;
        _native_object = nullptr;
    }
}

Ref<GDGDK_XAsyncBlock> GDGDK_XAsyncBlock::create(XAsyncBlock* block) {
    Ref<GDGDK_XAsyncBlock> wrapper;
    if (block) {
        wrapper.instantiate();
        wrapper->_native_object = block;
    }

    return wrapper;
}