/*PLATAFORMA DE ANÁLISIS DE DATA DE PACIENTES COVID-19 - LIMA, PERÚ - 2020
*********************Grupo 6 - FISI, UNMSM / 01.08.2020******************/

//Declaración de librerías
#include <iostream> //Input(entrada) - Output(salida) Stream. Permite el uso de cin y cout.
#include <conio.h> //Incluye funciones de entrada y salida de datos, permitiendo el uso de getch().
#include <iomanip> //Denota la manipulación del formato de salida con el uso de setw().
#include <string.h> //Manejo de cadenas de caracteres: strcpy(), strncpy(), strcat(), strcmp(), strrev(), strlen().
#include <stdio.h> //Permite trabajar con archivos mediante fclose, fopen, feof, fseek, ftell.
#include <locale.h> //Sirve para utilizar la función de idioma setlocale(LC_CTYPE,"Spanish") 
#include <Windows.h> //Sirve para utilizar la función de retardo de acción sleep()
using namespace std;

//Estructuras

struct Pacientes{
	char nombre[50];
	char apellido[50];
	int edad;
	char sexo[50];
	char pat_previa[50];
	char tratamiento[50];
	char hospital[50];
	char estado[50];
}pac;

struct Analistas{
	char nombre[50];
	char usuario[50];
	char contrasena[50];
}analista;

//Prototipos de funciones

void anadiranalista(Analistas analista, FILE *F);
void mostrarArchivosAnalistas(FILE *F, Analistas analista);
void verificaranalista(Analistas analista, FILE *F, Pacientes paciente, FILE *H);
void diferente(Analistas analista, FILE *F, char nuevousuario[]);
int menu1();
int menu();
int menu2();
void Encabezado();
void seleccion2(Pacientes pac, FILE *H, Analistas analista, FILE *F);
void seleccion1(Pacientes pac, FILE *H);
void crearArchivoA(FILE *F);
void crearArchivo(FILE *H);
void ingresarPacientes(FILE *H, Pacientes paciente);
void mostrarArchivos(FILE *H, Pacientes paciente);
void Eliminar(FILE *H, Pacientes paciente);
char menupav();
void Estadistica(FILE *H, Pacientes paciente);
void buscarpaciente(FILE*H,Pacientes paciente);
void grafica(int v[]);
void graficageneral(int v[]);
void graficasexo(int v[]);
void modificarpaciente(Pacientes paciente,FILE*H);
void ModificarAnalista(FILE* F, Analistas analista);

//FUNCIÓN PRINCIPAL

int main(){
	setlocale(LC_CTYPE,"Spanish");
	FILE *F, *H;
	int opcion;
	
	do{
		opcion=menu1();
		
		switch(opcion){
			case 1: 
				crearArchivoA(F);
			    break;
			case 2:
			    mostrarArchivosAnalistas(F, analista);
		    	break;
			case 3:
			    anadiranalista(analista, F);
			    break;
			case 4:
				system("cls");
				seleccion2(pac, H, analista, F);
				break;
			case 5:
				system("cls");
				ModificarAnalista(F, analista);
				break;
			case 6:
				Encabezado();
				cout<<"\tGracias por usar la plataforma"<<endl;
				break;
		}
	}while(opcion!=6);
}

//Implementación de funciones

void Encabezado(){
	cout<<"\t\t\t\t=========================================================="<<endl;
	cout<<"\t\t\t\t   PLATAFORMA DE ANÁLISIS DE DATA DE PACIENTES COVID-19"<<endl;
	cout<<"\t\t\t\t\t\t     LIMA, PERÚ - 2020"<<endl<<endl;
	cout<<"\t\t\t\t    Grupo 6 | FISI, UNMSM - MINSA | Gobierno del Perú"<<endl;
	cout<<"\t\t\t\t\t#PrimeroMiSalud | #PerúEstáEnNuestrasManos"<<endl;
	cout<<"\t\t\t\t=========================================================="<<endl<<endl;
}

void anadiranalista(Analistas analista, FILE *F){
	char nuevousuario[30];
	char cadena3[50],cadena4[50];
	
	F=fopen("Analistas.txt", "a+");
	Encabezado();
	
	cout<<"\tSeñor(a) analista, deberá rellenar campos para crear su cuenta."<<endl;
	cout<<"\tNOTA: La siguiente acción tendrá validez bajo declaración jurada."<<endl<<endl;	
	
	cout<<"\tDigite sólo su primer nombre: ";
	cin>>analista.nombre;
	
	int check;
	cout<<"\t-> ¿Conforme? (Sí:1 / No:0): "; cin>>check;	
	
	do{
		switch(check){
			case 0:
				cout<<"\tNombre: "; fflush(stdin);
				cin>>analista.nombre;
				cout<<"\t¿Conforme? (Sí:1 / No:0): "; cin>>check;
				break;
			case 1:
				break;
		}		
	}while(check!=1);	
	
	cout<<endl;

	cout<<"\tDigite su nombre de usuario: ";
	cin>>nuevousuario;
	diferente(analista, F, nuevousuario);
	strcpy(analista.usuario, nuevousuario);

	cout<<"\t-> ¿Conforme? (Sí:1 / No:0): "; cin>>check;	
	
	do{
		switch(check){
			case 0:
				cout<<"\tNombre de usuario: "; fflush(stdin);
					cin>>nuevousuario;
					diferente(analista, F, nuevousuario);
					strcpy(analista.usuario, nuevousuario);
				cout<<"\t¿Conforme? (Sí:1 / No:0): "; cin>>check;
				break;
			case 1:
				break;
		}		
	}while(check!=1);		
	
	cout<<endl;
	
	cout<<"\t-> Su contraseña por defecto será: ";
	strncpy(cadena3, analista.nombre, 3);
	strncpy(cadena4, analista.usuario, 3);
	strcat(cadena3, cadena4);
	strcpy(analista.contrasena, cadena3);
	cout<<analista.contrasena;
	
	if(F!=NULL){
		fwrite(&analista, sizeof(analista), 1, F);
		cout<<endl<<endl;
		cout<<"\tSus datos fueron guardados con éxito. ";
		if(!ferror(F)){
			fclose(F);
		}
		
		else{
			cout<<"\tError al intentar registrar su usuario."<<endl<<endl;
			cout<<"Intente nuevamente o contacte con el administrador."<<endl;
		}
	}
	Sleep(3000);
}

