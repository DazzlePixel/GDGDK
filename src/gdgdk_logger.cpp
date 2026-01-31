#include "gdgdk_logger.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GDGDKLogger::_bind_methods() {
}

void GDGDKLogger::log(const String& msg) {
    UtilityFunctions::print(msg);
}

void GDGDKLogger::error(const String& msg) {
    UtilityFunctions::push_error(msg);
}

void GDGDKLogger::warn(const String& msg) {
    UtilityFunctions::push_warning(msg);
}
