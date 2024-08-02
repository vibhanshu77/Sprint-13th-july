#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include<limits.h>

#include "../include/loggers.h"
#include "../include/server_functions.h"

#define SIZE 16000
#define MYPORT 15602

int main()
{
	int serverSocket, connectionSocket;
   	// Create a TCP socket 
    	LOG_INFO("Creating Socket %s", "");
	logMessage(INFO, "Creating Socket.");
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    	if(serverSocket == -1)
    	{
		LOG_FATAL("Socket creation failed %s\n", "");
		logMessage(FATAL, "Socket creation failed");
    	    	exit(EXIT_FAILURE);
    	}
    	
	 // Bind to a specific port
	LOG_INFO("Binding to port %s", "");
	logMessage(INFO, "Binding to port");
    	struct sockaddr_in serverAddress;
    	serverAddress.sin_family = AF_INET;
    	serverAddress.sin_port = htons(MYPORT);
    	serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    	if(bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
    	{
		LOG_FATAL("Bind failed %s", "");
		logMessage(FATAL, "Bind failed ");
    	    	exit(EXIT_FAILURE);
   	}
    	
	 // listening for connections
	LOG_INFO("Listening for incoming connections %s", "");
    	logMessage(INFO, "Listening for incoming connections");
	if(listen(serverSocket, 5) == -1)
    	{
		LOG_FATAL("Listen failed %s", "");
    	    	logMessage(FATAL, "Listen failed ");
    	    	exit(EXIT_FAILURE);
    	}

	// Accept incoming connection
    	LOG_INFO("Server Listening on port. %d\n", MYPORT);
	logMessage(INFO, "Server Listening on port. %d\n", MYPORT);
    	connectionSocket = accept(serverSocket, NULL, NULL);
        if(connectionSocket == -1)
        {
		LOG_FATAL("Accept failed %s", "");
		logMessage(FATAL, "Accept failed ");
                exit(EXIT_FAILURE);
        }	

	 // Accept connections and handle client requests
	while(1)
    	{
		int choice;
	 	// Receive client choice		
		recv(connectionSocket, &choice, sizeof(choice), 0);
        	LOG_INFO("Choice of client - %d", choice);
        	
		char buffer[SIZE] = "";
        	char result[SIZE] = "";
				
		switch(choice)
        	{
        	    case 1 :    recv(connectionSocket, buffer, sizeof(buffer), 0);	 // Search for file
				searchForFile(buffer, result);
        	                send(connectionSocket, result, sizeof(result), 0);
        	            	break;
        	            
        	    case 2 :    recv(connectionSocket, buffer, sizeof(buffer), 0);	 // Search for string in filesystem
        	                searchForString(buffer, result);
				send(connectionSocket, result, sizeof(result), 0);
				if (strcmp(result, "") == 0) 
				{
        	            		break;
        	        	}
        	       	 	strcpy(result, "");
        	        	recv(connectionSocket, buffer, sizeof(buffer), 0);
        	        	if (strcmp(buffer, "") == 0) 
				{
        	        		break;
        	        	}
        	        	displayFileContent(buffer, result);
				send(connectionSocket, result, sizeof(result), 0);
			    	break;
        	    
		    case 3 : 	recv(connectionSocket, buffer, sizeof(buffer), 0);	// Display file content
				displayFileContent(buffer, result);
        	                send(connectionSocket, result, sizeof(result), 0);
        	            	break;
        	            
        	    case 4 :    LOG_INFO("Exiting execution %s", "");
				logMessage(INFO, "Exiting execution ");
        	   		LOG_INFO("Closing socket now %s", "");
    				logMessage(INFO, "Closing Socket Now. ");
    				close(connectionSocket);
    				close(serverSocket);
    				LOG_INFO("Socket is now closed %s", "");
    				logMessage(INFO, "Socket is now closed.");
				exit(EXIT_SUCCESS);
                    
        	    default :
				LOG_WARN("Invalid choice from client %s", "");
				logMessage(WARN, "Invalid choice from client ");
				break;
		}
    	}

    close(connectionSocket);
    return 0;
}