void diferente(Analistas analista, FILE *F, char nuevousuario[]){
	
	while(!feof(F)){
		
		if(strcmp(analista.usuario,nuevousuario)==0){
			cout<<"\tEste usuario ya existe."<<endl<<endl;
	    	cout<<"\tIngrese otro nombre de usuario: ";
	    	cin>>nuevousuario;
	    	diferente(analista, F, nuevousuario);
		}
		fread(&analista, sizeof(analista), 1, F);
    }
}

void mostrarArchivosAnalistas(FILE *F, Analistas analista){
	F=fopen("Analistas.txt", "r");
	Encabezado();
	cout<<"\tREGISTRO TOTAL Y ACTUALIZADO DE ANALISTAS DE COVID-19 EN LIMA"<<endl;
	cout<<endl;
	cout<<"\tNOMBRE"<<setw(25)<<"USUARIO"<<setw(25)<<endl;
	cout<<"\t===============================\n";
	
	if(F==NULL){
		cout<<"\t\t\tError al visualizar la base de datos de analistas."<<endl<<endl;
		cout<<"\t\t\tIntente nuevamente o contacte con el administrador."<<endl;
		getch();
		exit(1);
	}
	
	while(!feof(F)){
		fread(&analista, sizeof(analista), 1, F);
		
		if(!feof(F)){
        	cout<<"\t"<<analista.nombre<<"\t\t\t"<<analista.usuario<<endl;
		}
	}
	getch();
}

int menu1(){
	int x;
	system("cls");
	Encabezado();
	cout<<"\t\t\t\tBienvenido(a) a la plataforma instaurada en el entorno de"<<endl;
	cout<<"\t\t\t\tla pandemia por la COVID-19."<<endl<<endl;
	cout<<"\t\t\t\t[1]. Crear base de datos de analistas"<<endl<<endl;
	cout<<"\t\t\t\t[2]. Ver listado de analistas a nivel de Lima"<<endl<<endl;
	cout<<"\t\t\t\t[3]. Crear cuenta institucional de analista"<<endl<<endl;
	cout<<"\t\t\t\t[4]. Iniciar sesión institucional entorno al ingreso de datos"<<endl<<endl;
	cout<<"\t\t\t\t[5]. Modificar usuario y contraseña de analista"<<endl<<endl;
	cout<<"\t\t\t\t[6]. Salir de la plataforma"<<endl<<endl;
	cout<<"\t\t\t\t-> Digite una opción: ";
	cin>>x;
	system("cls");
	return x;
}

int menu(){
	int x;
	system("cls");
	Encabezado();
	cout<<"\t¡Sesión iniciada correctamente!"<<endl;
	cout<<"\tBienvenido señor(a) analista"<<endl<<endl;
	cout<<"\tPROCEDIMIENTO: Ud. administrará los datos de los pacientes COVID-19 de Lima mediante las"<<endl;
	cout<<"\topciones del siguiente menú, donde primero deberá crear la base de datos de los pacientes"<<endl<<endl;
	cout<<"\t\t\t\t[1]. Crear base de datos de pacientes COVID-19"<<endl<<endl;
	cout<<"\t\t\t\t[2]. Agregar paciente al registro"<<endl<<endl;
	cout<<"\t\t\t\t[3]. Visualizar tabla actualizada de pacientes COVID-19 de Lima"<<endl<<endl;
	cout<<"\t\t\t\t[4]. Eliminar paciente del registro"<<endl<<endl;
	cout<<"\t\t\t\t[5]. Visualizar estadísticas actualizadas"<<endl<<endl;
	cout<<"\t\t\t\t[6]. Buscar paciente COVID-19 en el registro"<<endl<<endl;
	cout<<"\t\t\t\t[7]. Modificar datos de paciente"<<endl<<endl;
	cout<<"\t\t\t\t[8]. Cerrar sesión"<<endl<<endl;
	cout<<"\t\t\t\t-> Digite una opción: ";
	cin>>x;
	system("cls");
	return x;
}

int menu2(){
	int x;
	system("cls");
	Encabezado();
	cout<<"\t\tSISTEMA DE INICIO DE SESIÓN DE ANALISTA COVID-19"<<endl<<endl;
	cout<<"\t[1]. Iniciar sesión como analista certificado"<<endl<<endl;
	cout<<"\t[2]. Volver al menú principal"<<endl<<endl;
	cout<<"\t-> Digite una opción: ";
	cin>>x;
	system("cls");
	return x;
}

void seleccion2(Pacientes pac, FILE *H, Analistas analista, FILE *F){
	int op;
	
	do{
		op=menu2();
		
		switch(op){
			case 1:
				system("cls");
				verificaranalista(analista,F,pac,H);
				break;
			case 2:
				break;		
		}

	}while(op!=2);
}

void seleccion1(Pacientes pac, FILE *H){
	int op;	
	
	do{
		op=menu();
		
		switch(op){
			case 1:
				crearArchivo(H);
				break;
			case 2:
				ingresarPacientes(H, pac);
				break;
			case 3:
				mostrarArchivos(H, pac);
				break;
			case 4:
				Eliminar(H, pac);
				break;
			case 5:
				Estadistica(H, pac);
				break;
			case 6:
				buscarpaciente(H,pac);
				break;
			case 7:
			    modificarpaciente(pac,H);	
			case 8:
				break;	
		}
	}while(op!=8);
}

void crearArchivo(FILE *H){
	system("cls");
	Encabezado();
	H=fopen("Pacientes.txt", "w");
	
	if(H==NULL){
		cout<<"\tError al crear base de datos de pacientes."<<endl<<endl;
		cout<<"\tIntente nuevamente o contacte con el administrador."<<endl;
	}
	
	else{
		cout<<"\tCreando base de datos de pacientes"<<endl;
		for(int i=1;i<=3;i++){
			Sleep(500);
			cout<<"\t\t\t..."<<endl;
		}
		Sleep(2000);
		cout<<endl;
		cout<<"\tBase de datos de pacientes creada satisfactoriamente.";
		Sleep(2000);
		fclose(H);
	}
}

