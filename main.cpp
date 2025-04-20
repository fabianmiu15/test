#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstring>
using namespace std;


class Persoana /// Proiect 2
{
protected:
    char* nume;
    char* email;

public:
    Persoana()
    {
        nume = new char[strlen("Anonim") + 1];
        strcpy(nume, "Anonim");

        email = new char[strlen("anonim@email.com") + 1];
        strcpy(email, "anonim@email.com");
    }

    Persoana(const char* nume, const char* email)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);

        this->email = new char[strlen(email) + 1];
        strcpy(this->email, email);
    }

    Persoana(const Persoana& p)
    {
        nume = new char[strlen(p.nume) + 1];
        strcpy(nume, p.nume);

        email = new char[strlen(p.email) + 1];
        strcpy(email, p.email);
    }

    virtual ~Persoana() {
        if (nume) delete[] nume;
        if (email) delete[] email;
    }

    Persoana& operator=(const Persoana& p)
    {
        if (this != &p)
        {
            if (nume) delete[] nume;
            if (email) delete[] email;

            nume = new char[strlen(p.nume) + 1];
            strcpy(nume, p.nume);

            email = new char[strlen(p.email) + 1];
            strcpy(email, p.email);
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Persoana& p)
    {
        out << "Nume: " << p.nume << "\nEmail: " << p.email << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Persoana& p)
    {
        char buffer[100];
        cout << "Introdu numele: ";
        if (in.peek() == '\n')
            in.ignore();
        in.getline(buffer, 100);

        delete[] p.nume;

        p.nume = new char[strlen(buffer) + 1];
        strcpy(p.nume, buffer);

        cout << "Introdu email-ul: ";
        in.getline(buffer, 100);

        delete[] p.email;
        p.email = new char[strlen(buffer) + 1];
        strcpy(p.email, buffer);

        return in;
    }

    virtual void afiseazaProfil() const = 0; // Clasa abstracta
};



class Entitate
{
protected:
    static int generatorID;
    const int entitateID;

public:
    Entitate()
        : entitateID(generatorID++)
    {}

    Entitate(const Entitate& other)
        : entitateID(generatorID++)
    {}

    virtual ~Entitate() {}

    Entitate& operator=(const Entitate&) = default;

    int getEntitateID() const
    {
        return entitateID;
    }

    virtual void descrieEntitate() const = 0;

    friend ostream& operator<<(ostream& out, const Entitate& e)
    {
        out << "Entitate ID: " << e.entitateID << endl;
        return out;
    }
};
int Entitate::generatorID = 9000;


class Client : virtual public Persoana, public virtual Entitate
{
private:
    const int clientID;
    int puncteFidelitate;

    static int generatorID; /// Generator de ID-uri pentru clienti
    static int numarClienti; /// Contor pentru numarul de clienti
    static Client *listaClienti; /// Lista statica de clienti

public:
    /// Constructorul fara parametri
    Client()
        : Persoana(), clientID(generatorID++), puncteFidelitate(0)
    {}

    /// Constructor cu parametri - nume si email
    Client(const char* nume, const char* email)
        : Persoana(nume, email), clientID(generatorID++), puncteFidelitate(0)
    {}

    /// Constructor cu parametri - nume, email si puncte fidelitate
    Client(const char* nume, const char* email, int puncteFidelitate)
        : Persoana(nume, email), clientID(generatorID++), puncteFidelitate(puncteFidelitate)
    {}

    /// Constructor cu parametri - doar nume, email implicit
    Client(const char* nume)
        : Persoana(nume, "client@example.com"), clientID(generatorID++), puncteFidelitate(0)
    {}

    /// Constructorul de copiere
    Client(const Client& c)
        : Persoana(c), clientID(c.clientID), puncteFidelitate(c.puncteFidelitate)
    {}

    /// Destructorul
    ~Client()
    {}

    /// Operatorul de atribuire
    Client& operator=(const Client& c)
    {
        if (this == &c)
            return *this;

        Persoana::operator=(c);
        puncteFidelitate = c.puncteFidelitate;

        return *this;
    }


    /// Operatorul >> (stream input)
    friend istream& operator>>(istream& in, Client& c) /// Ne propunem citirea unui obiect de tip Client
    {
        char buffer[100];

        cout << "Introdu numele clientului: ";
        if (in.peek() == '\n') /// Se ignora caracterul newline ramas din citirea anterioara daca urmatorul caracter din stream este un newline
            in.ignore();
        in.getline(buffer, 100);

        if (c.nume != nullptr)
            delete[] c.nume;
        c.nume = new char[strlen(buffer) + 1];
        strcpy(c.nume, buffer);

        cout << "Introdu e-mailul clientului: ";
        in.getline(buffer, 100);

        if (c.email != nullptr)
            delete[] c.email;
        c.email = new char[strlen(buffer) + 1];
        strcpy(c.email, buffer);

        return in; /// Permite ca operatorul >> sa fie folosit in lant
    }

    /// Operatorul << (stream output)
    friend ostream& operator<<(ostream& out, const Client& c)
    {
        out << "Client ID: " << c.clientID << endl;
        out << "Nume: " << c.nume << endl;
        out << "Email: " << c.email << endl;
        out << "Puncte de fidelitate: " << c.puncteFidelitate << endl;
        return out;
    }

    /// Setters & Getters

    // Getter pentru nume
    const char* getNume() const /// Se returneaza un pointer la un sir de caractere constant
    {
        /// Metoda nu va modifica obiectul curent asupra caruia este apelata
        return nume;
    }

    // Setter pentru nume
    void setNume (char *numeNou)
    {
        if (this->nume != nullptr)
            delete[] this->nume;

        this->nume = new char[strlen(numeNou) + 1];
        strcpy(this->nume, numeNou);
    }

    // Getter pentru email
    const char *getEmail() const
    {
        return email;
    }

    // Setter pentru email
    void setEmail (char *email)
    {
        if (this->email != nullptr)
            delete[] this->email;

        this->email = new char[strlen(email) + 1];
        strcpy(this->email, email);
    }

    // Getter pentru numarRezervari
    int getPuncteFidelitate() const
    {
        return puncteFidelitate;
    }

    // Getter pentru clientID
    int getClientID() const
    {
        return this->clientID;
    }

    static int getNumarClienti()
    {
        return numarClienti;
    }

    static Client* getListaClienti()
    {
        return listaClienti;
    }

    static Client* getClientDupaID (int clientID)
    {
        for (int i = 0; i < numarClienti; i++)
            if (listaClienti[i].clientID == clientID)
                return &listaClienti[i];
        return nullptr;
    }


    /// Metoda din clasa abstracta Persoana
    void afiseazaProfil() const override
    {
        cout << "Client [" << clientID << "] - " << getNume()
             << " <" << getEmail() << ">, "
             << puncteFidelitate << " puncte de fidelitate." << endl;
    }


    /// Metode statice

    static void adaugaClientInLista (const Client& c)
    {
        listaClienti[numarClienti++] = c;
    }

    static void afiseazaTotiClientii()
    {
        for (int i = 0; i < numarClienti; i++)
            cout << listaClienti[i] << endl;
    }

    static void afiseazaClientDupaID(int clientID)
    {
        for (int i = 0; i < numarClienti; i++)
            if (listaClienti[i].clientID == clientID)
            {
                cout << listaClienti[i] << endl;
                return;
            }
        cout << "Nu am gasit niciun client cu ID-ul " << clientID << endl;
    }

    static void stergeClientDupaID(int clientID)
    {
        if (numarClienti == 0)
        {
            cout << "Nu exista clienti in lista" << endl;
            return;
        }

        bool startDelete = false;
        if (clientID == listaClienti[numarClienti - 1].clientID)
        {
            numarClienti--;
            return;
        }
        for (int i = 1; i < numarClienti; i++)
        {
            if (clientID == listaClienti[i - 1].clientID)
                startDelete = true;

            if (startDelete)
                listaClienti[i - 1] = listaClienti[i];
        }

        if (startDelete)
            numarClienti --;
        else
            cout << "Nu am gasit clientul cu ID-ul " << clientID << endl;
    }

    static void stergeListaClientilor()
    {
        numarClienti = 0;
        if (listaClienti != nullptr)
            delete[] listaClienti;
    }

    /// SUPRAINCARCAREA OPERATORILOR
    // Operatorul []
    const char* operator[](int index) const
    {
        switch(index)
        {
        case 0:
            return getNume();
        case 1:
            return getEmail();
        default:
            return "Index invalid";
        }
    }

    // Operator ++ prefix (++client)
    Client& operator++()
    {
        puncteFidelitate++;
        return *this; /// Returneaza o referinta la obiectul curent, adica instanta pe care operatorul a fost apelat
    }

    // Operator ++ postfix (client++)
    Client operator++(int) /// La sfarsit este un parametru dummy, folosit pentru a diferenta intre ++ prefix si postfix
    {
        Client temp = *this; /// Creeaza o copie a obiectului curent
        puncteFidelitate++;
        return temp; /// Returneaza copia obiectului curent
    }

    // Operator -- prefix (--client)
    Client& operator--()
    {
        if (puncteFidelitate > 0)
            puncteFidelitate--;
        return *this;
    }

    // Operator -- postfix (client--)
    Client operator--(int)
    {
        Client temp = *this;
        if (puncteFidelitate > 0)
            puncteFidelitate--;
        return temp;
    }

    // Operator + (adaugare puncte de fidelitate)
    Client operator+(int valoare) const
    {
        Client result = *this;
        result.puncteFidelitate += valoare;
        return result;
    }

    // Operator - (scadere puncte de fidelitate)
    Client operator-(int valoare) const
    {
        Client result = *this;
        result.puncteFidelitate = max(0, result.puncteFidelitate - valoare);
        return result;
    }


    bool operator==(const Client& other) const
    {
        return (strcmp(nume, other.nume) == 0) && (strcmp(email, other.email) == 0);
    }


    bool operator!=(const Client& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Client& other) const
    {

        return puncteFidelitate < other.puncteFidelitate;
    }

    void descrieEntitate() const override
    {
        cout << "[Entitate: Client] ID: " << getClientID()
             << ", Nume: " << getNume()
             << ", Email: " << getEmail() << endl;
    }
};


// Initializare membri statici
int Client::generatorID = 1000;
int Client::numarClienti = 0;
Client* Client::listaClienti = new Client[100];






class PachetTuristic
{
private:
    const int pachetID;
    char* numePachet;
    char* destinatie;
    float pret;
    char* perioada;
    char tipTransport;
    bool* disponibilitate; /// Array de disponibilitate pentru fiecare luna a anului (true - disponibil, false - indisponibil)
    int nrZile;

    static int generatorID;
    static int numarPachete;
    static PachetTuristic* listaPachete;

public:
    /// Constructorul fara parametri
    PachetTuristic() : pachetID(generatorID++), pret(0), nrZile(0), tipTransport('N')
    {
        numePachet = new char[strlen("Necunoscut") + 1];
        strcpy(numePachet, "Necunoscut");

        destinatie = new char[strlen("Nedefinit") + 1];
        strcpy(destinatie, "Nedefinit");

        perioada = new char[strlen("Nedefinit") + 1];
        strcpy(perioada, "Nedefinit");

        disponibilitate = new bool[12];
        for (int i = 0; i < 12; i++)
            disponibilitate[i] = false;
    }

    /// Constructorul cu toti parametrii
    PachetTuristic(const char* numePachet, const char* destinatie, float pret, const char* perioada,
                   char tipTransport, bool* disponibilitate, int nrZile) : pachetID(generatorID++)
    {
        this->numePachet = new char[strlen(numePachet) + 1];
        strcpy(this->numePachet, numePachet);

        this->destinatie = new char[strlen(destinatie) + 1];
        strcpy(this->destinatie, destinatie);

        this->pret = pret;

        this->perioada = new char[strlen(perioada) + 1];
        strcpy(this->perioada, perioada);

        this->tipTransport = tipTransport;

        this->disponibilitate = new bool[12];
        for (int i = 0; i < 12; i++)
            this->disponibilitate[i] = disponibilitate[i];

        this->nrZile = nrZile;
    }

    /// Constructor cu o parte din parametri (1)
    PachetTuristic(const char* numePachet, const char* destinatie, float pret) : pachetID(generatorID++), tipTransport('N'), nrZile(7)
    {
        this->numePachet = new char[strlen(numePachet) + 1];
        strcpy(this->numePachet, numePachet);

        this->destinatie = new char[strlen(destinatie) + 1];
        strcpy(this->destinatie, destinatie);

        this->pret = pret;

        this->perioada = new char[strlen("Nedefinit") + 1];
        strcpy(this->perioada, "Nedefinit");

        this->disponibilitate = new bool[12];
        for (int i = 0; i < 12; i++)
            this->disponibilitate[i] = false;
    }

    /// Constructor cu o parte din parametri (2)
    PachetTuristic(const char* destinatie, float pret, int nrZile, char tipTransport) : pachetID(generatorID++)
    {
        this->numePachet = new char[strlen("Pachet Standard") + 1];
        strcpy(this->numePachet, "Pachet Standard");

        this->destinatie = new char[strlen(destinatie) + 1];
        strcpy(this->destinatie, destinatie);

        this->pret = pret;

        this->perioada = new char[strlen("Nedefinit") + 1];
        strcpy(this->perioada, "Nedefinit");

        this->tipTransport = tipTransport;

        this->disponibilitate = new bool[12];
        for (int i = 0; i < 12; i++)
            this->disponibilitate[i] = false;

        this->nrZile = nrZile;
    }

