#include "utils.h"
#include <map>
#include <string>

#define LL_FILE "language_list"
#define PYTHON_PATH "python3"

Utils::Utils()
{
    exe_path = QCoreApplication::applicationDirPath().toStdString() + "/";
}

QMap<std::string, std::string> Utils::getLanguages()
{
    FILE* language_list_file = fopen((exe_path + LL_FILE).c_str(), "r");
    char lang[50];
    char code[10];
    QMap<std::string, std::string> map;
    while(fscanf(language_list_file, " %49[^/]%s", lang, code) != EOF)
    {
        map.insert(code + 1, lang);
    }
    return map;
}

struct result Utils::getResult()
{
    struct result result;
    FILE* result_file = fopen((exe_path + ".result").c_str(), "r");
    fscanf(result_file, "%s %s ", result.dest, result.src);

    int t = 0;
    while(fscanf(result_file, "%c", result.text + t++) != EOF);
    result.text[t-1] = 0;
    return result;
}

void Utils::translate(std::string text, std::string dest, std::string src)
{
    FILE* ask = fopen((exe_path + ".ask").c_str(), "w+");
    fprintf(ask, "%s\n%s\n%s", dest.c_str(), src.c_str(), text.c_str());
    fclose(ask);

    std::string cmd = PYTHON_PATH " " + exe_path +  "translate.py";
    system(cmd.c_str());
}
