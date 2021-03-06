
#include "SerialClass.h" // Biblioteca para acceder al puerto serie
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define DIM 30
struct CANCION
{
	char nombre[DIM];
	char artista[DIM];
};

void GuardarCancionesFichero(struct CANCION);
int BuscarCancion(struct CANCION, char*, int);
int BuscarArtista(struct CANCION, char*, int);
void llamararduino(void);

int main()
{
	int contador = 4;
	int encontrar = 0;
	int opcion = 0;
	int i, j = 0, k = 0;
	int resultado, resultado1;
	char nombre[DIM];
	char nombre1[DIM];
	struct CANCION canciones[4] = {
			{"Lose Yourself","Eminem"},
			{"Talking to the Moon","Bruno Mars"},
			{"Leave the door open","Bruno Mars"},
			{"Beautiful Mistakes","Maroon 5"}
	};
	for (i = 0; i < 4; i++)
	{
		GuardarCancionesFichero(canciones[i]);
	}

	//menu
	do
	{
		printf("********ESTE ES EL MENU**********\n");
		printf("\n\t1.-Buscar Cancion\n\t2.-Buscar Artista\n\t3.- Reproducir Cancion\n\t0.-Salir\n\n");
		scanf_s("%d", &opcion);
		getchar();
		system("cls");
		switch (opcion)
		{
		case 1:
		{
			printf("Introduce el nombre de la cancion que desea buscar:");
			gets_s(nombre, 20);
			do
			{
				resultado = BuscarCancion(canciones[j], nombre, j);
				j++;
			} while ((resultado + 1) != j && j <= 4);
			j = 0;
			if (resultado >= 0 && resultado <= 3)
			{
				printf("\n\n\nAqui esta la cancion que buscaba -----> ");
				printf("  %s  de  %s\n\n", canciones[resultado].nombre, canciones[resultado].artista);
			}
			else
			{
				printf("No se ha encontrado su busqueda\n");
			}


			break;
		}
		case 2:
		{
			printf("Introduce el nombre del artista que desea buscar:");
			gets_s(nombre1, 20);
			do
			{
				resultado1 = BuscarArtista(canciones[k], nombre1, k);

				if (resultado1 >= 0 && resultado1 <= 3)
				{
					encontrar++;
					printf("\n\nAqui esta las canciones del artista que buscaba -----> ");
					printf("  %s  de  %s\n", canciones[resultado1].nombre, canciones[resultado1].artista);
				}
				printf("\n");
				k++;
			} while (k <= 4);
			k = 0;
			if (encontrar == 0)
			{
				printf("\nNo se ha encontrado su busqueda\n\n\n");
			}
			encontrar = 0;

			break;
		}
		case 3:
		{
			printf("Yendo al reproductor de musica...\n");

			//funcion llamar a arduino
			llamararduino();
			system("pause");
			break;
		}
		case 0:
		{
			printf("Saliendo del menu\n");
			break;
		}
		}

	} while (opcion != 0);

	return 0;
}


void GuardarCancionesFichero(struct CANCION canciones)
{
	FILE* fichero;
	errno_t error;
	//int j;
	error = fopen_s(&fichero, "Playlist.txt", "a");
	if (error == 0)
	{
		fprintf(fichero, "%s", canciones.nombre);
		fprintf(fichero, " \t");

		fprintf(fichero, "%s", canciones.artista);
		fprintf(fichero, " \n");

		fclose(fichero);
	}

	else
	{
		printf("No se ha podido abrir el fichero joder\n");
	}

	return;
}


int BuscarCancion(struct CANCION canciones, char* nombre, int i)
{
	int resultado = -1;
	int orden, j;
	char* cancion = canciones.nombre;

	for (j = 0; nombre[j] != '\0'; j++)
	{
		if (nombre[j] >= 'a' && nombre[j] <= 'z')
			nombre[j] = nombre[j] - 'a' + 'A';
	}
	for (j = 0; cancion[j] != '\0'; j++)
	{
		if (cancion[j] >= 'a' && cancion[j] <= 'z')
			cancion[j] = cancion[j] - 'a' + 'A';
	}

	orden = strcmp(nombre, cancion);
	if (orden == 0)
	{
		resultado = i;
	}
	return resultado;
}

int BuscarArtista(struct CANCION canciones, char* nombre1, int k)
{
	int resultado1 = -1;
	int orden, j;
	char* artista = canciones.artista;

	for (j = 0; nombre1[j] != '\0'; j++)
	{
		if (nombre1[j] >= 'a' && nombre1[j] <= 'z')
			nombre1[j] = nombre1[j] - 'a' + 'A';
	}
	for (j = 0; artista[j] != '\0'; j++)
	{
		if (artista[j] >= 'a' && artista[j] <= 'z')
			artista[j] = artista[j] - 'a' + 'A';
	}
	orden = strcmp(nombre1, artista);
	if (orden == 0)
	{
		resultado1 = k;
	}
	return resultado1;
}

void llamararduino(void)
{
Serial* Arduino;
char puerto[]="COM5"; // Puerto serie en el que est?? conectado Arduino
char BufferEntrada[200];
int bytesRecibidos;

Arduino = new Serial((char *)puerto); // Crea conexi??n l??gica con Arduino
if(Arduino->IsConnected())
printf("Arduino conectado\n");
else
printf("Error\n");
while(Arduino->IsConnected())
{

 bytesRecibidos = Arduino->ReadData(BufferEntrada, sizeof(char)*199);
 if (bytesRecibidos != -1) // Lectura de mensaje desde el puerto
 {
 BufferEntrada[bytesRecibidos - 1] = '\0';
 printf(" %s\n",BufferEntrada);
 }
 else
 Sleep(1000);
 }
}