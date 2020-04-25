/*			EJERCICIO 2

Realice un programa que, dado el peso, la altura, la edad y el g�nero (M/F) de un grupo de N personas
que pertenecen a un departamento de la rep�blica, obtenga un promedio de peso, altura y edad de esta
poblaci�n. Los datos deben guardarse de forma ordenada por edad en un archivo de datos. As� mismo
el programa debe ser capaz leer los datos del archivo y generar un reporte con la media del peso, altura
y la edad.

*/
//Importaci�n de librer�as
#include <fstream> 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//creaci�n de estructura de tipo persona
struct persona{
	int edad;
	char genero;
	float altura;
	float peso;
};

//funci�n encargada de ordenar los registros en el archivo tomando c�mo �ndice el campo Edad
void ordenarArchivo(){
	persona temporalPersonas;
	vector<persona> vectorRegistros;


	ifstream archivoLectura;
	archivoLectura.open("HT6_EJERCICIO_02.txt",ios::in);
	
	while(archivoLectura>>temporalPersonas.edad>>temporalPersonas.genero>>temporalPersonas.altura>>temporalPersonas.peso){
    	vectorRegistros.push_back(temporalPersonas);
	};
	
  
  archivoLectura.close();
  
  for(int i=0; i<vectorRegistros.size(); i++) {
   for(int j=i+1; j<vectorRegistros.size(); j++)
   {

      if(vectorRegistros[j].edad < vectorRegistros[i].edad) {
         temporalPersonas = vectorRegistros[i];
         vectorRegistros[i] = vectorRegistros[j];
         vectorRegistros[j] = temporalPersonas;
      }
   }
  } 

    ofstream archivoNuevo;
    archivoNuevo.open("HT6_EJERCICIO_02.txt",ios::out);
    
    for (int i=0; i<vectorRegistros.size(); i++){
      archivoNuevo << vectorRegistros[i].edad <<"\t"<< vectorRegistros[i].genero <<"\t"<< vectorRegistros[i].altura <<"\t"<< vectorRegistros[i].peso <<endl;
    }
    
    archivoNuevo.close();	
}

//Funci�n para el registro de personas
void registroPersonas(){
	bool finalizar = false;
	char registrar;
	persona strPersona;
	
	cout << "---------REGISTRO DE PERSONA---------" << endl;
	
	do{
		cout << "Ingrese la edad de la persona" << endl;
		cin >> strPersona.edad;
		
		cout << "Ingrese el g�nero de la persona (M/F)" << endl;
		cin >> strPersona.genero;
		
		strPersona.genero = toupper(strPersona.genero);
		
		cout << "Ingrese la altura de la persona" << endl;
		cin >> strPersona.altura;
		
		cout << "Ingrese el peso de la persona" << endl;
		cin >> strPersona.peso;
		
		//creaci�n de archivo
		ofstream archivo("HT6_EJERCICIO_02.txt", std::ios_base::app);
		
		//grabar datos en archivo
		archivo << strPersona.edad << "\t" << strPersona.genero << "\t" << strPersona.altura << "\t" << strPersona.peso << endl;
		
		//Cerrar archivo
		archivo.close();
		
		cout << "Persona registrada correctamente!" << endl;
		
		cout << "�Desea registrar otra persona? (S/N)" << endl;
		cin >> registrar;
		
		registrar = toupper(registrar);
		
		if (registrar == 'S'){
			finalizar = false;
		}else{
			finalizar = true;
		}
		
	}while(finalizar != true);
	
	//Funci�n encargada de ordenar los registros
	//ordenarArchivo();
}

//Funci�n encargada de calcular promedios
void promedios(){
	//Declaraci�n de variables para promedio
	float promedioEdad = 0.00, promedioPeso = 0.00, promedioAltura = 0.00;
	//Contador del ciclo (variable global dentro de la funci�n)
	int i = 0;
	
	//Declaraci�n de variable tipo estructura de Persona
	persona temporalPersonas;
	//Declaraci�n de vector de tipo estructura de persona
	vector<persona> vectorRegistros;
	
	//Declaraci�n de variable archivo
	ifstream archivoLectura;
	//Abrir archivo
	archivoLectura.open("HT6_EJERCICIO_02.txt",ios::in);
	
	//Lectura l�nea por l�nea de los registros del archivo
	while(archivoLectura>>temporalPersonas.edad>>temporalPersonas.genero>>temporalPersonas.altura>>temporalPersonas.peso){
		//los registros se guardan en el vector
    	vectorRegistros.push_back(temporalPersonas);
	};
	
	//Cerramos archivo
  	archivoLectura.close();
	
	//Iteraci�n de vector para sacar promedios
	for (i; i < vectorRegistros.size(); i++){
		//Suma de registros
		promedioEdad = vectorRegistros[i].edad + promedioEdad;
		promedioAltura = vectorRegistros[i].altura + promedioAltura;
		promedioPeso = vectorRegistros[i].peso + promedioPeso;
	}
	
	//Calculo de promedios
	promedioEdad = promedioEdad/ (i);
	promedioAltura = promedioAltura /(i);
	promedioPeso = promedioPeso / (i);
	
	//Salida de pantalla
	cout << "--------------PROMEDIOS--------------" << endl;
	cout << "EDAD"  << "\t" << "ALTURA" << "\t" << "PESO" << endl;
	cout << promedioEdad  << "\t" << promedioAltura << "\t" << promedioPeso << endl;
	
}


//Funci�n encargada de mostrar reporte
void reporte(){
	//Declaraci�n de variable tipo estructura de persona
	persona temporalPersonas;
	
	//Salida de pantalla
	cout << "----------REPORTE DE REGISTRO DE PERSONAS----------" << endl;
	cout << "EDAD" << "\t" << "GENERO" << "\t" << "ALTURA" << "\t" << "PESO" << endl;
	
	//Declaraci�n de variable archivo
	ifstream archivoLectura;
	//Abrir archivo
	archivoLectura.open("HT6_EJERCICIO_02.txt",ios::in);
	
	//Lectura l�nea por l�nea de los registros del archivo
	while(archivoLectura>>temporalPersonas.edad>>temporalPersonas.genero>>temporalPersonas.altura>>temporalPersonas.peso){
		//Se muestran los registros del archivo en pantalla
    	cout <<  temporalPersonas.edad << "\t" << temporalPersonas.genero << "\t" << temporalPersonas.altura << "\t" << temporalPersonas.peso << endl;
	};
	
	//Cerramos archivo
  	archivoLectura.close();
  	
}

//funci�n principal
int main(){
	//Declaraci�n de variables para el manejo del men�
	int opcion;
	bool finalizar = false;
	
	do {
		//Menu princpial
		//limpiar buffer 
		fflush(stdin);
		cin.clear();
		
		cout << "----------------------CONTROL DE PESO 2,020--------------------" << endl;
		cout << "--------------------DEPARTAMENTO DE GUATEMALA--------------------" << endl;
		cout << "1. Registro de persona" << endl;
		cout << "2. Promedios de peso, altura y edad" << endl;
		cout << "3. Reporte" << endl;
		cout << "4. Salir" << endl;
		cout << "Por favor seleccione una opci�n: " << endl;
		cin >>  opcion;
		
		switch(opcion){
			case 1:
				registroPersonas();
				ordenarArchivo();
				break;
			case 2:
				promedios();
				break;
			case 3:
				reporte();
				break;
			case 4:
				finalizar = true;
				break;
			default:
				cout << "Por favor ingrese una opci�n v�lida" << endl;
				break;
		}
		
	}while (finalizar != true);
	
	
	return 0;
}


