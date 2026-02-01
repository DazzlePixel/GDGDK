#ifndef GDGDK_H
#define GDGDK_H

#include <variant/callable.hpp>
#include <godot_cpp/classes/object.hpp>
#include <Windows.h>
#include <XError.h>
#include <XTaskQueue.h>
#include <core/binder_common.hpp>
#include <core/gdvirtual.gen.inc>
#include <XUser.h>

namespace godot {

class GDKXUserChangeEvent: public Object {
    GDCLASS(GDKXUserChangeEvent, Object)
    
protected:
    static void _bind_methods();
    
public:
    enum Enum: uint32_t {
        SignedInAgain = 0,
        SigningOut = 1,
        SignedOut = 2,
        Gamertag = 3,
        GamerPicture = 4,
        Privileges = 5
    };
};
}

VARIANT_ENUM_CAST(GDKXUserChangeEvent::Enum);

namespace godot {
    class GDGDKLogger;
class GDGDK : public Object {
    GDCLASS(GDGDK, Object)

private:
    static GDGDK* _instance;
    bool _initialized = false;
    GDGDKLogger* _logger = nullptr;
    XTaskQueueHandle _async_queue = nullptr;
    XTaskQueueRegistrationToken _change_event_token;

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

    GDVIRTUAL2(_user_change_event, int, GDKXUserChangeEvent::Enum);
protected:
    static void _bind_methods();
    void _notification(int p_what);

private:
    void bind_callbacks();
    void unbind_callbacks();
};
}

#endif
