#ifndef GDGDK_USER_H
#define GDGDK_USER_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <core/binder_common.hpp>
#include "gdgdk_xasyncblock.h"
#include <XUser.h>

enum GDKXUserAddOptions : uint32_t {
    None = 0x00,  
    AddDefaultUserSilently = 0x01,  
    AllowGuests = 0x02,  
    AddDefaultUserAllowingUI = 0x04,
};
VARIANT_BITFIELD_CAST(GDKXUserAddOptions);

class XUser;

namespace godot {
class GDGDKUser : public RefCounted {
    GDCLASS(GDGDKUser, RefCounted)

private:
    XUserHandle _user = nullptr;

protected:
    static void _bind_methods();

public:
    static Ref<GDGDKUser> create(XUserHandle user);
    static Ref<GDGDK_XAsyncBlock> add_user_async(BitField<GDKXUserAddOptions> options);
    static Ref<GDGDK_XAsyncBlock> add_user_by_id_with_ui_async(int64_t user_id);
    static int get_max_users();
    static Ref<GDGDKUser> find_user_by_id(int64_t user_id);
    static bool is_sign_out_present();
    static Ref<GDGDKUser> find_user_by_local_id(int64_t local_id);
    // static Ref<GDGDKUser> find_user_for_device(const PackedByteArray& device_id);

    Ref<GDGDKUser> duplicate() const;
    void close_handle();
    bool compare(const Ref<GDGDKUser> other) const;
    Ref<GDGDK_XAsyncBlock> sign_out();
    int64_t get_id() const;
    int64_t get_local_id() const;
};
}

#endif