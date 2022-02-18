# Brainstorming

## Character Name Input

Use the screen that was there in the original games. Draw a RECTANGLE in the shape of the red cursor, have it move to the different letters and have it read the letter that's being selected with CheckCollisionPointRec() or whatever that function is. It could be something like if (GetKeyPressed(KEY_A)) { if(CheckCollisionPointRec(cursorRect, letterRect)) { `input letterRect letter`; }}

Something like that. Looks good to me. ;)


## Tilemaps

Once tilemaps are setup, implement a function that reads the tile clicked and spits out the coordinates of that tile. Then, I can set that tile to whatever needs to be placed there.

### Tilesets not using tmx.h (no-tmx branch of repo)

.tmx files seem to be giving an issue at the moment. ID and layer issues, my own .tmx files not working, etc. It's just not worth it to try and use that right now, I'll try to create my own system.

I'll just use raylib to draw all textures and create a system for collision, tile animation, object interaction, etc.

## Cameras and Map Rendering

Set the camera on a path? Or maybe just give it allowed positions and then adjust the current position based on the player position? I feel like that would be too much to write for just that and there's a simpler way to go about it. I'll have to do some research on the subject.
