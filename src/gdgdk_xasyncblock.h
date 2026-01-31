#ifndef GDGDK_XASYNCBLOCK_H
#define GDGDK_XASYNCBLOCK_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <variant/callable.hpp>
#include "gdgdk.h"
#include <XAsync.h>

struct XAsyncBlock;
namespace godot {

class GDGDK_XAsyncBlock : public RefCounted {
    GDCLASS(GDGDK_XAsyncBlock, RefCounted)

private:
    XAsyncBlock* _block = nullptr;

protected:
    static void _bind_methods();
    virtual void _notification(int p_what);

public:
    GDGDK_XAsyncBlock();
    static Ref<GDGDK_XAsyncBlock> create(XTaskQueueHandle queue);

    inline XAsyncBlock* get_block() { return _block; }
    void set_callback(XAsyncCompletionRoutine* callback);
    void emit(Dictionary data);
};
}


#endif