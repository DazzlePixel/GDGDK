#include "gdgdk.h"
#include "XError.h"
#include "core/memory.hpp"
#include "core/print_string.hpp"
#include "variant/callable.hpp"
#include "gdgdk_logger.h"
#include "variant/variant.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <windows.h>
#include <xsapi-c/services_c.h>
#include <XGameRuntime.h>
#include "gdgdk_user.h"
#include <classes/engine.hpp>

using namespace godot;

GDGDK* GDGDK::_instance = nullptr;
bool GDKXErrorCallback(HRESULT hr, const char* msg, void* context) {
    GDGDKLogger* logger = (GDGDKLogger*)context;
    logger->error(vformat("Error %s: %s", (int)hr, msg));
    return true;
}

GDGDK::GDGDK() {
    XErrorSetOptions(
        XErrorOptions::DebugBreakOnError | XErrorOptions::FailFastOnError | XErrorOptions::OutputDebugStringOnError,
        XErrorOptions::OutputDebugStringOnError);

    _logger = memnew(GDGDKLogger);
    XErrorSetCallback(GDKXErrorCallback, _logger);
}

GDGDK *godot::GDGDK::get_instance() {
    if (_instance)
        return _instance;

    _instance = memnew(GDGDK);
    return _instance;
}

void GDGDK::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("initialize_gdk", "scid"), &GDGDK::initialize_gdk);
    ClassDB::bind_method(D_METHOD("get_scid"), &GDGDK::get_scid);
}

void GDGDK::_notification(int p_what) {
    if (p_what == NOTIFICATION_PREDELETE) {
        if (_initialized) {
            XTaskQueueCloseHandle(_async_queue);
            XErrorSetCallback(nullptr, nullptr);
            memdelete(_logger);
            XGameRuntimeUninitialize();
        }
    }
}

int GDGDK::initialize_gdk(const String& scid) {
    HRESULT hr = XGameRuntimeInitialize();
    ERR_FAIL_COND_V_MSG(FAILED(hr), hr, "Failed to initialize GDK XGameRuntime.");
    
    XblInitArgs init_args = {};
    init_args.scid = scid.utf8().get_data();
    hr = XblInitialize(&init_args);
    ERR_FAIL_COND_V_MSG(FAILED(hr), hr, "Failed to initialize Xbox Live.");

    _async_queue = XblGetAsyncQueue();
    _initialized = true;

    return hr;
}

String GDGDK::get_scid() const {
    const char* scid = nullptr;
    HRESULT hr = XblGetScid(&scid);
    ERR_FAIL_COND_V_MSG(FAILED(hr), String(), "Failed to get SCID.");

    return String(scid);
}

int GDGDK::set_override_config(const String & override_scid, const uint32_t override_title_id) {
    HRESULT hr = XblSetOverrideConfiguration(override_scid.utf8().get_data(), override_title_id);
    ERR_FAIL_COND_V_MSG(FAILED(hr), hr, "Failed to set override configuration.");

    return hr;
}

int GDGDK::set_override_locale(const char& locale) {
    HRESULT hr = XblSetOverrideLocale(&locale);
    ERR_FAIL_COND_V_MSG(FAILED(hr), hr, "Failed to set override locale.");
    return hr;
}
