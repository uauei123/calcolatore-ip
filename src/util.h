#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <cmath>
#include <string>
#include <fstream>

#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Button.h>
#include <FL/Fl_Draw.h>
#include <FL/Fl_Table.h>
#include <FL/Fl_Input.h>
#include <FL/Fl_Native_File_Chooser.h>
#include <Fl/Fl_Ask.h>

#include "subnet.h"

class TabellaIP : public Fl_Table 
{
    public:
        TabellaIP(int X, int Y, int W, int H, std::vector<Subnet> sottoreti, const char *L = 0);

    private:
        std::vector<std::vector<std::string>> data;

        void DrawHeader(const char *s, int X, int Y, int W, int H);
        void DrawData(const char *s, int X, int Y, int W, int H);
        void draw_cell(TableContext context, int ROW = 0, int COL = 0, int X = 0, int Y = 0, int W = 0, int H = 0);
};

void crea_popup(const char* label, const char* messaggio);
int serializza(std::vector<Subnet> &sottoreti, const char* filename);
const char* seleziona_file();

#endif