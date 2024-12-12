#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>
#include <algorithm>

#include "ip.h"
#include "subnet.h"
#include "ui.h"
#include "util.h"

enum ctx
{
    CTX_NESSUNO,
    CTX_SERIALIZZABILE
};

std::vector<Subnet> sottoreti;

int ctx = CTX_NESSUNO;

#define stampa_subnet(_v, _t)                                                             \
    for (int i = 0; i < _t; i++) {                                                        \
        std::cout << i + 1 << ".\t" << sottoreti[i].calcola_host_bin(_v, true) << "\t\t"  \
                  << sottoreti[i].calcola_host(_v) << std::endl;                          \
    }

void calcola_fissa(Fl_Button* btn, void* data)
{
    if(ip_fissa_i->value()[0] != '\0')
    {
        IP ip(ip_fissa_i->value(), "");
        if(ip.leggi_classe() != IPClasse::INVALIDA)
        {
            sottoreti.clear();

            int n_sottoreti = sottoreti_fissa_s->value();

            if(n_sottoreti > (pow(2, 30 - bit_rete_per_classe(ip.leggi_classe()))))
            {
                crea_popup("Errore", "Non ci sono abbastanza bit.");
                return;
            }

            int bit_host = 32 - bit_rete_per_classe(ip.leggi_classe()) - bit_necessari(n_sottoreti);

            for(int i = 0; i < n_sottoreti; i++)
            {
                sottoreti.emplace_back(ip, i, bit_necessari(n_sottoreti), bit_host);
            }

            TabellaIP* table = new TabellaIP(0, 96, 875, 285, sottoreti);

            maschera_fissa_g->add(*table);

            maschera_fissa_g->redraw();

            ctx = CTX_SERIALIZZABILE;
        }
        else
        {
            crea_popup("Errore", "Hai inserito un IP invalido.");
        }
    }
}

void calcola_variabile(Fl_Button* btn, void* data)
{
    if(ip_variabile_i->value()[0] != '\0')
    {
        IP ip(ip_variabile_i->value(), "");
        if(ip.leggi_classe() != IPClasse::INVALIDA)
        {
            sottoreti.clear();

            int n_sottoreti = sottoreti_variabile_s->value();
            
            std::vector<int> hosts(n_sottoreti);

            for(int i = 0; i < n_sottoreti; i++)
            {
                std::string s = "Inserisci numero di host per la ";
                s += std::to_string(i + 1);
                s += " sottorete: ";
                
                const char* inserito = fl_input(s.c_str());
                if(inserito == NULL)
                    return;

                hosts[i] = std::stoi(inserito) + 3;
            }

            std::sort(hosts.begin(), hosts.end(), std::greater<int>());

            int sottorete_i = 0;

            for(int i = 0; i < n_sottoreti; i++)
            {
                int bit_host = bit_necessari(hosts[i]); 
                int bit_rete = 32 - bit_rete_per_classe(ip.leggi_classe()) - bit_host;

                if(bit_necessari(sottorete_i + 1) > bit_rete)
                {
                    crea_popup("Errore", "Non e' possibile creare sottoreti.");
                    return;
                }

                sottoreti.emplace_back(ip, sottorete_i, bit_rete, bit_host);
                sottorete_i++;
                sottorete_i = sottorete_i << (bit_host - bit_necessari(hosts[i + 1]));
            }

            // Crea una tabella e inizializza con sottoreti
            TabellaIP* table = new TabellaIP(0, 96, 875, 285, sottoreti);

            // Aggiungi la tabella al gruppo
            maschera_variabile_g->add(*table);

            // Ricarica il gruppo
            maschera_variabile_g->redraw();

            ctx = CTX_SERIALIZZABILE;
        }
        else
        {
            crea_popup("Errore", "Hai inserito un IP invalido.");
        }
    }
}

