#include "File.h"


File::File()
{
	clearData();
	clearVector();
	emptySave = " @empty";
}

std::string File::crypt(std::string str)
{
	std::string crypted = "";

	key(true);
	for (unsigned int temp = 0; temp < str.size(); temp++)
	{
		crypted += str[temp] ^ (int(key(false)) + temp) % 255;
	}

	return crypted;
}


int File::key(bool reset)
{
	{
		static int id = 0;
		if (reset)
		{
			id = 0;
			return 0;
		}
		else
			id = (id >= 7 ? 0 : id + 1);
		switch (id)
		{
		default:
		case 0:
			return (int)'s';
		case 1:
			return (int)'l';
		case 2:
			return (int)'a';
		case 3:
			return (int)'s';
		case 4:
			return (int)'k';
		case 5:
			return (int)'z';
		case 6:
			return (int)'a';
		case 7:
			return (int)'s';
		}
		return 0;
	}
}

void File::add(std::string str)
{
	entry.push_back(str);
}

void File::add(const char* str)
{
	std::string s = str;
	add(s);
}

void File::add(int val)
{
	std::string s = std::to_string(val);
	add(s);
}

void File::save(std::string file, bool encrypt)
{
	clearData();
	for (unsigned int i = 0; i < entry.size(); i++)
	{
		data += entry[i];
		data += '\n';
	}
	saveToFile(file, (encrypt ? crypt(data) : data));
	clearVector();
}

bool File::saveToFile(std::string file, std::string str)
{
	std::ofstream f;

	f.open(file);
	if (f.is_open())
	{
		f << str;
		f.close();
		return 1;
	}
	else
	{
		std::string str = "Unable to open file \"";
		str += file;
		str += "\"for writing.";
		LogHandler::error("File", str.c_str());
	}
	return 0;
}

bool File::load(std::string file, bool encrypted)
{
	std::ifstream f;

	f.open(file);
	if (f.is_open())
	{
		std::string content((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));
		data = (encrypted ? crypt(content) : content);
		f.close();
		clearVector();
		std::istringstream input(data);
		std::string line;
		while (std::getline(input, line))
		{
			entry.push_back(line);
		}
		return 1;
	}
	else
	{
		std::string str = "Unable to open file \"";
		str += file;
		str += "\"for reading.";
		LogHandler::error("File", str.c_str());
	}
	return 0;
}

int File::getint(int i)
{
	std::string str = get(i);
	std::istringstream input(str);
	int val = 0;
	input >> val;
	return val;
}

std::string File::get(int i)
{
	std::string val = "";
	if (i >= 0 && (unsigned int)i < entry.size())
		val = entry[i];
	else
	{
		std::string str = "Getting file entry ";
		str += i;
		str += " out of range.";
		LogHandler::error("File", str.c_str());
	}
	return val;
}

void File::clearVector()
{
	entry.clear();
}

void File::clearData()
{
	data = "";
}

void File::set(int i, int val)
{
	std::string s = std::to_string(val);
	set(i, s);
}

void File::set(int i, std::string val)
{
	if (i >= 0 && (unsigned int)i < entry.size())
		entry[i] = val;
	else
	{
		std::string str = "Setting file entry ";
		str += i;
		str += " out of range.";
		LogHandler::error("File", str.c_str());
	}
}

void File::searchFile(std::vector<std::string>*list, const char* path, const char* type) //type = *.* for all files or *.txt for txt files etc
{
	list->clear();
	std::string str = path;
	str += type;
	const char* filepath = str.c_str();

	int ff = _findfirst32(filepath, &data32);

	if (ff != -1)
	{
		int res = 0;
		while (res != -1)
		{
			list->push_back(data32.name);
			res = _findnext32(ff, &data32);
		}
		_findclose(ff);
	}
}