void crearArchivoA(FILE *F){
	system("cls");
	Encabezado();
	F=fopen("Analistas.txt", "w");
	
	if(F==NULL){
		cout<<"\tError al crear base de datos de analistas."<<endl<<endl;
		cout<<"\tIntente nuevamente o contacte con el administrador."<<endl;
		cout<<"\tVolviendo al menú principal..."<<endl;
		Sleep(2000);
	}
	
	else{
		cout<<"\tCreando base de datos de analistas"<<endl;
		for(int i=1;i<=3;i++){
			Sleep(500);
			cout<<"\t\t\t..."<<endl;
		}
		Sleep(2000);
		cout<<endl;
		cout<<"\tBase de datos de analistas creada satisfactoriamente.";
		Sleep(2000);
		fclose(F);
	}
}

void ingresarPacientes(FILE *H, Pacientes paciente){
	int op_1,op_2,op_3,op_4;
	H=fopen("Pacientes.txt", "a+");
	Encabezado();
	
	cout<<"\tSeñor(a) analista, deberá rellenar campos para registrar nuevo paciente."<<endl;
	cout<<"\tNOTA: La siguiente acción tendrá validez bajo declaración jurada."<<endl<<endl;	
	
	cout<<"\tNombre: ";
	cin>>paciente.nombre;
	
	int check;
	cout<<"\t-> ¿Conforme? (Sí:1 / No:0): "; cin>>check;	
	
	do{
		switch(check){
			case 0:
				cout<<"\tNombre: "; fflush(stdin);
				cin>>paciente.nombre;
				cout<<"\t¿Conforme? (Sí:1 / No:0): "; cin>>check;
				break;
			case 1:
				break;
		}		
	}while(check!=1);		
	
	cout<<endl;
	
	cout<<"\tApellido: ";
	cin>>paciente.apellido;
	
	cout<<"\t-> ¿Conforme? (Sí:1 / No:0): "; cin>>check;	
	
	do{
		switch(check){
			case 0:
				cout<<"\tApellido: "; fflush(stdin);
				cin>>paciente.apellido;
				cout<<"\t¿Conforme? (Sí:1 / No:0): "; cin>>check;
				break;
			case 1:
				break;
		}		
	}while(check!=1);		
	
	cout<<endl;
	
	cout<<"\tEdad: ";
	cin>>paciente.edad;
	
	cout<<"\t-> ¿Conforme? (Sí:1 / No:0): "; cin>>check;	
	
	do{
		switch(check){
			case 0:
				cout<<"\tEdad: "; fflush(stdin);
				cin>>paciente.edad;
				cout<<"\t¿Conforme? (Sí:1 / No:0): "; cin>>check;
				break;
			case 1:
				break;
		}		
	}while(check!=1);		
	
	cout<<endl;	
	
	cout<<"\tSexo: ";
	
	do{
		cout<<endl;
		cout<<"\t\t[1]. Masculino"<<endl;
		cout<<"\t\t[2]. Femenino"<<endl<<endl;
		cout<<"\t-> Digite opción: ";
		cin>>op_1;
	}
	while(op_1>2);
	
	switch(op_1){
		case 1:
			strcpy(paciente.sexo,"Masculino");
			break;
		case 2:
			strcpy(paciente.sexo,"Femenino");
			break;
	}
	
	cout<<"\tSexo: ";
	cout<<paciente.sexo<<endl;
	
	cout<<endl;
	
	cout<<"\tPatología previa más evidente que presente: "<<endl;
		
	do{
		cout<<endl;
		cout<<"\t[1]. E.respiratoria"<<endl;
		cout<<"\t[2]. E.coronaria"<<endl;
		cout<<"\t[3]. Obesidad"<<endl;
		cout<<"\t[4]. Hipertensión"<<endl;
		cout<<"\t[5]. N.antecedente"<<endl<<endl;
		cout<<"\t-> Digite opción: ";
		cin>>op_2;
    }while(op_2>5);
    
    switch(op_2){
    	case 1:
    		strcpy(paciente.pat_previa,"E.respiratoria");
    		break;
    	case 2:
    		strcpy(paciente.pat_previa,"E.coronaria");
    		break;
    	case 3:
    		strcpy(paciente.pat_previa,"Obesidad");
    		break;
    	case 4:
    		strcpy(paciente.pat_previa,"Hipertensión");
    		break;
    	case 5:
    		strcpy(paciente.pat_previa,"N.antecedente");
    		break;
	}
	
	cout<<"\tPatología previa: ";
	cout<<paciente.pat_previa<<endl;
	
	cout<<endl;
	
	cout<<"\tTratamiento utilizado: "<<endl;
	
	do{
		cout<<endl;
		cout<<"\t[1]. HIDROXICLOROQUINA"<<endl;
		cout<<"\t[2]. IVERMECTINA"<<endl;
		cout<<"\t[3]. AZITROMICINA"<<endl<<endl;
		cout<<"\t-> Digite opción: ";
		cin>>op_3;
    }while(op_3>3);
    
	switch(op_3){
    	case 1:
    		strcpy(paciente.tratamiento,"HIDROXICLOROQUINA");
    		break;
    	case 2:
    		strcpy(paciente.tratamiento,"IVERMECTINA");
    		break;
    	case 3:
    		strcpy(paciente.tratamiento,"AZITROMICINA");
    		break;
	}
	
	cout<<"\tTratamiento: ";
	cout<<paciente.tratamiento<<endl;
	
	cout<<endl;
		
	cout<<"\tHospital del paciente: ";
	cin>>paciente.hospital;
	fflush(stdin);
	
	cout<<endl;
	
	cout<<"\tSeleccione el estado actual del paciente: "<<endl;
	
	do{
		cout<<endl;
		cout<<"\t[1]. RECUPERADO"<<endl;
		cout<<"\t[2]. EN TRATAMIENTO"<<endl;
		cout<<"\t[3]. FALLECIDO"<<endl<<endl;
		cout<<"\t-> Digite opción: ";
		cin>>op_4;
    }while(op_4>3);
    
	switch(op_4){
    	case 1:
    		strcpy(paciente.estado,"RECUPERADO");
    		break;
    	case 2:
    		strcpy(paciente.estado,"EN TRATAMIENTO");
    		break;
    	case 3:
    		strcpy(paciente.estado,"FALLECIDO");
    		break;
	}
	
	cout<<"\tEstado actual del paciente: ";
	cout<<paciente.estado<<endl;
	
	Sleep(2000);
	for(int i=1;i<=3;i++){
		Sleep(500);
		cout<<"\t\t\t..."<<endl;
	}	
	
	system("cls");
	Encabezado();
	
	cout<<"\tGUARDANDO DATOS"<<endl;
	for(int i=1;i<=3;i++){
		Sleep(500);
		cout<<"\t\t\t..."<<endl;
	}
	Sleep(2000);
	cout<<endl;
	
	if(H!=NULL){
		fwrite(&paciente, sizeof(paciente), 1, H);
		cout<<"\tLos datos fueron guardados con éxito"<<endl;
		
		if(!ferror(H)){
			fclose(H);
		}
		
		else{
			cout<<"\tError de escritura al intentar registrar el paciente."<<endl;
			cout<<"Intente nuevamente o contacte con el administrador."<<endl;
			getch();
		}
	}
	Sleep(2000);
}

