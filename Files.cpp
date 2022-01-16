#include "Files.h"

// Методы
    std::string Files::To_name(const std::string str_i)
    {
		int itr = -1;
		for (int i = str_i.size() - 1; i > 0 && str_i[i] != '\\'; i--) itr = i;
		 if (itr == -1)  return "";

		return str_i.substr(itr, str_i.size() - itr);
	}
    std::string Files::To_type(const std::string str_i)
	{
		signed int itr = -1;
		for (int i = str_i.size() - 1; i >= 0; --i) if (str_i[i] == '.'){itr = i + 1; break;}

	    if (itr == -1) return "folder";
	
		return str_i.substr(itr, str_i.size() - itr);
	}

    void Files::SetSettings(const std::vector <std::string>& types, const std::string& folder)
    {
        Types = types;
		Folder.push_back(folder);
		Folder_name = folder;
		if (!std::filesystem::exists(std::filesystem::current_path()/folder)) {
			std::filesystem::current_path(std::filesystem::current_path());
			std::filesystem::create_directory(folder);
		}
    };
    void Files::SetSettings(Other_Types type, const std::string& folder)
    {
        Types_variant = type;
		Folder.push_back(folder);
		Folder_name = folder;
		if (!std::filesystem::exists(std::filesystem::current_path() /folder)) {
			std::filesystem::current_path(std::filesystem::current_path());
			std::filesystem::create_directory(folder);
		}
    };
	void Files::Start_Find()
	{
		for (const auto & entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
		{
			
			std::string Name = To_name(entry.path().string());

			if (Name != To_name(File_name)) {
				if(To_type(Name)=="folder"){ File.push_back({ std::to_string(id) , Name }); }
				else
				{
					File.push_back({ std::to_string(id) + "." + To_type(Name) , Name });

					std::filesystem::rename(std::filesystem::current_path() / File[File.size() - 1].second,
						std::filesystem::current_path() / File[File.size() - 1].first);

					id++;
				}
			}
		}

	}
	
	std::string Files::To_Lower(std::string & str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
		return str;
	}
	
	void Files::Start_Replace( std::pair <std::string , std::string> file, std::string to, Other_Types type)
	{
		std::string s1 = file.first;
		std::wstring stemp1 = std::wstring(s1.begin(), s1.end());
		LPCWSTR sw_1 = stemp1.c_str();
		std::string s2 = to + "\\" + file.first;
		std::wstring stemp2 = std::wstring(s2.begin(), s2.end());
		LPCWSTR sw_2 = stemp2.c_str();

		std::cout << file.first<<" "<<file.second << " " << to << std::endl;
		switch (type)
		{
		case Files::NONE:
			try {
				MoveFile(sw_1, sw_2);

				std::filesystem::rename(std::filesystem::current_path() / (to + "\\" + file.first),
					std::filesystem::current_path() / (to + "\\" + file.second));
			}catch(...){}
			break;
		case Files::FOLDER:
			try {
			MoveFile(sw_1, sw_2);
			std::filesystem::rename(std::filesystem::current_path() / (to + "\\" + file.first),
				                    std::filesystem::current_path() / (to + "\\" + file.second));
			}
			catch (...) {}
			break;
		case Files::NORMAL:
			try {
			MoveFile(sw_1, sw_2);
			std::filesystem::rename(std::filesystem::current_path() / (to + "\\" + file.first),
				                    std::filesystem::current_path() / (to + "\\" + file.second));
			}catch (...) {}
			break;
		default:
			break;
		}
	}

	void Files::Start_Sort()
	{
		switch (Types_variant)
		{
		case NORMAL:
			
				for (int i = 0; i < Types.size(); ++i)
				{
					for (int j = 0; j < File.size(); ++j)
					{
						if ( File[j].first != To_name(File_name) ) {
							    std::string str_n = To_type(File[j].first);
								if (To_Lower(str_n) == Types[i])
								{
									Start_Replace(File[j], Folder_name, Other_Types::NORMAL);

										std::cout << File[j].second << std::endl;
										File.erase(File.begin() + j); j--;
								}
						}
					}
				}
			
			break;
		case FOLDER:
			for (int j = 0; j < File.size(); ++j)
			{
			if (To_type(File[j].second) == "folder")
			{
				bool is_be = false;
				for (int i = 0; i < Folder.size(); ++i)
				{
					if (Folder[i] == File[j].second)
					{
						is_be = true;
					}
				}
				if (!is_be)
				{
					Start_Replace(File[j], Folder_name, Other_Types::FOLDER);

					std::cout << File[j].first << std::endl;
					File.erase(File.begin() + j); j--;
				}
			}
		}
			break;
		case NONE:
			for (int i = 0; i < File.size(); ++i)
			{
				if (!(File[i].second == To_name(File_name)))
				{
					Start_Replace(File[i], Folder_name, Other_Types::NONE);
					std::cout << File[i].second << std::endl;
				}
			}
			break;
		    
		 default: break;
		}
	}

// Определения переменных
bool Files::is_File_Find_Complete = false;
std::vector < std::pair <std::string, std::string> > Files::File;
std::vector < std::string > Files::Folder;
std::string Files::File_name;
int Files::id = 0;

// Конструкторы
void Files::Set_File_Name(char* name)
{
	File_name = name;
}

Files::Files()
{
    Types_variant = Other_Types::NORMAL;
	if (!is_File_Find_Complete) { Start_Find(); is_File_Find_Complete = true; }
}
Files::Files(const std::vector <std::string> & types)
{
    Types = types;
    Types_variant = Other_Types::NORMAL;
	if (!is_File_Find_Complete) { Start_Find(); is_File_Find_Complete = true; }
}
Files::Files(const std::vector <std::string>& types, const std::string& folder)
{
    Types = types;
    Folder.push_back(folder);
	Folder_name = folder;
	if (!is_File_Find_Complete) { Start_Find(); is_File_Find_Complete = true; }
	std::filesystem::create_directory(folder);
}


