#include <iostream>

using namespace std;

//declarare clasa 
class EchipaDeFotbal{
    

//membrii private ai clasei
private:    
    string nume;
    int puncte=0;
    unsigned nrJucatori;
    string* lot;

//variabila statica nrEchipe; o variabila statica este o variabila a carei valoare nu difera de 
//la un obiect la altul, cum sunt cele declarate mai sus; de aceea, se considera ca variabila
//statica este asociata intregii clase, nu fiecarui obiect in parte. Ca sa ne referim
//la o variabila statica, sintaxa recomandata este NumeClasa::numeMembru.
//vom discuta pe larg membrii statici ai unei clase in urmatorul seminar
    static int nrEchipe;

//initializarea (atribuirea unei valori initiale) pt variabilele statice 
//se face in afara clasei  


//functia citireLot(), private deoarece nu vrem sa fie apelata decat din constructor
    void citireLot(){
        cout<<"Cati jucatori are lotul echipei "<<this->nume<<"? "<<endl;
        cin>>this->nrJucatori;
//ignoram spatiul pe care l-am introdus in consola prin apasarea enter dupa numarul de jucatori


        cin.ignore(1,'\n');
        this->lot=new string[this->nrJucatori];
        for (size_t i = 0; i < this->nrJucatori; i++)
        {
            cout<<"Jucatorul "<<(i+1)<<": ";
            getline(cin,lot[i]);            
        }
    }

//membrii publici ai clasei
public:

//constructorul clasei (+2 supraincarcari)

//constructorul cu 2 parametri   
    EchipaDeFotbal(string nume, int nrpuncte):nume{nume}, puncte(nrpuncte){
        citireLot();
//la crearea unei echipe noi, crestem numarul de echipe
        nrEchipe++;
    }
//constructorul cu 1 parametru, care creaza si initializeaza obiectul prin apelearea constructorului cu 2 parametri (nume,0)
//procedeul se numeste constructor delegation; 
    
    EchipaDeFotbal(string nume):EchipaDeFotbal(nume,0){
        
    }
    EchipaDeFotbal(){
        nume="";
        nrJucatori=0;
        lot=NULL;

    }

//encapsluarea variabilelor, folosind gettere si settere

    string getNume(){
        return this->nume;
    }

    int getPuncte(){
        return this->puncte;
    }

    string* getLot(){

        return this->lot;

    }
    int getNrJucatori(){

        return this->nrJucatori;
    }

    void setLot(string* lot){

        this->lot=lot;
    }

//functia care afiseaza informatii despre obiectul curent

    void status(){
        cout<<"***********************************"<<endl;
        cout<<"Nume echipa: "<<this->nume<<endl;
        cout<<"Nr. puncte: "<<this->puncte<<endl;
        cout<<"Lot: "<<endl;
        for (size_t i = 0; i < nrJucatori; i++)
            cout<<this->lot[i]<<endl;
        cout<<"***********************************"<<endl;
    }

//declararea unei functii statice a clasei; o functie statica, la fel ca o variabila statica, 
//este asociata intregii clase, nu fiecarui obiect in parte. Pentru apelarea unei functii statice,
//se foloseste sintaxa NumeClasa::NumeFunctie(); 
    static int getNrEchipe();

//functiile statice trebuie definite in afara clasei


//FOARTE IMPORTANT
//In continuare, avem trei functii de interactiune intre obiecte de tip EchipaDeFotbal, pentru a exemplifica 
//diferenta de comportament a parametrilor, dupa modul de transmitere (prin obiect, prin pointer sau prin referinta).
//Codul functiilor este acelasi, singura diferenta este modalitatea de transmitere a parametrului


// Varianta 1: prin obiect (primeste ca argument obiectul si face o copie a acestuia, pe care o foloseste in cadrul functiei)
// Consecinta: deoarece modificarile se fac pe o copie a argumentului, nu pe argumentul in sine,
// MODIFICARILE NU VOR FI VAZUTE IN AFARA FUNCTIEI (nu se modifica argumentul, ci copia utilizata in functie)
    void meci1(EchipaDeFotbal e1){
        int result=rand()%3;
        switch(result){
            case 0: this->puncte+=3; cout<<this->nume<<" a castigat meciul cu "<<e1.nume; break;
            case 1: e1.puncte+=1; this->puncte+=1; cout<<this->nume<<" a terminat la egalitate meciul cu "<<e1.nume; break;
            case 2: e1.puncte+=3; cout<<e1.nume<<" a castigat meciul cu "<<this->nume; break;
        }
        cout<<endl;
    }

// Varianta 2: prin pointer (primeste ca argument adresa unui obiect)
// Consecinta: MODIFICARILE SUNT VAZUTE IN AFARA FUNCTIEI
    void meci2(EchipaDeFotbal *e1){
        int result=rand()%3;
        switch(result){
            case 0: this->puncte+=3; cout<<this->nume<<" a castigat meciul cu "<<e1->nume; break;
            case 1: e1->puncte+=1; this->puncte+=1; cout<<this->nume<<" a terminat la egalitate meciul cu "<<e1->nume; break;
            case 2: e1->puncte+=3; cout<<e1->nume<<" a castigat meciul cu "<<this->nume; break;
        }
        cout<<endl;
    }
// daca nu dorim posibilitatea modifcarii atributelor parametrului, il declaram const - meci2(const EchipaDeFotbal *e1)

// Varianta 3 (IN GENERAL, ESTE VARIANTA PREFERATA DE TRANSMITERE A PARAMETRILOR): PRIN REFERINTA (primeste ca argument adresa unui obiect)
// Consecinta: MODIFICARILE SUNT VAZUTE IN AFARA FUNCTIEI