void mostrarArchivos(FILE *H, Pacientes paciente){
	H=fopen("Pacientes.txt", "r");
	
	if(H==NULL){
		cout<<"No se puede abrir el archivo";
		getch();
	}
	
	Encabezado();
	cout<<endl;
	cout<<"\t\t\t\t         REGISTRO TOTAL DE PACIENTES COVID-19 DE LIMA"<<endl;
	cout<<endl;
	cout<<"NOMBRE"<<setw(20)<<"APELLIDO"<<setw(10)<<"EDAD"<<setw(10)<<"SEXO"<<setw(20)<<"PAT.PREVIA"<<setw(15)<<"TRATAMIENTO"<<setw(22)<<"HOSPITAL"<<setw(15)<<"ESTADO"<<endl;
	cout<<"=======================================================================================================================\n"<<endl;	
	
	while(!feof(H)){
		fread(&paciente, sizeof(paciente), 1, H);
		
		if (!feof(H)){
			
			if(paciente.edad!=0){
				cout<<paciente.nombre<<"\t      "<<paciente.apellido<<"\t\t"<<paciente.edad<<"\t"<<paciente.sexo <<"\t"<<paciente.pat_previa<<"\t"<<paciente.tratamiento<<"            "<<paciente.hospital<<"\t  "<<paciente.estado<<endl;
			}
		}
	}
	getch();
}

void Eliminar(FILE *H, Pacientes paciente){

	int respuesta;
	char nom[50];
	char ape[50];
	cout<<endl;
	Encabezado();
	cout<<"\t\tFORMATO DE ELIMINACIÓN DE PACIENTE\n"<<endl;
	cout<<"\tNOTA: La siguiente acción tendrá validez bajo declaración jurada."<<endl<<endl;
	H=fopen("Pacientes.txt","rb+");
	
	if(H==NULL){
		cout<<"\tERROR: La base de datos no ha sido encontrada o está dañada."<<endl;
		cout<<"\tIntente nuevamente o contacte con el administrador.";
		cout<<endl;
		getch();
		exit(1);
	}
	
	cout<<"\tIngrese el nombre y el apellido del paciente a continuación: "<<endl<<endl;
	cout<<"\t-> Nombre: ";
	cin>>nom;
	cout<<"\t-> Apellido: ";
	cin>>ape;
	system("cls");
	fread(&paciente,sizeof(paciente), 1, H);
	
	while(!feof(H)){
		 	
		if(strcmp(paciente.nombre, nom)==0){
			
			if(strcmp(paciente.apellido, ape)==0){		   	
				Encabezado();
				cout<<"\t\tFORMATO DE ELIMINACIÓN DE PACIENTE\n"<<endl;
				cout<<"\tNOTA: La siguiente acción tendrá validez bajo declaración jurada."<<endl<<endl;
				cout<<"\tEliminar datos del paciente: \n";
				cout<<endl;
				cout<<"\t\tNombre: ";
				cout<<paciente.nombre<<endl;
				cout<<"\t\tApellido: ";
				cout<<paciente.apellido<<endl;
				cout<<"\t\tEdad: ";
				cout<<paciente.edad<<endl;
				cout<<"\t\tEstado: ";
				cout<<paciente.estado<<endl;
				cout<<"\t\tPatología previa: ";
				cout<<paciente.pat_previa<<endl;
				cout<<"\t\tSexo: ";
				cout<<paciente.sexo<<endl;
				cout<<"\t\tTratamiento: ";
				cout<<paciente.tratamiento<<endl;
				cout<<"\t\tHospital: ";
				cout<<paciente.hospital<<endl;
				strcmp(paciente.nombre,"");
				strcmp(paciente.apellido,"");
				strcmp(paciente.sexo,"");
				strcmp(paciente.pat_previa,"");
				strcmp(paciente.tratamiento,"");
				strcmp(paciente.hospital,"");
				strcmp(paciente.estado,"");
				paciente.edad=0;
				cout<<endl;
				cout<<"\t\t\t¿Está seguro que desea eliminar los datos del paciente "<<nom<<" "<<ape<<"?: "<<endl;
				cout<<"\t\t\tSí = [1] / No = [0] \n";
				 
				do{
					cout<<endl;
					cout<<"\t\t\t-> Digite una opción: ";
					cin>>respuesta;
				}while(respuesta!=0 && respuesta!=1);
				system("cls");
				
				if(respuesta==1){
					Encabezado();
					cout<<"\t\tFORMATO DE ELIMINACIÓN DE PACIENTE\n"<<endl;
					cout<<"\t\t\tEliminando datos del paciente\n";
					for(int i=1;i<=3;i++){
						Sleep(500);
						cout<<"\t\t\t\t\t..."<<endl;
					}
					Sleep(2000);
					cout<<endl;					
					fseek(H,ftell(H)-sizeof(paciente),SEEK_SET);
					fwrite(&paciente,sizeof(paciente),1,H);
					cout<<"\t\t\tSe eliminó con éxito \n";
					cout<<endl;
					getch();
				}
				fclose(H);
				return;
		    }
		}
			fread(&paciente,sizeof(paciente),1,H);
	}
	
	cout<<endl;
	cout<<"\t\t\t\t\tELIMINAR PACIENTE\n";
	cout<<"\t\t\t\t\t************************\n";
	cout<<endl;
	cout<<"\t\t\t\t***********************************\n";
	cout<<"\t\t\t\tERROR: EL PACIENTE NO ESTA REGISTRADO\n";
	cout<<"\t\t\t\t***********************************\n";
	cout<<endl;
	system("pause");
	fclose(H);
	return;
}

