#include "Polinom.h"
inline double abs(double x) { return (x>0 ? x : -x); }
Polinom::Polinom()
{
    pocetak=0;
    brojClanova=0;
}

Polinom::Polinom(double broj)
{
    pocetak=new Cvor(0,broj,0,0);
    brojClanova=1;
}

Polinom::Polinom (const Polinom& p)
{
    if (!p.pocetak) { pocetak=0; return; }
    pocetak=new Cvor(p.pocetak->stepen,p.pocetak->koeficijent,0,0);
    Cvor *tekuci=pocetak;
    for (Cvor *i=p.pocetak->sljedeci; i; i=i->sljedeci)
        tekuci=tekuci->sljedeci=new Cvor(i->stepen,i->koeficijent,tekuci,0);
    brojClanova=p.brojClanova;
}
Polinom::~Polinom()
{
    if (pocetak)
    {
        Cvor* zaBrisanje=pocetak, *tekuci=pocetak;
        do
        {
            tekuci=tekuci->sljedeci;
            delete zaBrisanje;
            zaBrisanje=tekuci;
        } while(tekuci);
    }
}

Polinom& Polinom::operator=(const Polinom& p)
{
    if (&p==this) return *this;
    while (pocetak) izbrisiClan(pocetak);

    if (!p.pocetak) { pocetak=0; brojClanova=0; return *this; }
    pocetak=new Cvor(p.pocetak->stepen,p.pocetak->koeficijent,0,0);
    Cvor *tekuci=pocetak;
    for (Cvor *i=p.pocetak->sljedeci; i; i=i->sljedeci)
        tekuci=tekuci->sljedeci=new Cvor(i->stepen,i->koeficijent,tekuci,0);
    brojClanova=p.brojClanova;

    return *this;
}

void Polinom::dodajClan(double k, int e)
{
    if (k==0.0) return;
    if (!pocetak) { pocetak=new Cvor(e,k,0,0); brojClanova=1; }
    else
    {
        if (e > pocetak->stepen)
        {
            Cvor *pom=new Cvor(e,k,0,pocetak);
            pocetak->prethodni=pom;
            pocetak=pom;
            brojClanova++;
        }
        else if (e==pocetak->stepen)
        {
            pocetak->koeficijent += k;
            if (pocetak->koeficijent==0.0) izbrisiClan(pocetak);
        }
        else
        {
            Cvor *tekuci=pocetak;
            while (tekuci->sljedeci && tekuci->sljedeci->stepen >= e)
                tekuci=tekuci->sljedeci;

            if (tekuci->stepen == e)
            {
                tekuci->koeficijent += k;
                if (tekuci->koeficijent==0.0) izbrisiClan(tekuci);
            }
            else
            {
                Cvor *pom=new Cvor(e,k,tekuci,tekuci->sljedeci);
                if (tekuci->sljedeci) tekuci->sljedeci->prethodni=pom;
                tekuci->sljedeci=pom;
                brojClanova++;
            }
        }
    }
}

void Polinom::izbrisiClan(Cvor* zaBrisanje)
{
    if (zaBrisanje==pocetak)
    {
        if (!pocetak->sljedeci)
        {
            delete zaBrisanje;
            pocetak=0;
        }
        else
        {
            pocetak=pocetak->sljedeci;
            pocetak->prethodni=0;
            delete zaBrisanje;
        }
    }
    else
    {
        zaBrisanje->prethodni->sljedeci=zaBrisanje->sljedeci;
        if (zaBrisanje->sljedeci) zaBrisanje->sljedeci->prethodni=zaBrisanje->prethodni;
        delete zaBrisanje;
    }

    brojClanova--;
}

const Polinom Polinom::operator+(const Polinom& p) const
{
    Polinom rezultat(*this);
    for (Cvor *tekuci = p.pocetak; tekuci; tekuci=tekuci->sljedeci)
        rezultat.dodajClan(tekuci->koeficijent, tekuci->stepen);

    return rezultat;
}

const Polinom Polinom::operator-(const Polinom& p) const
{
    Polinom rezultat(*this);
    for (Cvor *tekuci = p.pocetak; tekuci; tekuci=tekuci->sljedeci)
        rezultat.dodajClan(-tekuci->koeficijent, tekuci->stepen);

    return rezultat;
}

const Polinom Polinom::operator*(const Polinom& p) const
{
    Polinom rezultat;

    Cvor *i,*j;

    for (i=pocetak; i; i=i->sljedeci)
        for (j=p.pocetak; j; j=j->sljedeci)
            rezultat.dodajClan((i->koeficijent) * (j->koeficijent), (i->stepen) + (j->stepen));

    return rezultat;
}

