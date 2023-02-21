
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <algorithm> //for the all_of() in thread1Function
#include <string>
#include <string.h>
#include <mutex>
#include <condition_variable>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;

//-----------------------------------------------------
//shared buffer for storing data from user input  
string shared_buffer; 

//mutex for synchronizing access to shared buffer  
mutex mtx; 

//condition variable for signaling when data is available in the buffer  
condition_variable cv; 

//buffer ready to be used in thread 2
bool buffer_ready;
//-----------------------------------------------------
void thread1Function() {
    while (true) {
        string user_input; 
        cout << "\nEnter a string of numbers without any spaces, which does not exceed 64 characters: " << endl; 
        cin >> user_input;
        if (user_input.length() > 64 || !all_of(user_input.begin(), user_input.end(), ::isdigit)) { 
            cout << "Invalid input!" << endl; 
            continue;
        }

        //sort the string in descending order and replace all even numbers with 'KB'   
        sort(user_input.begin(), user_input.end(), greater<char>());
        string newStr; //to create new string with "KB" for even numbers
        for (int i = 0; i < user_input.length(); i++) {    
            if ((user_input[i] - '0') % 2 == 0) { // convert char to int and check if even number  
                newStr += "KB"; // replace with KB  
            } else { 
                newStr += user_input[i]; // keep the same  
            } 
        }

        //lock the mutex and update the shared buffer with new data from newStr   
        unique_lock<mutex> lck(mtx);
        shared_buffer = move(newStr);
        buffer_ready = true;
        lck.unlock();
        cv.notify_one(); //notify thread2 that new data is available in the buffer
        lck.lock();
        cv.wait(lck, [](){ return buffer_ready == false; });
    }
}
//-----------------------------------------------------
void thread2Function() {
    int port = 8585;
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[64];
    socklen_t addr_size;

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    string stringbuffer;

    while (true) {
        string receivedData;
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, [](){ return buffer_ready; });
        receivedData = move(shared_buffer);
        buffer_ready = false; 
        lck.unlock();
        cout << "\nReceived Data: " << receivedData << endl; 
        int sum = 0; 
        // for (char ch : receivedData) { if (isdigit(ch)) sum += (int)ch;
        for (int i = 0; i < receivedData.length(); i++) {    
            if (isdigit(receivedData[i])) { 
                sum += receivedData[i] - '0'; 
            } 
        }
        cout << "Sum of all numerical elements: " << sum << endl;
        cv.notify_one();
        lck.lock();

        //transfer to program number 2
        memset(buffer, 0, 64); // clear the buffer
        stringbuffer = to_string(sum);
        for (int i=0; i < stringbuffer.length(); i++) {
            buffer[i] = stringbuffer[i];
        }
        sendto(sockfd, buffer, 64, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        cout << "Sent Data to program number 2: " << buffer << endl;
        
    }
    
}
//-----------------------------------------------------

int main() {
    cout << "Good day!\nPlease wait for the program to warm up the engines!\n" << endl; 
    
    std::thread t1(thread1Function);
    std::thread t2(thread2Function);

    t1.join();
    t2.join();

    return 0;
}