/*		EJERCICIO #1
En una librer�a se venden 4 modelos diferentes de cuadernos, con los siguientes precios:
	-Modelo#1 - Q10.00
	-Modelo#2 - Q15.00
	-MOdelo#3 - Q18.50
	-Modelo#4 - Q25.00
Por otra parte, se tiene informaci�n sobre las ventas realizadas durante los �ltimos 30 d�as,
estos movimientos se deben guardar en un archivo de la siguiente forma:

DIA1, MOD, CANT
DIA2, MOD, CANT
.
.
DIA30, MOD, CANT

DIAi = Variable que representa el d�a que se efectu� la venta i (1-30)
MOD = Variable que representa c�digo de modelo que se vendi� (1-4)
CANT = Variable que represetna la cantidad de unidades vendidas

El programa deber� ser capaz de:
	-Modificar el n�mero de unidades vendidas, solicitando al usuario el d�a y c�digo de art�culo (Modificaci�n del archivo)
	-Eliminaci�n de un d�a espec�fico de venta (Modificaci�n del archivo)
	-Calcular el total recaudado por modelo en los 30 d�as.
	-Calcular cu�l fue el modelo que se vendi� m�s en los 30 d�as.
*/

//Importaci�n de librer�as
#include <fstream> //Para el manejo de archivos
#include <iostream> //Para operaciones de entrada o salida
#include <string> //Para el manejo de car�cteres 
#include <vector> //Para el manejo de vectores

/*
	Espacio de nombres el cual se asocia a "n" funciones, 
	en este caso nos sirve para evitar los encapsulamientos st::cout o std::cin
*/
using namespace std;

//Creaci�n de estructura de tipo cuaderno
struct cuaderno{
	int DIA;
	int MOD;
	int CANT;
	float TOTAL;
};

//Funci�n encargada de la lectura de archivos
void lecturaArchivo(){
	//Variable de tipo archivo
	ifstream archivo;
	
	//Variables para guardar los datos del archivo
	int dia, mod, cant;
	float total;
	
	archivo.open("HT6_EJERCICIO_01.txt", ios::in);
	
	cout << "---------------REPORTE DE VENTA---------------" << endl;
	cout << "DIA" << "\t" << "MODELO" << "\t" << "CANTIDAD" << "\t" << "TOTAL" << endl;
	
	while(archivo >> dia >> mod >> cant >> total){
		cout << dia << "\t" << mod << "\t" << cant << "\t" << "\t" << total << endl;
	}
	
	archivo.close();
}

//Funci�n encargada de gestionar la compra de cuadernos
void compraCuadernos(){
	int opcionCuaderno;
	//Declaraci�n de variable de tipo estructura
	cuaderno strCuaderno;
	
	cout << "---------------MODELOS DE CUADERNOS DISPONIBLES---------------"<< endl;
	cout << "MODELO" << "\t" << "PRECIO" << endl;
	cout << "1"<< "\t" << "Q10.00"  << endl;
	cout << "2"<< "\t" << "Q15.00"  << endl;
	cout << "3"<< "\t" << "Q18.50"  << endl;
	cout << "4"<< "\t" << "Q25.00"  << endl;
	cout << "Seleccione una opci�n: " << endl;
	cin >> opcionCuaderno;	
	//Ingreso de la cantidad de cuadernos
	cout << "Ingrese la cantidad de cuadernos que comprar�: " << endl;
	cin >> strCuaderno.CANT;
	//Ingreso del d�a en que se realiza la compra
	cout << "Ingrese el d�a de la compra (1-30): " << endl;
	cin >> strCuaderno.DIA;
	
	switch(opcionCuaderno){
		case 1:
			//Se indica el modelo del cuaderno
			strCuaderno.MOD = 1;
			//Calculo del precio total a pagar
			strCuaderno.TOTAL = strCuaderno.CANT * 10;
			break;
		case 2:
			strCuaderno.MOD = 2;
			strCuaderno.TOTAL = strCuaderno.CANT * 15;
			break;
		case 3:
			strCuaderno.MOD = 3;
			strCuaderno.TOTAL = strCuaderno.CANT * 18.50;
			break;
		case 4:
			strCuaderno.MOD = 4;
			strCuaderno.TOTAL = strCuaderno.CANT * 25;
			break;
		default:
			cout << "�Opci�n inv�lida!" << endl;
			break;
	}
	
	//Crear Archivo
	ofstream archivoVentas("HT6_EJERCICIO_01.txt", std::ios_base::app);
	
	//Grabar datos en archivo
	archivoVentas << strCuaderno.DIA << "\t" << strCuaderno.MOD << "\t" << strCuaderno.CANT << "\t" << strCuaderno.TOTAL << endl;
	
	//Cerramos archivo
	archivoVentas.close();
	
	cout << "Venta guardada correctamente!" << endl;
}