const Polinom Polinom::operator/(const Polinom& p) const
{
    if (!p.pocetak) throw "Nije dozvoljeno dijeliti s nulom!";
    Polinom q;
    if (pocetak->stepen < p.pocetak->stepen) return q;

    Polinom r(*this);
    while (r.vratiStepen() >= p.vratiStepen())
    {
        q.dodajClan(r.pocetak->koeficijent / p.pocetak->koeficijent, r.pocetak->stepen - p.pocetak->stepen);
        Polinom pom1;
        pom1.dodajClan(r.pocetak->koeficijent / p.pocetak->koeficijent, r.pocetak->stepen - p.pocetak->stepen);
        r=r-p*pom1;
    }

    return q;
}

const Polinom Polinom::operator%(const Polinom& p) const
{
    if (!p.pocetak) throw "Nije dozvoljeno dijeliti s nulom!";
    Polinom q,r(*this);
    if (pocetak->stepen < p.pocetak->stepen) return r;

    while (r.vratiStepen() >= p.vratiStepen())
    {
        q.dodajClan(r.pocetak->koeficijent / p.pocetak->koeficijent, r.pocetak->stepen - p.pocetak->stepen);
        Polinom pom1;
        pom1.dodajClan(r.pocetak->koeficijent / p.pocetak->koeficijent, r.pocetak->stepen - p.pocetak->stepen);
        r=r-p*pom1;
    }

    return r;
}

const Polinom& Polinom::operator+=(const Polinom& p)
{
    for (Cvor *tekuci = p.pocetak; tekuci; tekuci=tekuci->sljedeci)
        dodajClan(tekuci->koeficijent, tekuci->stepen);

    return *this;
}

const Polinom& Polinom::operator-=(const Polinom& p)
{
    for (Cvor *tekuci = p.pocetak; tekuci; tekuci=tekuci->sljedeci)
        dodajClan(- tekuci->koeficijent, tekuci->stepen);

    return *this;
}

const Polinom& Polinom::operator*=(const Polinom& p)
{
    return *this=*this*p;
}

const Polinom& Polinom::operator/=(const Polinom& p)
{
    return *this=*this/p;
}

const Polinom& Polinom::operator%=(const Polinom& p)
{
    return *this=*this%p;
}

const Polinom Polinom::operator+() const
{
    return *this;
}

const Polinom Polinom::operator-() const
{
    Polinom rezultat;
    if (!pocetak) return rezultat;
    rezultat.pocetak = new Cvor(pocetak->stepen,-(pocetak->koeficijent),0,0);

    Cvor* tekuci=rezultat.pocetak;
    for (Cvor *i=pocetak->sljedeci; i; i=i->sljedeci)
        tekuci=tekuci->sljedeci=new Cvor(i->stepen,-(i->koeficijent),tekuci,0);
    rezultat.brojClanova=brojClanova;

    return rezultat;
}

bool Polinom::operator==(const Polinom& p) const
{
    if (brojClanova!=p.brojClanova) return false;
    Cvor *i,*j;

    for (i=pocetak, j=p.pocetak; i,j; i=i->sljedeci, j=j->sljedeci)
        if (i->koeficijent != j->koeficijent || i->stepen != j->stepen) return false;

    return true;
}

bool Polinom::operator!=(const Polinom& p) const
{
    if (brojClanova!=p.brojClanova) return true;
    Cvor *i,*j;

    for (i=pocetak, j=p.pocetak; i,j; i=i->sljedeci, j=j->sljedeci)
        if (i->koeficijent != j->koeficijent || i->stepen != j->stepen) return true;

    return false;
}

void ispisiClan(double k, int e, ostream &izlaz, bool prvi=false)
{
    if (k>0 && !prvi) izlaz << "+";
    else if (k<0) izlaz << "-";
    if (abs(k)!=1.0) izlaz << abs(k);
    else if (e==0) izlaz << abs(k);
    if (e>0) izlaz << "x";
    if (e>1) izlaz << "^" << e;
}

ostream& operator<<(ostream& izlaz, const Polinom& p)
{
    if (!p.pocetak) { izlaz << "0"; return izlaz; }

    ispisiClan(p.pocetak->koeficijent,p.pocetak->stepen, izlaz, true);
    for (Polinom::Cvor* tekuci=p.pocetak->sljedeci; tekuci; tekuci=tekuci->sljedeci)
        ispisiClan(tekuci->koeficijent,tekuci->stepen, izlaz);

    return izlaz;
}

istream& operator>>(istream& ulaz, Polinom& p)
{
    char znak;
    double k;
    int e;

    //ulaz.clear();
    //ulaz.ignore(100000,10);
    do
    {
        ulaz >> k >> znak >> znak >> e;
        p.dodajClan(k,e);
    } while (ulaz.peek()!='\n');

    return ulaz;
}

int Polinom::vratiStepen() const
{
    if (pocetak) return pocetak->stepen;
    else return 0;
}

bool Polinom::daLiJeNula() const
{
    return !pocetak;
}

int Polinom::vratiBrojClanova() const
{
    return brojClanova;
}
