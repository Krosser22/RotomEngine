/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "text.h"

/*void SetText(int x, int y, int size, int r, int g, int b, int a, int blur, char *text){
  ESAT::DrawSetTextFont("test.ttf");
  ESAT::DrawSetFillColor(r, g, b, a);
  ESAT::DrawSetTextSize(size);
  ESAT::DrawSetTextBlur(blur);
  ESAT::DrawText(x, y + size, text);
}

void SetText(int x, int y, int size, int r, int g, int b, int a, int blur, int number){
  char text[10] = "";
  ESAT::DrawSetTextFont("test.ttf");
  ESAT::DrawSetFillColor(r, g, b, a);
  ESAT::DrawSetTextSize(size);
  ESAT::DrawSetTextBlur(blur);
  ESAT::DrawText(x, y + size, itoa(number, text, 10));
}*/

/*void read_file(const char* file_name, EDK3::scoped_array<char> *source) {
  FILE *file = fopen(file_name, "rb");
  if (file == NULL) {
    printf("ERROR: File doesn't found (%s)\n", file_name);
    system("pause");
  } else {
    fseek(file, 0L, SEEK_END);
    int file_length = ftell(file);
    source->alloc(file_length + 1);
    fseek(file, 0L, SEEK_SET);
    for (int i = 0; i < file_length; ++i) source->get()[i] = fgetc(file);
    source->get()[file_length] = '\0';
    //printf("%s\n\n", source);
    fclose(file);
  }
}*/

using namespace std;
template<typename T> std::shared_ptr<T> make_shared_array(size_t size)
{
  return std::shared_ptr<T>(new T[size], default_delete<T[]>());
}

/*void read_file(const char* file_name, std::shared_ptr<char> source) {
  FILE *file = fopen(file_name, "rb");
  if (file == NULL) {
    printf("ERROR: File doesn't found (%s)\n", file_name);
    system("pause");
  } else {
    fseek(file, 0L, SEEK_END);
    int file_length = ftell(file);
    
    char* buffer = new char[file_length + 1];
    source = make_shared_array<char>(file_length + 1);

    //source->alloc(file_length + 1);
    fseek(file, 0L, SEEK_SET);
    for (int i = 0; i < file_length; ++i) {
      buffer[i] = fgetc(file);
      //source[i] = std::make_shared<char>(buffer[i]);
    }
    buffer[file_length] = '\0';
    //printf("%s\n\n", source);
    source = make_shared_array<char>(*buffer);
    //source.swap(std::make_shared<char>(*buffer));
    fclose(file);
  }
}*/