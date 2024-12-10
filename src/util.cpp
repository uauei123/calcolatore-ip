#include "util.h"

void TabellaIP::DrawHeader(const char *s, int X, int Y, int W, int H) 
{
    // Imposta proprieta' header della tabella
    fl_push_clip(X, Y, W, H);
    fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
    fl_color(FL_BLACK);
    // Scrivi l'header
    fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
    fl_pop_clip();
}

void TabellaIP::DrawData(const char *s, int X, int Y, int W, int H) 
{
    // Imposta proprieta' cella
    fl_push_clip(X, Y, W, H);
    fl_color(FL_WHITE);
    fl_rectf(X, Y, W, H);
    fl_color(FL_GRAY0);
    // Scrivi i dati nella cella
    fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
    fl_color(color());
    fl_rect(X, Y, W, H);
    fl_pop_clip();
}

void TabellaIP::draw_cell(TableContext context, int ROW, int COL, int X, int Y, int W, int H) 
{
    switch (context) 
    {
        case CONTEXT_STARTPAGE:
            // Carica il font appena inizializzata
            fl_font(FL_HELVETICA, 16);
            return;
        case CONTEXT_COL_HEADER:
            switch (COL) 
            {
                // Disegna gli header
                case 0: fl_draw("NET ID", X, Y, W, H, FL_ALIGN_CENTER); return;
                case 1: fl_draw("BROADCAST", X, Y, W, H, FL_ALIGN_CENTER); return;
                case 2: fl_draw("GATEWAY", X, Y, W, H, FL_ALIGN_CENTER); return;
                case 3: fl_draw("PRIMO HOST", X, Y, W, H, FL_ALIGN_CENTER); return;
                case 4: fl_draw("ULTIMO HOST", X, Y, W, H, FL_ALIGN_CENTER); return;
                case 5: fl_draw("SUBNET MASK", X, Y, W, H, FL_ALIGN_CENTER); return;
                case 6: fl_draw("CIDR", X, Y, W, H, FL_ALIGN_CENTER); return;
                default: return;
            }
        case CONTEXT_ROW_HEADER: 
        {
            // Disegna i numeri delle righe
            char s[40];
            sprintf(s, "%d", ROW + 1);
            DrawHeader(s, X, Y, W, H);
            return;
        }
        case CONTEXT_CELL:
            // Disegna i dati nella cella
            DrawData(data[ROW][COL].c_str(), X, Y, W, H);
            return;
        default:
            return;
    }
}

TabellaIP::TabellaIP(int X, int Y, int W, int H, std::vector<Subnet> sottoreti, const char *L)
    : Fl_Table(X, Y, W, H, L) 
{
    data.resize(sottoreti.size(), std::vector<std::string>(7));

    for (size_t r = 0; r < sottoreti.size(); r++) 
    {
        int bit_host = sottoreti[r].leggi_bit_host();

        data[r][0] = sottoreti[r].calcola_host(0);
        data[r][1] = sottoreti[r].calcola_host(std::pow(2, bit_host) - 1);
        data[r][2] = sottoreti[r].calcola_host(std::pow(2, bit_host) - 2);
        data[r][3] = sottoreti[r].calcola_host(1);
        data[r][4] = sottoreti[r].calcola_host(std::pow(2, bit_host) - 3);
        data[r][5] = sottoreti[r].leggi_subnet_mask();
        data[r][6] = "/";
        data[r][6] += std::to_string(sottoreti[r].leggi_bit_rete() + sottoreti[r].leggi_bit_ip());
    }

    rows(sottoreti.size());
    row_header(1);
    row_height_all(30);
    row_resize(0);

    cols(7);
    col_header(1);
    col_width_all(115);
    col_width(5, 125);
    col_width(6, 65);
    col_resize(0);

    end();
}

int serializza(std::vector<Subnet> &sottoreti, const char* filename)
{
    //Serializza un vettore di sottoreti in formato .csv
    FILE* fp = fopen(filename, "a");

    if(fp == NULL)
        return -1;

    fprintf(fp, "NET-ID,BROADCAST,GATEWAY,PRIMO HOST,ULTIMO HOST,SUBNET MASK,CIDR\n");

    for(int i = 0; i < sottoreti.size(); i++)
    {
        int bit_host = sottoreti[i].leggi_bit_host();

        fprintf(fp, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"/%s\",\n", 
         sottoreti[i].calcola_host(0).c_str(),
         sottoreti[i].calcola_host(std::pow(2, bit_host) - 1).c_str(), 
         sottoreti[i].calcola_host(std::pow(2, bit_host) - 2).c_str(), 
         sottoreti[i].calcola_host(1).c_str(),
         sottoreti[i].calcola_host(std::pow(2, bit_host) - 3).c_str(), 
         sottoreti[i].leggi_subnet_mask().c_str(),
         std::to_string(sottoreti[i].leggi_bit_rete() + sottoreti[i].leggi_bit_ip()).c_str());
    }

    fclose(fp);

    return 0;
}

void crea_popup(const char* label, const char* messaggio)
{
    Fl_Window* popup = new Fl_Window(200, 80, label);
    popup->set_modal();

    Fl_Box* msg_b = new Fl_Box(10, 5, 180, 40, messaggio);
    msg_b->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);

    Fl_Button* ok_btn = new Fl_Button(70, 50, 60, 25, "OK");
    ok_btn->callback([](Fl_Widget*, void* win) {
        static_cast<Fl_Window*>(win)->hide();
    }, popup);

    popup->end();
    popup->show();
}

const char* seleziona_file()
{
    Fl_Native_File_Chooser fc;
    fc.type(Fl_Native_File_Chooser::BROWSE_FILE);
    fc.title("Seleziona un file");

    int risultato = fc.show();

    if(risultato == -1)
    {
        return NULL;
    }
    else if(risultato == 1)
    {
        return NULL;
    }

    const char* percorso = fc.filename();
    if (percorso == NULL)
        return NULL;

    return percorso;
}