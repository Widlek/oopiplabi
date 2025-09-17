#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <algorithm>

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

    // Привязка сокета к адресу и порту
    sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(1280);
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR) {
        std::cout << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    // Прослушивание входящих подключений
    if (listen(s, 5) == SOCKET_ERROR) {
        std::cout << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port 1280..." << std::endl;

    // Основной цикл сервера
    while (true) {
        // Принятие подключения
        sockaddr_in remote_addr;
        int size = sizeof(remote_addr);
        SOCKET s2 = accept(s, (struct sockaddr*)&remote_addr, &size);
        if (s2 == INVALID_SOCKET) {
            std::cout << "Accept failed with error: " << WSAGetLastError() << std::endl;
            closesocket(s);
            WSACleanup();
            return 1;
        }

        std::cout << "Client connected!" << std::endl;

        // Общение с клиентом
        char b[255];
        int recvResult;

        while ((recvResult = recv(s2, b, sizeof(b), 0)) > 0) {
            b[recvResult] = '\0'; // Добавляем нулевой терминатор
            std::cout << "Received: " << b << std::endl;

            // Парсинг данных: x1, y1, x2, y2, x, y
            double x1, y1, x2, y2, x, y;
            std::istringstream iss(b);
            if (iss >> x1 >> y1 >> x2 >> y2 >> x >> y) {
                // Определяем границы прямоугольника
                double left = std::min(x1, x2);
                double right = std::max(x1, x2);
                double bottom = std::min(y1, y2);
                double top = std::max(y1, y2);

                // Проверяем, находится ли точка внутри прямоугольника
                bool inside = (x >= left) && (x <= right) && (y >= bottom) && (y <= top);
                
                // Формируем ответ
                std::string response = inside ? "Yes" : "No";
                send(s2, response.c_str(), response.size(), 0);
                std::cout << "Sent response: " << response << std::endl;
            } else {
                // В случае ошибки парсинга
                std::string error = "Error: Invalid input format";
                send(s2, error.c_str(), error.size(), 0);
                std::cout << "Invalid input format received" << std::endl;
            }
        }

        if (recvResult == 0) {
            std::cout << "Connection closed by client." << std::endl;
        } else {
            std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
        }

        closesocket(s2);
    }

    // Закрытие сокета и очистка Winsock
    closesocket(s);
    WSACleanup();
    return 0;
}