    /// Constructorul de copiere
    PachetTuristic(const PachetTuristic& p) : pachetID(p.pachetID)
    {
        this->numePachet = nullptr;
        this->destinatie = nullptr;
        this->perioada = nullptr;
        this->disponibilitate = nullptr;

        this->numePachet = new char[strlen(p.numePachet) + 1];
        strcpy(this->numePachet, p.numePachet);

        this->destinatie = new char[strlen(p.destinatie) + 1];
        strcpy(this->destinatie, p.destinatie);

        this->pret = p.pret;

        this->perioada = new char[strlen(p.perioada) + 1];
        strcpy(this->perioada, p.perioada);

        this->tipTransport = p.tipTransport;

        this->disponibilitate = new bool[12];
        for (int i = 0; i < 12; i++)
            this->disponibilitate[i] = p.disponibilitate[i];

        this->nrZile = p.nrZile;
    }

    /// Destructorul
    ~PachetTuristic()
    {
        if (this->numePachet != nullptr)
            delete[] this->numePachet;

        if (this->destinatie != nullptr)
            delete[] this->destinatie;

        if (this->perioada != nullptr)
            delete[] this->perioada;

        if (this->disponibilitate != nullptr)
            delete[] this->disponibilitate;
    }

    /// Operatorul de atribuire
    PachetTuristic& operator=(const PachetTuristic& p)
    {
        if (this == &p)
            return *this;

        if (this->numePachet != nullptr)
            delete[] this->numePachet;

        if (this->destinatie != nullptr)
            delete[] this->destinatie;

        if (this->perioada != nullptr)
            delete[] this->perioada;

        if (this->disponibilitate != nullptr)
            delete[] this->disponibilitate;

        this->numePachet = new char[strlen(p.numePachet) + 1];
        strcpy(this->numePachet, p.numePachet);

        this->destinatie = new char[strlen(p.destinatie) + 1];
        strcpy(this->destinatie, p.destinatie);

        this->pret = p.pret;

        this->perioada = new char[strlen(p.perioada) + 1];
        strcpy(this->perioada, p.perioada);

        this->tipTransport = p.tipTransport;

        this->disponibilitate = new bool[12];
        for (int i = 0; i < 12; i++)
            this->disponibilitate[i] = p.disponibilitate[i];

        this->nrZile = p.nrZile;

        return *this;
    }

    /// Operatorul >> (stream input)
    friend istream& operator>>(istream& in, PachetTuristic& p)
    {
        char buffer[100];

        cout << "Introdu numele pachetului: ";
        if (in.peek() == '\n') /// Se ignora caracterul newline ramas din citirea anterioara
            /// daca urmatorul caracter din stream este un newline
            in.ignore();
        in.getline(buffer, 100);

        if (p.numePachet != nullptr)
            delete[] p.numePachet;
        p.numePachet = new char[strlen(buffer) + 1];
        strcpy(p.numePachet, buffer);

        cout << "Introdu destinatia pachetului: ";
        in.getline(buffer, 100);

        if (p.destinatie != nullptr)
            delete[] p.destinatie;
        p.destinatie = new char[strlen(buffer) + 1];
        strcpy(p.destinatie, buffer);

        cout << "Introdu pretul pachetului: ";
        in >> p.pret;
        if (in.peek() == '\n')
            in.ignore();

        cout << "Introdu perioada recomandata a pachetului (primavara / vara / toamna / iarna): ";
        in.getline(buffer, 100);

        if (p.perioada != nullptr)
            delete[] p.perioada;
        p.perioada = new char[strlen(buffer) + 1];
        strcpy(p.perioada, buffer);

        cout << "Introdu tipul de transport (A - avion, T - tren, C - autocar): ";
        in >> p.tipTransport;

        cout << "Introdu numarul de zile: ";
        in >> p.nrZile;

        cout << "Introdu disponibilitatea pentru fiecare luna (1 - disponibil, 0 - indisponibil):" << endl;
        for (int i = 0; i < 12; i++)
        {
            cout << "Luna " << i + 1 << ": ";
            int disp;
            in >> disp;
            p.disponibilitate[i] = (disp == 1);
        }

        return in;
    }

    /// Operatorul << (stream output)
    friend ostream& operator<<(ostream& out, const PachetTuristic& p)
    {
        out << "Pachet ID: " << p.pachetID << endl;
        out << "Nume pachet: " << p.numePachet << endl;
        out << "Destinatie: " << p.destinatie << endl;
        out << "Pret: " << p.pret << " EUR" << endl;
        out << "Perioada recomandata: " << p.perioada << endl;
        out << "Tip transport: ";
        switch (p.tipTransport)
        {
        case 'A':
            out << "Avion";
            break;
        case 'T':
            out << "Tren";
            break;
        case 'C':
            out << "Autocar";
            break;
        default:
            out << "Nedefinit";
        }
        out << endl;
        out << "Numar zile: " << p.nrZile << endl;
        out << "Disponibilitate pe luni:" << endl;
        for (int i = 0; i < 12; i++)
        {
            out << "Luna " << i + 1 << ": " << (p.disponibilitate[i] ? "Disponibil" : "Indisponibil") << endl;
        }
        return out;
    }

    /// Setters & Getters

    // Getter pentru numePachet
    const char* getNumePachet() const
    {
        return numePachet;
    }

    // Setter pentru numePachet
    void setNumePachet(const char* numePachet)
    {
        if (this->numePachet != nullptr)
            delete[] this->numePachet;

        this->numePachet = new char[strlen(numePachet) + 1];
        strcpy(this->numePachet, numePachet);
    }

    // Getter pentru destinatie
    const char* getDestinatie() const
    {
        return destinatie;
    }

    // Setter pentru destinatie
    void setDestinatie(const char* destinatie)
    {
        if (this->destinatie != nullptr)
            delete[] this->destinatie;

        this->destinatie = new char[strlen(destinatie) + 1];
        strcpy(this->destinatie, destinatie);
    }

    // Getter pentru pret
    float getPret() const
    {
        return pret;
    }

    // Setter pentru pret
    void setPret(float pret)
    {
        this->pret = pret;
    }

    // Getter pentru perioada
    const char* getPerioada() const
    {
        return perioada;
    }

    // Setter pentru perioada
    void setPerioada(const char* perioada)
    {
        if (this->perioada != nullptr)
            delete[] this->perioada;

        this->perioada = new char[strlen(perioada) + 1];
        strcpy(this->perioada, perioada);
    }

    // Getter pentru tipTransport
    char getTipTransport() const
    {
        return tipTransport;
    }

    // Setter pentru tipTransport
    void setTipTransport(char tipTransport)
    {
        this->tipTransport = tipTransport;
    }

    // Getter pentru disponibilitate
    bool* getDisponibilitate() const
    {
        return disponibilitate;
    }

    // Setter pentru disponibilitate
    void setDisponibilitate(bool* disponibilitate)
    {
        if (this->disponibilitate != nullptr)
            delete[] this->disponibilitate;

        this->disponibilitate = new bool[12];
        for (int i = 0; i < 12; i++)
            this->disponibilitate[i] = disponibilitate[i];
    }

    // Getter pentru nrZile
    int getNrZile() const
    {
        return nrZile;
    }

    // Setter pentru nrZile
    void setNrZile(int nrZile)
    {
        this->nrZile = nrZile;
    }

    // Getter pentru pachetID
    int getPachetID() const
    {
        return this->pachetID;
    }

    /// Metode statice

    static PachetTuristic* getPachetDupaID(int pachetID)
    {
        for (int i = 0; i < numarPachete; i++)
            if (listaPachete[i].pachetID == pachetID)
                return &listaPachete[i];
        return nullptr;
    }

    static void adaugaPachetInLista(const PachetTuristic& p)
    {
        listaPachete[numarPachete++] = p;
    }

    static void afiseazaToatePachetele()
    {
        for (int i = 0; i < numarPachete; i++)
            cout << listaPachete[i] << endl;
    }

    static void afiseazaPachetDupaID(int pachetID)
    {
        for (int i = 0; i < numarPachete; i++)
            if (listaPachete[i].pachetID == pachetID)
            {
                cout << listaPachete[i] << endl;
                return;
            }
        cout << "Nu am gasit niciun pachet cu ID-ul " << pachetID << endl;
    }

    static void stergePachetDupaID(int pachetID)
    {
        if (numarPachete == 0)
        {
            cout << "Nu exista pachete in lista" << endl;
            return;
        }

        bool startDelete = false;
        if (pachetID == listaPachete[numarPachete - 1].pachetID)
        {
            numarPachete--;
            return;
        }
        for (int i = 1; i < numarPachete; i++)
        {
            if (pachetID == listaPachete[i - 1].pachetID)
                startDelete = true;

            if (startDelete)
                listaPachete[i - 1] = listaPachete[i];
        }

        if (startDelete)
            numarPachete--;
        else
            cout << "Nu am gasit pachetul cu ID-ul " << pachetID << endl;
    }

    static void stergeListaPachete()
    {
        numarPachete = 0;
        if (listaPachete != nullptr)
            delete[] listaPachete;
    }


    /// Metoda pentru calcularea discountului
    float calculeazaDiscount() const
    {
        float discount = 0;

        // Discount bazat pe durata
        if (nrZile > 14)
            discount += 0.15; // 15% pentru pachetele lungi
        else if (nrZile > 7)
            discount += 0.1; // 10% pentru pachetele medii

        // Discount bazat pe transport
        if (tipTransport == 'C')
            discount += 0.05; // 5% pentru autocar

        // Calcularea pretului final cu discount
        return pret * (1 - discount);
    }

    /// Metoda pentru modificarea perioadei
    void modificaPerioada(const char* nouaPerioada)
    {
        if (this->perioada != nullptr)
            delete[] this->perioada;

        this->perioada = new char[strlen(nouaPerioada) + 1];
        strcpy(this->perioada, nouaPerioada);

        cout << "Perioada a fost modificata cu succes!" << endl;
    }

    /// SUPRAINCARCAREA OPERATORILOR

    // Operatorul []
    const char* operator[](int index) const
    {
        switch (index)
        {
        case 0:
            return numePachet;
        case 1:
            return destinatie;
        case 2:
            return perioada;
        default:
            return "Index invalid";
        }
    }

    // Operator ++ prefix (++pachet)
    PachetTuristic& operator++()
    {
        nrZile++;
        return *this;
    }

    // Operator ++ postfix (pachet++)
    PachetTuristic operator++(int)
    {
        PachetTuristic temp = *this;
        nrZile++;
        return temp;
    }

    // Operator -- prefix (--pachet) - scade numarul de zile
    PachetTuristic& operator--()
    {
        if (nrZile > 1)
            nrZile--;
        return *this;
    }

    // Operator -- postfix (pachet--) - scade numarul de zile
    PachetTuristic operator--(int)
    {
        PachetTuristic temp = *this;
        if (nrZile > 1)
            nrZile--;
        return temp;
    }

    // Operator + (adaugare la pret)
    PachetTuristic operator+(float valoare) const
    {
        PachetTuristic result = *this;
        result.pret += valoare;
        return result;
    }

    // Operator - (scadere din pret)
    PachetTuristic operator-(float valoare) const
    {
        PachetTuristic result = *this;
        result.pret = max(0.0f, result.pret - valoare);
        return result;
    }

    // Operator pentru comutativitate
    friend PachetTuristic operator+(float valoare, const PachetTuristic& p)
    {
        return p + valoare;
    }

    // Operator pentru comutativitate
    friend PachetTuristic operator-(float valoare, const PachetTuristic& p)
    {
        PachetTuristic result = p;
        result.pret = max(0.0f, valoare - result.pret);
        return result;
    }

    // Operator * (inmultire pret cu un factor)
    PachetTuristic operator*(float factor) const
    {
        PachetTuristic result = *this;
        result.pret *= factor;
        return result;
    }

    // Operator pentru comutativitate
    friend PachetTuristic operator*(float factor, const PachetTuristic& p)
    {
        return p * factor;
    }

    // Operator == (verifica daca doua pachete au aceeasi destinatie)
    bool operator==(const PachetTuristic& other) const
    {
        return (strcmp(destinatie, other.destinatie) == 0);
    }

    // Operator != (verifica daca doua pachete au destinatii diferite)
    bool operator!=(const PachetTuristic& other) const
    {
        return !(*this == other);
    }

    // Operator < (verifica daca un pachet are pretul mai mic decat altul)
    bool operator<(const PachetTuristic& other) const
    {
        return pret < other.pret;
    }

};

int PachetTuristic::generatorID = 5000;
int PachetTuristic::numarPachete = 0;
PachetTuristic* PachetTuristic::listaPachete = new PachetTuristic[100];



class Hotel : public virtual Entitate
{
private:
    const int hotelID;
    char* numeHotel;
    int numarStele;
    float pretNoapte;
    char* adresa;

