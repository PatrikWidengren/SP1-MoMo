#include "Managers\File.h"
#pragma once

class SaveVariables
{
private:

	File mFile;
	std::vector<std::string> dataList;


	int sDupies;

	//need to check what mowers are unlocked
	bool sHasMow1;
	//also save damage values for stuff
	int sMow1DMG;


	bool sHasMow2;
	int sMow2DMG;

	bool sHasMow3;
	int sMow3DMG;

	bool sHasMow4;
	int smow4DMG;

	bool sHasHedge1;
	bool sHasHedge2;

	//same for unlocked worlds

	bool sHasFiji;
	bool sHasJapan;
	//add more
	
	//what's available in the shop


	//Last used mower and hedge cutter should also be saved
	

public:
	int curSave;

	void checkSaves();
	void setCurrentSave(int fileNumber);
	void newSave();
	void delSave();
	void save();

	SaveVariables();
	~SaveVariables();
};

