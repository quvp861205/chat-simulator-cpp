// SocketCliente.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "SocketCliente.h"

using namespace std;

void main()
{

	long SUCCESSFUL;
	WSAData WinSockData;
	WORD DLLVERSION;

	DLLVERSION = MAKEWORD(2,1);

	SUCCESSFUL = WSAStartup(DLLVERSION, &WinSockData);

	string RESPONSE;
	string CONVERTER;
	char MESSAGE[200];

	SOCKADDR_IN  ADDRESS;

	SOCKET sock;
	
	//Ciclo Infinito para enviar y recibir informacion al SocketServidor
	do
	{
		//Iniciamos con la conexion al servidor
		sock = socket(AF_INET, SOCK_STREAM, NULL);

		//datos del servidor
		ADDRESS.sin_addr.s_addr = inet_addr("10.26.59.34");
		ADDRESS.sin_family = AF_INET;
		ADDRESS.sin_port = htons(444);


		//Solicitamos por consola el mensaje a enviar
		cout << "\tTu>> ";
		getline(cin, RESPONSE);
		strcpy(MESSAGE, RESPONSE.c_str());
	
		//Si es nulo se finaliza la aplicacion
		if(RESPONSE=="")
			exit;

		//nos conectamos al servidor 
		connect(sock, (SOCKADDR*)&ADDRESS, sizeof(ADDRESS));		
		
		//enviamos mensaje al servidor
		SUCCESSFUL = send(sock, MESSAGE, 46, NULL);

		//se queda congelada la aplicacion hasta recibir una respuesta del servidor
		SUCCESSFUL = recv(sock, MESSAGE, sizeof(MESSAGE), NULL);
		
		//Mostramos la respuesta del servidor
		cout << "\tServidor>> " << MESSAGE << endl;
	
		//Cerramos la conexion al socket
		closesocket(sock);

	}while(true);

}