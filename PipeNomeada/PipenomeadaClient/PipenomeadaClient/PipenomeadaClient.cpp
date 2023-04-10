//Cliente named pipe - Testato no CLion
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib> 
#include <ctime>   

#define BUFFER_SIZE 1024

using namespace std;

int main()
{
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD dwRead, dwWritten;

    // Open named pipe
    hPipe = CreateFile("\\\\.\\pipe\\pipeso",
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);

    if (hPipe == INVALID_HANDLE_VALUE)
    {
       cout << " Falha em abrir o pipe. Codigo do erro:" + GetLastError() << endl;
        return 1;
    }

    cout << " Conectado ao servidor!"<<endl ;

	while (true)
	{
		srand(time(0));
		int pesoAleatorio = rand() % 10 + 1;

		//
		// Enviar peso pelo pipe
		string strPesoAleatorio = to_string(pesoAleatorio);
		if (WriteFile(hPipe, strPesoAleatorio.c_str(), strPesoAleatorio.length(), &dwWritten, NULL))
		{
			if (pesoAleatorio >= 5) {
				cout << "Dado Enviado ao Servidor " << endl;
				Sleep(1000);
			}
			
			else {
				cout << "Dado Enviado ao Servidor " << endl;
				Sleep(500);
			}
		}
		else
		{
			cout << "Erro ao escrever no pipe!" << endl;
			return 1;
		}
	}

    // Close named pipe and exit
    CloseHandle(hPipe);
    return 0;
}