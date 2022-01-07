//Andrew Richardson W9383619
/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file

	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there is a batch file for creating a redistributable Demo folder

	For help using HAPI please see the Reference folder in the HAPI sub-directory
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <Windows.h>
#include <math.h>
#include <cmath>
#include "Visuals.h"
#include "Sprite.h"
#include <unordered_map>
#include "World.h"

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

//unsigned int offset = (x + y * width) * 4; // Remember This

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

void HAPI_Main()
{
	
	//calls game to run
	World gameWorld;
	gameWorld.Run();
	
}