void verificaranalista(Analistas analista, FILE *F, Pacientes paciente, FILE *H){
	int respuesta=0;
	char usuario[50];
	char contrasena[50];
	
	Encabezado();
	cout<<"\t\tSISTEMA DE INICIO DE SESIÓN DE ANALISTA COVID-19"<<endl<<endl;
	F=fopen("Analistas.txt","rb+");
	
	if(F==NULL){
		cout<<"\t\t\t\t ERROR: ARCHIVO NO EXISTE\n";
		cout<<endl;
		system("pause");
	}
	
	cout<<"\tDigite sus datos de inicio de sesión:\n"<<endl;
	cout<<"\t-> USUARIO: ";
	cin>>usuario;
	
	cout<<"\t-> CONTRASEÑA: ";
	cin>>contrasena;
	system("cls");
	fread(&analista,sizeof(analista),1,F);
	
	while(!feof(F)){
		
		if(strcmp(analista.usuario,usuario)==0){
			
		   	if(strcmp(analista.contrasena,contrasena)==0){
			    Encabezado();
			    cout<<"\t\tSISTEMA DE INICIO DE SESIÓN DE ANALISTA COVID-19"<<endl<<endl;
		    	cout<<"\tIniciando sesión"<<endl;
		    	for(int i=1;i<=3;i++){
				Sleep(500);
				cout<<"\t\t..."<<endl;
				}
				Sleep(2500);
				cout<<endl;
			    system("cls");
			    respuesta=1;
			    seleccion1(paciente,H);		  
		    }
		}
		fread(&analista,sizeof(analista),1,F);
	}
	
	if(respuesta==0){
		Encabezado();
		cout<<"\t\tSISTEMA DE INICIO DE SESIÓN DE ANALISTA COVID-19"<<endl<<endl;
		cout<<"\tIniciando sesión"<<endl;
		for(int i=1;i<=3;i++){
			Sleep(500);
			cout<<"\t\t..."<<endl;
		}
		Sleep(2500);
		cout<<endl;		
		cout<<"\tUsuario y/o contraseña incorrectos"<<endl<<endl;
		cout<<"\tIntente nuevamente"<<endl;
		Sleep(2000);
	}
	fclose(F);
}

