#include "stdafx.h"
#include "SocketServer.h"

using namespace std;

void main()
{
	long SUCCESSFUL;
	WSAData WinSockData;
	WORD DLLVERSION;

	DLLVERSION = MAKEWORD(2,1);

	SUCCESSFUL = WSAStartup(DLLVERSION, &WinSockData);

	SOCKADDR_IN ADDRESS;
	int AddressSize = sizeof(ADDRESS);


	SOCKET sock_LISTEN;
	SOCKET sock_CONNECTION;

	//datos de este servidor
	sock_CONNECTION = socket(AF_INET, SOCK_STREAM, NULL);
	ADDRESS.sin_addr.s_addr = inet_addr("10.26.59.34");
	ADDRESS.sin_family = AF_INET;
	ADDRESS.sin_port = htons(444);

	sock_LISTEN = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sock_LISTEN, (SOCKADDR*)&ADDRESS, sizeof(ADDRESS));
	listen(sock_LISTEN, SOMAXCONN);

	string RESPONSE;
	string CONVERTER;
	char MESSAGE[200];

	int contador = 0;

	cout << "Esperando a alguien....";

	for(;;)
	{
		//Este ciclo permite recibir un mensaje de un cliente y luego enviarle un mensaje, esto se repite
		//No se puede enviar dos mensajes, tiene que ser recibir 1 mensaje y enviar 1 mensaje


		//esperamos alguna conexion
		if( sock_CONNECTION = accept(sock_LISTEN, (SOCKADDR*)&ADDRESS, &AddressSize))
		{	
			//Recibimos el mensaje del cliente
			SUCCESSFUL = recv(sock_CONNECTION, MESSAGE, sizeof(MESSAGE), NULL);
			CONVERTER = MESSAGE;
			cout << "\r\tCliente>> " << CONVERTER << endl;
			
			//Enviamos un mensaje al cliente
			cout << "\tTu>> ";
			getline(cin, CONVERTER);	
			strcpy(MESSAGE, CONVERTER.c_str());
			SUCCESSFUL = send(sock_CONNECTION, MESSAGE, 46, NULL);		
		}
		
	}
}
