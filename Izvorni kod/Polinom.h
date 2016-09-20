#ifndef POLINOM_H
#define POLINOM_H
#include <iostream>
using namespace std;
class Polinom
{
    struct Cvor
    {
        int stepen;
        double koeficijent;
        Cvor *prethodni, *sljedeci;

        Cvor (int stepen) : stepen(stepen), koeficijent(0.0), prethodni(0), sljedeci(0){}
        Cvor (double koeficijent) : stepen(0), koeficijent(koeficijent), prethodni(0), sljedeci(0){}
        Cvor (int stepen, double koeficijent) : stepen(stepen), koeficijent(koeficijent), prethodni(0), sljedeci(0){}
        Cvor (Cvor* prev, Cvor* next) : prethodni(prev), sljedeci(next){}
        Cvor (int stepen, double koef, Cvor* prev, Cvor* next) : stepen(stepen), koeficijent(koef), prethodni(prev), sljedeci(next){}
    };

    Cvor *pocetak;
    int brojClanova;

    public:
    Polinom(double broj);
    Polinom();
    ~Polinom();
    Polinom (const Polinom&);
    Polinom& operator=(const Polinom&);
    const Polinom operator+(const Polinom&) const;
    const Polinom operator-(const Polinom&) const;
    const Polinom operator*(const Polinom&) const;
    const Polinom operator/(const Polinom&) const;
    const Polinom operator%(const Polinom&) const;
    const Polinom& operator+=(const Polinom&);
    const Polinom& operator-=(const Polinom&);
    const Polinom& operator*=(const Polinom&);
    const Polinom& operator/=(const Polinom&);
    const Polinom& operator%=(const Polinom&);
    const Polinom operator+() const;
    const Polinom operator-() const;
    bool operator==(const Polinom&) const;
    bool operator!=(const Polinom&) const;
    friend ostream& operator<<(ostream& izlaz, const Polinom&);
    friend istream& operator>>(istream& ulaz, Polinom&);
    int vratiStepen() const;
    void dodajClan(double k, int e);
    void izbrisiClan(Cvor* zaBrisanje);
    bool daLiJeNula() const;
    int vratiBrojClanova() const;
};

#endif
