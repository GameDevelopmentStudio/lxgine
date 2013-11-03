#include "Utils.h"

char *callocStringWithContentsOfFile(const char *filename) {
    std::FILE *fp = std::fopen(filename, "r");
    if (fp) {
        std::fseek(fp, 0, SEEK_END);
        long dataLength = ftell(fp);
        char * data = (char *)calloc(dataLength,sizeof(char));
        std::rewind(fp);
        std::fread(data, 1, dataLength, fp);
        std::fclose(fp);
        return data;
    } else {
        return NULL;
    }
}

char *mallocStringWithEngineResource(const char *name, const char *extension) {
    char *result = (char *) calloc((strlen(name) + strlen(extension) + 2), sizeof(char));
    // Create mutale copy of the name
    strcpy(result, name);
    // Append extension
    strcat(result, extension);
    return result;
}


std::string getFileExtension(const char *filename) {
    // TODO: tmp implementation, better use ext library (boost)
    std::string strPath = std::string(filename);
    std::string extension = strPath.substr(strPath.find_last_of(".") + 1);

    return extension;
}

