#include <iostream>
#include <winsock2.h>
#include <windows.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    
    // Start Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cout << "Winsock initialization failed!" << endl;
        return 1;
    }

    char ip[100];
    int startPort, endPort;
    int openPorts = 0;

    cout << "======================================" << endl;
    cout << "        NETWORK PORT SCANNER" << endl;
    cout << "======================================" << endl;

    cout << "\nEnter IP Address: ";
    cin >> ip;

    cout << "Enter Starting Port: ";
    cin >> startPort;

    cout << "Enter Ending Port: ";
    cin >> endPort;

    if (startPort < 1 || endPort > 65535 || startPort > endPort)
    {
        cout << "\nInvalid port range!" << endl;
        WSACleanup();
        return 1;
    }

    cout << "\nScanning " << ip << "...\n\n";

    for (int port = startPort; port <= endPort; port++)
    {
        SOCKET sock;
        
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock == INVALID_SOCKET)
        {
            cout << "Could not create socket!" << endl;
            break;
        }

        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = inet_addr(ip);

        // Set connection timeout
        DWORD timeout = 300;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,
                   (char*)&timeout, sizeof(timeout));

        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO,
                   (char*)&timeout, sizeof(timeout));

        int result = connect(
            sock,
            (sockaddr*)&server,
            sizeof(server)
        );

        if (result == 0)
        {
            cout << "Port " << port << " : OPEN" << endl;
            openPorts++;
        }

        closesocket(sock);
    }

    cout << "\n======================================" << endl;
    cout << "Scan Completed!" << endl;
    cout << "Open Ports Found: " << openPorts << endl;
    cout << "======================================" << endl;

    WSACleanup();

    system("pause");

    return 0;
}



