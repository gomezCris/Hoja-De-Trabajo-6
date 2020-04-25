/*

*/
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <iomanip>      // std::setw
#include <vector>
#include <algorithm>    // std::max

using namespace std;

struct cuadernos{
  string descripcion;
  float precio;
  int cantidad;
} cuaderno[4];

struct lectura{
  int dia;
  int modelo;
  int cantidad;
};

vector<lectura> registro;


void pausar_pantalla(){
      // Pause
    string empty;
    cout << "\nPresione cualquier tecla para continuar \n";
    getline(cin,empty);
};

void limpiar_pantalla(){
  // limpiamos pantalla
  cout << "\033[2J\033[0;0H";
}

void iniciar_variables(){
  // lista de Cuadernos
  cuaderno[0]={"Modelo#1",10,0};
  cuaderno[1]={"Modelo#2",15,0};
  cuaderno[2]={"Modelo#3",18.50,0};
  cuaderno[3]={"Modelo#4",25,0};
  // Limpio el vector de registro
  registro.clear();
};

void ingresar(){
  int dia, modelo, cantidad;
  bool centinela=false;
  
  while (centinela==false) {
  cout << "Ingrese el dia de la venta: ";
  cin >> dia;
    // comprombamos si el dia esta en los parametros 1 al 31
    if (dia>=1 and dia<=31) {
      centinela=true;
    } else {
      centinela=false;
    }
  }
  centinela=false;
  
  while (centinela==false) {
    cout << "Ingrese el modelo del cuaderno: ";
    cin >> modelo;
    modelo=modelo-1;
    
    // comparamos que el modelo si este en el rango de la lista
    if (modelo>=0 and modelo<=3) {
      centinela=true;
    } else {
      cout << "El modelo ingresado no es valido, intente de nuevo"<< endl;
      centinela=false;
    }
  }
  
    cout << "Ingrese la cantidad de ventas del cuaderno: ";
    cin >> cantidad;
    
  ofstream archivo;
  try {
    archivo.open("archivo.txt",ios::app);

    archivo<<dia<<","<<modelo+1<<","<<cantidad<<endl;

    archivo.close();
  } catch(exception X){
		cout<<"Error en la manipulacion del archivo"<<endl;
		
    // Esto es una pausa para ingresar enter
    cout << "Presione enter para continuar.... "<< endl;
  
    pausar_pantalla();
    limpiar_pantalla();
	};
}

void leer_archivo_a_memoria(){
  lectura x;
  ifstream archivo; // Creamos el objeto
  string input;
  try {
    archivo.open("archivo.txt", ios::in);

    while(!archivo.eof()){
      getline(archivo,input,','); //Obtengo el primer string
			x.dia = atoi(input.c_str()); // Lo convierto en integer
      getline(archivo,input,',');
			x.modelo = atoi(input.c_str());
      getline(archivo,input,'\n');
			x.cantidad = atoi(input.c_str());
      
      // Lo almacenamos en un vector;
      if (x.dia !=0 and x.modelo != 0 and x.cantidad !=0){
        registro.push_back(x);
      }
      
    }
    
    // cierro el archivo.
    archivo.close();
  }
  catch (exception X){
    cout<<"Error en la manipulacion del archivo"<<endl;
    pausar_pantalla();
    limpiar_pantalla();
  }
};

void mostrar(){
  limpiar_pantalla();
  registro.clear();
  leer_archivo_a_memoria();
  cout << "Día " <<"\t" <<"Modelo" <<"\t"<<"Cantidad"<<endl;
  cout << "------------------------------" << endl;
  for (int i=0; i<registro.size(); i++){
    cout << registro[i].dia  << setw(8) << registro[i].modelo << setw(10) << registro[i].cantidad << "\n";
  }
  cin.ignore();
  pausar_pantalla();


};



void memoria_a_archivo(){
  ofstream archivo;
  archivo.open("archivo.txt", ios::out);

  // pasamos de la memoria al archivo.
  for (int i=0; i<registro.size(); i++){
    // Si es distinto de  0 en el archivo no lo graba
    if (registro[i].dia != 0 and registro[i].modelo != 0 and registro[i].cantidad != 0){
      archivo << registro[i].dia <<","<<registro[i].modelo<<","<<registro[i].cantidad<<"\n";
    }
    
  }

  //Cerrramos el archivo.
  archivo.close();
}