//Funci�n encargada de modificar cantidad comprada de cuadernos
void modificarCantidad(){
	//declaraci�n de variables
	int dia, modelo, nuevaCantidad, diaAnterior, modeloAnterior, cantidadAnterior;
	float totalAnterior;
	char respuesta;
	bool bandera = false, bandera2 = false;
	
	//Creaci�n de archivos
	ifstream archivoAnterior;
	ofstream archivoNuevo;
	
	cout <<"---------------MODIFICACI�N DE CANTIDAD VENDIDA---------------" << endl;
	lecturaArchivo();
	//Remover archivo si en caso existe
	remove("Temporal.txt");
	
	archivoAnterior.open("HT6_EJERCICIO_01.txt", ios::in);
	archivoNuevo.open("Temporal.txt", ios::app);
	
	cout <<"\nIngrese el d�a en que se registr� la venta (1-30): " << endl;
	cin >> dia;
	
	cout << "Ingrese el modelo del que desea modificar la cantidad (1-4): " << endl;
	cin >> modelo;
	
	//Obtenci�n de nuevos datos
	do{
		cout << "Ingrese la nueva cantidad: " << endl;
		cin	>> nuevaCantidad;
		cout << "�Seguro que desa modificar el registro? S/N" << endl;
		cin	>> respuesta;
		//Convertir respuesta a may�scula con la funci�n toupper
		respuesta = toupper(respuesta);
	}while(respuesta != 'S');
	
	//Leer datos del archivo anterior para modificarlos
	while(archivoAnterior >> diaAnterior >> modeloAnterior >> cantidadAnterior >> totalAnterior){
		//Si existe un registro con los par�metros ingresados iguales se modifica
		if(dia == diaAnterior and modelo == modeloAnterior){
			//Calcular el nuevo total
			switch(modelo){
				case 1:
					totalAnterior = nuevaCantidad * 10;
					break;
				case 2:
					totalAnterior = nuevaCantidad * 15;
					break;
				case 3:
					totalAnterior = nuevaCantidad * 18.50;
					break;
				case 4:
					totalAnterior = nuevaCantidad * 25;
					break;
				default:
					cout << "Modelo no existe!" << endl;
					break;
			}
			//guardar datos en nuevo archivo
			archivoNuevo << diaAnterior << "\t" << modeloAnterior << "\t" << nuevaCantidad << "\t" << totalAnterior << endl;
			//Variable bandera que utilizaremos para renombrar el archivo
			bandera = true;
			
		}//Si lo anterior no se cumple entonces no se modifican los registros y se guardan en el archivo nuevo con la data anterior
		else if (dia != diaAnterior and modelo != modeloAnterior){
			archivoNuevo << diaAnterior << "\t" << modeloAnterior << "\t" << cantidadAnterior << "\t" << totalAnterior << endl;
			bandera2 = true;
		}
	}
	
	if(bandera == false and bandera2 == true){
		cout << "-- no se encontr� la venta con los par�metros ingresados--" << endl;
	}
	
	//Cerramos archivo
	archivoAnterior.close();
	archivoNuevo.close();
	
	if(bandera){
		cout << "Registro actualizaco correctamente..." << endl;
		//Eliminamos el archivo anterior
		remove("HT6_EJERCICIO_01.txt");
		//Renombramos el archivo nuevo
		rename("Temporal.txt", "HT6_EJERCICIO_01.txt");
	}
	
}

