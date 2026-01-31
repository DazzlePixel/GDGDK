#include "gdgdk_user.h"
#include "gdgdk.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void GDGDKUser::_bind_methods() {
    BIND_BITFIELD_FLAG(None);
    BIND_BITFIELD_FLAG(AddDefaultUserSilently);
    BIND_BITFIELD_FLAG(AllowGuests);
    BIND_BITFIELD_FLAG(AddDefaultUserAllowingUI);

    ClassDB::bind_static_method("GDGDKUser", D_METHOD("add_user_async", "options"), &GDGDKUser::add_user_async);
    ClassDB::bind_static_method("GDGDKUser", D_METHOD("add_user_by_id_with_ui_async", "user_id"), &GDGDKUser::add_user_by_id_with_ui_async);
    ClassDB::bind_static_method("GDGDKUser", D_METHOD("get_max_users"), &GDGDKUser::get_max_users);
    ClassDB::bind_static_method("GDGDKUser", D_METHOD("is_sign_out_present"), &GDGDKUser::is_sign_out_present);
    ClassDB::bind_static_method("GDGDKUser", D_METHOD("find_user_by_local_id", "local_id"), &GDGDKUser::find_user_by_local_id);
    ClassDB::bind_method(D_METHOD("duplicate"), &GDGDKUser::duplicate);
    ClassDB::bind_method(D_METHOD("close_handle"), &GDGDKUser::close_handle);
    ClassDB::bind_method(D_METHOD("compare", "other"), &GDGDKUser::compare);
    ClassDB::bind_method(D_METHOD("sign_out"), &GDGDKUser::sign_out);
    ClassDB::bind_method(D_METHOD("get_id"), &GDGDKUser::get_id);
    ClassDB::bind_method(D_METHOD("get_local_id"), &GDGDKUser::get_local_id);
}

Ref<GDGDKUser> GDGDKUser::create(XUserHandle user) {
    Ref<GDGDKUser> user_wrapper;
    if (user)
    {
        user_wrapper.instantiate();
        user_wrapper->_user = user;
    }
    return user_wrapper;
}

Ref<GDGDK_XAsyncBlock> GDGDKUser::add_user_async(BitField<GDKXUserAddOptions> options)
{
    XUserAddOptions xoptions = (XUserAddOptions)((int64_t)options);
    XTaskQueueHandle queue = GDGDK::get_instance()->get_async_queue();
    Ref<GDGDK_XAsyncBlock> b = GDGDK_XAsyncBlock::create(queue);
    b->set_callback([](XAsyncBlock* async) {
        GDGDK_XAsyncBlock* wrapper = reinterpret_cast<GDGDK_XAsyncBlock*>(async->context);

        XUserHandle user = nullptr;
        HRESULT hr = XUserAddResult(async, &user);
        ERR_FAIL_COND_MSG(FAILED(hr), vformat("XUserAddResult Error: %08X", hr));

        Dictionary d;
        d["user"] = GDGDKUser::create(user);
        wrapper->emit(d);
    });

    HRESULT hr = XUserAddAsync(xoptions, b->get_block());
    ERR_FAIL_COND_V_MSG(FAILED(hr), b, vformat("XUserAddAsync Error: %08X", hr));
    return b;
}

Ref<GDGDK_XAsyncBlock> GDGDKUser::add_user_by_id_with_ui_async(int64_t user_id)
{
    /* 
        https://github.com/godotengine/godot-proposals/issues/9740
        Suggested to use int64 instead of uint64 cuz they are the same size
    */

    XTaskQueueHandle queue = GDGDK::get_instance()->get_async_queue();
    Ref<GDGDK_XAsyncBlock> b = GDGDK_XAsyncBlock::create(queue);
    b->set_callback([](XAsyncBlock* async) {
        GDGDK_XAsyncBlock* wrapper = reinterpret_cast<GDGDK_XAsyncBlock*>(async->context);

        XUserHandle user = nullptr;
        HRESULT hr = XUserAddByIdWithUiResult(async, &user);
        ERR_FAIL_COND_MSG(FAILED(hr), vformat("XUserAddByIdWithUiResult Error: %08X", hr));

        Dictionary d;
        d["user"] = GDGDKUser::create(user);
        wrapper->emit(d);
    });

    HRESULT hr = XUserAddByIdWithUiAsync(user_id, b->get_block());
    ERR_FAIL_COND_V_MSG(FAILED(hr), b, vformat("XUserAddByIdWithUiAsync Error: %08X", hr));
    return b;
}

