# Funkin' Everywhere
<img alt="Our logo" src="docs/FE_Logo.png" />
Funkin' Everywhere is a Friday Night Funkin' fan project based on Scratch Everywhere! that allows you to play Friday Night Funkin on basically any 6th-8th generation handheld/console. This program is written in c++ and uses no generative AI outside of using it for fixing bugs if need be (I still hope to change this, I am still a little bit of a beginner at c++ but I know haxe pretty well).

Sorry that my code is really unreadable lol

## Compiling

For Windows/Linux, you will need gcc, g++, sdl3, sdl3-image, pugixml, and nlohmann_json. For Windows, I would reccommend using MSYS2 to compile.

To compile, just run the make command in the FunkinEverywhere folder. If you are compiling to any platform other than Windows, make sure to add PLATFORM=targetplatform to the make command.

## Usage

This only comes with the source code, so after compiling, you will get a standalone app file. The assets don't come with Funkin' Everywhere, so you must get them from Funkin's latest preview build, then put the assets folder in the same directory as the app.