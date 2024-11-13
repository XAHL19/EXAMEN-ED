#include <iostream>
#include <malloc.h>
using namespace std;

struct nodo{
    int edad;
    int identificacion;
    nodo *izq;
    nodo *der;
};

struct nodo *raiz, *aux, *aux2, *padre, *sucesor;

int posicionar(){    
    if(aux->edad < aux2->edad){        
        if(aux2->izq==NULL){
            aux2->izq = aux;            
            return 0;
        }
        else {
            aux2 = aux2->izq;
            posicionar();
        }
    } 
    else {
        if(aux2->der==NULL){
            aux2->der = aux;            
            return 0;
        } else {
            aux2 = aux2->der;
            posicionar();
        }
    }
}

int registrar(){
    aux = ((struct nodo *) malloc (sizeof(struct nodo))); 
    cout<<"Ingrese la edad del paciente: "<<endl;
    cin>>aux->edad;
    cout<<"Ingrese el numero de identificacioln del paciente: "<<endl;
    cin>>aux->identificacion;
    aux->izq = aux->der = NULL;
    if(!raiz){
        raiz = aux;
        aux = NULL;
        free(aux);
    }
    else {        
        aux2 = raiz;
        posicionar();
        aux = NULL;
        free(aux);
    }
    
    return 0;
}

int recorrer(nodo *a) {
     
    if(a->der!=NULL){
        recorrer(a->der);
    }
    cout<<"La edad del paciente es: "<<a->edad<<endl;
    cout<<"Su Identificacion es: "<<a->identificacion<<endl; 
    cout<<"--------------------------"<<endl; 
    
    if(a->izq!=NULL){
        recorrer(a->izq);
    }
    
    return 0;
}

int mostrar(){
    if(raiz){        
        recorrer(raiz);
    }
}
int ubicar(nodo *a, int aguja){
    if(a->identificacion==aguja){
        aux2 = a;
        return 1;
    } else {
        if(a->izq!=NULL){
            ubicar(a->izq, aguja);
        } 
        
        if(a->der!=NULL){
            ubicar(a->der, aguja);
        }         
    }
    return 0;
}

int buscar(int aguja){
    aux = NULL;
    if(raiz!=NULL){
        aux = raiz;
        ubicar(aux, aguja);
    }
}
int pedirAguja(){
    aux2 = NULL;
    int dato;
    cout<<"Paciente a buscar"<<endl;
    cin>>dato;
    buscar(dato);
    if(aux2){
        cout<<"El paciente es: "<<endl;
        cout<<"Su Identificacion es: "<< aux2->identificacion <<endl;
        cout<<"Su edad es: "<< aux2->edad <<endl;
    } else {
        cout<<"El paciente no se encontro"<<endl;
    }
}

int ubicarPadre(nodo *a){
    if((a->izq==aux2)||(a->der==aux2)){
        padre = a;
    }
    else {
        if(a->izq!=NULL){
            ubicarPadre(a->izq);
        } 
        
        if(a->der!=NULL){
            ubicarPadre(a->der);
        }         
    }
    return 0;
}

int casoUno(){
    if (aux2!=raiz){
        ubicarPadre(raiz);
    }
    if(padre->izq==aux2){
        padre->izq=NULL;
    }
    else{
        padre->der=NULL;
    }
    free(aux2);
    return 0;

}
int casoDos(){
    if (aux2!=raiz){
        ubicarPadre(raiz);
    }
    if(padre->izq==aux2){
        if(padre->izq!=NULL)
            padre->izq=aux2->izq;
            else if(padre->der!=NULL)
                padre->izq=aux2->der;
    }
    else if(padre->der==aux2){
       if(padre->izq!=NULL)
            padre->der=aux2->izq;
            if(padre->der!=NULL)
                padre->der=aux2->der;
    }
    free(aux2);
    return 0;
}

nodo* ubicarSucesor(nodo* e){
    aux = e->der;
    while(aux && aux->izq !=NULL){
        aux=aux->izq;
    }
    return aux; 
}


int eliminar(){
    int numero;  
    cout<<"Ingrese la identificacion del paciente a eliminar"<<endl;
    cin>>numero;
    cout<<"---------------------------------------"<<endl;
    ubicar(raiz, numero);
    if ((aux2->der ==NULL)&&(aux2->izq==NULL)){
        casoUno();
    }
    else if(((aux2->der ==NULL)&&(aux2->izq!=NULL))||((aux2->der !=NULL)&&(aux2->izq==NULL))){
        casoDos();
    }
    else{
        nodo* sucesor = ubicarSucesor(aux2);
        aux2->edad= sucesor->edad;
        aux2->identificacion=sucesor->identificacion;
        aux2=sucesor;
        if((sucesor->izq==NULL)&&(sucesor->der==NULL)){
            casoUno();
        } 
        else{
            casoDos();
        }
    }
    return 0;
}


int main(){
    int opc;
    do{
        cout<<"---Gestion de pacientes---"<<endl;
        cout<<"Seleccione una opcion: "<<endl;
        cout<<"1. Registrar"<<endl;
        cout<<"2. Mostrar"<<endl;
        cout<<"3. Buscar"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Salir"<<endl;
        cin>>opc;
        switch(opc){
            case 1: registrar(); break;
            case 2: mostrar(); break;
            case 3: pedirAguja(); break;
            case 4: eliminar(); break;
            }
    }while(opc!=5);
    return 0;
}
