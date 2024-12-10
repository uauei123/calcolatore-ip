#ifndef IP_H
#define IP_H

#include <iostream>
#include <cstdint>
#include <cmath>
#include <string>

using u8 = uint8_t;

enum IPClasse
{
    A,
    B,
    C,
    INVALIDA
};

class IP
{
    public:

        IP(const std::string& ip, const std::string& mask);

        void imposta_ottetto(int i, u8 valore);
        u8 leggi_ottetto(int i) const;
        const u8* leggi_ottetti() const;

        u8 leggi_mask(int i) const;
        void imposta_mask(int i, u8 valore);

        IPClasse leggi_classe() const;

        bool leggi_privato() const;

    private:

        u8 ottetti[4];
        u8 subnet_mask[4];
        IPClasse classe;
        bool privato;

};

static IPClasse calcola_classe(u8 ott);
static bool trova_privato(const u8* ottetti);
void analizza_stringa(const std::string& stringa, u8* ottetti);
std::string default_mask(IPClasse classe);
bool stessa_rete(const IP& ip1, const IP& ip2);
int bit_necessari(int host);
int bit_rete_per_classe(IPClasse classe);

#endif
