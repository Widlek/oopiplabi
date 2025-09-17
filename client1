#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

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
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        std::cout << "Socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Настройка адреса сервера
    sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(1280);
    peer.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Подключение к серверу
    if (connect(s, (struct sockaddr*)&peer, sizeof(peer)) == SOCKET_ERROR) {
        std::cout << "Connect failed with error: " << WSAGetLastError() << std::endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server!" << std::endl;

    // Ввод данных от пользователя
    double x1, y1, x2, y2, x, y;
    std::cout << "Enter rectangle coordinates (x1 y1 x2 y2): ";
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << "Enter point coordinates (x y): ";
    std::cin >> x >> y;

    // Формирование строки для отправки
    std::ostringstream oss;
    oss << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x << " " << y;
    std::string data = oss.str();

    // Отправка данных
    if (send(s, data.c_str(), data.size(), 0) == SOCKET_ERROR) {
        std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    // Получение ответа от сервера
    char response[255];
    int recvResult = recv(s, response, sizeof(response), 0);
    if (recvResult > 0) {
        response[recvResult] = '\0';
        std::cout << "Point is inside rectangle: " << response << std::endl;
    } else if (recvResult == 0) {
        std::cout << "Connection closed by server." << std::endl;
    } else {
        std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
    }

    // Закрытие сокета и очистка Winsock
    closesocket(s);
    WSACleanup();

    system("pause");
    return 0;
}