void informazioni_ip(const char* ip_str)
{
    if(ip_str[0] != '\0')
    {
        IP ip(std::string(ip_str), "");
        if(ip.leggi_classe() != IPClasse::INVALIDA)
        {
            if(dialogo_w != NULL)
                dialogo_w->hide();
            
            Fl_Double_Window* ip_w = analizza_ip();
            ip_w->show();

            std::string classe;
            switch(ip.leggi_classe())
            {
                case IPClasse::A:
                    classe = "A";
                    break;
                case IPClasse::B:
                    classe = "B";
                    break;
                case IPClasse::C:
                    classe = "C";
                    break;
            }

            std::string mask = default_mask(ip.leggi_classe());
            mask += "/";
            mask += std::to_string(bit_rete_per_classe(ip.leggi_classe()));

            classe_ip_l->value(classe.c_str());
            output_ip_l->value(mask.c_str());
            privato_ip_l->value((ip.leggi_privato() ? "Si" : "No"));
        }
        else
        {
            crea_popup("Errore", "Hai inserito un IP invalido.");
        }
    }
}

void confronta(Fl_Button* btn, void* data)
{
    // Se gli IP non sono vuoti
    if(ip_confronto_1_i->value()[0] != '\0' && ip_confronto_2_i->value()[0] != '\0')
    {
        std::string mask1;

        // Se non viene usata la maschera di default
        if(mask_1_b->value() == 0)
        {
            // Se la maschera non e' vuota
            if(mask_1_i->value()[0] != '\0')
                mask1 = mask_1_i->value();
            else
                return;
        }

        std::string mask2;
        
        // Se non viene usata la maschera di default
        if(mask_2_b->value() == 0)
        {
            // Se la maschera non e' vuota
            if(mask_2_i->value()[0] != '\0')
                mask2 = mask_2_i->value();
            else
                return;
        }

        IP ip1(ip_confronto_1_i->value(), mask1);
        IP ip2(ip_confronto_2_i->value(), mask2);

        if(ip1.leggi_classe() == IPClasse::INVALIDA || ip2.leggi_classe() == IPClasse::INVALIDA)
        {
            crea_popup("Errore", "Hai inserito un IP invalido.");
            return;
        }

        if(stessa_rete(ip1, ip2))
        {
            crea_popup("Confronto", "IP sono della stessa rete.");
        }
        else
        {
            crea_popup("Confronto", "IP non sono della stessa rete.");
        }
    }
}

void salva(Fl_Menu_* btn, void* data)
{
    if(ctx == CTX_SERIALIZZABILE)
    {
        //fl_file_chooser("Seleziona un file", "*.csv", NULL, 0);
        const char *filename = seleziona_file();

        if(filename == NULL)
            return;

        if(serializza(sottoreti, filename) == 0)
            crea_popup("Salvato", "Salvataggio completato.");
        else
            crea_popup("Errore", "Non e' stato possibile salvare.");
    }
    else
    {
        crea_popup("Errore", "Non c'e' niente da salvare.");
    }
}

void cambia_ctx(Fl_Group* attivo)
{
    if(confronto_rete_g != NULL)
        confronto_rete_g->hide();

    if(maschera_fissa_g != NULL)
        maschera_fissa_g->hide();
    
    if(maschera_variabile_g != NULL)
        maschera_variabile_g->hide();

    attivo->show();

    ctx = CTX_NESSUNO;
}



