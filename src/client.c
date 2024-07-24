#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include<limits.h>


#define SIZE 16000 
#define MYPORT 15836 

int main()
{   // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if(clientSocket == -1)
    {
        perror("Socket Creation is Failed.");
        exit(EXIT_FAILURE);
    }
    // Connect to the server
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(MYPORT);			 // Server port
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");	 // Server IP address
    
    if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
    {
        perror("Connection is not done.");
        exit(EXIT_FAILURE);
    }
   
    int choice;
    char buffer[SIZE];

    
    while(1)
    {
	strcpy(buffer, "");
        printf("Options : \n");
        printf("1 . Search for a file \n");
        printf("2 . Search for a string \n");
        printf("3 . Display the content of file \n");
        printf("4 . Exit \n");
        printf("\nEnter your Choice : ");
        
        scanf("%d", &choice);
	getchar();
        
        send(clientSocket, &choice, sizeof(choice), 0);
        
	switch(choice)						
        {
            case 1 :	;						// Search for file
			int case1SubChoice = 0;
		    	printf("    1. Enter with path\n");
                	printf("    2. Enter without path\n");
                	printf("    Enter Choice: ");
               		scanf("%d", &case1SubChoice);
                	getchar();
                	char basePath[SIZE] = "";
			if (case1SubChoice == 1){
                		printf("Enter the Path: ");
			}
                	if (case1SubChoice == 2) {
				printf("Enter Filename : ");
                	    	strcat(basePath, "/home2/user16/code/data");
                	}
                	scanf("%s", buffer);
                	strcat(basePath, buffer);
                	send(clientSocket, basePath, sizeof(buffer), 0);
               		recv(clientSocket, buffer, sizeof(buffer), 0);
                        printf("Server Response : \n %s \n", buffer);
            
                    break;
                    
            case 2 :	printf("Enter String : ");		// Search for a string in the filesystem
			fgets(buffer, sizeof(buffer), stdin);
			buffer[strcspn(buffer, "\n")] = 0;
			send(clientSocket, buffer, sizeof(buffer), 0);
               	 	recv(clientSocket, buffer, sizeof(buffer), 0);
                	printf("Server response : \n %s \n", buffer);
                	if (strcmp(buffer, "") == 0) 
			{
                		printf("This string was not found in any file\n\n");
                	   	break;
                	}
                	int case2SubChoice = 0;
                	printf("    1. View a file\n");
                	printf("    2. Do not view file\n");
                	printf("    Enter Choice: ");
                	scanf("%d", &case2SubChoice);
                	getchar();
                	if (case2SubChoice == 1) 
			{
                    		printf("    Enter the path: ");
                    		fgets(buffer, sizeof(buffer), stdin);
                        	buffer[strcspn(buffer, "\n")] = 0;
                    		send(clientSocket, buffer, sizeof(buffer), 0);
                    		recv(clientSocket, buffer, sizeof(buffer), 0);
                    		printf("Server response:\n%s\n", buffer);
                	}
			else
			{
				send(clientSocket, "", 1, 0);
				printf("\n\n");
			}	

                    break;
            
            case 3 :	printf("Enter File Path : ");			//  Display the content of a file
                	fgets(buffer, sizeof(buffer), stdin);
                        buffer[strcspn(buffer, "\n")] = 0;
			send(clientSocket, buffer, sizeof(buffer), 0);
                	recv(clientSocket, buffer, sizeof(buffer), 0);
                	printf("Server response:\n%s\n", buffer);
                    
		    break;
                    
            case 4 : 
                        close(clientSocket);
			printf("EXITED.\n");
                        exit(EXIT_FAILURE);
                    
            default :
                        printf("Invalid Choice \n");
			break;
        }
    }
    close(clientSocket);
    return 0;
}
