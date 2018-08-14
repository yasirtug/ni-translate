#include "utils.h"
#include <iostream>
#include <map>
#include <string>
#define FILE_NAME "language_list"


QMap<std::string, std::string> Utils::getLanguages()
{
    FILE* language_list_file = fopen(FILE_NAME, "r");
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
    FILE* result_file = fopen(".result", "r");
    fscanf(result_file, "%s %s ", result.dest, result.src);

    int t = 0;
    while(fscanf(result_file, "%c", result.text + t++) != EOF);
    result.text[t-1] = 0;
    return result;
}

void Utils::translate(std::string text, std::string dest, std::string src)
{
    FILE* ask = fopen(".ask", "w+");
    fprintf(ask, "%s\n%s\n%s", dest.c_str(), src.c_str(), text.c_str());
    fclose(ask);

    std::string cmd = "python3 translate.py";
    system(cmd.c_str());
}