int GDGDKUser::get_max_users() {
    uint32_t max_users = 0;
    HRESULT hr = XUserGetMaxUsers(&max_users);
    ERR_FAIL_COND_V_MSG(FAILED(hr), -1, vformat("XUserGetMaxUsers Error: %08X", hr));

    return max_users;
}

Ref<GDGDKUser> GDGDKUser::find_user_by_id(int64_t user_id) {
    XUserHandle user = nullptr;
    HRESULT hr = XUserFindUserById(user_id, &user);
    ERR_FAIL_COND_V_MSG(FAILED(hr), GDGDKUser::create(nullptr), vformat("XUserFindUserById Error: %08X", hr));
    return GDGDKUser::create(user);
}

Ref<GDGDKUser> GDGDKUser::duplicate() const {
    Ref<GDGDKUser> dup;
    
    XUserHandle handle;
    HRESULT hr = XUserDuplicateHandle(_user, &handle);
    ERR_FAIL_COND_V_MSG(FAILED(hr), dup, vformat("XUserDuplicateHandle Error: %08X", hr));
    
    dup.instantiate();
    dup->_user = handle; 

    return dup;
}

void GDGDKUser::close_handle()
{
    XUserCloseHandle(_user);
}

bool GDGDKUser::compare(const Ref<GDGDKUser> other) const {
    return XUserCompare(_user, other->_user) == 0;
}

bool GDGDKUser::is_sign_out_present() {
    return XUserIsSignOutPresent();
}

Ref<GDGDKUser> GDGDKUser::find_user_by_local_id(int64_t local_id) {
    XUserLocalId id;
    id.value = local_id;

    XUserHandle user = nullptr;
    HRESULT hr = XUserFindUserByLocalId(id, &user);
    ERR_FAIL_COND_V_MSG(FAILED(hr), GDGDKUser::create(nullptr), vformat("XUserFindUserByLocalId Error: %08X", hr));
    return GDGDKUser::create(user);
}

Ref<GDGDK_XAsyncBlock> GDGDKUser::sign_out() {
    XTaskQueueHandle queue = GDGDK::get_instance()->get_async_queue();
    Ref<GDGDK_XAsyncBlock> b = GDGDK_XAsyncBlock::create(queue);
    b->set_callback([](XAsyncBlock* async) {
        GDGDK_XAsyncBlock* wrapper = reinterpret_cast<GDGDK_XAsyncBlock*>(async->context);
        
        HRESULT hr = XUserSignOutResult(async);
        ERR_FAIL_COND_MSG(FAILED(hr), vformat("XUserSignOutResult Error: %08X", hr));
        wrapper->emit(Dictionary());
    });

    HRESULT hr = XUserSignOutAsync(_user, b->get_block());
    ERR_FAIL_COND_V_MSG(FAILED(hr), b, vformat("XUserSignOutAsync Error: %08X", hr));
    return b;
}

int64_t GDGDKUser::get_id() const {
    uint64_t id;
    
    HRESULT hr = XUserGetId(_user, &id);
    ERR_FAIL_COND_V_MSG(FAILED(hr), 0, vformat("XUserGetId Error: %08X", hr));
    
    return id;
}

int64_t GDGDKUser::get_local_id() const {
    XUserLocalId id;
    HRESULT hr = XUserGetLocalId(_user, &id);
    ERR_FAIL_COND_V_MSG(FAILED(hr), 0, vformat("XUserGetLocalId Error: %08X", hr));
    return id.value;
}
