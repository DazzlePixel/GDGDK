#ifndef GDGDK_H
#define GDGDK_H

#include <godot_cpp/classes/object.hpp>

namespace godot {
class GDGDK : public Object {
    GDCLASS(GDGDK, Object)

private:
    static GDGDK* _instance;
    bool _initialized = false;

/*------------------------------------------------------------------------ */

public:
    static GDGDK* get_instance();

    int initialize_gdk();

protected:
    static void _bind_methods();
    void _notification(int p_what);
};
}


#endif
