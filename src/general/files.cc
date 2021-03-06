/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/files.h"

void ROTOM::FILES::ReadFile(const char* path, std::shared_ptr<char[]> source) {
  FILE *file = fopen(path, "rb");
  if (file == nullptr) {
    printf("ERROR: File doesn't found (%s)\n", path);
    system("pause");
  } else {
    fseek(file, 0L, SEEK_END);
    int file_length = ftell(file);
    fseek(file, 0L, SEEK_SET);
    for (int i = 0; i < file_length; ++i) {
      ((*source.get())[i]) = fgetc(file);
    }
    ((*source.get())[file_length]) = '\0';
    fclose(file);
  }
}

void ROTOM::FILES::ReadFile(const char* path, std::shared_ptr<std::string> source) {
  FILE *file = fopen(path, "rb");
  if (file == nullptr) {
    printf("ERROR: File doesn't found (%s)\n", path);
    system("pause");
  } else {
    fseek(file, 0L, SEEK_END);
    int file_length = ftell(file);
    source->resize(file_length + 1);
    source->clear();
    fseek(file, 0L, SEEK_SET);
    for (int i = 0; i < file_length; ++i) {
      char buf[2];
      sprintf(buf, "%s", fgets(buf, 2, file));
      source->append(buf);
    }
    //printf("%s\n\n", source->data());
    fclose(file);
  }
}

std::string ROTOM::FILES::ReadFile(const char *path) {
  std::string source;
  FILE *file = fopen(path, "rb");
  if (file == nullptr) {
    printf("ERROR: File doesn't found (%s)\n", path);
    system("pause");
  } else {
    fseek(file, 0L, SEEK_END);
    int file_length = ftell(file);
    source.resize(file_length + 1);
    source.clear();
    fseek(file, 0L, SEEK_SET);
    for (int i = 0; i < file_length; ++i) {
      char buf[2];
      sprintf(buf, "%s", fgets(buf, 2, file));
      source.append(buf);
    }
    //printf("%s\n\n", source->data());
    fclose(file);
  }
  return source;
}