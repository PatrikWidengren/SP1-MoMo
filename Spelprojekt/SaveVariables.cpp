#include "SaveVariables.h"

//Strukturen på sparfilerna är nu:
//Game Data/Save Data/MFS1 meep.dat
//Game Data/Save Data/MFS2 meep.dat
//osv...

SaveVariables::SaveVariables()
{	
	
}

void SaveVariables::checkSaves()
{
	mFile.searchFile(&fileList,  "Game Data/Save Data/", "*.dat");
	mFile.checkSaves(&fileList, 5, "Game Data/Save Data/", "MFS", "dat");
	LogHandler::notify("File", "Created Saves");
}

void SaveVariables::setCurrentSave(int fileNumber)
{
	//Kalla på detta när man startar upp en sparfil.
	curSave = fileNumber;
}

void SaveVariables::newSave() //Ny Sparfil
{
	if (curSave != NULL)
		mFile.newSave(curSave, "Game Data/Save Data/", "MFS", "dat", "meep");
	else
		LogHandler::notify("Game", "Current Savefile not set.");
}

void SaveVariables::delSave() //Ta Bort Sparfil
{
	if (curSave != NULL)
		mFile.deleteSave(curSave, "Game Data/Save Data/", "MFS", "dat", "meep");
	else
		LogHandler::notify("Game", "Current Savefile not set.");
}

void SaveVariables::save()
{
	std::string file = "Game Data/Save Data/MFS" + std::to_string(curSave);
	file += " meep.dat";



	//Basically do this:
	sDupies = 69; //riktiga dupie variable värdet
	mFile.add(sDupies);
	//För allt som behöver sparas

	mFile.save(file, true);

}


SaveVariables::~SaveVariables()
{
}