void calculo(){
  registro.clear();
  int modelo1, modelo2, modelo3, modelo0;
  float total1, total2, total3, total0;
  leer_archivo_a_memoria();
  
  int modelo;
  
  // Contamos cuantos modelos se vendieron en total
  for (int i=0; i<registro.size(); i++){
    modelo=registro[i].modelo-1;
    cuaderno[modelo].cantidad+=registro[i].cantidad;
  }

  float total=0;
  for (int i=0; i<4; i++){
    total=((cuaderno[i].precio*cuaderno[i].cantidad));
    cout << "Total recaudado por "<< cuaderno[i].descripcion <<" es de: Q." << total<< "\n";
  }

  int mayor;
  if (cuaderno[0].cantidad>cuaderno[1].cantidad and cuaderno[0].cantidad>cuaderno[2].cantidad and cuaderno[0].cantidad>cuaderno[3].cantidad) {
    mayor=0;
  } else if  
    (cuaderno[1].cantidad>cuaderno[2].cantidad and cuaderno[1].cantidad>cuaderno[3].cantidad and cuaderno[1].cantidad>cuaderno[0].cantidad) {
    mayor=1;
  }
   else if  
    (cuaderno[2].cantidad>cuaderno[3].cantidad and cuaderno[2].cantidad>cuaderno[0].cantidad and cuaderno[2].cantidad>cuaderno[1].cantidad) {
    mayor=2;
  } else{
    mayor=3;
  }

  cout << "El modelo mas vendidco es: " << cuaderno[mayor].descripcion << "\n";
      cout <<"Con la cantidad de: " << cuaderno[mayor].cantidad << " Unidades vendidas" << "\n";

}

void modificar(){
  mostrar();
  int dia, modelo, cantidad;
  cout << "Ingrese el dia: ";
  cin >> dia;
  cout << "Ingrese modelo: ";
  cin >> modelo;
  cout << "Ingrese la nueva cantidad: ";
  cin >> cantidad;
  
  int position=0;
  bool encontrado=false;
  
  for (int i=0; i<registro.size(); i++){
    if(registro[i].dia==dia and registro[i].modelo==modelo) {
      position=i;
      encontrado=true;
    } else {
      encontrado=false;
    }

  }
  
  if (encontrado==true){
    registro[position].cantidad=cantidad; // Eliminamos el 
  } else {
    cout << "Ingreso un dato incorrecto" << endl;
    pausar_pantalla();
  }
  //registro de la memoria.
  memoria_a_archivo();
  mostrar();
  return;
};

void eliminar(){
  mostrar();
  int dia, modelo;
  cout << "Ingrese el dia: ";
  cin >> dia;
  cout << "Ingrese modelo: ";
  cin >> modelo;
  bool encontrado=false;
  int position=0;
  
  for (int i=0; i<registro.size(); i++){
    if(registro[i].dia==dia and registro[i].modelo==modelo) {
      position=i;
      encontrado=true;
    } else {
      encontrado=false;
    }

  }
  
  if (encontrado==true){
    registro.erase(registro.begin() + position); // Eliminamos el 
  } else {
    cout << "Ingreso un dato incorrecto" << endl;
    pausar_pantalla();
  }
  //registro de la memoria.
  memoria_a_archivo();
  mostrar();
  return;
};

void mp(){
	int resp;
	do {
    // limpiamos pantalla
    limpiar_pantalla();
		cout<<"--------------------------"<<"\n";
		cout<<" Menu Principal"<<"\n";
		cout<<"-------------------"<<"\n";
		cout<<" 1 - Ingresar registro "<<"\n";
		cout<<" 2 - Reporte "<<"\n";
    cout<<" 3 - Modificar"<<"\n";
		cout<<" 4 - Eliminar"<<"\n";
    cout<<" 5 - Salir"<<"\n";
		cout<<"--------------------------"<<"\n";
		cout<<" Seleccione su opcion: ";
		cin>>resp;
		if (resp==1){		
			  // limpiamos pantalla
      limpiar_pantalla();
			ingresar();			
		}
		else if (resp==2){		
      mostrar();
      calculo();
      pausar_pantalla();
		}
    else if (resp==3){		
      modificar();
		}
    else if (resp==4){		
      eliminar();
		}
		else if (resp==5)
			break;
		else 
			break;
		
	} while(resp!=5);	
};


int main(){
  iniciar_variables();
  mp();
  return 0;
};
