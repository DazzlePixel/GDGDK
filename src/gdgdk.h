#ifndef GDGDK_H
#define GDGDK_H

#include <variant/callable.hpp>
#include <godot_cpp/classes/object.hpp>
#include <Windows.h>
#include <XError.h>
#include <XTaskQueue.h>

namespace godot {
    class GDGDKLogger;
    class GDGDKSettings;
class GDGDK : public Object {
    GDCLASS(GDGDK, Object)

private:
    static GDGDK* _instance;
    bool _initialized = false;
    GDGDKLogger* _logger = nullptr;
    XTaskQueueHandle _async_queue = nullptr;

/*------------------------------------------------------------------------ */

public:
    GDGDK();
    ~GDGDK() = default;
    static GDGDK* get_instance();

    int initialize_gdk(const String& scid);
    String get_scid() const;
    int set_override_config(const String& override_scid, const uint32_t override_title_id);
    int set_override_locale(const char& locale);

    inline XTaskQueueHandle get_async_queue() const { return _async_queue; }
protected:
    static void _bind_methods();
    void _notification(int p_what);

private:
};
}


#endif
