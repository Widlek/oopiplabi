#include <winsock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Инициализация Winsock
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        std::cout << "WSAStartup failed with error: " << err << std::endl;
        return 1;
    }

    // Создание сокета
    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == INVALID_SOCKET) {
        std::cout << "Socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Настройка адреса сервера
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1024);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Ввод данных от пользователя
    std::string romanNumber;
    std::cout << "Enter a Roman number: ";
    std::cin >> romanNumber;

    // Отправка данных серверу
    int sendResult = sendto(s, romanNumber.c_str(), romanNumber.size(), 0,
        (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    if (sendResult == SOCKET_ERROR) {
        std::cout << "sendto failed with error: " << WSAGetLastError() << std::endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    // Получение ответа от сервера
    char buffer[1024];
    int serverAddrSize = sizeof(serverAddr);
    int bytesReceived = recvfrom(s, buffer, sizeof(buffer), 0,
        (struct sockaddr*)&serverAddr, &serverAddrSize);

    if (bytesReceived == SOCKET_ERROR) {
        std::cout << "recvfrom failed with error: " << WSAGetLastError() << std::endl;
    }
    else {
        buffer[bytesReceived] = '\0';
        std::cout << "Arabic number: " << buffer << std::endl;
    }

    // Закрытие сокета и очистка Winsock
    closesocket(s);
    WSACleanup();

    return 0;
}