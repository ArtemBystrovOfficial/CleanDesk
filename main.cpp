#include "Files.h"

void Settings(Files* files);

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	//~~~!!!Флаг который обязательно нужно указывать
	Files::Set_File_Name(argv[0]);

    Files files[7];

	//Настройка в функции
	Settings(files);

    for (int i = 0; i < 7; i++)
	  {
		//Запуск сортировки
	  	files[i].Start_Sort();
	  }

	std::cout << "Ok\n";
	system("pause");

}

//settings--------
enum
{
    Images,
    Videos,
    Sounds,
    Folders,
    Documents,
    Apps,
    Other
};

void Settings(Files* files)
{
    files[Images].SetSettings({ "jpg","png","gif","bmp","tif" }, "Images");
    files[Videos].SetSettings({ "mp4","avi","mov" }, "Videos");
    files[Sounds].SetSettings({ "mp3","wav","ogg" }, "Sounds");
    files[Folders].SetSettings( Files::Other_Types::FOLDER , "Folders");
    files[Documents].SetSettings({ "doc","docx","xlsx","xlx","pdf","txt" }, "Documnets");
    files[Apps].SetSettings({ "lnk","exe", "url" }, "Apps");
    files[Other].SetSettings( Files::Other_Types::NONE , "Other");
}
//----------------