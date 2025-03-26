/* =================================================================
 *
 * Author: Keith Michelangelo Fernandez
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
 * ===============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 4096

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Send HTTP GET request
    const char *http_request = 
        "GET / HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Connection: close\r\n"
        "\r\n";
    
    send(sock, http_request, strlen(http_request), 0);

    // Read response
    int bytes_received;
    while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    close(sock);
    return 0;
}

