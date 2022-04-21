#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <sstream>
 
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <queue>


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Write server name: " << std::endl;
        return 1;
    } 
  const std::string serverName = "/tmp/" + std::string(argv[1]);
  key_t key = ftok("progfile", 65);
  int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("Cannot create message queue\n");
        return 1;
    }
    std::string msg;
      //std::queue<msg> msg_queue;
     // if(msg_queue.empty()){
         // std::cout<<"Cannot pop message: ";
  //    }
      //msg_queue.pop_back();
    int bytes_count = msgrcv(msgid, &msg.c_str(), sizeof(msg), 1, 0);
    if (bytes_count == -1)
    {
        perror("Unable to receive a message.\n");
        return 1;
    }
	std::cout<<"Data received: %s \n",msg;
	msgctl(msgid, IPC_RMID, NULL);
     while(true)
    {
        const int server = open(serverName.c_str(), O_RDONLY);
        if (server == -1)
        {
            std::cout << "Error: " << std::strerror(errno) << std::endl;
            return 1;
        }
 
        char sizeBuffer[4];
        if (read(server, sizeBuffer, 4) == 0)
        {
            std::cout << "Error: " << std::strerror(errno) << std::endl;
            continue;
        }    
        if(std::string(sizeBuffer) == "exit"){
        	close(server);
        	unlink(serverName.c_str());
        	break;
        }
 
        std::size_t             bufferSize = std::stoi(sizeBuffer) + 1;
        char* buffer = new char[bufferSize];
        if (read(server, buffer, bufferSize) == 0)
        {
            std::cout << "Error: " << std::strerror(errno) << std::endl;
            continue;
        }
 
        close(server);
        std::cout << "Info: Received: " << sizeBuffer << " " << buffer << std::endl;
      
        char op;
        stream >> op;

        double left;
        stream >> left;

        double right;
        stream >> right;

        double result = 0;
        switch(op)
        {
            case '+': result = left + right; break;
            case '-': result = left - right; break;
            case '*': result = left * right; break;
            case '/': result = left / right; break;
            default:
                break;
        }

        if (clientName.empty())
        {
            std::cout << "Error: Incorrect client name." << std::endl;
            continue;
        }

        std::string resultStr     = std::to_string(result);
        std::string resultStrSize = std::to_string(resultStr.size());
        if (resultStrSize.size() < 4)
            resultStrSize.insert(0, 4 - resultStrSize.size(), '0');

        resultStr = resultStrSize + ' ' + resultStr;        

        const int client = open(clientName.c_str(), O_WRONLY);
        if (client == -1)
        {
            std::cout << "Error: " << std::strerror(errno) << std::endl;
            continue;
        }

        if (write(client, resultStr.c_str(), resultStr.size()) == -1)
        {
            std::cout << "Error: " << std::strerror(errno) << std::endl;
            continue;
        }
        close(client);
    return 0;
}


