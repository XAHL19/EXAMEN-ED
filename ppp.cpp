#include <iostream>
#include <malloc.h>
using namespace std;

struct nodo{ // parqueadero
    string vehiculo;
    int valor;

    nodo*sig;
};

struct nodo *top, *top2, *aux;

int ingresos = 0;

int registrar(){
    aux=((struct nodo *)malloc(sizeof(struct nodo)));
    int vehic;
    cout<<"Registrar el vehiculo (carro o moto): "<<endl;
    cout<<"1. Carro"<<endl;
    cout<<"2. Moto"<<endl;
    cin>>vehic;
    if (vehic==1) {
        aux->vehiculo="Carro";
    } else if (vehic==2) {
        aux->vehiculo="Moto";
    } else {
        cout<<"No es una opcion"<<endl; 
        free(aux);
        return 0;   
    }
    aux->valor = 0;

    if(aux->vehiculo=="Carro") {
        aux->sig=top;
        top=aux;
    } else {
        aux->sig=top2;
        top2=aux;
    }
    cout<<aux->vehiculo<<"Vehiculo registrado"<<endl;
    aux=NULL;
    return 0;
}

int mostrar(){
    cout<<"los vehiculos son: "<<endl;
    while(top!=NULL){
        cout<<top->vehiculo<<endl;
        if(top2==NULL){
            top2=top;
            top=top->sig;
            top2->sig=NULL;
        }
        else{
            aux=top;
            top = top->sig;
            aux->sig = top2;
            top2=aux;
            aux= NULL;
        }
    }
    while(top2!=NULL){
        cout<<top2->vehiculo;
        if(top==NULL){
            top=top2;
            top2=top2->sig;
            top->sig=NULL;
        }
        else{
            aux=top2;
            top2=top2->sig;
            aux->sig=top;
            top=aux;
            aux=NULL;
        }
    }
     return 0;   
}
int cambiar() {
    int a;
     cout<<"Registrar el vehiculo a cambiar (carro o moto): "<<endl;
    cout<<"1. Carro"<<endl;
    cout<<"2. Moto"<<endl;
    cin>>a;
     nodo *top=(a==1) ? top : top2;

    if (!top) {
        cout<<((a==1) ? "No hay carros registrados" : "No hay motos registradas")<<endl;
        return 0;
    }

    top->valor++;
    cout << top->vehiculo << " Vehiculo cambiado: Movimientos: "<<top->valor<<endl;
    return 0;
}

int eliminar(){
int e;
    cout<<"Registrar el vehiculo a eliminar (carro o moto): "<<endl;
    cout<<"1. Carro"<<endl;
    cout<<"2. Moto"<<endl;
    cin>>e;

    nodo *top = (e==1) ? top : top2;

    if (!top) {
        cout<<((e==1) ? "No hay carros registrados" : "No hay motos registradas")<<endl;
        return 0;
    }

    aux=top;
    if (e==1) {
        top=top->sig;
    } else {
        top2=top2->sig;
    }

    int tarifa=(aux->vehiculo == "Carro" ? 2000 : 1000) + (aux->valor * 100);
    ingresos += tarifa;

    cout<<aux->vehiculo <<" Tarifa de vehiculo retirado: $"<<tarifa<<endl;
    free(aux);
    aux = NULL;
    return 0;
}
int ingresosTotales(){
    cout<<"Ingresos totales: $"<<ingresos<<endl;
    return 0;

}

int main(){
    int opc;
    do{
        cout<<"PARQUEADERO"<<endl;
        cout<<"1. Registrar"<<endl;
        cout<<"2. Mostrar"<<endl;
        cout<<"3. Movimientos"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Total de ingresos"<<endl;
        cout<<"6. Salir"<<endl;
        cin>>opc;

        switch(opc){
            case 1: registrar(); break;
            case 2: mostrar(); break;
            case 3: cambiar(); break;
            case 4: eliminar(); break;
            case 5: ingresosTotales();break;
        }
    }
    while (opc!=6);
    return 0;
}