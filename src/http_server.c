/* ===============================================================
 * 
 * http_server.c - A basic HTTP server in C
 *
 * Author: Keith Fernandez
 * Date: 2025-03-25
 * Description:
 *   - This program implements a simple HTTP 1.1 server.
 *   - Listens on port 8080 and accepts incoming connections.
 *   - Processes GET requests and returns a static HTML response.
 *   - Demonstrates basic socket programming for HTTP handling.
 *
 * Usage:
 *   Compile: gcc -o http_server http_server.c
 *   Run: ./http_server
 *   Test: Open a web browser and visit http://localhost:8080
 *
 * Future Enhancements:
 *   - Serve dynamic content and static files.
 *   - Implement multi-threading for handling multiple clients.
 *   - Support additional HTTP methods (e.g., POST, PUT, DELETE).
 *
 * ===============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0) {
        perror("recv");
        close(client_socket);
        return;
    }
    
    buffer[bytes_received] = '\0';  // Null-terminate the buffer
    printf("Received Request:\n%s\n", buffer);

    // Basic HTTP response
    const char *http_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 48\r\n"
        "\r\n"
        "<html><body><h1>Welcome to My HTTP Server</h1></body></html>";
    
    send(client_socket, http_response, strlen(http_response), 0);
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create a TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) < 0) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("HTTP Server listening on port %d...\n", PORT);

    while (1) {
        // Accept client connections
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}


