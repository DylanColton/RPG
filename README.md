# RPG

### Disclaimer!

The basics of this code come from Joey de Vries' book on [Learn OpenGL](https://learnopengl.com/)
In addition to that, I am using a number of open source softwares, such as OpenGL, GLFW, OpenAL and GLAD, among others.

On top of this framework, I implemented `sound` and `sound_device` objects using OpenAL, rolling them into the `ResourceManager` that de Vries laid out for textures and shaders.

## Purpose
This is a test of my knowledge in programming, and it had taken me 2 years of on-and-off chipping at the book to get to this starting point.

The game will be a simple VN/RPG.
This means the game will be an RPG where the player moves an avatar around locations,
but the player will also be brought into dialogs with other characters, where a textbox appears and instead of a simpler 'overworld' sprite, a more detailed sprite of the character is shown,
usually with a larger range of emotions.

## Initial Conceptualisation:

### MoSCow
The game:
	- Must:
		- Render sprites to screen
		- Display levels and handle collision sensibly
		- Play audio apropos to the scenario
		- Handle post processing such as screen-shaking, hue and brightness shifting, etc,.
		- Have a pause menu featuring the party, items and equipment

	- Should:
		- Have a level editor (also exporting these levels to .map files?)
		- A save and load feature
		- 

	- Could:
		- Allow for multiple fonts

	- Won't:
		- 