    static int generatorID;
    static int numarHoteluri;
    static Hotel* listaHoteluri;

public:
    /// Constructorul fara parametri
    Hotel() : hotelID(generatorID++), numarStele(0), pretNoapte(0)
    {
        numeHotel = new char[strlen("Necunoscut") + 1];
        strcpy(numeHotel, "Necunoscut");

        adresa = new char[strlen("Nedefinit") + 1];
        strcpy(adresa, "Nedefinit");
    }

    /// Constructorul cu toti parametrii
    Hotel(const char* numeHotel, int numarStele, float pretNoapte, const char* adresa) : hotelID(generatorID++)
    {
        this->numeHotel = new char[strlen(numeHotel) + 1];
        strcpy(this->numeHotel, numeHotel);

        this->numarStele = numarStele;
        this->pretNoapte = pretNoapte;

        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
    }

    /// Constructor cu doi parametri
    Hotel(const char* numeHotel, float pretNoapte) : hotelID(generatorID++), numarStele(3)
    {
        this->numeHotel = new char[strlen(numeHotel) + 1];
        strcpy(this->numeHotel, numeHotel);

        this->pretNoapte = pretNoapte;

        this->adresa = new char[strlen("Nedefinit") + 1];
        strcpy(this->adresa, "Nedefinit");
    }

    /// Constructor cu trei parametri
    Hotel(const char* numeHotel, int numarStele, const char* adresa) : hotelID(generatorID++), pretNoapte(100)
    {
        this->numeHotel = new char[strlen(numeHotel) + 1];
        strcpy(this->numeHotel, numeHotel);

        this->numarStele = numarStele;

        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
    }

    /// Constructorul de copiere
    Hotel(const Hotel& h) : hotelID(h.hotelID)
    {
        this->numeHotel = nullptr;
        this->adresa = nullptr;

        this->numeHotel = new char[strlen(h.numeHotel) + 1];
        strcpy(this->numeHotel, h.numeHotel);

        this->numarStele = h.numarStele;
        this->pretNoapte = h.pretNoapte;

        this->adresa = new char[strlen(h.adresa) + 1];
        strcpy(this->adresa, h.adresa);
    }

    /// Destructorul
    ~Hotel()
    {
        if (this->numeHotel != nullptr)
            delete[] this->numeHotel;

        if (this->adresa != nullptr)
            delete[] this->adresa;
    }

    /// Operatorul de atribuire
    Hotel& operator=(const Hotel& h)
    {
        if (this == &h)
            return *this;

        if (this->numeHotel != nullptr)
            delete[] this->numeHotel;

        if (this->adresa != nullptr)
            delete[] this->adresa;

        this->numeHotel = new char[strlen(h.numeHotel) + 1];
        strcpy(this->numeHotel, h.numeHotel);

        this->numarStele = h.numarStele;
        this->pretNoapte = h.pretNoapte;

        this->adresa = new char[strlen(h.adresa) + 1];
        strcpy(this->adresa, h.adresa);

        return *this;
    }

    /// Operatorul >> (stream input)
    friend istream& operator>>(istream& in, Hotel& h)
    {
        char buffer[100];

        cout << "Introdu numele hotelului: ";
        if (in.peek() == '\n') /// Se ignora caracterul newline ramas din citirea anterioara
            /// daca urmatorul caracter din stream este un newline
            in.ignore();
        in.getline(buffer, 100);

        if (h.numeHotel != nullptr)
            delete[] h.numeHotel;
        h.numeHotel = new char[strlen(buffer) + 1];
        strcpy(h.numeHotel, buffer);

        cout << "Introdu numarul de stele (1-5): ";
        in >> h.numarStele;

        if (h.numarStele < 1 || h.numarStele > 5)
            h.numarStele = 3; // Valoare implicita daca input-ul nu este valid

        cout << "Introdu pretul pe noapte: ";
        in >> h.pretNoapte;
        if (in.peek() == '\n')
            in.ignore();

        cout << "Introdu adresa hotelului: ";
        in.getline(buffer, 100);

        if (h.adresa != nullptr)
            delete[] h.adresa;
        h.adresa = new char[strlen(buffer) + 1];
        strcpy(h.adresa, buffer);

        return in;
    }

    /// Operatorul << (stream output)
    friend ostream& operator<<(ostream& out, const Hotel& h)
    {
        out << "Hotel ID: " << h.hotelID << endl;
        out << "Nume hotel: " << h.numeHotel << endl;
        out << "Numar stele: " << h.numarStele << endl;
        out << "Pret pe noapte: " << h.pretNoapte << " EUR" << endl;
        out << "Adresa: " << h.adresa << endl;
        return out;
    }

    /// Setters & Getters

    // Getter pentru numeHotel
    const char* getNumeHotel() const
    {
        return numeHotel;
    }

    // Setter pentru numeHotel
    void setNumeHotel(const char* numeHotel)
    {
        if (this->numeHotel != nullptr)
            delete[] this->numeHotel;

        this->numeHotel = new char[strlen(numeHotel) + 1];
        strcpy(this->numeHotel, numeHotel);
    }

    // Getter pentru numarStele
    int getNumarStele() const
    {
        return numarStele;
    }

    // Setter pentru numarStele
    void setNumarStele(int numarStele)
    {
        if (numarStele >= 1 && numarStele <= 5)
            this->numarStele = numarStele;
    }

    // Getter pentru pretNoapte
    float getPretNoapte() const
    {
        return pretNoapte;
    }

    // Setter pentru pretNoapte
    void setPretNoapte(float pretNoapte)
    {
        if (pretNoapte >= 0)
            this->pretNoapte = pretNoapte;
    }

    // Getter pentru adresa
    const char* getAdresa() const
    {
        return adresa;
    }

    // Setter pentru adresa
    void setAdresa(const char* adresa)
    {
        if (this->adresa != nullptr)
            delete[] this->adresa;

        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
    }

    // Getter pentru hotelID
    int getHotelID() const
    {
        return hotelID;
    }

    /// Metode statice

    static Hotel* getHotelDupaID(int hotelID)
    {
        for (int i = 0; i < numarHoteluri; i++)
            if (listaHoteluri[i].hotelID == hotelID)
                return &listaHoteluri[i];
        return nullptr;
    }

    static void adaugaHotelInLista(const Hotel& h)
    {
        listaHoteluri[numarHoteluri++] = h;
    }

    static void afiseazaToateHotelurile()
    {
        for (int i = 0; i < numarHoteluri; i++)
            cout << listaHoteluri[i] << endl;
    }

    static void afiseazaHotelDupaID(int hotelID)
    {
        for (int i = 0; i < numarHoteluri; i++)
            if (listaHoteluri[i].hotelID == hotelID)
            {
                cout << listaHoteluri[i] << endl;
                return;
            }
        cout << "Nu am gasit niciun hotel cu ID-ul " << hotelID << endl;
    }

    static void stergeHotelDupaID(int hotelID)
    {
        if (numarHoteluri == 0)
        {
            cout << "Nu exista hoteluri in lista" << endl;
            return;
        }

        bool startDelete = false;
        if (hotelID == listaHoteluri[numarHoteluri - 1].hotelID)
        {
            numarHoteluri--;
            return;
        }
        for (int i = 1; i < numarHoteluri; i++)
        {
            if (hotelID == listaHoteluri[i - 1].hotelID)
                startDelete = true;

            if (startDelete)
                listaHoteluri[i - 1] = listaHoteluri[i];
        }

        if (startDelete)
            numarHoteluri--;
        else
            cout << "Nu am gasit hotelul cu ID-ul " << hotelID << endl;
    }

    static void stergeListaHoteluri()
    {
        numarHoteluri = 0;
        if (listaHoteluri != nullptr)
            delete[] listaHoteluri;
    }

    /// Metode specifice

    // Metoda pentru calcularea costului total
    float calculeazaCostTotal(int nrNopti) const
    {
        float costTotal = pretNoapte * nrNopti;

        // Aplicam reduceri bazate pe durata sederii
        if (nrNopti > 7)
            costTotal *= 0.9; // 10% reducere pentru sederi mai lungi de 7 nopti
        else if (nrNopti > 3)
            costTotal *= 0.95; // 5% reducere pentru sederi intre 4 si 7 nopti

        return costTotal;
    }

    // Metoda pentru verificarea disponibilitatii
    bool verificaDisponibilitate(const char* dataCheckIn, const char* dataCheckOut) const
    {
        // Simulam o disponibilitate aleatorie
        int random = rand() % 100;
        return random < 70; // 70% sansa sa fie disponibil
    }

    /// SUPRAINCARCAREA OPERATORILOR

    // Operatorul de indexare []
    const char* operator[](int index) const
    {
        switch (index)
        {
        case 0:
            return numeHotel;
        case 1:
            return adresa;
        default:
            return "Index invalid";
        }
    }

    // Operator ++ prefix (++hotel) - creste numarul de stele
    Hotel& operator++()
    {
        if (numarStele < 5)
            numarStele++;
        return *this;
    }

    // Operator ++ postfix (hotel++) - creste numarul de stele
    Hotel operator++(int)
    {
        Hotel temp = *this;
        if (numarStele < 5)
            numarStele++;
        return temp;
    }

    // Operator -- prefix (--hotel) - scade numarul de stele
    Hotel& operator--()
    {
        if (numarStele > 1)
            numarStele--;
        return *this;
    }

    // Operator -- postfix (hotel--) - scade numarul de stele
    Hotel operator--(int)
    {
        Hotel temp = *this;
        if (numarStele > 1)
            numarStele--;
        return temp;
    }

    // Operator + (adaugare la pret)
    Hotel operator+(float valoare) const
    {
        Hotel result = *this;
        result.pretNoapte += valoare;
        return result;
    }

    // Operator - (scadere din pret)
    Hotel operator-(float valoare) const
    {
        Hotel result = *this;
        result.pretNoapte = max(0.0f, result.pretNoapte - valoare);
        return result;
    }

    // Operator pentru comutativitate
    friend Hotel operator+(float valoare, const Hotel& h)
    {
        return h + valoare;
    }

    // Operator pentru comutativitate
    friend Hotel operator-(float valoare, const Hotel& h)
    {
        Hotel result = h;
        result.pretNoapte = max(0.0f, valoare - result.pretNoapte);
        return result;
    }

    // Operator * (inmultire pret cu un factor)
    Hotel operator*(float factor) const
    {
        Hotel result = *this;
        result.pretNoapte *= factor;
        return result;
    }

    // Operator pentru comutativitate
    friend Hotel operator*(float factor, const Hotel& h)
    {
        return h * factor;
    }

    // Operator == (verifica daca doua hoteluri au acelasi numar de stele)
    bool operator==(const Hotel& other) const
    {
        return (numarStele == other.numarStele);
    }

    // Operator != (verifica daca doua hoteluri au numar diferit de stele)
    bool operator!=(const Hotel& other) const
    {
        return !(*this == other);
    }

    // Operator < (verifica daca un hotel are pretul mai mic decat altul)
    bool operator<(const Hotel& other) const
    {
        return pretNoapte < other.pretNoapte;
    }

    void descrieEntitate() const override
    {
        cout << "[Entitate: Hotel] " << numeHotel
             << " (" << numarStele << " stele), pret: " << pret
             << ", adresa: " << adresa << ", ID: " << getEntitateID() << endl;
    }

};


int Hotel::generatorID = 4000;
int Hotel::numarHoteluri = 0;
Hotel* Hotel::listaHoteluri = new Hotel[100];


class Rezervare
{
private:
    const int rezervareID;
    int clientID;
    int pachetID;
    char* dataRezervare;
    char* metodaPlata;
    float sumaPlatita;
    float sumaRamasa;
    bool* statusPlata; // Array pentru a marca platile partiale (true - platit, false - neplatit)
    char statusRezervare; // 'C' - confirmata, 'A' - anulata, 'P' - in asteptare

    static int generatorID;
    static int numarRezervari;
    static Rezervare* listaRezervari;

public:
    /// Constructorul fara parametri
    Rezervare() : rezervareID(generatorID++), clientID(0), pachetID(0), sumaPlatita(0), sumaRamasa(0), statusRezervare('P')
    {
        dataRezervare = new char[strlen("01/01/2025") + 1];
        strcpy(dataRezervare, "01/01/2025");

        metodaPlata = new char[strlen("Nedefinit") + 1];
        strcpy(metodaPlata, "Nedefinit");

        statusPlata = new bool[3]; // Presupunem 3 transe de plata
        for (int i = 0; i < 3; i++)
            statusPlata[i] = false;
    }

    /// Constructor cu toti parametrii
    Rezervare(int clientID, int pachetID, const char* dataRezervare, const char* metodaPlata,
              float sumaPlatita, float sumaRamasa, bool* statusPlata, char statusRezervare)
              : rezervareID(generatorID++)
    {
        this->clientID = clientID;
        this->pachetID = pachetID;

        this->dataRezervare = new char[strlen(dataRezervare) + 1];
        strcpy(this->dataRezervare, dataRezervare);

        this->metodaPlata = new char[strlen(metodaPlata) + 1];
        strcpy(this->metodaPlata, metodaPlata);

        this->sumaPlatita = sumaPlatita;
        this->sumaRamasa = sumaRamasa;

        this->statusPlata = new bool[3];
        for (int i = 0; i < 3; i++)
            this->statusPlata[i] = statusPlata[i];

        this->statusRezervare = statusRezervare;
    }

