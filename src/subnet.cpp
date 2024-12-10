#include "subnet.h"

Subnet::Subnet(IP indirizzo, int indice_sottorete, int bit_rete, int bit_host) 
    : ip(indirizzo), indice(indice_sottorete), bit_rete(bit_rete), bit_host(bit_host) {}

static std::string converti_bin(int num, int bit)
{
    std::bitset<32> bin(num);

    return bin.to_string().substr(32 - bit);
}

static std::string converti_dec(const std::string& bin) {
    std::bitset<32> bits(bin);
    return std::to_string(bits.to_ulong());
}

std::string Subnet::calcola_host(int indice_host)
{
    std::string risultato = "";

    for(int i = 0; i < ip.leggi_classe() + 1; i++)
    {
        risultato += std::to_string(ip.leggi_ottetto(i));
        risultato += ".";
    }

    std::string host_bin = calcola_host_bin(indice_host);

    for (int i = 0; i < 3 - ip.leggi_classe(); i++)
    {
        std::string ottetto_dec = converti_dec(host_bin.substr(i * 8, 8));

        if (i > 0)
            risultato += ".";

        risultato += ottetto_dec;
    }
    
    return risultato;
}

std::string Subnet::calcola_host_bin(int indice_host, bool separatore)
{
    std::string risultato = "";

    risultato += converti_bin(indice, bit_rete);
    if(separatore)
        risultato += " | ";
    risultato += converti_bin(indice_host, bit_host);

    return risultato;
}

std::string Subnet::leggi_subnet_mask()
{
    //~((1 << 32 - (bit_rete_per_classe(ip.leggi_classe()) + bit_rete)) - 1) 
    // Trova la maschera dell'host e poi fai il NOT per avere la mask della rete
    unsigned int mask = ~((1 << bit_host) - 1); 

    std::string risultato = "";
    for (int i = 3; i >= 0; i--) {
        // Aggiungi un ottetto ogni 8 bit (2^8 - 255, 0xFF)
        unsigned int ottetto = (mask >> (i * 8)) & 0xFF;
        risultato += std::to_string(ottetto);
        if (i > 0) {
            risultato += ".";
        }
    }

    return risultato;
}

std::string Subnet::leggi_subnet_mask_bin()
{
    unsigned int mask = ~((1 << bit_host) - 1); 

    std::string risultato = "";
    for (int i = 3; i >= 0; i--) {
        unsigned int ottetto = (mask >> (i * 8)) & 0xFF;
        risultato += converti_bin(ottetto, 8);
        if (i > 0) {
            risultato += ".";
        }
    }

    return risultato;
}

int Subnet::leggi_bit_host() const
{
    return bit_host;
}

int Subnet::leggi_bit_rete() const
{
    return bit_rete;
}

int Subnet::leggi_bit_ip() const
{
    return bit_rete_per_classe(ip.leggi_classe());
}