int main(int argc, char **argv)
{
    using namespace std;
    {
        if(argc == 1 || strcmp(argv[1], "--gui") == 0 )
        {
            // Crea la finestra principale
            Fl_Double_Window* app_w = app();
            app_w->show();
            return Fl::run();
        }
        
        if(strcmp(argv[1], "-i") == 0 && argc == 3)
        {
            IP ip(argv[2], "");
            
            if(ip.leggi_classe() == IPClasse::INVALIDA)
            {
                cout << "Hai inserito un IP invalido." << endl;
                return -1;
            }

            char classe;
            switch(ip.leggi_classe())
            {
                case IPClasse::A:
                    classe = 'A';
                    break;
                case IPClasse::B:
                    classe = 'B';
                    break;
                case IPClasse::C:
                    classe = 'C';
                    break;
            }

            cout << "Classe: " << classe << endl;
            cout << "Default Subnet Mask: " << default_mask(ip.leggi_classe()) << endl;
            cout << "Privato? " << ((ip.leggi_privato()) ? "Si" : "No");
        } 
        else if(strcmp(argv[1], "-c") == 0 && argc == 6)
        {
            string mask1 = "";
            string mask2 = "";

            if(strcmp(argv[3], "-d") != 0)
            {
                mask1 = argv[3];
            }
            if(strcmp(argv[5], "-d") != 0) 
            {
                mask2 = argv[5];
            }

            IP ip1(argv[2], mask1);
            IP ip2(argv[4], mask2);

            if(ip1.leggi_classe() == IPClasse::INVALIDA || ip2.leggi_classe() == IPClasse::INVALIDA)
            {
                cout << "Hai inserito un IP invalido.";
                return -1;
            }

            cout << stessa_rete(ip1, ip2);
        }
        else if(strcmp(argv[1], "-sf") == 0 && (argc == 4 || (argc == 6 && strcmp(argv[4], "-f") == 0)))
        {
            IP ip(argv[2], "");
            
            if(ip.leggi_classe() == IPClasse::INVALIDA)
            {
                cout << "Hai inserito un IP invalido." << endl;
                return -1;
            }

            int n_sottoreti = stoi(argv[3]);

            // Calcola numero di sottoreti massime con almeno 1 host
            if(n_sottoreti > (pow(2, 30 - bit_rete_per_classe(ip.leggi_classe()))))
            {
                cout << "Non ci sono abbastanza bit per creare sottoreti." << endl;
                return -1;
            }

            int bit_host = 32 - bit_rete_per_classe(ip.leggi_classe()) - bit_necessari(n_sottoreti);

            for(int i = 0; i < n_sottoreti; i++)
            {
                sottoreti.emplace_back(ip, i, bit_necessari(n_sottoreti), bit_host);
            }

            if(argc == 4)
            {
                cout << "NET ID\n\n";
                stampa_subnet(0, n_sottoreti)

                cout << "\n\n\nBROADCAST\n\n";
                stampa_subnet(pow(2, bit_host) - 1, n_sottoreti)

                cout << "\n\n\nGATEWAY\n\n";
                stampa_subnet(pow(2, bit_host) - 2, n_sottoreti)

                cout << "\n\n\nPRIMO HOST\n\n";
                stampa_subnet(1, n_sottoreti)

                cout << "\n\n\nULTIMO HOST\n\n";
                stampa_subnet(pow(2, bit_host) - 3, n_sottoreti)

                cout << "\n\n\nSUBNET MASK\n\n";
                cout << sottoreti[0].leggi_subnet_mask_bin() << "\t" << sottoreti[0].leggi_subnet_mask();
                cout << "/" << sottoreti[0].leggi_bit_rete() + sottoreti[0].leggi_bit_ip(); 
            }
            else
            {
                if(serializza(sottoreti, argv[5]) == 0)
                {
                    cout << "Salvato nel file " << argv[5] << endl;
                }
                else
                {
                    cout << "Errore nel salvataggio del file" << endl;
                }
            }

        }
        else if(strcmp(argv[1], "-sv") == 0 && argc > 3)
        {
            bool file_salva = false;

            IP ip(argv[2], "");
            
            if(ip.leggi_classe() == IPClasse::INVALIDA)
            {
                cout << "Hai inserito un IP invalido." << endl;
                return -1;
            }

            int n_sottoreti = argc - 3;

            if(strcmp(argv[argc - 2], "-f") == 0)
            {
                file_salva = true;
                n_sottoreti -= 2;
            }

            vector<int> hosts;

            hosts.resize(n_sottoreti);

            for(int i = 0; i < n_sottoreti; i++)
                hosts[i] = stoi(argv[i + 3]) + 3;

            //                   [] (int a, int b) { return a > b; }
            //                                    v
            sort(hosts.begin(), hosts.end(), greater<int>());

            int sottorete_i = 0;

            for(int i = 0; i < n_sottoreti; i++)
            {
                int bit_host = bit_necessari(hosts[i]); 
                int bit_rete = 32 - bit_rete_per_classe(ip.leggi_classe()) - bit_host;

                // Quando i bit per creare la sottorete sono piu' di quelli disponibili,
                // annulla.
                if(bit_necessari(sottorete_i + 1) > bit_rete)
                {
                    cout << "Impossibile creare sottoreti." << endl;
                    return -1;
                }

                sottoreti.emplace_back(ip, sottorete_i, bit_rete, bit_host);
                sottorete_i++;
                // Se servono piu' bit per gli host, fai lo shift a sinistra
                sottorete_i = sottorete_i << (bit_host - bit_necessari(hosts[i + 1]));
            }

            if(file_salva)
            {
                if(serializza(sottoreti, argv[argc - 1]) == 0)
                {
                    cout << "Salvato nel file " << argv[argc - 1] << endl;
                }
                else
                {
                    cout << "Errore nel salvataggio del file" << endl;
                }
            }
            else
            {
                cout << "NET ID\n\n";
                stampa_subnet(0, n_sottoreti)

                cout << "\n\n\nBROADCAST\n\n";
                stampa_subnet(pow(2, bit_necessari(hosts[i])) - 1, n_sottoreti)

                cout << "\n\n\nGATEWAY\n\n";
                stampa_subnet(pow(2, bit_necessari(hosts[i])) - 2, n_sottoreti)

                cout << "\n\n\nPRIMO HOST\n\n";
                stampa_subnet(1, n_sottoreti)

                cout << "\n\n\nULTIMO HOST\n\n";
                stampa_subnet(pow(2, bit_necessari(hosts[i])) - 3, n_sottoreti)

                cout << "\n\n\nSUBNET MASK\n\n";
                for(int i = 0; i < n_sottoreti; i++)
                {
                    cout << i + 1 << ".\t" << sottoreti[i].leggi_subnet_mask_bin() << "\t" << sottoreti[i].leggi_subnet_mask();
                    cout << "/" << sottoreti[i].leggi_bit_rete() + sottoreti[i].leggi_bit_ip() << endl; 
                }
            }
        }
        else
        {
            cout << "Utilizzo: " << argv[0] << " [opzioni]" << endl;
            cout << endl;
            cout << "Opzioni:" << endl;
            cout << "  --help" << endl;
            cout << "      Mostra questa schermata." << endl;
            cout << endl;
            cout << "  --gui" << endl;
            cout << "      Avvia l'interfaccia grafica (GUI)." << endl;
            cout << endl;
            cout << "  -i <IP>" << endl;
            cout << "      Mostra informazioni sull'IP inserito." << endl;
            cout << endl;
            cout << "  -c <IP1> <maschera1> <IP2> <maschera2>" << endl;
            cout << "      Verifica se due IP appartengono alla stessa rete." << endl;
            cout << "      Usando '-d' verra' impostata la maschera di default per l'IP inserito." << endl;
            cout << endl;
            cout << "  -sf <IP> <n_sottoreti>" << endl;
            cout << "      Calcola e mostra le sottoreti per un dato IP e numero di sottoreti." << endl;
            cout << "      Usando '-f <nome_file>' come ultimo argomento, il risultato verra' scritto nel file." << endl;
            cout << endl;
            cout << "  -sv <IP> <host_1> [host_2] [...]" << endl;
            cout << "      Calcola sottoreti di diverse dimensioni per un dato IP." << endl;
            cout << "      Usando '-f <nome_file>' come ultimo argomento, il risultato verra' scritto nel file." << endl;
            cout << endl;
        }
    }

    return 0;
}
