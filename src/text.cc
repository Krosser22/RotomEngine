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

void ROTOM::read_file(const char* file_name, std::shared_ptr<std::string> source) {
  FILE *file = fopen(file_name, "rb");
  if (file == NULL) {
    printf("ERROR: File doesn't found (%s)\n", file_name);
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
    //source->append("\0");
    printf("%s\n\n", source->data());
    fclose(file);
  }
}