#include "register_types.h"
#include <godot_cpp/classes/engine.hpp>
#include "gdgdk.h"

using namespace godot;

static GDGDK* gdgdk;

void init_gdgdk(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    GDREGISTER_CLASS(GDGDK);
    gdgdk = GDGDK::get_instance();
    Engine::get_singleton()->register_singleton("GDGDK", gdgdk);

}

void uninit_gdgdk(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    Engine::get_singleton()->unregister_singleton("GDGDK");
    memdelete(gdgdk);
}

extern "C" {
    GDExtensionBool GDE_EXPORT gdgdk_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(init_gdgdk);
	init_obj.register_terminator(uninit_gdgdk);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
    }
}
