#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;
int main(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    // Create socket file descriptor
    if((server_fd=socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("Socket Failed");
        exit(EXIT_FAILURE);
    }

        // Define the address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8000);

    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("Bind Failed");
        exit(EXIT_FAILURE);
    }
    
    if(listen(server_fd, 3) < 0){
        perror("Listen Failed");
        exit(EXIT_FAILURE);
    }

    cout<<"Server is running on port 8000"<<endl;

    while(true){
        if((new_socket = accept(server_fd, (struct sockaddr *)&address ,(socklen_t *)&addrlen)) < 0){
                perror("Accept Failed");
                exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};

        ssize_t bytes_read = read(new_socket,buffer,30000);
        if(bytes_read < 0) {
                perror("Read failed");
                close(new_socket);
                continue;
        }else{
                cout<<"Received request \n" << buffer << endl;            
        }
        string http_response = 
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-lenght: 12\n\n"
            "Hello World";
      
        send(new_socket, http_response.c_str(), http_response.size(), 0);
        cout<<"Response sent"<<endl;
        close(new_socket);
    }
     return 0;

}
