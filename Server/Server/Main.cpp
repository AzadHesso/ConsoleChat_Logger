#include <iostream>
#include "Server.h"
#include "Chat_Server.h"

using namespace std;

int main() {
    try {
        string serverMessage, clientMessage;
        Server server;
        Chat chat;

        server.createSocket();
        server.bindSocket();
        server.dataReceivingServer();

        while (true) {
            clientMessage = server.readData();
            if (clientMessage == "exit") {
                break;
            }
            serverMessage = chat.messageProcessing(clientMessage);
            server.writeData(serverMessage);
        }

        server.closeSocket();
    }
    catch (const std::runtime_error& e) {
        cerr << "Runtime error: " << e.what() << endl;
        return 1;
    }
    catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "Unknown error occurred" << endl;
        return 1;
    }

    return 0;
}