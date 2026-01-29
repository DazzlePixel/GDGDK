#include "gdgdk.h"
#include "gdgdk_macros.h"

#include <godot_cpp/core/class_db.hpp>
#include <windows.h>
#include <xsapi-c/services_c.h>
#include <XGameRuntime.h>

using namespace godot;

GDGDK* GDGDK::_instance = nullptr;

void GDGDK::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize_gdk"), &GDGDK::initialize_gdk);
}

void GDGDK::_notification(int p_what) {
    if (p_what == NOTIFICATION_PREDELETE) {
        if (_initialized) {
            XGameRuntimeUninitialize();
        }
    }
}

GDGDK* GDGDK::get_instance() {
    if (_instance)
        return _instance;

    _instance = memnew(GDGDK);
    return _instance;
}

int GDGDK::initialize_gdk() {
    HRESULT hr = XGameRuntimeInitialize();
    if (FAILED(hr)) {
        print_error("XGameRuntimeInitialize failed");
        return hr;
    }

    XblInitArgs args;
    args.scid = "";
    
    hr = XblInitialize(&args);
    if (FAILED(hr)){
        print_error("XblInitialize failed");
        return hr; 
    }

    _initialized = true;

    return hr;
}
