
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string>
#include <chrono>
#include <iomanip>

#pragma comment(lib, "ws2_32.lib")

using namespace std;
using namespace chrono;

// Return common service names
string getServiceName(int port)
{
    switch (port)
    {
        case 21:   return "FTP";
        case 22:   return "SSH";
        case 23:   return "Telnet";
        case 25:   return "SMTP";
        case 53:   return "DNS";
        case 80:   return "HTTP";
        case 110:  return "POP3";
        case 143:  return "IMAP";
        case 443:  return "HTTPS";
        case 3306: return "MySQL";
        case 3389: return "RDP";
        case 5432: return "PostgreSQL";
        case 8080: return "HTTP-Proxy";
        default:   return "Unknown";
    }
}

// Check whether a TCP port accepts a connection
bool isPortOpen(const sockaddr_in& target, int port)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET)
        return false;

    // Enable non-blocking mode
    u_long mode = 1;
    if (ioctlsocket(sock, FIONBIO, &mode) == SOCKET_ERROR)
    {
        closesocket(sock);
        return false;
    }

    sockaddr_in server = target;
    server.sin_port = htons(static_cast<u_short>(port));

    int result = connect(
        sock,
        reinterpret_cast<sockaddr*>(&server),
        sizeof(server)
    );

    bool open = false;

    if (result == 0)
    {
        open = true;
    }
    else if (WSAGetLastError() == WSAEWOULDBLOCK)
    {
        fd_set writeSet;
        fd_set errorSet;

        FD_ZERO(&writeSet);
        FD_ZERO(&errorSet);

        FD_SET(sock, &writeSet);
        FD_SET(sock, &errorSet);

        // Connection timeout: 300 milliseconds
        timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 300000;

        result = select(
            0, nullptr, &writeSet, &errorSet, &timeout
        );

        if (result > 0 && FD_ISSET(sock, &writeSet))
        {
            int socketError = 0;
            int length = sizeof(socketError);

            if (getsockopt(
                    sock, SOL_SOCKET, SO_ERROR,
                    reinterpret_cast<char*>(&socketError),
                    &length) == 0 && socketError == 0)
            {
                open = true;
            }
        }
    }

    closesocket(sock);
    return open;
}

int main()
{
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cout << "Error: Winsock initialization failed.\n";
        return 1;
    }

    string hostname;
    int startPort, endPort;
    int openPorts = 0;

    cout << "\n========================================\n";
    cout << "       ADVANCED NETWORK PORT SCANNER\n";
    cout << "========================================\n";
    cout << "Scan only systems you are authorized to test.\n\n";

    cout << "Enter IP address or hostname: ";
    cin >> hostname;

    cout << "Enter starting port (1-65535): ";
    if (!(cin >> startPort))
    {
        cout << "Invalid starting port input.\n";
        WSACleanup();
        return 1;
    }

    cout << "Enter ending port (1-65535): ";
    if (!(cin >> endPort))
    {
        cout << "Invalid ending port input.\n";
        WSACleanup();
        return 1;
    }

    if (startPort < 1 || endPort > 65535 ||
        startPort > endPort)
    {
        cout << "Invalid port range!\n";
        WSACleanup();
        return 1;
    }

    // Resolve IP address or hostname
    addrinfo hints = {};
    addrinfo* addresses = nullptr;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int lookup = getaddrinfo(
        hostname.c_str(), nullptr, &hints, &addresses
    );

    if (lookup != 0 || addresses == nullptr)
    {
        cout << "Error: Could not resolve target hostname/IP.\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in target =
        *reinterpret_cast<sockaddr_in*>(addresses->ai_addr);

    char resolvedIP[INET_ADDRSTRLEN] = {};

    inet_ntop(
        AF_INET, &target.sin_addr,
        resolvedIP, sizeof(resolvedIP)
    );

    freeaddrinfo(addresses);

    int totalPorts = endPort - startPort + 1;

    cout << "\nTarget: " << hostname;
    cout << "\nResolved IP: " << resolvedIP;
    cout << "\nPort range: " << startPort
         << "-" << endPort;
    cout << "\n----------------------------------------\n";

    cout << left << setw(12) << "PORT"
         << setw(18) << "SERVICE"
         << "STATUS\n";
    cout << "----------------------------------------\n";

    auto scanStart = steady_clock::now();

    for (int port = startPort; port <= endPort; port++)
    {
        if (isPortOpen(target, port))
        {
            cout << left << setw(12) << port
                 << setw(18) << getServiceName(port)
                 << "OPEN\n";
            openPorts++;
        }
    }

    auto scanEnd = steady_clock::now();

    double elapsed = duration<double>(
        scanEnd - scanStart
    ).count();

    cout << "\n========================================\n";
    cout << "             SCAN SUMMARY\n";
    cout << "========================================\n";
    cout << "Target IP       : " << resolvedIP << '\n';
    cout << "Ports scanned   : " << totalPorts << '\n';
    cout << "Open ports      : " << openPorts << '\n';
    cout << "Closed/filtered : "
         << totalPorts - openPorts << '\n';
    cout << fixed << setprecision(2);
    cout << "Time taken      : " << elapsed << " seconds\n";
    cout << "Scan completed!\n";
    cout << "========================================\n";

    WSACleanup();

    cout << "\nPress Enter to exit...";
    cin.ignore(10000, '\n');
    cin.get();

    return 0;
}




