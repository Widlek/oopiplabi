#include <winsock2.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#pragma comment(lib, "ws2_32.lib")

// ������� ��� �������������� �������� ����� � ��������
int romanToArabic(const std::string& roman) {
    std::map<char, int> romanMap = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };

    int result = 0;
    int prevValue = 0;

    for (int i = roman.length() - 1; i >= 0; i--) {
        int currentValue = romanMap[toupper(roman[i])];

        if (currentValue < prevValue) {
            result -= currentValue;
        }
        else {
            result += currentValue;
        }

        prevValue = currentValue;
    }

    return result;
}

int main() {
    // ������������� Winsock
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        std::cout << "WSAStartup failed with error: " << err << std::endl;
        return 1;
    }

    // �������� ������
    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == INVALID_SOCKET) {
        std::cout << "Socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // �������� ������ � ������ � �����
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1024);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    std::cout << "UDP Server is listening on port 1024..." << std::endl;

    // �������� ���� �������
    while (true) {
        char buffer[1024];
        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);

        // ��������� ������ �� �������
        int bytesReceived = recvfrom(s, buffer, sizeof(buffer), 0,
            (struct sockaddr*)&clientAddr, &clientAddrSize);

        if (bytesReceived == SOCKET_ERROR) {
            std::cout << "recvfrom failed with error: " << WSAGetLastError() << std::endl;
            continue;
        }

        buffer[bytesReceived] = '\0';
        std::string romanNumber(buffer);

        std::cout << "Received Roman number: " << romanNumber << std::endl;

        // �������������� �������� ����� � ��������
        int arabicNumber = romanToArabic(romanNumber);
        std::string response = std::to_string(arabicNumber);

        // �������� ������ �������
        int sendResult = sendto(s, response.c_str(), response.size(), 0,
            (struct sockaddr*)&clientAddr, clientAddrSize);

        if (sendResult == SOCKET_ERROR) {
            std::cout << "sendto failed with error: " << WSAGetLastError() << std::endl;
        }
        else {
            std::cout << "Sent Arabic number: " << response << std::endl;
        }
    }

    // �������� ������ � ������� Winsock
    closesocket(s);
    WSACleanup();
    return 0;
}