    /// Constructor cu parametri (1)
    Rezervare(int clientID, int pachetID) : rezervareID(generatorID++), sumaPlatita(0), statusRezervare('P')
    {
        this->clientID = clientID;
        this->pachetID = pachetID;

        // Obtinem referinta la pachetul turistic pentru a calcula suma
        PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetID);
        this->sumaRamasa = (pachet != nullptr) ? pachet->getPret() : 0;


        this->dataRezervare = new char[strlen("24/03/2025") + 1];
        strcpy(this->dataRezervare, "24/03/2025");

        // Metoda de plata implicita
        this->metodaPlata = new char[strlen("Card") + 1];
        strcpy(this->metodaPlata, "Card");

        // Status plata
        this->statusPlata = new bool[3];
        for (int i = 0; i < 3; i++)
            this->statusPlata[i] = false;
    }

    /// Constructor cu parametri (2) - pentru rezervare cu plata integrala
    Rezervare(int clientID, int pachetID, const char* dataRezervare, const char* metodaPlata)
              : rezervareID(generatorID++), statusRezervare('C')
    {
        this->clientID = clientID;
        this->pachetID = pachetID;

        this->dataRezervare = new char[strlen(dataRezervare) + 1];
        strcpy(this->dataRezervare, dataRezervare);

        this->metodaPlata = new char[strlen(metodaPlata) + 1];
        strcpy(this->metodaPlata, metodaPlata);

        // Obtinem referinta la pachetul turistic pentru a calcula suma
        PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetID);

        if (pachet != nullptr)
        {
            this->sumaPlatita = pachet->getPret();
            this->sumaRamasa = 0;

            // Actualizam numarul de rezervari pentru client
            Client* client = Client::getClientDupaID(clientID);
            if (client != nullptr)
                ++(*client);
        }
        else
        {
            this->sumaPlatita = 0;
            this->sumaRamasa = 0;
        }

        // Toate transele sunt platite
        this->statusPlata = new bool[3];
        for (int i = 0; i < 3; i++)
            this->statusPlata[i] = true;
    }

    /// Constructorul de copiere
    Rezervare(const Rezervare& r) : rezervareID(r.rezervareID)
    {
        this->clientID = r.clientID;
        this->pachetID = r.pachetID;

        this->dataRezervare = nullptr;
        this->metodaPlata = nullptr;
        this->statusPlata = nullptr;

        this->dataRezervare = new char[strlen(r.dataRezervare) + 1];
        strcpy(this->dataRezervare, r.dataRezervare);

        this->metodaPlata = new char[strlen(r.metodaPlata) + 1];
        strcpy(this->metodaPlata, r.metodaPlata);

        this->sumaPlatita = r.sumaPlatita;
        this->sumaRamasa = r.sumaRamasa;

        this->statusPlata = new bool[3];
        for (int i = 0; i < 3; i++)
            this->statusPlata[i] = r.statusPlata[i];

        this->statusRezervare = r.statusRezervare;
    }

    /// Destructorul
    ~Rezervare()
    {
        if (this->dataRezervare != nullptr)
            delete[] this->dataRezervare;

        if (this->metodaPlata != nullptr)
            delete[] this->metodaPlata;

        if (this->statusPlata != nullptr)
            delete[] this->statusPlata;
    }

    /// Operatorul de atribuire
    Rezervare& operator=(const Rezervare& r)
    {
        if (this == &r)
            return *this;

        if (this->dataRezervare != nullptr)
            delete[] this->dataRezervare;

        if (this->metodaPlata != nullptr)
            delete[] this->metodaPlata;

        if (this->statusPlata != nullptr)
            delete[] this->statusPlata;

        this->clientID = r.clientID;
        this->pachetID = r.pachetID;

        this->dataRezervare = new char[strlen(r.dataRezervare) + 1];
        strcpy(this->dataRezervare, r.dataRezervare);

        this->metodaPlata = new char[strlen(r.metodaPlata) + 1];
        strcpy(this->metodaPlata, r.metodaPlata);

        this->sumaPlatita = r.sumaPlatita;
        this->sumaRamasa = r.sumaRamasa;

        this->statusPlata = new bool[3];
        for (int i = 0; i < 3; i++)
            this->statusPlata[i] = r.statusPlata[i];

        this->statusRezervare = r.statusRezervare;

        return *this;
    }

    /// Operatorul >> (stream input)
    friend istream& operator>>(istream& in, Rezervare& r)
    {
        char buffer[100];
        int clientIDInput, pachetIDInput;

        cout << "Introdu ID-ul clientului: ";
        in >> clientIDInput;

        Client* client = Client::getClientDupaID(clientIDInput);
        if (client == nullptr)
        {
            cout << "Client inexistent! Rezervarea nu poate fi creata." << endl;
            return in;
        }
        r.clientID = clientIDInput;

        cout << "Introdu ID-ul pachetului: ";
        in >> pachetIDInput;

        PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetIDInput);
        if (pachet == nullptr)
        {
            cout << "Pachet inexistent! Rezervarea nu poate fi creata." << endl;
            return in;
        }
        r.pachetID = pachetIDInput;

        cout << "Introdu data rezervarii (ZZ/LL/AAAA): ";
        if (in.peek() == '\n') /// Se ignora caracterul newline ramas din citirea anterioara
            /// daca urmatorul caracter din stream este un newline
            in.ignore();
        in.getline(buffer, 100);

        if (r.dataRezervare != nullptr)
            delete[] r.dataRezervare;
        r.dataRezervare = new char[strlen(buffer) + 1];
        strcpy(r.dataRezervare, buffer);

        cout << "Introdu metoda de plata (Card/Transfer/Numerar): ";
        in.getline(buffer, 100);

        if (r.metodaPlata != nullptr)
            delete[] r.metodaPlata;
        r.metodaPlata = new char[strlen(buffer) + 1];
        strcpy(r.metodaPlata, buffer);

        cout << "Introdu suma platita: ";
        in >> r.sumaPlatita;

        // Calculam suma ramasa
        r.sumaRamasa = pachet->getPret() - r.sumaPlatita;

        cout << "Introdu statusul pentru fiecare transa de plata (1 - platit, 0 - neplatit):" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "Transa " << i + 1 << ": ";
            int status;
            in >> status;
            r.statusPlata[i] = (status == 1);
        }

        cout << "Introdu statusul rezervarii (C - confirmata, A - anulata, P - in asteptare): ";
        in >> r.statusRezervare;

        return in;
    }

    /// Operatorul << (stream output)
    friend ostream& operator<<(ostream& out, const Rezervare& r)
    {
        out << "Rezervare ID: " << r.rezervareID << endl;

        Client* client = Client::getClientDupaID(r.clientID);
        out << "Client: ";
        if (client != nullptr)
            out << client->getNume() << " (ID: " << r.clientID << ")" << endl;
        else
            out << "Necunoscut (ID: " << r.clientID << ")" << endl;

        PachetTuristic* pachet = PachetTuristic::getPachetDupaID(r.pachetID);
        out << "Pachet: ";
        if (pachet != nullptr)
            out << pachet->getNumePachet() << " - " << pachet->getDestinatie() << " (ID: " << r.pachetID << ")" << endl;
        else
            out << "Necunoscut (ID: " << r.pachetID << ")" << endl;

        out << "Data rezervarii: " << r.dataRezervare << endl;
        out << "Metoda de plata: " << r.metodaPlata << endl;
        out << "Suma platita: " << r.sumaPlatita << " EUR" << endl;
        out << "Suma ramasa: " << r.sumaRamasa << " EUR" << endl;

        out << "Status plati: " << endl;
        for (int i = 0; i < 3; i++)
            out << "Transa " << i + 1 << ": " << (r.statusPlata[i] ? "Platit" : "Neplatit") << endl;

        out << "Status rezervare: ";
        switch (r.statusRezervare)
        {
        case 'C':
            out << "Confirmata";
            break;
        case 'A':
            out << "Anulata";
            break;
        case 'P':
            out << "In asteptare";
            break;
        default:
            out << "Nedefinit";
        }
        out << endl;

        return out;
    }

    /// Setters & Getters

    // Getter pentru rezervareID
    int getRezervareID() const
    {
        return rezervareID;
    }

    // Getter pentru clientID
    int getClientID() const
    {
        return clientID;
    }

    // Setter pentru clientID
    void setClientID(int clientID)
    {
        this->clientID = clientID;
    }

    // Getter pentru pachetID
    int getPachetID() const
    {
        return pachetID;
    }

    // Setter pentru pachetID
    void setPachetID(int pachetID)
    {
        this->pachetID = pachetID;
    }

    // Getter pentru dataRezervare
    const char* getDataRezervare() const
    {
        return dataRezervare;
    }

    // Setter pentru dataRezervare
    void setDataRezervare(const char* dataRezervare)
    {
        if (this->dataRezervare != nullptr)
            delete[] this->dataRezervare;

        this->dataRezervare = new char[strlen(dataRezervare) + 1];
        strcpy(this->dataRezervare, dataRezervare);
    }

    // Getter pentru metodaPlata
    const char* getMetodaPlata() const
    {
        return metodaPlata;
    }

    // Setter pentru metodaPlata
    void setMetodaPlata(const char* metodaPlata)
    {
        if (this->metodaPlata != nullptr)
            delete[] this->metodaPlata;

        this->metodaPlata = new char[strlen(metodaPlata) + 1];
        strcpy(this->metodaPlata, metodaPlata);
    }

    // Getter pentru sumaPlatita
    float getSumaPlatita() const
    {
        return sumaPlatita;
    }

    // Setter pentru sumaPlatita
    void setSumaPlatita(float sumaPlatita)
    {
        this->sumaPlatita = sumaPlatita;
    }

    // Getter pentru sumaRamasa
    float getSumaRamasa() const
    {
        return sumaRamasa;
    }

    // Setter pentru sumaRamasa
    void setSumaRamasa(float sumaRamasa)
    {
        this->sumaRamasa = sumaRamasa;
    }

    // Getter pentru statusPlata
    bool* getStatusPlata() const
    {
        return statusPlata;
    }

    // Setter pentru statusPlata
    void setStatusPlata(bool* statusPlata)
    {
        if (this->statusPlata != nullptr)
            delete[] this->statusPlata;

        this->statusPlata = new bool[3];
        for (int i = 0; i < 3; i++)
            this->statusPlata[i] = statusPlata[i];
    }

    // Getter pentru statusRezervare
    char getStatusRezervare() const
    {
        return statusRezervare;
    }

    // Setter pentru statusRezervare
    void setStatusRezervare(char statusRezervare)
    {
        this->statusRezervare = statusRezervare;
    }

    /// Metode statice

    static Rezervare* getRezervariClient(int clientID, int& numarRezervariGasite)
    {
        numarRezervariGasite = 0;

        if (numarRezervari == 0 || listaRezervari == nullptr)
            return nullptr;

        for (int i = 0; i < numarRezervari; i++)
            if (listaRezervari[i].clientID == clientID && listaRezervari[i].statusRezervare != 'A')
                numarRezervariGasite++;

        if (numarRezervariGasite == 0)
            return nullptr;

        Rezervare* rezultat = new Rezervare[numarRezervariGasite];
        int index = 0;

        for (int i = 0; i < numarRezervari; i++)
            if (listaRezervari[i].clientID == clientID && listaRezervari[i].statusRezervare != 'A')
                rezultat[index++] = listaRezervari[i];

        return rezultat;
    }

    static Rezervare* getRezervaredupaID(int rezervareID)
    {
        for (int i = 0; i < numarRezervari; i++)
            if (listaRezervari[i].rezervareID == rezervareID)
                return &listaRezervari[i];
        return nullptr;
    }

    static void adaugaRezervareInLista(const Rezervare& r)
    {
        listaRezervari[numarRezervari++] = r;
    }

    static void afiseazaToateRezervarile()
    {
        for (int i = 0; i < numarRezervari; i++)
            cout << listaRezervari[i] << endl;
    }

    static void afiseazaRezervaredupaID(int rezervareID)
    {
        for (int i = 0; i < numarRezervari; i++)
            if (listaRezervari[i].rezervareID == rezervareID)
            {
                cout << listaRezervari[i] << endl;
                return;
            }
        cout << "Nu am gasit nicio rezervare cu ID-ul " << rezervareID << endl;
    }

    static void stergeRezervaredupaID(int rezervareID)
    {
        if (numarRezervari == 0)
        {
            cout << "Nu exista rezervari in lista" << endl;
            return;
        }

        bool startDelete = false;
        if (rezervareID == listaRezervari[numarRezervari - 1].rezervareID)
        {
            numarRezervari--;
            return;
        }
        for (int i = 1; i < numarRezervari; i++)
        {
            if (rezervareID == listaRezervari[i - 1].rezervareID)
                startDelete = true;

            if (startDelete)
                listaRezervari[i - 1] = listaRezervari[i];
        }

        if (startDelete)
            numarRezervari--;
        else
            cout << "Nu am gasit rezervarea cu ID-ul " << rezervareID << endl;
    }

    static void stergeListaRezervari()
    {
        numarRezervari = 0;
        if (listaRezervari != nullptr)
            delete[] listaRezervari;
    }

    // Functie de anulare a rezervarii
    bool anuleazaRezervare()
    {
        if (statusRezervare == 'A')
        {
            cout << "Rezervarea este deja anulata!" << endl;
            return false;
        }

        statusRezervare = 'A';

        // Decrementam numarul de rezervari pentru client
        Client* client = Client::getClientDupaID(clientID);
        if (client != nullptr)
            --(*client);

        cout << "Rezervarea a fost anulata cu succes!" << endl;
        return true;
    }

    // Functie de plata a unei transe
    bool platesteTransa(int indexTransa, float suma)
    {
        if (indexTransa < 0 || indexTransa >= 3)
        {
            cout << "Index transa invalid!" << endl;
            return false;
        }

        if (statusPlata[indexTransa])
        {
            cout << "Transa " << indexTransa + 1 << " a fost deja platita!" << endl;
            return false;
        }

        sumaPlatita += suma;
        sumaRamasa -= suma;
        statusPlata[indexTransa] = true;

        // Verificam daca toate transele sunt platite
        bool toatePlatite = true;
        for (int i = 0; i < 3; i++)
            if (!statusPlata[i])
                toatePlatite = false;

        if (toatePlatite && sumaRamasa <= 0)
            statusRezervare = 'C';

        cout << "Transa " << indexTransa + 1 << " a fost platita cu succes!" << endl;
        return true;
    }

    /// SUPRAINCARCAREA OPERATORILOR

    // Operatorul []
    const char* operator[](int index) const
    {
        switch(index)
        {
        case 0:
            return dataRezervare;
        case 1:
            return metodaPlata;
        default:
            return "Index invalid";
        }
    }

    // Operator ++ prefix (++rezervare) - marcheaza urmatoarea transa ca platita
    Rezervare& operator++()
    {
        for (int i = 0; i < 3; i++)
        {
            if (!statusPlata[i])
            {
                statusPlata[i] = true;
                break;
            }
        }
        return *this;
    }

    // Operator ++ postfix (rezervare++)
    Rezervare operator++(int)
    {
        Rezervare temp = *this;
        ++(*this);
        return temp;
    }

    // Operator -- prefix (--rezervare) - marcheaza ultima transa platita ca neplatita
    Rezervare& operator--()
    {
        for (int i = 2; i >= 0; i--)
        {
            if (statusPlata[i])
            {
                statusPlata[i] = false;
                break;
            }
        }
        return *this;
    }

    // Operator -- postfix (rezervare--)
    Rezervare operator--(int)
    {
        Rezervare temp = *this;
        --(*this);
        return temp;
    }

    // Operator + (adauga plata)
    Rezervare operator+(float valoare) const
    {
        Rezervare result = *this;
        result.sumaPlatita += valoare;
        result.sumaRamasa = max(0.0f, result.sumaRamasa - valoare);
        return result;
    }

    // Operator - (retrage plata)
    Rezervare operator-(float valoare) const
    {
        Rezervare result = *this;
        result.sumaPlatita = max(0.0f, result.sumaPlatita - valoare);
        result.sumaRamasa += valoare;
        return result;
    }

    // Operator pentru comutativitate
    friend Rezervare operator+(float valoare, const Rezervare& r)
    {
        return r + valoare;
    }

    // Operator pentru comutativitate
    friend Rezervare operator-(float valoare, const Rezervare& r)
    {
        Rezervare result = r;
        result.sumaRamasa = valoare;
        result.sumaPlatita = 0;
        return result;
    }

    // Operator == (verifica daca doua rezervari au acelasi client si pachet)
    bool operator==(const Rezervare& other) const
    {
        return (clientID == other.clientID && pachetID == other.pachetID);
    }

    // Operator != (verifica daca doua rezervari au client sau pachet diferit)
    bool operator!=(const Rezervare& other) const
    {
        return !(*this == other);
    }

    // Operator < (compara sumele platite)
    bool operator<(const Rezervare& other) const
    {
        return sumaPlatita < other.sumaPlatita;
    }
};

