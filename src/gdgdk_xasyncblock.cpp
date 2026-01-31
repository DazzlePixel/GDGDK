#include "gdgdk_xasyncblock.h"

using namespace godot;

GDGDK_XAsyncBlock::GDGDK_XAsyncBlock() {
    _block = new XAsyncBlock();
    ZeroMemory(_block, sizeof(XAsyncBlock));

    _block->context = this;
}

void GDGDK_XAsyncBlock::_bind_methods() {
    ADD_SIGNAL(MethodInfo("completed", PropertyInfo(Variant::DICTIONARY, "result")));
}

void GDGDK_XAsyncBlock::_notification(int p_what) {
    if (p_what == NOTIFICATION_PREDELETE && _block) {
        delete _block;
        _block = nullptr;
    }

    if (p_what == NOTIFICATION_PREDELETE) {
        print_line(_block != nullptr);
    }
}

Ref<GDGDK_XAsyncBlock> GDGDK_XAsyncBlock::create(XTaskQueueHandle queue) {
    Ref<GDGDK_XAsyncBlock> wrapper;
    wrapper.instantiate();
    
    XAsyncBlock* b = wrapper->_block;
    b->queue = queue;

    return wrapper;
}

void GDGDK_XAsyncBlock::set_callback(XAsyncCompletionRoutine *callback) {
    _block->callback = callback;
}

void GDGDK_XAsyncBlock::emit(Dictionary data) {
    emit_signal("completed", data);
}