//Funci�n encargada de eliminar registro de venta
void eliminarDiaVenta(){
	//Declaraci�n de variables
	int dia, diaAnterior, modeloAnterior, cantidadAnterior;
	float totalAnterior;
	bool bandera = false;
	
	//Creaci�n de archivos
	ifstream archivoAnterior;
	ofstream archivoNuevo;
	
	cout <<"---------------ELIMINACI�N DE D�A DE VENTA---------------" << endl;
	lecturaArchivo();
	
	//Remover archivo si en caso existe
	remove("Temporal.txt");
	
	//Abrir archivos
	archivoAnterior.open("HT6_EJERCICIO_01.txt", ios::in);
	archivoNuevo.open("Temporal.txt", ios::app);
	
	//Obtenci�n del d�a a eliminar
	cout << "\nPor favor ingrese el d�a que desea eliminar del reporte:" << endl;
	cin >> dia;
	
	
	while(archivoAnterior >> diaAnterior >> modeloAnterior >> cantidadAnterior >> totalAnterior){
			if (dia == diaAnterior){
				bandera = true;
			}
			else if (dia != diaAnterior){
				archivoNuevo << diaAnterior << "\t" << modeloAnterior << "\t" << cantidadAnterior << "\t" << totalAnterior << endl;
			}
	}
	
	if (bandera == false){
		cout << "D�a no encontrado en el registro de ventas" << endl;
		remove("Temporal.txt");
	}
	
	//Cerramos archivo
	archivoAnterior.close();
	archivoNuevo.close();
	
	if(bandera){
		cout << "Registros eliminados correctamente..." << endl;
		//Eliminamos el archivo anterior
		remove("HT6_EJERCICIO_01.txt");
		//Renombramos el archivo nuevo
		rename("Temporal.txt", "HT6_EJERCICIO_01.txt");
	}
	
}

//Total recaudado por modelo en los 30 d�as
void totalXModelo(){
	//Creaci�n de variable tipo archivo
	ifstream archivo;
	//Variables que almacenar�n los datos del archivo
	int dia, mod, cant;
	float total;
	//Contadores de totales por modelo de cuaderno
	float totalMod1 = 0.00, totalMod2= 0.00, totalMod3 = 0.00, totalMod4 = 0.00;
	
	//Abrir archivo
	archivo.open("HT6_EJERCICIO_01.txt", ios::in);
	
	//lectura de archivo y validaci�n de modelo de cuaderno
	while(archivo >> dia >> mod >> cant >> total){
		if (mod == 1){
			totalMod1 = totalMod1 + total;
		}else if (mod == 2){
			totalMod2 =  totalMod2 + total;
		}else if (mod == 3){
			totalMod3 = totalMod3 + total;
		}else if (mod == 4){
			totalMod4 = totalMod4 + total;
		}
	}
	
	//Cerrar archivo
	archivo.close();
	
	//Salida en pantalla
	cout << "-------------TOTAL VENDIDO POR MODELO DE CUADERNO-------------"<< endl; 
	cout << "MODELO" << "\t" << "TOTAL" << endl;
	cout << "1" << "\t" << "Q" <<totalMod1 << endl;
	cout << "2" << "\t" << "Q" <<totalMod2 << endl;
	cout << "3" << "\t" << "Q" <<totalMod3 << endl;
	cout << "4" << "\t" << "Q" <<totalMod4 << endl;
}


