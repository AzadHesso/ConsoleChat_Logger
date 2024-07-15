#include "Server.h"

void Server::createSocket()
{
#if defined (_WIN32) || (_WIN64)
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw runtime_error("Winsock initialization error!");
    }

    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == INVALID_SOCKET) {
        throw runtime_error("Creation of Socket failed!");
    }
    else {
        cout << "Socket creation was successful.!" << endl;
    }
#elif defined (__linux__)
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        throw runtime_error("Creation of Socket failed!");
    }
    else {
        cout << "Socket creation was successful.!" << endl;
    }
#endif
}

void Server::bindSocket()
{
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;
    bind_status = bind(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (bind_status == -1) {
        throw runtime_error("Socket binding failed!");
    }
    else {
        cout << "The socket binding was successful!" << endl;
    }
}

void Server::closeSocket()
{
#if defined (_WIN32) || (_WIN64)
    closesocket(socket_file_descriptor);
    WSACleanup();
#elif defined (__linux__)
    close(socket_file_descriptor);
#endif 
}

void Server::dataReceivingServer()
{
    connection_status = listen(socket_file_descriptor, 5);

    if (connection_status == -1) {
        throw runtime_error("Socket is unable to listen for new connections!");
    }
    else {
        cout << "Server is listening for new connection: " << endl;
    }

    length = sizeof(client);
    connection = accept(socket_file_descriptor, (struct sockaddr*)&client, &length);

    if (connection == -1) {
        throw runtime_error("Server is unable to accept the data from client!");
    }
    else {
        cout << "The client has joined!" << endl;
    }
}

char* Server::readData()
{
    memset(message, '\0', MESSAGE_LENGTH);

#if defined (_WIN32) || (_WIN64)
    int bytesReceived = recv(connection, message, MESSAGE_LENGTH, 0);
#elif defined (__linux__)
    int bytesReceived = read(connection, message, MESSAGE_LENGTH);
#endif

    if (bytesReceived < 0) {
        throw runtime_error("Failed to read data from client!");
    }

    cout << "Data received from client: " << message << endl;
    return message;
}

void Server::writeData(string serverMessage)
{
    memset(message, '\0', MESSAGE_LENGTH);
    strcpy_s(message, serverMessage.c_str());

#if defined (_WIN32) || (_WIN64)
    int bytesSent = send(connection, message, strlen(message), 0);
#elif defined (__linux__)
    ssize_t bytesSent = write(connection, message, strlen(message));
#endif

    if (bytesSent < 0) {
        throw runtime_error("Failed to send data to client!");
    }

    cout << "Data successfully sent to the client.!" << message << endl;
}