int Rezervare::generatorID = 7000;
int Rezervare::numarRezervari = 0;
Rezervare* Rezervare::listaRezervari = new Rezervare[100];


class ClientCazatLaHotel : public Client, public Hotel
{
private:
    int nrNopti;

public:
    ClientCazatLaHotel()
        : Client(), Hotel(), nrNopti(1)
    {}

    ClientCazatLaHotel(const char* nume, const char* email, int puncte,
                       const char* numeHotel, int stele, float pret, const char* adresa,
                       int nrNopti)
        : Client(nume, email, puncte), Hotel(numeHotel, stele, pret, adresa), nrNopti(nrNopti)
    {}

    ClientCazatLaHotel(const Client& c, const Hotel& h, int nopti)
        : Client(c), Hotel(h), nrNopti(nopti)
    {}

    ClientCazatLaHotel(const ClientCazatLaHotel& other)
        : Client(other), Hotel(other), nrNopti(other.nrNopti)
    {}

    ~ClientCazatLaHotel() {}

    ClientCazatLaHotel& operator=(const ClientCazatLaHotel& other)
    {
        if (this != &other)
        {
            Client::operator=(other);
            Hotel::operator=(other);
            nrNopti = other.nrNopti;
        }
        return *this;
    }

    void descrieEntitate() const override
    {
        cout << "[CLIENT CAZAT LA HOTEL]" << endl;
        cout << "Client: " << getNume() << " (" << getEmail() << "), "
             << "ID: " << getClientID() << endl;
        cout << "Hotel: " << getNumeHotel() << ", " << getNumarStele()
             << " stele, " << getAdresa() << endl;
        cout << "Nr. nopti cazare: " << nrNopti << endl;
        cout << "Entitate ID unic: " << getEntitateID() << endl;
    }

    friend ostream& operator<<(ostream& out, const ClientCazatLaHotel& x)
    {
        x.descrieEntitate();
        return out;
    }

    friend istream& operator>>(istream& in, ClientCazatLaHotel& x)
    {
        char nume[100], email[100], numeHotel[100], adresa[100];
        int puncte, stele, nopti;
        float pret;

        cout << "Nume client: ";
        in.ignore();
        in.getline(nume, 100);

        cout << "Email client: ";
        in.getline(email, 100);

        cout << "Puncte fidelitate: ";
        in >> puncte;

        cout << "Nume hotel: ";
        in.ignore();
        in.getline(numeHotel, 100);

        cout << "Nr. stele: ";
        in >> stele;

        cout << "Pret pe noapte: ";
        in >> pret;

        cout << "Adresa hotel: ";
        in.ignore();
        in.getline(adresa, 100);

        cout << "Numar nopti: ";
        in >> nopti;

        x = ClientCazatLaHotel(nume, email, puncte, numeHotel, stele, pret, adresa, nopti);
        return in;
    }
};




void cleanup()
{
    Client::stergeListaClientilor();
    PachetTuristic::stergeListaPachete();
    Hotel::stergeListaHoteluri();
    Rezervare::stergeListaRezervari();
}

