#include <iostream>
#include <cstdlib>
#include "Polinom.h"
using namespace std;
int main()
{
    try
    {
        int izbor;

        while (true)
        {
            system("clear");
            cout << "Izaberite opciju: " << endl;
            cout << " 1.  operator +" << endl;
            cout << " 2.  operator -" << endl;
            cout << " 3.  operator *" << endl;
            cout << " 4.  operator /" << endl;
            cout << " 5.  operator %" << endl;
            cout << " 6.  operator +=" << endl;
            cout << " 7.  operator -=" << endl;
            cout << " 8.  operator *=" << endl;
            cout << " 9.  operator /=" << endl;
            cout << " 10. operator %=" << endl;
            cout << " 11. operator ==" << endl;
            cout << " 12. operator !=" << endl;
            cout << " 13. operator +" << endl;
            cout << " 14. operator -" << endl;
            cout << " 0.  KRAJ PROGRAMA" << endl;
            cout << "?: ";
            cin >> izbor;
            system("clear");

            if (izbor<13 && izbor>0)
            {
                Polinom p,q,r;
                cout << "Unesite polinom P: ";
                cin >> p;
                cout << "Unesite polinom Q: ";
                cin >> q;
                 switch (izbor)
                 {
                     case 1:
                        r=p+q;
                        cout << "Polinom R=P+Q: " << r << endl;
                        break;
                    case 2:
                        r=p-q;
                        cout << "Polinom R=P-Q: " << r << endl;
                        break;
                    case 3:
                        r=p*q;
                        cout << "Polinom R=P*Q: " << r << endl;
                        break;
                    case 4:
                        r=p/q;
                        cout << "Polinom R=P/Q: " << r << endl;
                        break;
                    case 5:
                        r=p%q;
                        cout << "Polinom R=P%Q: " << r << endl;
                        break;
                    case 6:
                        p+=q;
                        cout << "Polinom P (nakon operacije P+=Q): " << p << endl;
                        break;
                    case 7:
                        p-=q;
                        cout << "Polinom P (nakon operacije P-=Q): " << p << endl;
                        break;
                    case 8:
                        p*=q;
                        cout << "Polinom P (nakon operacije P*=Q): " << p << endl;
                        break;
                    case 9:
                        p/=q;
                        cout << "Polinom P (nakon operacije P/=Q): " << p << endl;
                        break;
                    case 10:
                        p%=q;
                        cout << "Polinom P (nakon operacije P%=Q): " << p << endl;
                        break;
                    case 11:
                        if (p==q) cout << "Polinomi P i Q su jednaki!" << endl;
                        else cout << "Polinomi P i Q nisu jednaki!" << endl;
                        break;
                    case 12:
                        if (p!=q) cout << "Polinomi P i Q su razliciti!" << endl;
                        else cout << "Polinomi P i Q nisu razliciti!" << endl;
                        break;
                 }
            }
            else if (izbor==13)
            {
                Polinom p,q;
                cout << "Unesite polinom P: ";
                cin >> p;
                q=+p;
                cout << "Polinom Q=+P: " << q << endl;
            }
            else if (izbor==14)
            {
                Polinom p,q;
                cout << "Unesite polinom P: ";
                cin >> p;
                q=-p;
                cout << "Polinom Q=-P: " << q << endl;
            }
            else if (izbor==0) break;
            system("pause");
        }

        cout << "KRAJ PROGRAMA!!!" << endl;
    }
    catch (const char poruka[])
    {
        cout << poruka << endl;
    }
    catch (bad_alloc)
    {
        cout << "Nedovoljno memorije!" << endl;
    }
    catch(...)
    {
        cout << "Došlo je do problema!" << endl;
    }

    return 0;
}