//Funci�n encargada de obtener el modelo de cuaderno m�s vendido
void modeloMasVendido(){
	//creaci�n de variable tipo archivo
	ifstream archivo;
	//Declaraci�n de variables que almacenar�n los datos del archivo
	int dia, mod, cantidad = 0;
	float total;
	//Contadores de cantidades vendidas por modelo
	int contMod1 = 0, contMod2 = 0, contMod3 = 0, contMod4 = 0;
	//Variable de control de qui�n es mayor
	int aux = 0, cont = 1;
	
	//Abrir archivo
	archivo.open("HT6_EJERCICIO_01.txt", ios::in);
	
	//lectura de archivo y validaci�n de cantidad vendida por modelo de cuaderno
	while(archivo >> dia >> mod >> cantidad >> total){
		if (mod == 1){
			contMod1 =  contMod1 +  cantidad;
		}else if (mod == 2){
			contMod2 =  contMod2 +  cantidad;
		}else if (mod == 3){
			contMod3 =  contMod3 +  cantidad;
		}else if (mod == 4){
			contMod4 =  contMod4 +  cantidad;
		}
	}
	
	//Arreglo para realizar iteraciones para saber qui�n es mayor
	int arregloContadores[4] = {contMod1, contMod2, contMod3, contMod4};
	
	//Iteraci�n del arreglo
	//Iteraci�n: Ir uno a uno seg�n los registros que se encuentren en un vector, arreglo, lista, etc.
	for(int i = 0; i <= 3; i ++){
		if(arregloContadores[i] > aux){
			aux = arregloContadores[i];
			cont = cont + 1;
		}
	}
	
	switch(cont){
		case 1:
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "EL MODELO M�S VENDIDO ES EL MODELO 1 CON " << contMod1 << " CANTIDADES VENDIDAS." << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
			break;
		case 2:
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "EL MODELO M�S VENDIDO ES EL MODELO 2 CON " << contMod2 << " CANTIDADES VENDIDAS." << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
			break;
		case 3:
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "EL MODELO M�S VENDIDO ES EL MODELO 3 CON " << contMod3 << " CANTIDADES VENDIDAS." << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
			break;
		case 4:
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "EL MODELO M�S VENDIDO ES EL MODELO 4 CON " << contMod4 << " CANTIDADES VENDIDAS." << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
			break;
		default:
			cout << "-------------------------------------------" << endl;
			cout <<"NO SE PUDO CALCULAR EL MODELO M�S VENDIDO :(" << endl;
			cout << "-------------------------------------------" << endl;
			break;
	}
}


//Funci�n principal del programa
int main(){
	//Declaraci�n de variables
	int opcion; //int = va a almacenar n�mero enteros (todos los reales 1, 2, 3, 4, ... n)
	bool finalizar = false; //bool = almacenan valores verdaderos o falsos
	
	//Ciclo
	do {
		//Menu principal
		//limpiar buffer
		fflush(stdin);
		cin.clear();
		
		//Salida de consola
		cout << "--------------------------LIBRER�A S.A.-------------------------" << endl;
		cout << "-------------------------MEN� PRINCIPAL-------------------------" << endl;
		cout << "1. Compra de cuadernos" << endl;
		cout << "2. Modificar unidades vendidas" << endl;
		cout << "3. Eliminaci�n de d�a de venta" << endl;
		cout << "4. Total recaudado por modelo (30 d�as)" << endl;
		cout << "5. Modelo m�s vendido (30 d�as)" << endl;
		cout << "6. Salir" << endl;
		cout << "Por favor seleccione una opci�n" << endl;
		//obtener opci�n ingresada por el usuario
		cin >> opcion;
		
		//Validaci�n de la opci�n ingresada por el usuario
		switch(opcion){
			case 1:
				//Invocaci�n de funci�n para comprar cuadernos
				compraCuadernos();
				break;
			case 2:
				//Invocaci�n de la funci�n para modificar cantidad comprada de cuadernos
				modificarCantidad();
				break;
			case 3:
				//Invocaci�n de la funci�n para eliminar d�a de venta
				eliminarDiaVenta();
				break;
			case 4:
				//Invocaci�n de la funci�n para calcular totales vendidos
				totalXModelo();
				break;
			case 5:
				//Invocaci�n de la funci�n para obtener el modelo m�s vendido
				modeloMasVendido();
				break;
			case 6: 
				finalizar = true;
				break;
			default:
				cout << "�Opci�n Inv�lida!" << endl;
				opcion = 0;
				break;
		}
		
	}while (finalizar != true);
	
	
	return 0;
}