int main()
{

    int op;
    do
    {
        system("cls");
        cout << "[Gestiune Agentie de Turism] -- MENIU --: " << endl;
        cout << "0. Exit" << endl;
        cout << endl << "--- GESTIONARE CLIENTI (ID: 1000+) ---" << endl;
        cout << "1. Introdu un client in aplicatie" << endl;
        cout << "2. Vizualizeaza un client din aplicatie" << endl;
        cout << "3. Vizualizeaza toti clientii din aplicatie" << endl;
        cout << "4. Actualizeaza un client din aplicatie" << endl;
        cout << "5. Sterge un client din aplicatie" << endl;
        cout << "6. Creeaza o copie a unui client" << endl;
        cout << "7. Copiaza datele unui client in altul" << endl;
        cout << "8. Adauga un punct de fidelitate pentru un client" << endl;
        cout << "9. Anuleaza un punct de fidelitate pentru un client" << endl;
        cout << "10. Adauga mai multe puncte de fidelitate pentru un client" << endl;
        cout << "11. Anuleaza mai multe puncte de fidelitate pentru un client" << endl;
        cout << "12. Vizualizeaza numele / email-ul pentru un anumit client" << endl;
        cout << "13. Verifica daca doi clienti sunt identici" << endl;
        cout << "14. Compara numarul de rezervari pentru doi clienti" << endl;


        cout << endl << "--- GESTIONARE PACHETE TURISTICE (ID: 5000+) ---" << endl;
        cout << "15. Introdu un pachet turistic in aplicatie" << endl;
        cout << "16. Vizualizeaza un pachet turistic din aplicatie" << endl;
        cout << "17. Vizualizeaza toate pachetele turistice din aplicatie" << endl;
        cout << "18. Actualizeaza un pachet turistic din aplicatie" << endl;
        cout << "19. Sterge un pachet turistic din aplicatie" << endl;
        cout << "20. Creeaza o copie a unui pachet turistic" << endl;
        cout << "21. Copiaza datele unui pachet turistic in altul" << endl;
        cout << "22. Adauga o zi la durata unui pachet turistic" << endl;
        cout << "23. Scade o zi din durata unui pachet turistic" << endl;
        cout << "24. Adauga la pretul unui pachet turistic" << endl;
        cout << "25. Scade din pretul unui pachet turistic" << endl;
        cout << "26. Calculeaza discountul pentru un pachet turistic" << endl;
        cout << "27. Modifica perioada recomandata pentru un pachet turistic" << endl;
        cout << "28. Vizualizeaza numele / destinatia / perioada recomandata pentru un anumit pachet" << endl;
        cout << "29. Verifica daca doua pachete au aceeasi destinatie" << endl;
        cout << "30. Compara preturile a doua pachete turistice" << endl;
        cout << "31. Inmulteste pretul unui pachet cu un factor" << endl;

        cout << endl << "--- GESTIONARE HOTELURI (ID: 4000+) ---" << endl;
        cout << "32. Introdu un hotel in aplicatie" << endl;
        cout << "33. Vizualizeaza un hotel din aplicatie" << endl;
        cout << "34. Vizualizeaza toate hotelurile din aplicatie" << endl;
        cout << "35. Actualizeaza un hotel din aplicatie" << endl;
        cout << "36. Sterge un hotel din aplicatie" << endl;
        cout << "37. Creeaza o copie a unui hotel" << endl;
        cout << "38. Copiaza datele unui hotel in altul" << endl;
        cout << "39. Creste clasificarea cu o stea pentru un hotel" << endl;
        cout << "40. Scade clasificarea cu o stea pentru un hotel" << endl;
        cout << "41. Creste pretul pe noapte pentru un hotel" << endl;
        cout << "42. Scade pretul pe noapte pentru un hotel" << endl;
        cout << "43. Vizualizeaza numele / adresa pentru un anumit hotel" << endl;
        cout << "44. Verifica daca doua hoteluri au acelasi numar de stele" << endl;
        cout << "45. Compara preturile pentru doua hoteluri" << endl;
        cout << "46. Calculeaza costul total pentru un sejur" << endl;
        cout << "47. Verifica disponibilitatea unui hotel" << endl;

        cout << endl << "--- GESTIONARE REZERVARI (ID: 7000+) ---" << endl;
        cout << "48. Creeaza o rezervare noua" << endl;
        cout << "49. Vizualizeaza o rezervare dupa ID" << endl;
        cout << "50. Vizualizeaza toate rezervarile" << endl;
        cout << "51. Actualizeaza o rezervare existenta" << endl;
        cout << "52. Sterge o rezervare dupa ID" << endl;
        cout << "53. Creeaza o copie a unei rezervari" << endl;
        cout << "54. Copiaza datele unei rezervari in alta" << endl;
        cout << "55. Marcheaza o transa de plata ca platita" << endl;
        cout << "56. Marcheaza o transa de plata ca neplatita" << endl;
        cout << "57. Adauga plata pentru o rezervare" << endl;
        cout << "58. Retrage plata pentru o rezervare" << endl;
        cout << "59. Anuleaza o rezervare" << endl;
        cout << "60. Efectueaza plata unei transe" << endl;
        cout << "61. Vizualizeaza data / metoda de plata pentru o rezervare" << endl;
        cout << "62. Compara doua rezervari (acelasi client si pachet)" << endl;
        cout << "63. Compara sumele platite pentru doua rezervari" << endl;

        cout << endl << "Introdu o optiune: ";
        cin >> op;

        switch (op)
        {
        /// Client
        case 1:
        {
            Client client;
            cin >> client;
            Client::adaugaClientInLista(client);
            break;
        }
        case 2:
        {
            int clientIDToView;
            cout << "Introdu ID-ul clientului pe care vrei sa il vizualizezi: ";
            cin >> clientIDToView;
            Client::afiseazaClientDupaID(clientIDToView);
            break;
        }
        case 3: /// Testam mostenirea, virtualizarea, polimorfismul
        {
            for (int i = 0; i < Client::getNumarClienti(); i++)
            {
                Persoana* p = &Client::getListaClienti()[i];
                p->afiseazaProfil();
                cout << endl;
            }
            break;
        }
        case 4:
        {
            int clientIDToUpdate;
            cout << "Introdu ID-ul clientului pe care vrei sa il actualizezi: ";
            cin >> clientIDToUpdate;
            cin.get();

            Client *client = Client::getClientDupaID(clientIDToUpdate);
            if (client != nullptr)
            {
                Client clientAux;
                cin >> clientAux;
                *client = clientAux;
                cout << "Client actualizat cu succes!" << endl;
            }
            else
                cout << "Clientul cu ID-ul " << clientIDToUpdate << " nu exista" << endl;
            break;
        }
        case 5:
        {
            int clientIDToDelete;
            cout << "Introdu un ID al unui client pe care vrei sa il stergi: ";
            cin >> clientIDToDelete;
            Client::stergeClientDupaID(clientIDToDelete);
            break;
        }
        case 6:
        {
            int clientIDToCopy;
            cout << "Introdu ID-ul clientului pe care vrei sa il copiezi: ";
            cin >> clientIDToCopy;

            Client* clientOriginal = Client::getClientDupaID(clientIDToCopy);
            if (clientOriginal != nullptr)
            {
                Client clientCopie(*clientOriginal);
                Client::adaugaClientInLista(clientCopie);
                cout << "Copia a fost adaugata in lista de clienti." << endl;
            }
            else
                cout << "Clientul cu ID-ul " << clientIDToCopy << " nu exista" << endl;
            break;
        }
        case 7:
        {
            int clientID1, clientID2;
            cout << "Introdu ID-ul clientului sursa: ";
            cin >> clientID1;
            cout << "Introdu ID-ul clientului destinatie: ";
            cin >> clientID2;

            Client* client1 = Client::getClientDupaID(clientID1);
            Client* client2 = Client::getClientDupaID(clientID2);

            if (client1 != nullptr && client2 != nullptr)
            {
                cout << "Inainte de copiere:" << endl;
                cout << "Client sursa:" << endl << *client1 << endl;
                cout << "Client destinatie:" << endl << *client2 << endl;

                *client2 = *client1;

                cout << "Dupa copiere (ID-ul ramane neschimbat, restul datelor sunt copiate):" << endl;
                cout << "Client sursa:" << endl << *client1 << endl;
                cout << "Client destinatie:" << endl << *client2 << endl;
            }
            else
                cout << "Unul sau ambii clienti nu exista!" << endl;
            break;
        }
        case 8:
        {
            int clientID;
            cout << "Introdu ID-ul clientului pentru care vrei sa adaugi un punct de fidelitate: ";
            cin >> clientID;

            Client* client = Client::getClientDupaID(clientID);
            if (client != nullptr)
            {
                cout << "Clientul avea " << client->getPuncteFidelitate() << " puncte de fidelitate" << endl;
                Client prefixClient = ++(*client);
                cout << "Clientul are acum " << prefixClient.getPuncteFidelitate() << " puncte de fidelitate" << endl;
            }
            else
                cout << "Clientul cu ID-ul " << clientID << " nu exista" << endl;
            break;
        }
        case 9:
        {
            int clientID;
            cout << "Introdu ID-ul clientului pentru care vrei sa anulezi un punct de fidelitate: ";
            cin >> clientID;

            Client* client = Client::getClientDupaID(clientID);
            if (client != nullptr)
            {
                cout << "Clientul avea " << client->getPuncteFidelitate() << " puncte de fidelitate" << endl;
                Client prefixClient = --(*client);
                cout << "Clientul are acum " << max(0, prefixClient.getPuncteFidelitate()) << " puncte de fidelitate" << endl;
            }
            else
                cout << "Clientul cu ID-ul " << clientID << " nu exista" << endl;
            break;
        }
        case 10:
        {
            int clientID, valoare;
            cout << "Introdu ID-ul clientului pentru care vrei sa adaugi mai multe puncte de fidelitate: ";
            cin >> clientID;

            Client* client = Client::getClientDupaID(clientID);
            if (client != nullptr)
            {
                cout << "Introdu numarul de puncte de fidelitate pe care vrei sa le adaugi: ";
                cin >> valoare;
                cout << "Clientul avea " << client->getPuncteFidelitate() << " puncte de fidelitate" << endl;

                Client rezultat = *client + valoare;
                *client = rezultat;
                cout << "Clientul are acum " << rezultat.getPuncteFidelitate() << " puncte de fidelitate" << endl;
            }
            else
                cout << "Clientul cu ID-ul " << clientID << " nu exista" << endl;
            break;
        }

        case 11:
        {
            int clientID, valoare;
            cout << "Introdu ID-ul clientului pentru care vrei sa anulezi mai multe puncte de fidelitate: ";
            cin >> clientID;

            Client* client = Client::getClientDupaID(clientID);
            if (client != nullptr)
            {
                cout << "Introdu numarul de puncte de fidelitate de anulat: ";
                cin >> valoare;
                cout << "Clientul avea " << client->getPuncteFidelitate() << " puncte de fidelitate" << endl;

                Client rezultat = *client - valoare;
                *client = rezultat;
                cout << "Clientul are acum " << max(0, rezultat.getPuncteFidelitate()) << " puncte de fidelitate" << endl;
            }
            else
                cout << "Clientul cu ID-ul " << clientID << " nu exista" << endl;
            break;
        }
        case 12:
        {
            int clientID, optiune;
            cout << "Introdu ID-ul clientului: ";
            cin >> clientID;

            Client* client = Client::getClientDupaID(clientID);
            if (client != nullptr)
            {
                cout << "Ce doresti sa vizualizezi (0 - numele, 1 - emailul)?: ";
                cin >> optiune;
                cout << (*client)[optiune] << endl;
            }
            else
                cout << "Clientul cu ID-ul " << clientID << " nu exista" << endl;
            break;
        }
        case 13:
        {
            int clientID1, clientID2;
            cout << "Introdu ID-ul primului client: ";
            cin >> clientID1;
            cout << "Introdu ID-ul celui de-al doilea client: ";
            cin >> clientID2;

            Client* client1 = Client::getClientDupaID(clientID1);
            Client* client2 = Client::getClientDupaID(clientID2);

            if (client1 != nullptr && client2 != nullptr)
            {
                if (*client1 == *client2)
                    cout << "Clientii sunt aceiasi" << endl;
                else if (*client1 != *client2)
                    cout << "Clientii sunt diferiti" << endl;
            }
            else
                cout << "Unul sau ambii clienti nu exista!" << endl;
            break;
        }
        case 14:
        {
            int clientID1, clientID2;
            cout << "Introdu ID-ul primului client: ";
            cin >> clientID1;
            cout << "Introdu ID-ul celui de-al doilea client: ";
            cin >> clientID2;

            Client* client1 = Client::getClientDupaID(clientID1);
            Client* client2 = Client::getClientDupaID(clientID2);

            if (client1 != nullptr && client2 != nullptr)
            {
                cout << "Client 1: " << client1->getNume() << " - " << client1->getPuncteFidelitate() << " puncte de fidelitate" << endl;
                cout << "Client 2: " << client2->getNume() << " - " << client2->getPuncteFidelitate() << " puncte de fidelitate" << endl;
                if (*client1 < *client2)
                    cout << "Clientul 1 are mai putine puncte de fidelitate decat clientul 2" << endl;
                else
                    cout << "Clientul 1 are mai multe puncte de fidelitate decat clientul 2" << endl;
            }
            else
                cout << "Unul sau ambii clienti nu exista!" << endl;
            break;
        }

        /// PachetTuristic
        case 15:
        {
            PachetTuristic pachet;
            cin >> pachet;
            PachetTuristic::adaugaPachetInLista(pachet);
            break;
        }
        case 16:
        {
            int pachetIDToView;
            cout << "Introdu ID-ul pachetului pe care vrei sa il vizualizezi: ";
            cin >> pachetIDToView;
            PachetTuristic::afiseazaPachetDupaID(pachetIDToView);
            break;
        }
        case 17:
        {
            PachetTuristic::afiseazaToatePachetele();
            break;
        }
        case 18:
        {
            int pachetIDToUpdate;
            cout << "Introdu ID-ul pachetului pe care vrei sa il actualizezi: ";
            cin >> pachetIDToUpdate;
            cin.get();

            PachetTuristic *pachet = PachetTuristic::getPachetDupaID(pachetIDToUpdate);
            if (pachet != nullptr)
            {
                PachetTuristic pachetAux;
                cin >> pachetAux;
                *pachet = pachetAux;
                cout << "Pachet actualizat cu succes!" << endl;
            }
            else
                cout << "Pachetul cu ID-ul " << pachetIDToUpdate << " nu exista" << endl;
            break;
        }
        case 19:
        {
            int pachetIDToDelete;
            cout << "Introdu un ID al unui pachet pe care vrei sa il stergi: ";
            cin >> pachetIDToDelete;
            PachetTuristic::stergePachetDupaID(pachetIDToDelete);
            break;
        }
        case 20:
        {
            int pachetIDToCopy;
            cout << "Introdu ID-ul pachetului pe care vrei sa il copiezi: ";
            cin >> pachetIDToCopy;

            PachetTuristic* pachetOriginal = PachetTuristic::getPachetDupaID(pachetIDToCopy);
            if (pachetOriginal != nullptr)
            {
                PachetTuristic pachetCopie(*pachetOriginal);
                PachetTuristic::adaugaPachetInLista(pachetCopie);
                cout << "Copia a fost adaugata in lista de pachete." << endl;
            }
            else
                cout << "Pachetul cu ID-ul " << pachetIDToCopy << " nu exista" << endl;
            break;
        }
        case 21:
        {
            int pachetID1, pachetID2;
            cout << "Introdu ID-ul pachetului sursa: ";
            cin >> pachetID1;
            cout << "Introdu ID-ul pachetului destinatie: ";
            cin >> pachetID2;

            PachetTuristic* pachet1 = PachetTuristic::getPachetDupaID(pachetID1);
            PachetTuristic* pachet2 = PachetTuristic::getPachetDupaID(pachetID2);

            if (pachet1 != nullptr && pachet2 != nullptr)
            {
                cout << "Inainte de copiere:" << endl;
                cout << "Pachet sursa:" << endl << *pachet1 << endl;
                cout << "Pachet destinatie:" << endl << *pachet2 << endl;

                *pachet2 = *pachet1;

                cout << "Dupa copiere (ID-ul ramane neschimbat, restul datelor sunt copiate):" << endl;
                cout << "Pachet sursa:" << endl << *pachet1 << endl;
                cout << "Pachet destinatie:" << endl << *pachet2 << endl;
            }
            else
                cout << "Unul sau ambele pachete nu exista!" << endl;
            break;
        }
        case 22:
        {
            int pachetID;
            cout << "Introdu ID-ul pachetului pentru care vrei sa adaugi o zi: ";
            cin >> pachetID;

            PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetID);
            if (pachet != nullptr)
            {
                cout << "Pachetul avea " << pachet->getNrZile() << " zile" << endl;
                PachetTuristic prefixPachet = ++(*pachet);
                cout << "Pachetul are acum " << prefixPachet.getNrZile() << " zile" << endl;
            }
            else
                cout << "Pachetul cu ID-ul " << pachetID << " nu exista" << endl;
            break;
        }
        case 23:
        {
            int pachetID;
            cout << "Introdu ID-ul pachetului pentru care vrei sa scazi o zi: ";
            cin >> pachetID;

            PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetID);
            if (pachet != nullptr)
            {
                cout << "Pachetul avea " << pachet->getNrZile() << " zile" << endl;
                PachetTuristic prefixPachet = --(*pachet);
                cout << "Pachetul are acum " << prefixPachet.getNrZile() << " zile" << endl;
            }
            else
                cout << "Pachetul cu ID-ul " << pachetID << " nu exista" << endl;
            break;
        }
        case 24:
        {
            int pachetID;
            float valoare;
            cout << "Introdu ID-ul pachetului pentru care vrei sa adaugi la pret: ";
            cin >> pachetID;

            PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetID);
            if (pachet != nullptr)
            {
                cout << "Introdu valoarea de adaugat la pret: ";
                cin >> valoare;
                cout << "Pachetul avea pretul " << pachet->getPret() << " EUR" << endl;

                PachetTuristic rezultat = *pachet + valoare;
                *pachet = rezultat;
                cout << "Pachetul are acum pretul " << rezultat.getPret() << " EUR" << endl;
            }
            else
                cout << "Pachetul cu ID-ul " << pachetID << " nu exista" << endl;
            break;
        }
        case 25:
        {
            int pachetID;
            float valoare;
            cout << "Introdu ID-ul pachetului pentru care vrei sa scazi din pret: ";
            cin >> pachetID;

            PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetID);
            if (pachet != nullptr)
            {
                cout << "Introdu valoarea de scazut din pret: ";
                cin >> valoare;
                cout << "Pachetul avea pretul " << pachet->getPret() << " EUR" << endl;

                PachetTuristic rezultat = *pachet - valoare;
                *pachet = rezultat;
                cout << "Pachetul are acum pretul " << rezultat.getPret() << " EUR" << endl;
            }
            else
                cout << "Pachetul cu ID-ul " << pachetID << " nu exista" << endl;
            break;
        }
        case 26:
        {
            int pachetID;
            cout << "Introdu ID-ul pachetului pentru care vrei sa calculezi discountul: ";
            cin >> pachetID;

            PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetID);
            if (pachet != nullptr)
            {
                float pretOriginal = pachet->getPret();
                float pretDiscount = pachet->calculeazaDiscount();

                cout << "Pretul original: " << pretOriginal << " EUR" << endl;
                cout << "Pretul cu discount: " << pretDiscount << " EUR" << endl;
                cout << "Discount aplicat: " << (pretOriginal - pretDiscount) << " EUR ("
                     << ((pretOriginal - pretDiscount) / pretOriginal * 100) << "%)" << endl;
            }
            else
                cout << "Pachetul cu ID-ul " << pachetID << " nu exista" << endl;
            break;
        }
        case 27:
        {
            int pachetID;
            cout << "Introdu ID-ul pachetului pentru care vrei sa modifici perioada: ";
            cin >> pachetID;

            PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetID);
            if (pachet != nullptr)
            {
                char perioadaNoua[100];
                cout << "Perioada actuala: " << pachet->getPerioada() << endl;
                cout << "Introdu noua perioada: ";
                cin.ignore();
                cin.getline(perioadaNoua, 100);

                pachet->modificaPerioada(perioadaNoua);

            }
            else
                cout << "Pachetul cu ID-ul " << pachetID << " nu exista" << endl;
            break;
        }
        case 28:
        {
            int pachetID, optiune;
            cout << "Introdu ID-ul pachetului: ";
            cin >> pachetID;

            PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetID);
            if (pachet != nullptr)
            {
                cout << "Ce doresti sa vizualizezi (0 - numele, 1 - destinatia, 2 - perioada)?: ";
                cin >> optiune;
                cout << (*pachet)[optiune] << endl;
            }
            else
                cout << "Pachetul cu ID-ul " << pachetID << " nu exista" << endl;
            break;
        }
        case 29:
        {
            int pachetID1, pachetID2;
            cout << "Introdu ID-ul primului pachet: ";
            cin >> pachetID1;
            cout << "Introdu ID-ul celui de-al doilea pachet: ";
            cin >> pachetID2;

            PachetTuristic* pachet1 = PachetTuristic::getPachetDupaID(pachetID1);
            PachetTuristic* pachet2 = PachetTuristic::getPachetDupaID(pachetID2);

            if (pachet1 != nullptr && pachet2 != nullptr)
            {
                if (*pachet1 == *pachet2)
                    cout << "Pachetele au aceeasi destinatie: " << pachet1->getDestinatie() << endl;
                else if (*pachet1 != *pachet2)
                    cout << "Pachetele au destinatii diferite: " << pachet1->getDestinatie() << " vs " << pachet2->getDestinatie() << endl;
            }
            else
                cout << "Unul sau ambele pachete nu exista!" << endl;
            break;
        }
        case 30:
        {
            int pachetID1, pachetID2;
            cout << "Introdu ID-ul primului pachet: ";
            cin >> pachetID1;
            cout << "Introdu ID-ul celui de-al doilea pachet: ";
            cin >> pachetID2;

            PachetTuristic* pachet1 = PachetTuristic::getPachetDupaID(pachetID1);
            PachetTuristic* pachet2 = PachetTuristic::getPachetDupaID(pachetID2);

            if (pachet1 != nullptr && pachet2 != nullptr)
            {
                cout << "Pachet 1: " << pachet1->getNumePachet() << " - " << pachet1->getPret() << " EUR" << endl;
                cout << "Pachet 2: " << pachet2->getNumePachet() << " - " << pachet2->getPret() << " EUR" << endl;
                if (*pachet1 < *pachet2)
                    cout << "Pachetul 1 are pret mai mic decat pachetul 2" << endl;
                else
                    cout << "Pachetul 1 are pret mai mare sau egal cu pachetul 2" << endl;
            }
            else
                cout << "Unul sau ambele pachete nu exista!" << endl;
            break;
        }
        case 31:
        {
            int pachetID;
            float factor;
            cout << "Introdu ID-ul pachetului pentru care vrei sa inmultesti pretul: ";
            cin >> pachetID;

            PachetTuristic* pachet = PachetTuristic::getPachetDupaID(pachetID);
            if (pachet != nullptr)
            {
                cout << "Introdu factorul de inmultire: ";
                cin >> factor;
                cout << "Pachetul avea pretul " << pachet->getPret() << " EUR" << endl;

                PachetTuristic rezultat = *pachet * factor;
                *pachet = rezultat;
                cout << "Pachetul are acum pretul " << rezultat.getPret() << " EUR" << endl;
            }
            else
                cout << "Pachetul cu ID-ul " << pachetID << " nu exista" << endl;
            break;
        }

        /// Hotel
        case 32:
        {
            Hotel hotel;
            cin >> hotel;
            Hotel::adaugaHotelInLista(hotel);
            break;
        }
        case 33:
        {
            int hotelIDToView;
            cout << "Introdu ID-ul hotelului pe care vrei sa il vizualizezi: ";
            cin >> hotelIDToView;
            Hotel::afiseazaHotelDupaID(hotelIDToView);
            break;
        }
        case 34:
        {
            Hotel::afiseazaToateHotelurile();
            break;
        }
        case 35:
        {
            int hotelIDToUpdate;
            cout << "Introdu ID-ul hotelului pe care vrei sa il actualizezi: ";
            cin >> hotelIDToUpdate;
            cin.get();

            Hotel *hotel = Hotel::getHotelDupaID(hotelIDToUpdate);
            if (hotel != nullptr)
            {
                Hotel hotelAux;
                cin >> hotelAux;
                *hotel = hotelAux;
                cout << "Hotel actualizat cu succes!" << endl;
            }
            else
                cout << "Hotelul cu ID-ul " << hotelIDToUpdate << " nu exista" << endl;
            break;
        }
        case 36:
        {
            int hotelIDToDelete;
            cout << "Introdu un ID al unui hotel pe care vrei sa il stergi: ";
            cin >> hotelIDToDelete;
            Hotel::stergeHotelDupaID(hotelIDToDelete);
            break;
        }
        case 37:
        {
            int hotelIDToCopy;
            cout << "Introdu ID-ul hotelului pe care vrei sa il copiezi: ";
            cin >> hotelIDToCopy;

            Hotel* hotelOriginal = Hotel::getHotelDupaID(hotelIDToCopy);
            if (hotelOriginal != nullptr)
            {
                Hotel hotelCopie(*hotelOriginal);
                Hotel::adaugaHotelInLista(hotelCopie);
                cout << "Copia a fost adaugata in lista de hoteluri." << endl;
            }
            else
                cout << "Hotelul cu ID-ul " << hotelIDToCopy << " nu exista" << endl;
            break;
        }
        case 38:
        {
            int hotelID1, hotelID2;
            cout << "Introdu ID-ul hotelului sursa: ";
            cin >> hotelID1;
            cout << "Introdu ID-ul hotelului destinatie: ";
            cin >> hotelID2;

            Hotel* hotel1 = Hotel::getHotelDupaID(hotelID1);
            Hotel* hotel2 = Hotel::getHotelDupaID(hotelID2);

            if (hotel1 != nullptr && hotel2 != nullptr)
            {
                *hotel2 = *hotel1;

                cout << "Dupa copiere (ID-ul ramane neschimbat, restul datelor sunt copiate):" << endl;
                cout << "Hotel sursa:" << endl << *hotel1 << endl;
                cout << "Hotel destinatie:" << endl << *hotel2 << endl;
            }
            else
                cout << "Unul sau ambele hoteluri nu exista!" << endl;
            break;
        }
        case 39:
        {
            int hotelID;
            cout << "Introdu ID-ul hotelului pentru care vrei sa cresti clasificarea: ";
            cin >> hotelID;

            Hotel* hotel = Hotel::getHotelDupaID(hotelID);
            if (hotel != nullptr)
            {
                cout << "Hotelul avea " << hotel->getNumarStele() << " stele" << endl;
                Hotel prefixHotel = ++(*hotel);
                cout << "Hotelul are acum " << prefixHotel.getNumarStele() << " stele" << endl;
            }
            else
                cout << "Hotelul cu ID-ul " << hotelID << " nu exista" << endl;
            break;
        }
        case 40:
        {
            int hotelID;
            cout << "Introdu ID-ul hotelului pentru care vrei sa scazi clasificarea: ";
            cin >> hotelID;

            Hotel* hotel = Hotel::getHotelDupaID(hotelID);
            if (hotel != nullptr)
            {
                cout << "Hotelul avea " << hotel->getNumarStele() << " stele" << endl;
                Hotel prefixHotel = --(*hotel);
                cout << "Hotelul are acum " << prefixHotel.getNumarStele() << " stele" << endl;
            }
            else
                cout << "Hotelul cu ID-ul " << hotelID << " nu exista" << endl;
            break;
        }
        case 41:
        {
            int hotelID;
            float valoare;
            cout << "Introdu ID-ul hotelului pentru care vrei sa cresti pretul: ";
            cin >> hotelID;

            Hotel* hotel = Hotel::getHotelDupaID(hotelID);
            if (hotel != nullptr)
            {
                cout << "Introdu valoarea cu care vrei sa cresti pretul: ";
                cin >> valoare;
                cout << "Hotelul avea pretul pe noapte " << hotel->getPretNoapte() << " EUR" << endl;

                Hotel rezultat = *hotel + valoare;
                *hotel = rezultat;
                cout << "Hotelul are acum pretul pe noapte " << rezultat.getPretNoapte() << " EUR" << endl;
            }
            else
                cout << "Hotelul cu ID-ul " << hotelID << " nu exista" << endl;
            break;
        }
        case 42:
        {
            int hotelID;
            float valoare;
            cout << "Introdu ID-ul hotelului pentru care vrei sa scazi pretul: ";
            cin >> hotelID;

            Hotel* hotel = Hotel::getHotelDupaID(hotelID);
            if (hotel != nullptr)
            {
                cout << "Introdu valoarea cu care vrei sa scazi pretul: ";
                cin >> valoare;
                cout << "Hotelul avea pretul pe noapte " << hotel->getPretNoapte() << " EUR" << endl;

                Hotel rezultat = *hotel - valoare;
                *hotel = rezultat;
                cout << "Hotelul are acum pretul pe noapte " << rezultat.getPretNoapte() << " EUR" << endl;
            }
            else
                cout << "Hotelul cu ID-ul " << hotelID << " nu exista" << endl;
            break;
        }
        case 43:
        {
            int hotelID, optiune;
            cout << "Introdu ID-ul hotelului: ";
            cin >> hotelID;

            Hotel* hotel = Hotel::getHotelDupaID(hotelID);
            if (hotel != nullptr)
            {
                cout << "Ce doresti sa vizualizezi (0 - numele, 1 - adresa)?: ";
                cin >> optiune;
                cout << (*hotel)[optiune] << endl;
            }
            else
                cout << "Hotelul cu ID-ul " << hotelID << " nu exista" << endl;
            break;
        }
        case 44:
        {
            int hotelID1, hotelID2;
            cout << "Introdu ID-ul primului hotel: ";
            cin >> hotelID1;
            cout << "Introdu ID-ul celui de-al doilea hotel: ";
            cin >> hotelID2;

            Hotel* hotel1 = Hotel::getHotelDupaID(hotelID1);
            Hotel* hotel2 = Hotel::getHotelDupaID(hotelID2);

            if (hotel1 != nullptr && hotel2 != nullptr)
            {
                if (*hotel1 == *hotel2)
                    cout << "Hotelurile au acelasi numar de stele" << endl;
                else if (*hotel1 != *hotel2)
                    cout << "Hotelurile au un numar diferit de stele" << endl;
            }
            else
                cout << "Unul sau ambele hoteluri nu exista!" << endl;
            break;
        }
        case 45:
        {
            int hotelID1, hotelID2;
            cout << "Introdu ID-ul primului hotel: ";
            cin >> hotelID1;
            cout << "Introdu ID-ul celui de-al doilea hotel: ";
            cin >> hotelID2;

            Hotel* hotel1 = Hotel::getHotelDupaID(hotelID1);
            Hotel* hotel2 = Hotel::getHotelDupaID(hotelID2);

            if (hotel1 != nullptr && hotel2 != nullptr)
            {
                cout << "Hotel 1: " << hotel1->getNumeHotel() << " - " << hotel1->getPretNoapte() << " EUR/noapte" << endl;
                cout << "Hotel 2: " << hotel2->getNumeHotel() << " - " << hotel2->getPretNoapte() << " EUR/noapte" << endl;
                if (*hotel1 < *hotel2)
                    cout << "Hotelul 1 are pretul mai mic decat hotelul 2" << endl;
                else
                    cout << "Hotelul 1 are pretul mai mare sau egal cu hotelul 2" << endl;
            }
            else
                cout << "Unul sau ambele hoteluri nu exista!" << endl;
            break;
        }
        case 46:
        {
            int hotelID, nrNopti;
            cout << "Introdu ID-ul hotelului pentru care vrei sa calculezi costul total: ";
            cin >> hotelID;

            Hotel* hotel = Hotel::getHotelDupaID(hotelID);
            if (hotel != nullptr)
            {
                cout << "Introdu numarul de nopti pentru sejur: ";
                cin >> nrNopti;

                float costTotal = hotel->calculeazaCostTotal(nrNopti);
                cout << "Cost total pentru " << nrNopti << " nopti la " << hotel->getNumeHotel() << ": " << costTotal << " EUR" << endl;
                if (nrNopti > 7)
                    cout << "(Include reducere de 10% pentru sejur mai lung de 7 nopti)" << endl;
                else if (nrNopti > 3)
                    cout << "(Include reducere de 5% pentru sejur intre 4 si 7 nopti)" << endl;
            }
            else
                cout << "Hotelul cu ID-ul " << hotelID << " nu exista" << endl;
            break;
        }
        case 47:
        {
            int hotelID;
            char dataCheckIn[20], dataCheckOut[20];
            cout << "Introdu ID-ul hotelului pentru care vrei sa verifici disponibilitatea: ";
            cin >> hotelID;

            Hotel* hotel = Hotel::getHotelDupaID(hotelID);
            if (hotel != nullptr)
            {
                cin.ignore();
                cout << "Introdu data de check-in (format: ZZ/LL/AAAA): ";
                cin.getline(dataCheckIn, 20);

                cout << "Introdu data de check-out (format: ZZ/LL/AAAA): ";
                cin.getline(dataCheckOut, 20);

                if (hotel->verificaDisponibilitate(dataCheckIn, dataCheckOut))
                    cout << "Hotelul " << hotel->getNumeHotel() << " este disponibil in perioada specificata!" << endl;
                else
                    cout << "Hotelul " << hotel->getNumeHotel() << " nu este disponibil in perioada specificata!" << endl;
            }
            else
                cout << "Hotelul cu ID-ul " << hotelID << " nu exista" << endl;
            break;
        }

        /// Rezervare
        case 48:
        {
            Rezervare rezervare;
            cin >> rezervare;
            Rezervare::adaugaRezervareInLista(rezervare);
            break;
        }
        case 49:
        {
            int rezervareIDToView;
            cout << "Introdu ID-ul rezervarii pe care vrei sa o vizualizezi: ";
            cin >> rezervareIDToView;
            Rezervare::afiseazaRezervaredupaID(rezervareIDToView);
            break;
        }
        case 50:
        {
            Rezervare::afiseazaToateRezervarile();
            break;
        }
        case 51:
        {
            int rezervareIDToUpdate;
            cout << "Introdu ID-ul rezervarii pe care vrei sa o actualizezi: ";
            cin >> rezervareIDToUpdate;
            cin.get();

            Rezervare *rezervare = Rezervare::getRezervaredupaID(rezervareIDToUpdate);
            if (rezervare != nullptr)
            {
                Rezervare rezervareAux;
                cin >> rezervareAux;
                *rezervare = rezervareAux;
                cout << "Rezervare actualizata cu succes!" << endl;
            }
            else
                cout << "Rezervarea cu ID-ul " << rezervareIDToUpdate << " nu exista" << endl;
            break;
        }
        case 52:
        {
            int rezervareIDToDelete;
            cout << "Introdu un ID al unei rezervari pe care vrei sa o stergi: ";
            cin >> rezervareIDToDelete;
            Rezervare::stergeRezervaredupaID(rezervareIDToDelete);
            break;
        }
        case 53:
        {
            int rezervareIDToCopy;
            cout << "Introdu ID-ul rezervarii pe care vrei sa o copiezi: ";
            cin >> rezervareIDToCopy;

            Rezervare* rezervareOriginal = Rezervare::getRezervaredupaID(rezervareIDToCopy);
            if (rezervareOriginal != nullptr)
            {
                Rezervare rezervareCopie(*rezervareOriginal);
                Rezervare::adaugaRezervareInLista(rezervareCopie);
                cout << "Copia a fost adaugata in lista de rezervari." << endl;
            }
            else
                cout << "Rezervarea cu ID-ul " << rezervareIDToCopy << " nu exista" << endl;
            break;
        }
        case 54:
        {
            int rezervareID1, rezervareID2;
            cout << "Introdu ID-ul rezervarii sursa: ";
            cin >> rezervareID1;
            cout << "Introdu ID-ul rezervarii destinatie: ";
            cin >> rezervareID2;

            Rezervare* rezervare1 = Rezervare::getRezervaredupaID(rezervareID1);
            Rezervare* rezervare2 = Rezervare::getRezervaredupaID(rezervareID2);

            if (rezervare1 != nullptr && rezervare2 != nullptr)
            {
                cout << "Inainte de copiere:" << endl;
                cout << "Rezervare sursa:" << endl << *rezervare1 << endl;
                cout << "Rezervare destinatie:" << endl << *rezervare2 << endl;

                *rezervare2 = *rezervare1;

                cout << "Dupa copiere (ID-ul ramane neschimbat, restul datelor sunt copiate):" << endl;
                cout << "Rezervare sursa:" << endl << *rezervare1 << endl;
                cout << "Rezervare destinatie:" << endl << *rezervare2 << endl;
            }
            else
                cout << "Una sau ambele rezervari nu exista!" << endl;
            break;
        }
        case 55:
        {
            int rezervareID;
            cout << "Introdu ID-ul rezervarii pentru care vrei sa marchezi o transa platita: ";
            cin >> rezervareID;

            Rezervare* rezervare = Rezervare::getRezervaredupaID(rezervareID);
            if (rezervare != nullptr)
            {
                cout << "Status plati inainte:" << endl;
                bool* statusPlata = rezervare->getStatusPlata();
                for (int i = 0; i < 3; i++)
                    cout << "Transa " << i + 1 << ": " << (statusPlata[i] ? "Platit" : "Neplatit") << endl;


                ++(*rezervare); // marcheaza urmatoarea transa ca platita

                cout << "Status plati dupa:" << endl;
                statusPlata = rezervare->getStatusPlata();
                for (int i = 0; i < 3; i++)
                    cout << "Transa " << i + 1 << ": " << (statusPlata[i] ? "Platit" : "Neplatit") << endl;
            }
            else
                cout << "Rezervarea cu ID-ul " << rezervareID << " nu exista" << endl;
            break;
        }
        case 56:
        {
            int rezervareID;
            cout << "Introdu ID-ul rezervarii pentru care vrei sa marchezi o transa neplatita: ";
            cin >> rezervareID;

            Rezervare* rezervare = Rezervare::getRezervaredupaID(rezervareID);
            if (rezervare != nullptr)
            {
                cout << "Status plati inainte:" << endl;
                bool* statusPlata = rezervare->getStatusPlata();
                for (int i = 0; i < 3; i++)
                    cout << "Transa " << i + 1 << ": " << (statusPlata[i] ? "Platit" : "Neplatit") << endl;

                --(*rezervare); // marcheaza ultima transa platita ca neplatita

                cout << "Status plati dupa:" << endl;
                statusPlata = rezervare->getStatusPlata();
                for (int i = 0; i < 3; i++)
                    cout << "Transa " << i + 1 << ": " << (statusPlata[i] ? "Platit" : "Neplatit") << endl;
            }
            else
                cout << "Rezervarea cu ID-ul " << rezervareID << " nu exista" << endl;
            break;
        }
        case 57:
        {
            int rezervareID;
            float valoare;
            cout << "Introdu ID-ul rezervarii pentru care vrei sa adaugi plata: ";
            cin >> rezervareID;

            Rezervare* rezervare = Rezervare::getRezervaredupaID(rezervareID);
            if (rezervare != nullptr)
            {
                cout << "Introdu suma de adaugat la plata: ";
                cin >> valoare;
                cout << "Rezervarea avea suma platita " << rezervare->getSumaPlatita() << " EUR si "
                     << rezervare->getSumaRamasa() << " EUR ramasi de platit" << endl;

                Rezervare rezultat = *rezervare + valoare;
                *rezervare = rezultat;
                cout << "Rezervarea are acum suma platita " << rezervare->getSumaPlatita() << " EUR si "
                     << rezervare->getSumaRamasa() << " EUR ramasi de platit" << endl;
            }
            else
                cout << "Rezervarea cu ID-ul " << rezervareID << " nu exista" << endl;
            break;
        }
        case 58:
        {
            int rezervareID;
            float valoare;
            cout << "Introdu ID-ul rezervarii pentru care vrei sa retragi plata: ";
            cin >> rezervareID;

            Rezervare* rezervare = Rezervare::getRezervaredupaID(rezervareID);
            if (rezervare != nullptr)
            {
                cout << "Introdu suma de retras din plata: ";
                cin >> valoare;
                cout << "Rezervarea avea suma platita " << rezervare->getSumaPlatita() << " EUR si "
                     << rezervare->getSumaRamasa() << " EUR ramasi de platit" << endl;

                Rezervare rezultat = *rezervare - valoare;
                *rezervare = rezultat;
                cout << "Rezervarea are acum suma platita " << rezervare->getSumaPlatita() << " EUR si "
                     << rezervare->getSumaRamasa() << " EUR ramasi de platit" << endl;
            }
            else
                cout << "Rezervarea cu ID-ul " << rezervareID << " nu exista" << endl;
            break;
        }
        case 59:
        {
            int rezervareID;
            cout << "Introdu ID-ul rezervarii pe care vrei sa o anulezi: ";
            cin >> rezervareID;

            Rezervare* rezervare = Rezervare::getRezervaredupaID(rezervareID);
            if (rezervare != nullptr)
                rezervare->anuleazaRezervare();
            else
                cout << "Rezervarea cu ID-ul " << rezervareID << " nu exista" << endl;
            break;
        }
        case 60:
        {
            int rezervareID, indexTransa;
            float suma;
            cout << "Introdu ID-ul rezervarii: ";
            cin >> rezervareID;

            Rezervare* rezervare = Rezervare::getRezervaredupaID(rezervareID);
            if (rezervare != nullptr)
            {
                cout << "Status plati curent:" << endl;
                bool* statusPlata = rezervare->getStatusPlata();
                for (int i = 0; i < 3; i++)
                    cout << "Transa " << i + 1 << ": " << (statusPlata[i] ? "Platit" : "Neplatit") << endl;

                cout << "Introdu indexul transei pe care vrei sa o platesti (0, 1 sau 2): ";
                cin >> indexTransa;
                cout << "Introdu suma de platit: ";
                cin >> suma;

                rezervare->platesteTransa(indexTransa, suma);

                cout << "Status plati dupa efectuarea platii:" << endl;
                statusPlata = rezervare->getStatusPlata();
                for (int i = 0; i < 3; i++)
                    cout << "Transa " << i + 1 << ": " << (statusPlata[i] ? "Platit" : "Neplatit") << endl;
                cout << "Suma platita: " << rezervare->getSumaPlatita() << " EUR" << endl;
                cout << "Suma ramasa: " << rezervare->getSumaRamasa() << " EUR" << endl;
            }
            else
                cout << "Rezervarea cu ID-ul " << rezervareID << " nu exista" << endl;
            break;
        }
        case 61:
        {
            int rezervareID, optiune;
            cout << "Introdu ID-ul rezervarii: ";
            cin >> rezervareID;

            Rezervare* rezervare = Rezervare::getRezervaredupaID(rezervareID);
            if (rezervare != nullptr)
            {
                cout << "Ce doresti sa vizualizezi (0 - data rezervarii, 1 - metoda de plata)?: ";
                cin >> optiune;
                cout << (*rezervare)[optiune] << endl;
            }
            else
                cout << "Rezervarea cu ID-ul " << rezervareID << " nu exista" << endl;
            break;
        }
        case 62:
        {
            int rezervareID1, rezervareID2;
            cout << "Introdu ID-ul primei rezervari: ";
            cin >> rezervareID1;
            cout << "Introdu ID-ul celei de-a doua rezervari: ";
            cin >> rezervareID2;

            Rezervare* rezervare1 = Rezervare::getRezervaredupaID(rezervareID1);
            Rezervare* rezervare2 = Rezervare::getRezervaredupaID(rezervareID2);

            if (rezervare1 != nullptr && rezervare2 != nullptr)
            {
                if (*rezervare1 == *rezervare2)
                    cout << "Rezervarile au acelasi client (ID: " << rezervare1->getClientID() << ") si pachet (ID: " << rezervare1->getPachetID() << ")" << endl;
                else if (*rezervare1 != *rezervare2)
                    cout << "Rezervarile au client sau pachet diferit" << endl;
            }
            else
                cout << "Una sau ambele rezervari nu exista!" << endl;
            break;
        }
        case 63:
        {
            int rezervareID1, rezervareID2;
            cout << "Introdu ID-ul primei rezervari: ";
            cin >> rezervareID1;
            cout << "Introdu ID-ul celei de-a doua rezervari: ";
            cin >> rezervareID2;

            Rezervare* rezervare1 = Rezervare::getRezervaredupaID(rezervareID1);
            Rezervare* rezervare2 = Rezervare::getRezervaredupaID(rezervareID2);

            if (rezervare1 != nullptr && rezervare2 != nullptr)
            {
                cout << "Rezervare 1: Suma platita = " << rezervare1->getSumaPlatita() << " EUR" << endl;
                cout << "Rezervare 2: Suma platita = " << rezervare2->getSumaPlatita() << " EUR" << endl;

                if (*rezervare1 < *rezervare2)
                    cout << "Rezervarea 1 are suma platita mai mica decat rezervarea 2" << endl;
                else
                    cout << "Rezervarea 1 are suma platita mai mare sau egala cu rezervarea 2" << endl;
            }
            else
                cout << "Una sau ambele rezervari nu exista!" << endl;
            break;
        }
        default :
            cout << "Nu s-a selectat nimic din meniu." << endl;
    }
        getch();
    }
    while (op);


    cleanup();
    return 0;
}
