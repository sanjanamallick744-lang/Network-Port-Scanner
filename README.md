# Advanced Network Port Scanner

## About the Project
The **Advanced Network Port Scanner** is a C++-based cybersecurity tool that identifies open TCP ports on a target IP address or hostname. It uses the Windows Sockets API (Winsock) to test connections and displays useful information about detected ports.

## Features
- **IP and Hostname Support:** Accepts an IP address or domain name.
- **Custom Port Range:** Scan a specific range of TCP ports.
- **Service Identification:** Displays common service names such as HTTP, HTTPS, SSH, FTP, and MySQL based on port numbers.
- **Non-Blocking Connections:** Uses non-blocking sockets and `select()` with a connection timeout.
- **Scan Summary:** Displays total ports scanned, open ports, other ports not detected as open, and scan duration.
- **Input Validation:** Checks the entered port range and handles invalid input.
- **Error Handling:** Handles Winsock initialization and hostname resolution errors.

## Technologies Used
- **Programming Language:** C++
- **Networking API:** Windows Sockets API (Winsock)
- **Libraries:** `iostream`, `winsock2.h`, `ws2tcpip.h`, `windows.h`, `string`, `chrono`, and `iomanip`
- **Compiler:** MinGW-w64 G++

## Requirements
- Windows operating system
- Visual Studio Code or another C++ IDE
- MinGW-w64 G++ compiler
- Winsock library (`ws2_32`)

## How to Compile and Run

**Step 1: Save the source code**

Save the program as `port_scanner.cpp`.

**Step 2: Open the terminal**

Navigate to the directory containing your source file.

**Step 3: Compile the program**

```bash
g++ port_scanner.cpp -o port_scanner.exe -lws2_32
```

**Step 4: Run the program**

```bash
./port_scanner.exe
```

## Example Output

```text
========================================
       ADVANCED NETWORK PORT SCANNER
========================================

Enter IP address or hostname: 127.0.0.1
Enter starting port (1-65535): 75
Enter ending port (1-65535): 90

PORT        SERVICE           STATUS
----------------------------------------
80          HTTP              OPEN

========================================
             SCAN SUMMARY
========================================
Target IP       : 127.0.0.1
Ports scanned   : 16
Open ports      : 1
Closed/filtered : 15
Time taken      : 0.05 seconds
Scan completed!
```

*Note: This is sample output. Actual results depend on the target system and network conditions.*

## How It Works
1. Initializes Winsock for network communication.
2. Accepts a target IP address or hostname.
3. Resolves the hostname into an IPv4 address.
4. Validates the specified port range.
5. Attempts TCP connections to each port using non-blocking sockets.
6. Identifies ports that accept connections and displays their commonly associated service names.
7. Calculates the scan duration and displays a summary.

## Learning Outcomes
- Understanding TCP/IP networking fundamentals.
- Learning how TCP ports and services work.
- Implementing socket programming in C++.
- Using non-blocking sockets and connection timeouts.
- Understanding basic network reconnaissance techniques.
- Practicing input validation and error handling.

## Limitations
- Supports TCP scanning only; UDP scanning is not implemented.
- Service names are inferred from port numbers and are not verified through service detection.
- Ports that fail to respond within the timeout may be closed, filtered, or unreachable.
- Scanning a large port range can take longer depending on network conditions.

## Ethical Use
This tool is intended for educational purposes and authorized security testing only. Scan your own devices or systems for which you have explicit permission. Unauthorized scanning may violate applicable policies or laws.

## Future Improvements
- Export scan results to a text or CSV report.
- Add a scan progress indicator.
- Implement configurable connection timeouts.
- Add verified service detection.
- Support optional concurrent scanning for improved performance.

## Author
**Sanjana Mallick**

B.Tech CSIT (Cybersecurity)

## License
This project is available for educational and learning purposes.