    void meci3(EchipaDeFotbal &e1){
        //se stabileste random rezultatul (0 - victorie gazde, 1 - egal, 2 - victorie oaspeti)
        int result=rand()%3;
        switch(result){
            case 0: this->puncte+=3; cout<<this->nume<<" a castigat meciul cu "<<e1.nume; break;
            case 1: e1.puncte+=1; this->puncte+=1; cout<<this->nume<<" a terminat la egalitate meciul cu "<<e1.nume; break;
            case 2: e1.puncte+=3; cout<<e1.nume<<" a castigat meciul cu "<<this->nume; break;
        }
        cout<<endl;
    }
// daca nu dorim posibilitatea modifcarii atributelor parametrului, il declaram const - meci3(const EchipaDeFotbal &e1)


//ACELEASI PRINCIPII DE LA TRANSMITEREA PARAMETRILOR UNEI FUNCTII SE APLICA SI LA TRANSMITEREA 
//REZULTATULUI UNEI FUNCTII (return type). Aici trebuie facuta distinctia importanta intre
//doua cazuri, transmiterea prin valoare sau prin referinta. Vom exemplifica, implementand doua variante ale urmatoarei functii:

//functia getPlayer(i) trebuie sa returneze jucatorul al i-lea din lot (incepand cu 0)

//Varianta 1: transmiterea prin valoare
string getPlayer1(int i){
    return this->lot[i];
}

//Varianta 2: transmiterea prin referinta
string& getPlayer2(int i){
    return this->lot[i];
}

//se observa ca singura diferenta intre cele doua implementari este un & adaugat la tipul de data returnat al functiei
//varianta fara & implica transmiterea rezultatului prin valoare, cea cu & implica transmiterea prin referinta
//DPDV al comportamentului, diferenta este FOARTE IMPORTANTA: 
//daca transmitem prin valoare, se face o copie a obiectului din functie, care este returnata, deci nu ne referim la acelasi obiect
//ca in interiorul functiei.
//daca transmitem prin referinta, se returneaza o referinta catre obiectul din functie, deci ne referim la acelasi obiect
//ca in interiorul functiei
//CONCLUZIE: daca dorim doar utilizarea valorii returnate de functie, nu conteaza ce varianta alegem, dar daca dorim
//sa putem modifica this->lot[i] folosind getPlayer(i), trebuie sa folosim varianta a doua (transmiterea prin referinta)




//Urmatoarele trei declaratii (destructor, constructor de copiere, supraincarcarea operatorului =) NU AU FOST DISCUTATE INCA LA SEMINAR! 


//Daca obiectul (clasa) nu contine atribute alocate dinamic, nu sunt necesare aceste trei declaratii
//Daca obiectul (clasa) contine atribute alocate dinamic (cum este cazul nostru - atributul lot), atunci trebuie implementat 
//destructorul, pentru a dezaloca memoria utilizata de atributele dinamice (atunci cand se distruge un obiect, se apeleaza destructorul)
//In C++ exista o regula foarte importanta, numita "Rule of 3", care spune faptul ca, daca intr-o clasa se implementeaza
//vreuna dintre cele trei (destructor, constructor de copiere, supraincarcarea operatorului =), atunci, OBLIGATORIU,
//TREBUIE IMPLEMENTATE SI CELELALTE DOUA. Vom discuta la seminar de ce exista aceasta regula


//constructorul de copiere, se foloseste pentru a crea o copie a unui obiect de tip EchipaDeFotbal
// il vom discuta pe larg in urmatorul seminar
    
