#include "register_types.h"
#include <godot_cpp/classes/engine.hpp>
#include <classes/project_settings.hpp>

#include "gdgdk.h"
#include "gdgdk_user.h"
#include "gdgdk_xasyncblock.h"

using namespace godot;

static GDGDK* gdgdk = nullptr;

void init_gdgdk(ModuleInitializationLevel p_level) {
    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
        GDREGISTER_CLASS(GDGDK_XAsyncBlock);
        GDREGISTER_CLASS(GDKXUserAddOptions);
        GDREGISTER_CLASS(GDKXUserState);
        GDREGISTER_CLASS(GDKXUserGamertagComponent);
        GDREGISTER_CLASS(GDKXUserGamerPictureSize);
        GDREGISTER_CLASS(GDKXUserAgeGroup);
        GDREGISTER_CLASS(GDKXUserPrivilege);
        GDREGISTER_CLASS(GDKXUserPrivilegeOptions);
        GDREGISTER_CLASS(GDKXUserPrivilegeDenyReason);
        GDREGISTER_CLASS(GDKXUserGetTokenAndSignatureOptions);
        GDREGISTER_CLASS(GDKXUserGetTokenAndSignatureData);
        GDREGISTER_CLASS(GDKXUserSignOutDeferralHandle);
        GDREGISTER_CLASS(GDGDKUser);
        GDREGISTER_CLASS(GDGDK);
        
        gdgdk = GDGDK::get_instance();
        Engine::get_singleton()->register_singleton("GDGDK", gdgdk);
    }
}

void uninit_gdgdk(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    Engine::get_singleton()->unregister_singleton("GDGDK");
    memdelete(gdgdk);
    gdgdk = nullptr;
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
