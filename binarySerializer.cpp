
#include <fstream>
#include <string>
#include <iostream>

using namespace std;


class MasinaSerializationTest{
    string marca="";
    char *model=NULL;
    int cp=0;
    int nrAccesorii=0;
    int *listaAccesorii=NULL;

public:

    MasinaSerializationTest(){}

    MasinaSerializationTest(string marca, const char* model, int cp, int nrAccesorii, int*listaAccesorii){
        this->marca=marca;
        this->model=new char[strlen(model)+1];
        strcpy(this->model,model);
        this->cp=cp;
        this->nrAccesorii=nrAccesorii;
        this->listaAccesorii=listaAccesorii;


    }


    void deserialize(string filename){
        ifstream file (filename, ifstream::binary);
        if (file.is_open()){
            int lungimeMarca=0;
            
            file.read((char*)&lungimeMarca,sizeof(int));
            // cout<<endl<<lungimeMarca<<endl;
            char temp[100];
            file.read(temp,lungimeMarca);
            this->marca=string(temp);
            // cout<<endl<<this->marca<<endl;
            int lungimeModel=0;
            file.read((char*)&lungimeModel,sizeof(int));
            // cout<<endl<<lungimeModel<<endl;
            if (this->model!=NULL)
                delete[] this->model;
            this->model=new char[lungimeModel];
            file.read(this->model,lungimeModel);
            // cout<<endl<<this->model<<endl;
            file.read((char*)&this->cp,sizeof(int));
            // cout<<endl<<this->cp<<endl;
            file.read((char*)&this->nrAccesorii,sizeof(int));
            // cout<<endl<<this->nrAccesorii<<endl;
            if (this->listaAccesorii!=NULL)
                delete[] this->listaAccesorii;
            this->listaAccesorii=new int[this->nrAccesorii];
            for (int i = 0; i < this->nrAccesorii; i++)
                file.read((char*)&this->listaAccesorii[i],sizeof(int));
                
        }

        file.close();


    }
    void serialize(string filename){

        ofstream file (filename, ifstream::binary);
        if (file.is_open()){
            int lungimeMarca=this->marca.length()+1;
            file.write((char*)&lungimeMarca,sizeof(int));
            file.write(this->marca.c_str(),lungimeMarca);
            int lungimeModel=strlen(this->model)+1;
            file.write((char*)&lungimeModel,sizeof(int));
            file.write(this->model,lungimeModel);
            file.write((char*)&this->cp,sizeof(int));
            file.write((char*)&this->nrAccesorii,sizeof(int));

            for (int i = 0; i < this->nrAccesorii; i++)
                file.write((char*)&this->listaAccesorii[i],sizeof(int));
        }

        file.close();

    }
    friend ostream& operator <<(ostream&,MasinaSerializationTest&);
};

ostream& operator <<(ostream& os,MasinaSerializationTest& m){
    cout<<endl<<m.marca<<endl<<(m.model==NULL?"":m.model)<<endl<<m.cp<<endl<<m.nrAccesorii;
    for (int i = 0; i < m.nrAccesorii; i++)
    {
        cout<<endl<<m.listaAccesorii[i];
    }
    


    return os;
}

int main(){


    int* la=new int[3]{4,1,255};
    MasinaSerializationTest m("Mercedes", "C-Class", 170,3,la);
    m.serialize("test.txt");
    MasinaSerializationTest m2;
    cout<<m2;
    m2.deserialize("test.txt");
    cout<<m2;





}