    EchipaDeFotbal(const EchipaDeFotbal& e):nume(e.nume),puncte(e.puncte),nrJucatori(e.nrJucatori){
        if (e.lot!=NULL){
        this->lot=new string[this->nrJucatori];
            for (size_t i = 0; i < this->nrJucatori; i++)
                this->lot[i]=e.lot[i];
        }
        nrEchipe++;
    }

//destructorul clasei. Se apeleaza atunci cand se distruge (se sterge din memorie) un obiect de tipul EchipaDeFotbal
//in general, in destructor se dezaloca spatiul alocat dinamic in cadrul aplicatiei
// il vom discuta pe larg in urmatorul seminar
    ~EchipaDeFotbal(){
//aici dezalocam spatiul de memorie alocat pentru pointer-ul lot
        delete[] lot;
//scadem numarul echipelor
        nrEchipe--;
    }

//In c++, la fel cum se pot supraincarca functiile, se pot supraincarca si anumiti operatori (=,+,-,[],etc). 
//Asta inseamna, practic, ca implementam noi ceea ce dorim sa se intample cand se foloseste respectivul operator


//supraincarcare assignment operator (=). Operatorul = se foloseste de fiecare data cand se atribuie o valoare unui
//obiect de tipul EchipaDeFotbal
//utilizam const in declararea parametrului pentru a asigura faptul ca acesta nu este modificat dupa apelarea operatorului =
//adica, cand zicem a=b, vrem sa ne asiguram ca b nu se modifica
//il vom discuta pe larg in urmatorul seminar
    EchipaDeFotbal operator = (const EchipaDeFotbal& e){
        this->nume=e.nume;
        this->puncte=e.puncte;
        this->nrJucatori=e.nrJucatori;
        delete[] this->lot;
        if (e.lot!=NULL){
            this->lot=new string[this->nrJucatori];
            for (size_t i = 0; i < this->nrJucatori; i++)
                this->lot[i]=e.lot[i];
        }

        return *this;

    }



//daca, de exemplu, avem un obiect e de tipul EchipaDeFotbal si dorim sa ne referim la jucatorul numarul i din echipa cu e[i]
//nu doar cu variantele e.lot[i] sau e.getPlayer2(i), putem supraincarca operatorul []: 

    string& operator [](int i){
        return this->lot[i];

    }

friend ostream& operator <<(ostream& os, EchipaDeFotbal& e);
friend istream& operator >>(istream& is, EchipaDeFotbal& e);
};

//in general, membrii unei clase pot fi definiti/initializati in interiorul sau in afara clasei, mai putin
//cei statici, care. obligatoriu, trebuie definiti/initializati in afara clasei
//vom discuta diferentele in urmatorul seminar
//initializarea variabilei statice, obligatoriu in afara clasei
int EchipaDeFotbal::nrEchipe=0;

//definirea functiei statice, obligatoriu in afara clasei
int EchipaDeFotbal::getNrEchipe(){
   
    return EchipaDeFotbal::nrEchipe;
}

ostream& operator <<(ostream& os, EchipaDeFotbal& e){
    cout<<e.getNume()<<" "<<e.getPuncte()<<" "<<e.getNrJucatori()<<" ";
    for (size_t i = 0; i < e.getNrJucatori(); i++)
        cout<<e.lot[i]<<" ";
    return os;
    
}
istream& operator >>(istream& is, EchipaDeFotbal& e){
    cin>>e.nume>>e.puncte>>e.nrJucatori;
    delete[] e.lot;
    e.lot=new string[e.getNrJucatori()];
    for (size_t i = 0; i < e.getNrJucatori(); i++)
        cin>>e.lot[i];
    return is;
}


//functie driver pentru exemplificarea manipularii obiectelor

