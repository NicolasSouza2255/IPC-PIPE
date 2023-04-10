//Servidor Named Pipe - testado com CLion
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib> 

#define BUFFER_SIZE 1024

using namespace std;
double time1, timedif;

struct Esteira {
    int PesoTotal = 0; // peso de cada item
    int TotalItensProcessados = 0; // quantidade de itens processados
};


int main()
{
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD dwRead;

    // Create named pipe
    hPipe = CreateNamedPipe("\\\\.\\pipe\\pipeso",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1,
        BUFFER_SIZE,
        BUFFER_SIZE,
        0,
        NULL);

	// Wait for client to connect
	cout << "Esperando o cliente conectar..." << endl;
	if (!ConnectNamedPipe(hPipe, NULL))
	{
		cout << "Falha em conectar ao cliente. Codigo do erro: %d" + GetLastError();
		CloseHandle(hPipe);
		return 1;
	}

	time1 = (double)clock();
	time1 = time1 / CLOCKS_PER_SEC;

    if (hPipe == INVALID_HANDLE_VALUE)
    {
       cout << "Falha em criar o pipe. Codigo do erro: "+  GetLastError();
        return 1;
    }

	Esteira esteira1;
	Esteira esteira2;
	int contador = 0;
	while (esteira1.TotalItensProcessados + esteira2.TotalItensProcessados < 500)
	{
		if (ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL))
		{
			int peso = stoi(buffer);
			contador++;
			if (peso >= 5)
			{
				esteira1.PesoTotal += peso;
				esteira1.TotalItensProcessados++;
				cout << "Esteira 1: Quantidade itens processados: " << esteira1.TotalItensProcessados << " peso processado: " << peso << "Kg" << endl;
			}
			else
			{
				esteira2.PesoTotal += peso;
				esteira2.TotalItensProcessados++;
				cout << "Esteira 2: Quantidade itens processados: " << esteira2.TotalItensProcessados << " peso processado: " << peso << "Kg" << endl;
			}
			if (contador % 10 == 0 && contador != 0)
			{
				system("cls");
				cout << "Peso total: " << esteira1.PesoTotal + esteira2.PesoTotal << "Kg. Quantidade itens processados: " << esteira1.TotalItensProcessados + esteira2.TotalItensProcessados << endl;
			}
		}
		else
		{
			cout << "Erro ao ler do pipe!" << endl;
			return 1;
		}
	}

	timedif = (((double)clock()) / CLOCKS_PER_SEC) - time1;
	cout << "Tempo Total " << timedif << endl;

	CloseHandle(hPipe);
    return 0;
}