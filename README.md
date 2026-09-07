# 🔐 Network Port Scanner

A simple **TCP Network Port Scanner** developed using **C++**.
The project scans a specified host within a given port range and identifies which ports are open or closed.

> ⚠️ **Disclaimer:** Use this tool only on systems, devices, or networks that you own or have explicit permission to scan.

## 📌 Features

* Scan a specified IP address or hostname
* Specify starting and ending port numbers
* Detect open and closed TCP ports
* Display common services associated with ports
* Count the total number of open ports
* Simple command-line interface
* Suitable for learning basic network security and socket programming

## 🛠️ Technologies Used

* **C++**
* TCP/IP
* Socket Programming
* Windows Winsock API
* Networking & Cybersecurity Concepts

## ⚙️ How It Works

1. The user enters the target IP address or hostname.
2. The user provides a port range.
3. The program attempts to establish a TCP connection with each port.
4. If a connection is successful, the port is considered **OPEN**.
5. If the connection fails, the port is considered **CLOSED**.
6. The program displays the scan results.

## 💻 Example

```text
========================================
        NETWORK PORT SCANNER
========================================

Enter IP Address: 127.0.0.1
Enter Starting Port: 20
Enter Ending Port: 100

Scanning...

Port 21  : OPEN   (FTP)
Port 22  : OPEN   (SSH)
Port 23  : CLOSED
Port 25  : CLOSED
Port 53  : OPEN   (DNS)
Port 80  : OPEN   (HTTP)

----------------------------------------
Scan Completed!
Open Ports Found: 3
----------------------------------------
```

## 📚 Common Ports

| Port  | Service | Purpose             |
| ----- | ------- | ------------------- |
| 20/21 | FTP     | File Transfer       |
| 22    | SSH     | Secure Remote Login |
| 23    | Telnet  | Remote Login        |
| 25    | SMTP    | Email               |
| 53    | DNS     | Domain Name System  |
| 80    | HTTP    | Web Traffic         |
| 443   | HTTPS   | Secure Web Traffic  |

## 🚀 How to Run

### Using Dev-C++

1. Open **Dev-C++**.
2. Create a new C++ source file.
3. Add the project source code.
4. Make sure the **Winsock library** is linked.
5. Compile and run the program.
6. For testing, use:

```text
127.0.0.1
```

## 🎯 Learning Objectives

* Understand TCP ports and network services
* Learn basic socket programming in C++
* Understand how port scanning works
* Identify commonly used network services
* Gain practical knowledge of network security

## 🔮 Future Improvements

* Multithreaded scanning
* Service/version detection
* Scan multiple hosts
* Export results to a text or CSV file
* Add a graphical user interface
* Add timeout configuration
* Improve scanning speed

## 👩‍💻 Author

**Sanjana Mallick**

B.Tech CSIT — Cybersecurity