void play(){
    
//crearea unui obiect folosind constructorul cu 2 parametri
    EchipaDeFotbal e1("Depunctatii",-3);
//crearea unui obiect folosind constructorul cu 1 parametru
    EchipaDeFotbal e2("Foresta Falticeni");
//declararea, definirea si initializarea unei referinte catre e1. 
//Acum, e1 si e1Ref se refera la acelasi obiect (e1), iar e2 si e2Ref se refera la acelasi obiect e2
//NOTA: Odata atribuita, o referinta nu mai poate fi reatribuita (va referi acelasi obiect pe toata durata vietii respectivei referinte)
    EchipaDeFotbal &e1Ref=e1, &e2Ref=e2;
//declararea, definirea si initializarea unor pointeri catre e1, respectiv catre e2. 
//Acum, e1 si e1Ptr se refera la acelasi obiect (e1), iar e2 si e2Ptr se refera la acelasi obiect e2
    EchipaDeFotbal *e1Ptr=&e1, *e2Ptr=&e2;

//pentru referinte se foloseste aceeasi sintaxa ca pentru obiect (. pentru accesarea membrilor)
//pentru pointer se foloseste -> pentru a accesa membrii. e2Ptr->status este echivalent cu (*e2Ptr).status()
//Cele doua abordari (transmiterea prin referinta sau prin pointer) sunt similare dpdv tehnic, dar se prefera utilizarea
//variantei prin referinta (vom discuta la seminar de ce)

//testarea trimiterii parametrilor prin valoare - meci1
    cout<<"---------------------------------------------";cout<<endl;
    for (int i = 0; i < 10; i++)
        e1.meci1(e2);
    cout<<endl;
    cout<<"---------------------------------------------";cout<<endl;
    cout<<"Se observa ca, dupa cele 10 apeluri ale functiei meci1(), numarul de puncte ale lui e2 nu a fost modificat (ramane 0)";
    cout<<endl;
    cout<<"---------------------------------------------";cout<<endl;
    e1.status();
    e2.status();

//testarea trimiterii parametrilor prin pointer - meci2

    cout<<"---------------------------------------------"; cout<<endl;
    for (int i = 0; i < 10; i++)
        e1.meci2(&e2);

    cout<<endl;
    cout<<"---------------------------------------------";cout<<endl;
    cout<<"Se observa ca, dupa cele 10 apeluri ale functiei meci2(), numarul de puncte ale lui e2 se modifica, datorita transmiterii parametrului prin pointer";
    cout<<endl;
    cout<<"---------------------------------------------";cout<<endl;
    e1.status();
    e2.status();

//testarea trimiterii parametrilor prin referinta - meci3
    cout<<"---------------------------------------------"; cout<<endl;
    for (int i = 0; i < 10; i++)
        e1.meci3(e2);

    cout<<endl;
    cout<<"---------------------------------------------";cout<<endl;
    cout<<"Se observa ca, dupa cele 10 apeluri ale functiei meci3(), numarul de puncte ale lui e2 se modifica, datorita transmiterii parametrului prin referinta";
    cout<<endl;
    cout<<"---------------------------------------------";cout<<endl;
    e1.status();
    e2.status();
    cout<<"---------------------------------------------";cout<<endl;


//folosim operatorul supraincarcat [] pentru a schimba numele unui jucator din lot
    e2[0]="Portarus";
    e2.status();

//daca folosim getPlayer1(0), obiectul returnat este o copie a e2.lot[0], deoarece functia returneaza prin valoare,
//deci modificarile se fac pe copie, nu pe obiectul original e2.lot[0] => e2.lot[0] NU SE MODIFICA
    e2.getPlayer1(0)="Portar Portarovici";
    e2.status();

//daca folosim getPlayer2(0), obiectul returnat este o referinta catre obiectul original e2.lot[0],
// deoarece functia returneaza prin referinta, deci modificarile se fac chiar pe obiectul original e2.lot[0] => e2.lot[0] SE MODIFICA
    e2.getPlayer2(0)="Portarus Modificatus";
    e2.status();

    cout<<"in campionat s-au inscris "<<EchipaDeFotbal::getNrEchipe()<<" echipe";

    EchipaDeFotbal e3;
    cout<<"acu"<<endl;
    cin>>e3;
    cout<<e3;
    e3.status();

}


//functia main, care pur si simplu apeleaza functia play
//vom discuta la urmatorul seminar de ce am folosit aceasta abordare si nu am scris direct
//codul in functia main

int main(){

    play();





}