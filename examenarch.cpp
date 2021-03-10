#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

struct Empleado
{
	int codigo_empleado;
	char nombre[50];
	char apellido[50];
	char puesto[50];
	double sueldo_base;
	double bonificacion;
	double total;	
}; Empleado empleado;

void crear()
{
	FILE * archivo=fopen("empleados.dat","ab");
	string nombre, apellido, puesto;
	
	cout<<"Ingrese el codigo: "; cin>>empleado.codigo_empleado;
	cin.ignore();
	cout<<"Ingrese el Nombre: "; getline(cin, nombre);
	strcpy(empleado.nombre, nombre.c_str());	
	cout<<"Ingrese el Apellido: "; getline(cin, apellido);
	strcpy(empleado.apellido, apellido.c_str());
	cout<<"Ingrese el puesto: "; getline(cin, puesto);
	strcpy(empleado.puesto, puesto.c_str());
	cout<<"Ingrese el sueldo base: "; cin>>empleado.sueldo_base;
	cin.ignore();
	cout<<"Ingrese la bonificacion: "; cin>>empleado.bonificacion;
	cin.ignore();
	empleado.total=empleado.sueldo_base+empleado.bonificacion;
	cout<<"\nEl sueldo total es de: "<<empleado.total<<endl;
	
	fwrite(&empleado,sizeof(Empleado),1,archivo);
	fclose(archivo);
}

void leer()
{
	FILE * archivo=fopen("empleados.dat","rb");
	if (!archivo){
		cout<<"archivo no encontrado"<<endl;
		exit;
	}
	int id = 0;
	double total;
	fread(&empleado,sizeof(Empleado),1,archivo);
	cout<<"ID  Codigo     Nombre       Apellido        Puesto      Sueldo    Bonificacion    Sueldo total"<<endl;
	do{
		cout<<"_________________________________________________________________________________________________"<<endl;
		cout<<id<<" | "<<empleado.codigo_empleado<<" | "<<empleado.nombre<<" | "<<empleado.apellido<<" | "<<empleado.puesto<<" | "
		<<empleado.sueldo_base<<" | "<<empleado.bonificacion<<" | "<<empleado.total<<endl;
		fread(&empleado,sizeof(Empleado),1,archivo);
		id+=1;
	} while (feof(archivo) ==0);
	cout<<endl;
	fclose(archivo);
}

void buscar()
{
	FILE * archivo=fopen("empleados.dat","rb");
	int codigo;
	double total;
	cout<<"Busque por el codigo del empleado: "; cin>>codigo;
	fread(&empleado,sizeof(Empleado),1,archivo);
	do
	{
		if(codigo==empleado.codigo_empleado)
		{
			fseek(archivo,codigo* sizeof(Empleado),SEEK_SET);
			fread(&empleado,sizeof(Empleado),1,archivo);
			cout<<"\n _________________ codigo "<<codigo<<" _________________"<<endl;
			cout<<"Codigo :      "<<empleado.codigo_empleado<<endl;
			cout<<"Nombre:       "<<empleado.nombre<<endl;
			cout<<"Apellido:     "<<empleado.apellido<<endl;
			cout<<"Puesto:       "<<empleado.puesto<<endl;
			cout<<"Sueldo base:  "<<empleado.sueldo_base<<endl;
			cout<<"Bonificacion: "<<empleado.bonificacion<<endl;
			cout<<"Sueldo total: "<<empleado.total;
		}
		fread(&empleado,sizeof(Empleado),1,archivo);
	}while(feof(archivo)==0);
	fclose(archivo);
}

void eliminar()
{
	int id;
	double total;
	FILE * archivo=fopen("empleados.dat","rb");
	FILE * auxiliar=fopen("auxiliar.dat","wb");
	cout<<"Busque el codigo del empleado que desea eliminar: ";cin>>id;
	fread(&empleado,sizeof(Empleado),1,archivo);
	while(!feof(archivo))
	{
		fwrite(&empleado,sizeof(Empleado),1,auxiliar);
		if(empleado.codigo_empleado==id)
		{
			int pos=ftell(auxiliar)-sizeof(Empleado);
			fseek(auxiliar,pos,SEEK_SET);
		}
		fread(&empleado,sizeof(Empleado),1,archivo);
	}
	cout<<"Registro eliminado"<<endl;
	fclose(archivo);
	fclose(auxiliar);
	remove("empleados.dat");
	rename("auxiliar.dat","empleados.dat");
}

void modificar()
{
	FILE* archivo = fopen("empleados.dat","r+b");
	string nombre, apellido, puesto;
	int codigo, id=0;
	cout<<"\nQue registro desea modificar (ID): "; cin>>id;
	fseek(archivo,id* sizeof(Empleado), SEEK_SET);
	cout<<"_____________________________________________________________";
	cout<<"\nIngrese el nuevo codigo: ";cin>>empleado.codigo_empleado;
	cin.ignore();
	cout<<"Ingrese el nuevo nombre: "; getline(cin,nombre);
	strcpy(empleado.nombre,nombre.c_str());
	cout<<"Ingrese el nuevo apellido: "; getline(cin,apellido);
	strcpy(empleado.apellido, apellido.c_str());
	cout<<"Ingrese el nuevo puesto: "; getline(cin,puesto);
	strcpy(empleado.puesto, puesto.c_str());
	cout<<"Ingrese el nuevo sueldo base: "; cin>>empleado.sueldo_base;
	cin.ignore();
	cout<<"Ingrese la nueva bonificacion: ";cin>>empleado.bonificacion;
	cin.ignore();
	empleado.total=empleado.sueldo_base+empleado.bonificacion;
	cout<<"El nuevo salario total es de: "<<empleado.total<<endl;
	fwrite(&empleado,sizeof(Empleado),1,archivo);
	fclose(archivo);
}

void menu()
{
	int opc;
	string opcion;
	cout<<"------------------- Menu de manejo de archivos -------------------"<<endl;
	cout<<"1. Agregar registros"<<endl;
	cout<<"2. Leer registros"<<endl;
	cout<<"3. Buscar por codigo de empleado"<<endl;
	cout<<"4. Modificar registros"<<endl;
	cout<<"5. Eliminar registros"<<endl;
	cout<<"\nQue opcion quiere ejecutar: "; cin>>opc;
	switch(opc)
	{
		case 1:
			system("cls");
			crear();
		break;
		case 2:
			system("cls");
			leer();
		break;
		case 3:
			system("cls");
			leer();
			buscar();
		break;
		case 4:
			system("cls");
			leer();
			modificar();
			cout<<"\n------------------- los cambios ya realizados -------------------"<<endl;
			leer();
		break;
		case 5:
			system("cls");
			leer();
			eliminar();
			cout<<"\n------------------- los cambios ya realizados -------------------"<<endl;
			leer();
		break;
		default:
			cout<<"Esa opcion no existe"<<endl;
		break;
	}
	cout<<"\nDesea probar otra opcion (s/n): "; cin>>opcion;
	if(opcion=="s"||opcion=="S")
	{
		system("cls");
		menu();
	}
	else
	{
		cout<<"Proceso terminado"<<endl;
	}
}

main()
{
	menu();
}
