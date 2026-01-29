#ifndef GDGDK_XASYNCBLOCK_H
#define GDGDK_XASYNCBLOCK_H

#include <godot_cpp/classes/ref_counted.hpp>
#include "gdgdk_macros.h"

struct XAsyncBlock;
namespace godot {
    
class GDGDK_XAsyncBlock : public RefCounted {
    GDCLASS(GDGDK_XAsyncBlock, RefCounted)
    GDKOBJECT(GDGDK_XAsyncBlock, XAsyncBlock*)

protected:
    static void _bind_methods();
    virtual void _notification(int p_what);
};
}


#endif