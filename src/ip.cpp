#include "ip.h"

std::string default_mask(IPClasse classe)
{
    switch(classe)
    {
        case IPClasse::A:
            return "255.0.0.0";
        case IPClasse::B:
            return "255.255.0.0";
        case IPClasse::C:
            return "255.255.255.0";
        default:
            return "255.255.255.255";
    }
}

IP::IP(const std::string& ip, const std::string& mask)
{
    std::string sm;

    analizza_stringa(ip, ottetti);

    classe = calcola_classe(ottetti[0]);

    if(mask.empty())
    {
        sm = default_mask(classe);
    }
    else
    {
        sm = mask;
    }

    analizza_stringa(sm, subnet_mask);

    bool zero = false;
    for (int ottetto : subnet_mask) {
        for (int i = 7; i >= 0; --i) {
            // Conta se al primo 0 tutti i restanti bit sono 0
            bool bit = (ottetto >> i) & 1;
            if (bit == 0) {
                zero = true;
            }
            if (zero && bit == 1) {
                 for(int j = 0; j < 4; j++)
                    subnet_mask[j] = 255;
                classe = IPClasse::INVALIDA;
            }
        }
    }    

    privato = trova_privato(ottetti);
}

void IP::imposta_ottetto(int i, u8 valore)
{
    if(valore >= 0 && valore <= 255)
        ottetti[i] = valore;
}

u8 IP::leggi_ottetto(int i) const
{
    return ottetti[i];
}

const u8* IP::leggi_ottetti() const
{
    return ottetti;
}

u8 IP::leggi_mask(int i) const
{
    return subnet_mask[i];
}

void IP::imposta_mask(int i, u8 valore)
{
    if(valore >= 0 && valore <= 255)
        subnet_mask[i] = valore;
}

IPClasse IP::leggi_classe() const
{
    return classe;
}

bool IP::leggi_privato() const
{
    return privato;
}

static IPClasse calcola_classe(u8 ott)
{
    if(ott < 128)
        return IPClasse::A;
    else if(ott < 192)
        return IPClasse::B;
    else if(ott < 224)
        return IPClasse::C;
    else
        return IPClasse::INVALIDA;
}

static bool trova_privato(const u8* ottetti)
{
    if(ottetti[0] == 10)
        return true;
    else if(ottetti[0] == 172 && ottetti[1] <= 31 && ottetti[1] >= 16)
        return true;
    else if(ottetti[0] == 172 && ottetti[1] == 168)
        return true;
    else if(ottetti[0] == 192 && ottetti[1] == 168)
        return true;
    else
        return false;
}

void analizza_stringa(const std::string& stringa, uint8_t* ottetti)
{
    std::string ottetto;
    int i = 0;
    int numero_punti = 0;

    for (size_t j = 0; j < stringa.length(); ++j)
    {
        char c = stringa[j];
        
        if (c == '.')
        {
            if (ottetto.empty() || ottetto.length() > 3)
                goto ip_invalido;

            int valore = std::stoi(ottetto);

            if (valore < 0 || valore > 255)
                goto ip_invalido;

            ottetti[i++] = valore;
            ottetto.clear();
            numero_punti++;

            if (numero_punti > 3)
                goto ip_invalido;
        }
        else if (std::isdigit(c))
        {
            ottetto += c;
        }
        else
        {
            goto ip_invalido;
        }
    }

    if (ottetto.empty() || ottetto.length() > 3)
        goto ip_invalido;

    {
        int valore = std::stoi(ottetto);
        if (valore < 0 || valore > 255)
            goto ip_invalido;

        ottetti[i++] = valore;
    }

    return;

ip_invalido:
    for (int j = 0; j < 4; ++j)
    {
        ottetti[j] = 255;
    }
}


bool stessa_rete(const IP& ip1, const IP& ip2)
{
    for(int i = 0; i < 4; i++)
    {
        if((ip1.leggi_ottetto(i) & ip1.leggi_mask(i)) != (ip2.leggi_ottetto(i) & ip2.leggi_mask(i)))
            return false;
    }

    return true;
}

int bit_necessari(int host)
{
    return ceil(log2(host));
}

int bit_rete_per_classe(IPClasse classe)
{
    switch (classe) 
    {
        case IPClasse::A:
            return 8;
        case IPClasse::B:
            return 16;
        case IPClasse::C:
            return 24;
        default:
            return -1;
    }
}