void File::checkSaves(std::vector<std::string>*list, int amountSaves, const char* path, const char* savename, const char* fileType)
{
	std::string type = ".";
	type += fileType;

	for (unsigned int i = 0; i < amountSaves; i++)
	{
		bool found = false;
		std::string saveName = savename;
		saveName += std::to_string(i + 1);

		std::string fullSavePath = path;
		fullSavePath += saveName;

		if (list->size() == NULL)
		{
			createSaves(fullSavePath, type);
		}
		else
		{
			for (unsigned int c = 0; c < list->size(); c++)
			{
				std::string fullFile = list->at(c);
				std::string substrSaveName = fullFile.substr(0, saveName.length());
				if (substrSaveName == saveName)
				{
					int pos = fullFile.find(type);
					std::string substrFileEnd = fullFile.substr(pos);
					
					if (substrFileEnd == type)
					{
						//use substrFileName to set the filenames in the game later on.
						//std::string substrFileName = fullFile.substr(substrSaveName.length() + 1, pos - type.length() - 2);
						found = true;
						break;
					}
				}
			}
			if (found != true && list->size() != NULL)
			{
				createSaves(fullSavePath, type);
			}

		}
	}
}

void File::createSaves(std::string fileName, std::string fileEnd)
{
	

	std::string newfile = fileName;
	newfile += emptySave;
	newfile += fileEnd;
	std::string str = fileName;
	str += " created";

	std::ofstream f;

	f.open(newfile);

	if (f.is_open())
	{
		LogHandler::log("File", str.c_str());
		f.close();
	}
}


void File::newSave(int sFile, const char* path, const char* savename, const char* fileType, const char* pName)
{
	//if this is run, it's always after making sure that all saves exist
	//get the correct savefile to rename

	int result;

	std::string fullFile = path;
	fullFile +=	savename;
	fullFile += std::to_string(sFile);
	fullFile += emptySave;
	fullFile += ".";
	fullFile += fileType;

	std::string newFile = path;
	newFile += savename;
	newFile += std::to_string(sFile);
	newFile += " ";
	newFile += pName;
	newFile += ".";
	newFile += fileType;

	result = std::rename(fullFile.c_str(), newFile.c_str());

	if (result == 0)
	{
		std::string str = newFile;
		str += " created succesfully";
		LogHandler::log("File", str.c_str());
	}
	else
	{
		std::string str = newFile;
		str += " not created";
		LogHandler::error("File", str.c_str());
	}
}

void File::copySave(int sFile, int cToFile, const char* path, const char* savename, const char* fileType, const char* pName)
{
	std::string copyFile = path;
	copyFile += savename;
	copyFile += std::to_string(sFile);
	copyFile += " ";
	copyFile += pName;
	copyFile += ".";
	copyFile += fileType;

	std::string toFile = path;
	toFile += savename;
	toFile += std::to_string(cToFile);

	std::string newName = toFile;

	toFile += emptySave;
	toFile += ".";
	toFile += fileType;

	newName += " ";
	newName += pName;
	newName += ".";
	newName += fileType;

	std::ifstream f;

	f.open(copyFile);
	if (f.is_open())
	{
		std::string content((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));
		data = content;
		f.close();
	}
	else
	{
		std::string str = "Error opening file: ";
		str += copyFile;
		LogHandler::error("File", str.c_str());
	}


	std::ofstream f2;

	f2.open(toFile);
	if (f2.is_open())
	{
		f2 << data;
		f2.close();
	}
	else
	{
		std::string str = "Error opening file: ";
		str += toFile;
		LogHandler::error("File", str.c_str());
	}

	int result = std::rename(toFile.c_str(), newName.c_str());

	if (result == 0)
	{
		std::string str = newName;
		str += " succesfully copied";
		LogHandler::log("File", str.c_str());
	}
	else
	{
		std::string str = "Error copying ";
		str += newName;
		LogHandler::error("File", str.c_str());
	}
}

void File::deleteSave(int sFile, const char* path, const char* savename, const char* fileType, const char* pName)
{
	//if this is run, it's always after making sure that all saves exist
	//get the correct savefile delete

	std::string fileEnd = ".";
	fileEnd += fileType;

	std::string fullSavePath = path;
	fullSavePath += savename;
	fullSavePath += std::to_string(sFile);

	std::string delFile = path;
	delFile += savename;
	delFile += std::to_string(sFile);
	delFile += " ";
	delFile += pName;
	delFile += ".";
	delFile += fileType;

	if (std::remove(delFile.c_str()) != 0)
	{
		std::string str = "Can't delete ";
		str += delFile;
		LogHandler::error("File", str.c_str());
	}
	else
	{
		std::string str = delFile;
		str += " succesfully removed";
		LogHandler::log("File", str.c_str());
		createSaves(fullSavePath, fileEnd);
	}
}

File::~File()
{
}