extends Node


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	GDGDK.initialize_gdk("")
	#var block: GDGDK_XAsyncBlock = GDGDKUser.add_user_async(GDGDKUser.AddDefaultUserSilently)
	#var result: Dictionary = await block.completed
	#GDGDKUser.Test()
	pass # Replace with function body.