void Estadistica(FILE *H, Pacientes paciente){
	H=fopen("Pacientes.txt", "r");
	
	if(H==NULL){
		cout << "No se puede abrir el archivo";
		getch();
		exit(1);
	}
	int v[20],g[20],s[20];
	float conta_sm=0, conta_sf=0, total_p;
	float conta_pi=0, conta_i=0, conta_a=0, conta_j=0, conta_ad=0, conta_pm=0;
	float conta_r=0, conta_t=0, conta_f=0;
	float conta_er=0, conta_ec=0, conta_o=0, conta_h=0, conta_na=0;
	float conta_hidroxi=0, conta_iver=0, conta_azi=0;
	float p100_sm, p100_sf;
	float p100_pi, p100_i, p100_a, p100_j, p100_ad, p100_pm;
	float p100_r, p100_t, p100_f;
	float p100_er, p100_ec, p100_o, p100_h, p100_na;
	float p100_hidroxi, p100_iver, p100_azi;
	
	while(!feof(H)){
		fread(&paciente, sizeof(paciente), 1, H);
		
		if (!feof(H)){
		  if(paciente.edad!=0){
			
			if(strcmp(paciente.sexo, "Masculino")==0){
				conta_sm++;
			}
			
			else if(strcmp(paciente.sexo, "Femenino")==0){
				conta_sf++;
			}
	      }
		}
		
		if (!feof(H)){
		
		  if(paciente.edad!=0){
			
			if(paciente.edad>0 and paciente.edad<=5){
				conta_pi++;
			}
			else if(paciente.edad>=6 and paciente.edad<=11){
				conta_i++;
			}
			else if(paciente.edad==12 or paciente.edad==13){
				conta_a++;
			}
			else if(paciente.edad>=14 and paciente.edad<=26){
				conta_j++;
			}
			else if(paciente.edad>=27 and paciente.edad<=59){
				conta_ad++;
			}
			else if(paciente.edad>=60){
				conta_pm++;
			}
	      }
		}	
		
		if (!feof(H)){
		   if(paciente.edad!=0){	
			if(strcmp(paciente.estado, "RECUPERADO")==0){
				conta_r++;
			}
			
			else if(strcmp(paciente.estado, "EN TRATAMIENTO")==0){
				conta_t++;
			}
			
			else if(strcmp(paciente.estado, "FALLECIDO")==0){
				conta_f++;
			}			
	      }
		}	

		if (!feof(H)){
		   if(paciente.edad!=0){	
			if(strcmp(paciente.pat_previa, "E.respiratoria")==0){
				conta_er++;
			}
			
			else if(strcmp(paciente.pat_previa, "E.coronaria")==0){
				conta_ec++;
			}
			
			else if(strcmp(paciente.pat_previa, "Obesidad")==0){
				conta_o++;
			}
			
			else if(strcmp(paciente.pat_previa, "Hipertensión")==0){
				conta_h++;
			}
			
			else if(strcmp(paciente.pat_previa, "N.antecedente")==0){
				conta_na++;
			}												
          }
		}
		
		
		if (!feof(H)){
		  if(paciente.edad!=0){	
			if(strcmp(paciente.tratamiento, "HIDROXICLOROQUINA")==0 and strcmp(paciente.estado, "RECUPERADO")==0){
				conta_hidroxi++;
			}
			
			else if(strcmp(paciente.tratamiento, "IVERMECTINA")==0 and strcmp(paciente.estado, "RECUPERADO")==0){
				conta_iver++;
			}
			
			else if(strcmp(paciente.tratamiento, "AZITROMICINA")==0 and strcmp(paciente.estado, "RECUPERADO")==0){
				conta_azi++;
			}			
	      }											
        }
	}
	
	total_p=conta_sm+conta_sf;

	p100_r=(conta_r/total_p)*100;
	p100_t=(conta_t/total_p)*100;
	p100_f=(conta_f/total_p)*100;
		
	p100_sm=(conta_sm/total_p)*100;
	p100_sf=(conta_sf/total_p)*100;
	
	p100_pi=(conta_pi/total_p)*100;
	p100_i=(conta_i/total_p)*100;
	p100_a=(conta_a/total_p)*100;
	p100_j=(conta_j/total_p)*100;
	p100_ad=(conta_ad/total_p)*100;
	p100_pm=(conta_pm/total_p)*100;
	
	p100_er=(conta_er/total_p)*100;
	p100_ec=(conta_ec/total_p)*100;
	p100_o=(conta_o/total_p)*100;
	p100_h=(conta_h/total_p)*100;
	p100_na=(conta_na/total_p)*100;
	
	p100_hidroxi=(conta_hidroxi/total_p)*100;
	p100_iver=(conta_iver/total_p)*100;
	p100_azi=(conta_azi/total_p)*100;
	
	Encabezado();
	cout<<"\t\t\tANÁLISIS GENERAL COVID-19 - LIMA, PERÚ - 2020"<<endl;
	cout<<"\n\tRESUMEN GENERAL"<<endl;
	cout<<"\t*****************"<<endl;
	cout.precision(3);
	cout<<"Total de pacientes: "<<total_p<<endl;
	cout<<"Pacientes recuperados: "<<conta_r<<" -> "<<p100_r<<"%"<<endl;
	cout<<"Pacientes en tratamiento: "<<conta_t<<" -> "<<p100_t<<"%"<<endl;
	cout<<"Pacientes fallecidos: "<<conta_f<<" -> "<<p100_f<<"%"<<endl;
	cout<<"-> TASA DE MORTALIDAD: "<<conta_f/9674755<<"%"<<endl;
	cout<<"-> TASA DE LETALIDAD: "<<(conta_f/total_p)*100<<"%"<<endl;
	cout<<endl;
	g[0]=conta_t;
	g[1]=conta_f;
	g[2]=conta_r;
	graficageneral(g);
	
	cout<<"\n\tCASOS POR SEXO"<<endl;
	cout<<"\t*****************"<<endl;
	cout.precision(3);
	cout<<"Existen "<<conta_sm<<" hombre(s) de "<<total_p<<" pacientes: "<<p100_sm<<"%"<<endl;
	cout<<"Existen "<<conta_sf<<" mujer(es) de "<<total_p<<" pacientes: "<<p100_sf<<"%"<<endl;
	cout<<endl;
	s[0]=conta_sm;
	s[1]=conta_sf;
	graficasexo(s);
	
	cout<<"\n\tCASOS POR CICLO DE VIDA (EDAD)"<<endl;
	cout<<"\t**************************"<<endl;
	cout.precision(3);
	cout<<"Primera infancia (0-5 años): "<<conta_pi<<" -> "<<p100_pi<<"%"<<endl;
	cout<<"Infancia (6-11 años): "<<conta_i<<" -> "<<p100_i<<"%"<<endl;
	cout<<"Adolescencia (12-13 años): "<<conta_a<<" -> "<<p100_a<<"%"<<endl;
	cout<<"Juventud (14-26 años): "<<conta_j<<" -> "<<p100_j<<"%"<<endl;
	cout<<"Adultez (27-59 años): "<<conta_ad<<" -> "<<p100_ad<<"%"<<endl;
	cout<<"Persona mayor (60 años a más): "<<conta_pm<<" -> "<<p100_pm<<"%"<<endl;
	cout<<endl;
	v[0]=conta_pi;
	v[1]=conta_i;
	v[2]=conta_a;
	v[3]=conta_j;
	v[4]=conta_ad;
	v[5]=conta_pm;
	grafica(v);
	cout<<"\n\tCASOS SEGÚN PATOLOGÍA PREVIA"<<endl;
	cout<<"\t******************************"<<endl;
	cout.precision(3);
	cout<<"Enfermedad respiratoria: "<<conta_er<<" -> "<<p100_er<<"%"<<endl;
	cout<<"Enfermedad coronaria: "<<conta_ec<<" -> "<<p100_ec<<"%"<<endl;
	cout<<"Obesidad: "<<conta_o<<" -> "<<p100_o<<"%"<<endl;
	cout<<"Hipertensión: "<<conta_h<<" -> "<<p100_h<<"%"<<endl;
	cout<<"Ningún antecedente: "<<conta_na<<" -> "<<p100_na<<"%"<<endl;
	
	cout<<"\n\tEFICACIA DE TRATAMIENTOS"<<endl;
	cout<<"\t**************************"<<endl;
	cout.precision(3);
	cout<<"Hidroxicloroquina: "<<conta_hidroxi<<" -> "<<p100_hidroxi<<"%"<<endl;
	cout<<"Ivermectina: "<<conta_iver<<" -> "<<p100_iver<<"%"<<endl;
	cout<<"Azitromicina: "<<conta_azi<<" -> "<<p100_azi<<"%"<<endl;
	
	getch();
}
void buscarpaciente(FILE*H,Pacientes paciente){
		int respuesta;
	char nom[50];
	char ape[50];
	cout<<endl;
	cout<<"\t\t\t\t\t Ingrese al paciente que desea buscar\n";
	cout<<"\t\t\t\t\t ************************************\n";
	cout<<endl;
	H=fopen("Pacientes.txt","rb+");
	
	if(H==NULL){
		cout<<"\t\t\t\tERROR: ARCHIVO NO EXISTE\n";
		cout<<endl;
		getch();
		exit(1);
	}
	
	cout<<"\t\t\t\tIngrese el nombre y el apellido del paciente: \n";
	cout<<"\t\t\t\tNombre---> ";
	cin>>nom;
	
	cout<<"\t\t\t\tApellido---> ";
	cin>>ape;
	system("cls");
	fread(&paciente,sizeof(paciente), 1, H);
	
	while(!feof(H)){
		
		if(strcmp(paciente.nombre, nom)==0){
			
			if(strcmp(paciente.apellido, ape)==0){		   	
				cout<<endl;
				cout<<"\t\t\t\t\tBUSCANDO DATOS DEL PACIENTE \n";
				cout<<"\t\t\t\t\t *************************** \n";
				cout<<endl;
				cout<<"\t\t\t\tNombre---> ";
				cout<<paciente.nombre<<endl;
				cout<<"\t\t\t\tApellido---> ";
				cout<<paciente.apellido<<endl;
				cout<<"\t\t\t\tEdad---> ";
				cout<<paciente.edad<<endl;
				cout<<"\t\t\t\tHospital---> ";
				cout<<paciente.hospital<<endl;
				cout<<"\t\t\t\tPatología previa---> ";
				cout<<paciente.pat_previa<<endl;
				cout<<"\t\t\t\tSexo---> ";
				cout<<paciente.sexo<<endl;
				cout<<"\t\t\t\tTratamiento---> ";
				cout<<paciente.tratamiento<<endl;
				cout<<"\t\t\t\tEstado---> ";
				cout<<paciente.estado<<endl;
				system("pause");
				fclose(H);
				return;
		    }
		}
			fread(&paciente,sizeof(paciente),1,H);
   }	
	cout<<endl;
	cout<<"\t\t\t\t\tBUSCAR PACIENTE\n";
	cout<<"\t\t\t\t\t************************\n";
	cout<<endl;
	cout<<"\t\t\t\t***********************************\n";
	cout<<"\t\t\t\tERROR: EL PACIENTE NO ESTA REGISTRADO\n";
	cout<<"\t\t\t\t***********************************\n";
	cout<<endl;
	system("pause");
	fclose(H);
	return;
}
void grafica(int v[]){
	int contador;
	char edad[50];
	cout<<"\t\t\tGRAFICA SEGUN EDAD"<<endl;
	cout<<"\t\t\t------------------"<<endl;
	cout<<endl;
	for(int i=0;i<6;i++){
		contador=contador+1;
		switch(contador){
			case 1:
				strcpy(edad,"Primera infancia (0-5años)     ");
				break;
			case 2:
				strcpy(edad,"Infancia (6-11 años):          ");
				break;
			case 3:
				strcpy(edad,"Adolescencia (12-13 años):     ");
				break;
			case 4:
				strcpy(edad,"Juventud (14-26 años):         ");
				break;
			case 5:
				strcpy(edad,"Adultez (27-59 años):          ");
				break;
			case 6:
				strcpy(edad,"Persona mayor (60 años a más): ");
				break;
			
		}
		cout<<edad;
		for(int j=0;j<v[i];j++){
          cout<<"*";
       }
       cout<<endl;
	}
	cout<<endl;
}
void graficasexo(int v[]){
	int contador;
	char sexo[50];
	cout<<"\t\t\tGRAFICA SEGUN SEXO"<<endl;
	cout<<"\t\t\t------------------"<<endl;
	cout<<endl;
	for(int i=0;i<2;i++){
		contador=contador+1;
		switch(contador){
			case 1:
				strcpy(sexo,"MASCULINO:     ");
				break;
			case 2:
				strcpy(sexo,"FEMENINO:      ");
				break;
			
		}
		cout<<sexo;
		for(int j=0;j<v[i];j++){
          cout<<"*";
       }
       cout<<endl;
	}
	cout<<endl;
}
void graficageneral(int v[]){
	int contador;
	char general[50];
	cout<<"\t\t\tGRAFICA GENERAL"<<endl;
	cout<<"\t\t\t---------------"<<endl;
	cout<<endl;
	for(int i=0;i<3;i++){
		contador=contador+1;
		switch(contador){
			case 1:
				strcpy(general,"EN_TRATAMIENTO:    ");
				break;
			case 2:
				strcpy(general,"FALLECIDOS:        ");
				break;
			case 3:
				strcpy(general,"RECUPERADOS:       ");
				break;
			
		}
		cout<<general;
		for(int j=0;j<v[i];j++){
          cout<<"*";
       }
       cout<<endl;
	}
	cout<<endl;
}
void modificarpaciente(Pacientes paciente,FILE*H){
	int op, res;
	char nom[50], ape[50];
	cout << endl;
	H = fopen("Pacientes.txt", "rb+");
	
	if(H == NULL){
		cout << "No se encontro el archivo" << endl;
		system("pause");
	}
	
	cout << "Ingrese nombre: ";
	cin >> nom;
	cout << "Ingrese apellido: ";
	cin >> ape;
	system("cls");
	fread(&paciente, sizeof(paciente), 1, H);
	while(!feof(H)){
		if(strcmp(paciente.nombre,nom)==0 && strcmp(paciente.apellido,ape)==0){
			do{
				cout << endl;
			    cout << "Nombre: " << paciente.nombre << endl;
			    cout << "Apellido: " << paciente.apellido << endl;
			    cout << "Edad: " << paciente.edad << endl;
			    cout << "Sexo: " << paciente.sexo << endl;
			    cout << "Patologia previa: " << paciente.pat_previa << endl;
			    cout << "Tratamiento: " << paciente.tratamiento << endl;
			    cout << "Hospital: " << paciente.hospital << endl;
			    cout << "Estado: " << paciente.estado << endl;
			    cout << endl;
			    cout << "\tSeleccione el dato que desea modificar" << endl;
			    cout<<"\t----------------------------------------"<<endl;
			    cout << "1. Nombre" << endl;
			    cout << "2. Apellido" << endl;
			    cout << "3. Edad "<< endl;
			    cout << "4. Sexo" << endl;
			    cout << "5. Patologia Previa" << endl;
			    cout << "6. Tratamiento" << endl;
			    cout << "7. Hospital" << endl;
			    cout << "8. Estado" << endl;
			    cout << "9. Confirmar datos" << endl;
			do{
				cout<<"DIGITE UNA OPCION --> ";
				cin >> op;
			}while(op>9 && op<1);
			cout<<"\t\t\t\tMODIFICANDO DATOS"<<endl;
			cout<<"\t\t\t\t******************"<<endl;
			switch(op){
				case 1:
					cout << "Ingrese nuevo nombre: ";
					fflush(stdin);
					gets(paciente.nombre);
					system("pause");
					break;
				case 2:
					cout << "Ingrese nuevo apellido: ";
					fflush(stdin);
					gets(paciente.apellido);
					system("pause");
					break;
				case 3:
					cout << "Ingrese nueva edad: ";
					cin>>paciente.edad;
					system("pause");
					break;
				case 4:
					cout << "Ingrese nuevo sexo: ";
					fflush(stdin);
					gets(paciente.sexo);
					system("pause");
					break;
				case 5:
					cout << "Ingrese nueva patologia: ";
					fflush(stdin);
					gets(paciente.pat_previa);
					system("pause");
					break;
				case 6:
					cout << "Ingrese nuevo tratamiento: ";
					fflush(stdin);
					gets(paciente.tratamiento);
					system("pause");
					break;
				case 7:
					cout << "Ingrese nuevo hospital: ";
					fflush(stdin);
					gets(paciente.hospital);
					system("pause");
					break;
				case 8:
					cout << "Ingrese nuevo estado del paciente: ";
					fflush(stdin);
					gets(paciente.estado);
					system("pause");
					break;
				case 9:
					cout<<"\t\t\t\t ESTA SEGURO QUE DESEA GUARDAR LOS DATOS? \n";
					cout<<"\t\t\t\t           SI = [1] / NO = [0] \n";
					do{
					cout<<endl;
					cin>>res;
					}while(res!=1 && res!=0);
					system("cls");
					if(res==1){
						cout << endl;
						cout << "----------Datos guardados----------";
						cout<<endl;
						system("pause");
						fseek(H,ftell(H)-sizeof(paciente),SEEK_SET);
						fwrite(&paciente,sizeof(paciente),1,H);
						fclose(H);
		             	return;
					}
					fclose(H);
		           	return;
					break;
					
			}system("cls");
			}while(op != 9);
		}
		fread(&paciente, sizeof(paciente), 1, H);
	}cout<<endl;
	cout<<"\t\t\t\t\t MODIFICAR DATOS \n";
	cout<<"\t\t\t\t\t *************** \n";
	cout<<endl;
	cout<<"\t\t\t\t ******************************************************* \n";
	cout<<"\t\t\t\t ERROR: NO SE ENCUENTRA REGISTRADO EL PACIENTE DIGITADO \n";
	cout<<"\t\t\t\t ******************************************************* \n";
	cout<<endl;
	system("pause");
	fclose(H);
	return;
}
void ModificarAnalista(FILE* F, Analistas analista){
	F = fopen("Analistas.txt", "rb+");
	
	if (F == NULL){
		cout<<"No se encontro el archivo"<<endl;
	}	
	
	char usu[50];
	char con[50];
	int op;
	int res;
	
	cout << "Ingrese usuario: ";
	cin >> usu;
	cout << "Ingrese contraseña: ";
	cin >> con;
	
	fread(&analista, sizeof(analista), 1, F);
	while(!feof(F)){
		if(strcmp(analista.usuario, usu) == 0 && strcmp(analista.contrasena, con) == 0){
			do{
				cout<<endl;
				cout << "Nombre: ";
				cout << analista.nombre << endl;
				cout << "Usuario: ";
				cout << analista.usuario << endl;
				cout << "Contraseña: ";
				cout << analista.contrasena << endl;
				cout<<endl;
				cout << "Seleccion el dato a modificar" << endl;
				cout << "1. Nombre" << endl;
				cout << "2. Usuario" << endl;
				cout << "3. Contraseña" << endl;
				cout << "4. Confirmar datos" << endl;
				cout<<"Ingrese una opcion --> "<<endl;
				cin >> op;
				cout<<"\t\t\t\tMODIFICANDO USUARIO"<<endl;
		     	cout<<"\t\t\t\t******************"<<endl;
				switch(op){
					case 1:
						cout << "Ingrese nuevo nombre: ";
						fflush(stdin);
						gets(analista.nombre);
						system("cls");
						break;
					case 2:
						cout << "Ingrese nuevo usuario: ";
						fflush(stdin);
						gets(analista.usuario);
						system("cls");
						break;
					case 3:
						cout << "Ingrese nueva contraseña: ";
						fflush(stdin);
						gets(analista.contrasena);
						system("cls");
						break;
					case 4:
						cout<<"\t\t\t\t ESTA SEGURO QUE DESEA GUARDAR LOS DATOS? \n";
						cout<<"\t\t\t\t           SI = 1 / NO = 0 \n";
						do{
						cout<<endl;
						cin>>res;
						}while(res!=1 && res!=0);
						system("cls");
						if(res==1){
							cout << endl;
							cout << "----------Datos guardados----------";
							cout<<endl;
							system("pause");
							fseek(F,ftell(F)-sizeof(analista),SEEK_SET);
							fwrite(&analista,sizeof(analista),1,F);
							fclose(F);
			             	return;
						}
						fclose(F);
		           		return;
						break;
				}
			}while(op != 4);
        }
		fread(&analista, sizeof(analista), 1, F);
	}cout<<endl;
	cout<<"\t\t\t\t\t MODIFICAR USUARIO \n";
	cout<<"\t\t\t\t\t *************** \n";
	cout<<endl;
	cout<<"\t\t\t\t ******************************************************* \n";
	cout<<"\t\t\t\t ERROR: NO SE ENCUENTRA REGISTRADO ESTE ANALISTA \n";
	cout<<"\t\t\t\t ******************************************************* \n";
	cout<<endl;
	system("pause");
	fclose(F);
	return;    
}
