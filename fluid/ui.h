#ifndef ui_h
#define ui_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *dialogo_w;
#include <FL/Fl_Input.H>
extern Fl_Input *ip_input_d_i;
#include <FL/Fl_Button.H>
Fl_Double_Window* inserisci_ip();
#include <FL/Fl_Box.H>
Fl_Double_Window* informazioni_app();
#include <FL/Fl_Output.H>
extern Fl_Output *output_ip_l;
extern Fl_Output *privato_ip_l;
extern Fl_Output *classe_ip_l;
Fl_Double_Window* analizza_ip();
#include <FL/Fl_Menu_Bar.H>
extern void salva(Fl_Menu_*, void*);
#include <cstdlib>
#include <FL/filename.h>
#include <FL/Fl_Group.H>
extern Fl_Group *confronto_rete_g;
extern Fl_Input *ip_confronto_1_i;
extern Fl_Input *ip_confronto_2_i;
#include <FL/Fl_Round_Button.H>
extern Fl_Round_Button *mask_1_b;
extern Fl_Round_Button *mask_2_b;
extern void confronta(Fl_Button*, void*);
extern Fl_Input *mask_1_i;
extern Fl_Input *mask_2_i;
extern Fl_Group *maschera_fissa_g;
extern Fl_Input *ip_fissa_i;
#include <FL/Fl_Spinner.H>
extern Fl_Spinner *sottoreti_fissa_s;
extern void calcola_fissa(Fl_Button*, void*);
extern Fl_Group *maschera_variabile_g;
extern Fl_Input *ip_variabile_i;
extern Fl_Spinner *sottoreti_variabile_s;
extern void calcola_variabile(Fl_Button*, void*);
Fl_Double_Window* app();
extern Fl_Menu_Item menu_[];
extern void informazioni_ip(const char* ip_str);
extern void cambia_ctx(Fl_Group* attivo);
#endif
