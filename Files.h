#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <filesystem>

class Files
{
public:

    enum Other_Types
    {
        NONE,
        FOLDER,
        NORMAL
    };

    Files();
    Files(const std::vector <std::string>&);
    Files(const std::vector <std::string>&, const std::string&);

    void SetSettings(const std::vector <std::string>&, const std::string&);
    void SetSettings(Other_Types, const std::string& folder);
	static void Set_File_Name(char *);

	void Start_Sort();
	
    Files(const Files&) = delete;
    Files(Files&&) = delete;
	~Files() {};


private:

	void Start_Find();

	void Start_Replace(std::pair <std::string, std::string>, std::string, Other_Types);

	std::string To_Lower(std::string &);

	std::string To_name(const std::string str_i);

	std::string To_type(const std::string str_i);

	static int id;
	static bool is_File_Find_Complete;
    static std::vector < std::pair <std::string, std::string> > File;
	Other_Types Types_variant = Other_Types::NORMAL;
	std::vector < std::string > Types;
	static std::vector <std::string> Folder;
	std::string Folder_name;
	static std::string File_name;

};



