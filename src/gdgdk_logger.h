#ifndef GDGDK_LOGGER_H
#define GDGDK_LOGGER_H

#include <godot_cpp/classes/object.hpp>

namespace godot {
class GDGDKLogger : public Object {
public:
    void log(const String& msg);
    void error(const String& msg);
    void warn(const String& msg);

protected:
    static void _bind_methods();
};
}

#endif
