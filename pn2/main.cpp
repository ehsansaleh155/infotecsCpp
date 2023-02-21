#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main( )
{

    int port = 8585;
    int sockfd;
    struct sockaddr_in si_me, si_other;
    char buffer[64];
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&si_me, '\0', sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = inet_addr("127.0.0.1");

    int data = 0; 

    while (true)
    {
        cout << "Listening ..." << endl;
        bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));
        addr_size = sizeof(si_other);
        recvfrom(sockfd, buffer, 64, 0, (struct sockaddr*)& si_other, &addr_size);
        cout << "Data Received: " << buffer << endl;

        //Check the data and display result accordingly    
        data = atoi(buffer);
        if (data > 9 ) { 
            cout << "The data is more than two characters!" << endl;
            if (data % 32 == 0) {
                cout << "The data is a multiple of 32!" << endl; 
            } else {
                cout << "The data is NOT a multiple of 32!!!" << endl;
            }
            
        } 
        else { cout << "The received data is less than two characters!!!" << endl; } 
    }

    return 0;
}