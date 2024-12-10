#include "ui.h"

Fl_Double_Window *dialogo_w=(Fl_Double_Window *)0;

Fl_Input *ip_input_d_i=(Fl_Input *)0;

static void cb_Ok(Fl_Button*, void*) {
  informazioni_ip(ip_input_d_i->value());
}

Fl_Double_Window* inserisci_ip() {
  { dialogo_w = new Fl_Double_Window(290, 86, "Inserisci IP");
    { ip_input_d_i = new Fl_Input(80, 15, 200, 32, "Indirizzo IP:");
    } // Fl_Input* ip_input_d_i
    { Fl_Button* o = new Fl_Button(114, 49, 74, 22, "Ok");
      o->callback((Fl_Callback*)cb_Ok);
    } // Fl_Button* o
    dialogo_w->set_modal();
    dialogo_w->end();
  } // Fl_Double_Window* dialogo_w
  return dialogo_w;
}

Fl_Double_Window* informazioni_app() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(320, 145, "Informazioni");
    w = o; (void)w;
    { new Fl_Box(108, 11, 110, 52, "Calcolatore IP");
    } // Fl_Box* o
    { new Fl_Box(98, 94, 130, 36, "v .1.0 - 08/12/2024");
    } // Fl_Box* o
    o->end();
  } // Fl_Double_Window* o
  return w;
}

Fl_Output *output_ip_l=(Fl_Output *)0;

Fl_Output *privato_ip_l=(Fl_Output *)0;

Fl_Output *classe_ip_l=(Fl_Output *)0;

Fl_Double_Window* analizza_ip() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(268, 106, "Informazioni IP");
    w = o; (void)w;
    { output_ip_l = new Fl_Output(110, 10, 141, 20, "Default Mask: ");
    } // Fl_Output* output_ip_l
    { privato_ip_l = new Fl_Output(128, 38, 34, 22, "Privato? ");
    } // Fl_Output* privato_ip_l
    { classe_ip_l = new Fl_Output(128, 68, 30, 22, "Classe: ");
    } // Fl_Output* classe_ip_l
    o->end();
  } // Fl_Double_Window* o
  return w;
}

static void cb_Esci(Fl_Menu_*, void*) {
  exit(0);
}

static void cb_Informazioni(Fl_Menu_*, void*) {
  dialogo_w = inserisci_ip();
  dialogo_w->show();
}

static void cb_Confronto(Fl_Menu_*, void*) {
  cambia_ctx(confronto_rete_g);
}

static void cb_Fissa(Fl_Menu_*, void*) {
  cambia_ctx(maschera_fissa_g);
}

static void cb_Variabile(Fl_Menu_*, void*) {
  cambia_ctx(maschera_variabile_g);
}

static void cb_Documentazione(Fl_Menu_*, void*) {
  fl_open_uri("https://github.com/uauei123/calcolatore-ip", NULL, 0);
}

static void cb_Informazioni1(Fl_Menu_*, void*) {
  Fl_Window* informazioni_w = informazioni_app();
  informazioni_w->show();
}

