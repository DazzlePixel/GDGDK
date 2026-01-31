extends Node


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	GDGDK.initialize_gdk("")
	
	var block: GDGDK_XAsyncBlock = GDGDKUser.add_user_async(GDGDKUser.AddDefaultUserSilently)
	print(await block.completed)
	pass # Replace with function body.
