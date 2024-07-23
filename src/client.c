#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include<limits.h>


#define SIZE 10000 
#define MYPORT 15836 

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if(clientSocket == -1)
    {
        perror("Socket Creation is Failed.");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in serverAddress;
    //memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(MYPORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    
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
        
        send(clientSocket, &choice, sizeof(choice), 0);
        
	switch(choice)
        {
            case 1 :	;
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
                	    	strcat(basePath, "/home2/user16/Sprint-13th-july/data");
                	}
                	scanf("%s", buffer);
                	strcat(basePath, buffer);
                	send(clientSocket, basePath, sizeof(buffer), 0);
               		recv(clientSocket, buffer, sizeof(buffer), 0);
                        printf("Server Response : \n %s \n", buffer);
            
                    break;
                    
            case 2 :	printf("Enter String : ");
                	getchar();
                	scanf("%[^\n]s", buffer);
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
                    		scanf("%[^\n]s", buffer);
                    		send(clientSocket, buffer, sizeof(buffer), 0);
                    		recv(clientSocket, buffer, sizeof(buffer), 0);
                    		printf("Server response:\n%s\n", buffer);
                	} 
			else 
			{
                    		send(clientSocket, "", sizeof(buffer), 0);
                	}
                    break;
            
            case 3 :	printf("Enter File Path : ");
                	getchar();
                	scanf("%[^\n]s", buffer);
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
        }
    }
    return 0;
}