Fl_Menu_Item menu_[] = {
 {"File", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Salva...", 0,  (Fl_Callback*)salva, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Esci", 0,  (Fl_Callback*)cb_Esci, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Opzioni", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Informazioni IP", 0,  (Fl_Callback*)cb_Informazioni, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Confronto Rete", 0,  (Fl_Callback*)cb_Confronto, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Calcola Sottorete", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Fissa", 0,  (Fl_Callback*)cb_Fissa, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Variabile", 0,  (Fl_Callback*)cb_Variabile, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0},
 {"Aiuto", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Documentazione", 0,  (Fl_Callback*)cb_Documentazione, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Informazioni", 0,  (Fl_Callback*)cb_Informazioni1, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

Fl_Group *confronto_rete_g=(Fl_Group *)0;

Fl_Input *ip_confronto_1_i=(Fl_Input *)0;

Fl_Input *ip_confronto_2_i=(Fl_Input *)0;

static void cb_(Fl_Button*, void*) {
  informazioni_ip(ip_confronto_1_i->value());
}

static void cb_1(Fl_Button*, void*) {
  informazioni_ip(ip_confronto_2_i->value());
}

Fl_Round_Button *mask_1_b=(Fl_Round_Button *)0;

static void cb_mask_1_b(Fl_Round_Button*, void*) {
  if(mask_1_b->value() == 0) mask_1_i->show(); else mask_1_i->hide();
}

Fl_Round_Button *mask_2_b=(Fl_Round_Button *)0;

static void cb_mask_2_b(Fl_Round_Button*, void*) {
  if(mask_2_b->value() == 0) mask_2_i->show(); else mask_2_i->hide();
}

Fl_Input *mask_1_i=(Fl_Input *)0;

Fl_Input *mask_2_i=(Fl_Input *)0;

Fl_Group *maschera_fissa_g=(Fl_Group *)0;

Fl_Input *ip_fissa_i=(Fl_Input *)0;

Fl_Spinner *sottoreti_fissa_s=(Fl_Spinner *)0;

static void cb_2(Fl_Button*, void*) {
  informazioni_ip(ip_fissa_i->value());
}

Fl_Group *maschera_variabile_g=(Fl_Group *)0;

Fl_Input *ip_variabile_i=(Fl_Input *)0;

Fl_Spinner *sottoreti_variabile_s=(Fl_Spinner *)0;

static void cb_3(Fl_Button*, void*) {
  informazioni_ip(ip_fissa_i->value());
}

Fl_Double_Window* app() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(811, 380, "Calcolatore IP");
    w = o; (void)w;
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(1, 0, 809, 20);
      o->menu(menu_);
    } // Fl_Menu_Bar* o
    { confronto_rete_g = new Fl_Group(-1, 16, 836, 364);
      confronto_rete_g->hide();
      { ip_confronto_1_i = new Fl_Input(196, 55, 197, 33, "Primo IP: ");
      } // Fl_Input* ip_confronto_1_i
      { ip_confronto_2_i = new Fl_Input(196, 159, 197, 33, "Secondo IP: ");
      } // Fl_Input* ip_confronto_2_i
      { Fl_Button* o = new Fl_Button(396, 58, 28, 28, "?");
        o->callback((Fl_Callback*)cb_);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(396, 161, 28, 28, "?");
        o->callback((Fl_Callback*)cb_1);
      } // Fl_Button* o
      { mask_1_b = new Fl_Round_Button(427, 62, 78, 22, "Maschera di default");
        mask_1_b->down_box(FL_ROUND_DOWN_BOX);
        mask_1_b->value(1);
        mask_1_b->callback((Fl_Callback*)cb_mask_1_b);
      } // Fl_Round_Button* mask_1_b
      { mask_2_b = new Fl_Round_Button(427, 165, 78, 22, "Maschera di default");
        mask_2_b->down_box(FL_ROUND_DOWN_BOX);
        mask_2_b->value(1);
        mask_2_b->callback((Fl_Callback*)cb_mask_2_b);
      } // Fl_Round_Button* mask_2_b
      { Fl_Button* o = new Fl_Button(299, 240, 125, 32, "Confronta");
        o->callback((Fl_Callback*)confronta);
      } // Fl_Button* o
      { mask_1_i = new Fl_Input(96, 88, 197, 30, "Subnet Mask:");
        mask_1_i->hide();
      } // Fl_Input* mask_1_i
      { mask_2_i = new Fl_Input(96, 157, 197, 30, "Subnet Mask:");
        mask_2_i->hide();
      } // Fl_Input* mask_2_i
      confronto_rete_g->end();
    } // Fl_Group* confronto_rete_g
    { maschera_fissa_g = new Fl_Group(0, 16, 835, 364);
      maschera_fissa_g->hide();
      { ip_fissa_i = new Fl_Input(91, 35, 128, 24, "Indirizzo IP: ");
      } // Fl_Input* ip_fissa_i
      { sottoreti_fissa_s = new Fl_Spinner(373, 34, 97, 24, "Numero sottoreti:");
        sottoreti_fissa_s->maximum(4.1943e+06);
      } // Fl_Spinner* sottoreti_fissa_s
      { Fl_Button* o = new Fl_Button(223, 35, 23, 23, "?");
        o->callback((Fl_Callback*)cb_2);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(184, 66, 98, 23, "Calcola");
        o->callback((Fl_Callback*)calcola_fissa);
      } // Fl_Button* o
      maschera_fissa_g->end();
    } // Fl_Group* maschera_fissa_g
    { maschera_variabile_g = new Fl_Group(0, 16, 810, 364);
      maschera_variabile_g->hide();
      { ip_variabile_i = new Fl_Input(91, 37, 128, 24, "Indirizzo IP: ");
      } // Fl_Input* ip_variabile_i
      { sottoreti_variabile_s = new Fl_Spinner(373, 36, 97, 24, "Numero sottoreti:");
        sottoreti_variabile_s->maximum(4.1943e+06);
      } // Fl_Spinner* sottoreti_variabile_s
      { Fl_Button* o = new Fl_Button(223, 37, 23, 23, "?");
        o->callback((Fl_Callback*)cb_3);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(184, 68, 98, 23, "Calcola");
        o->callback((Fl_Callback*)calcola_variabile);
      } // Fl_Button* o
      maschera_variabile_g->end();
    } // Fl_Group* maschera_variabile_g
    o->end();
  } // Fl_Double_Window* o
  return w;
}
