#ifndef SUBNET_H
#define SUBNET_H

#include "ip.h"

#include <bitset>

class Subnet
{
    public:
        Subnet(IP indirizzo, int indice_sottorete, int bit_rete, int bit_host);

        std::string calcola_host(int indice_host);
        std::string calcola_host_bin(int indice_host, bool separatore = false);

        std::string leggi_subnet_mask();
        std::string leggi_subnet_mask_bin();

        int leggi_bit_host() const;
        int leggi_bit_rete() const;

        int leggi_bit_ip() const;

    private:
        IP ip;
        int indice;
        int bit_rete;
        int bit_host;
};

static std::string converti_bin(int num, int bit);
static std::string converti_dec(const std::string& bin);

#endif