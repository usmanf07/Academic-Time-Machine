/*
        TCP_Client. This Program will implement the Client Side for TCP_Socket Programming.
        It will get some data from user and will send to the server and as a reply from the
        server, it will get its data back.
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>

void invert_vowels(char* str){
	int found = 0;
	int j = 0;
	int k;
	int i = 0;
	while (i < strlen(str)){
		if(str[i+1] == 0){
			if (found==0){
				k = i-1;
				while (j < k){
					char temp = str[j];
					str[j] = str[k];
					str[k] = temp;
					k--;
					j++;
				}
				found = 0;
				j = i+1;
			}
			else{
				j = i+1;
				found = 0;
			}
			
		} 
		if(str[i] == ' '){
			if (found==0){
				k = i-1;
				while (j < k){
					char temp = str[j];
					str[j] = str[k];
					str[k] = temp;
					k--;
					j++;
				}
				found = 0;
				j = i+1;
			}
			else{
				j = i+1;
				found = 0;
			}
			
		} 
		if(str[i]=='a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u'){
			found = 1;
		}
		i++;
	}
	
}
int main(void)
{
        int socket_desc;
        struct sockaddr_in server_addr;
        char server_message[2030], client_message[2030];
        
        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Specifying the IP and Port of the server to connect
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2020);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        //Now connecting to the server accept() using connect() from client side
        
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
                printf("Connection Failed. Error!!!!!");
                return -1;
        }
        
        printf("Connected\n");
        printf("Enter Message\n");
       	gets(client_message);
        printf("%s", client_message);
        printf("%c", '\n');
        //Send the message to Server
        
        if(send(socket_desc, client_message, strlen(client_message),0) < 0)
        {
                printf("Send Failed. Error!!!!\n");
                return -1;
        }
        
        //Receive the message back from the server
        
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Server Message: %s\n",server_message);
        invert_vowels(server_message);
        printf("Inverted: %s\n", server_message);
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Closing the Socket
        
        close(socket_desc);
        
        return 0;
}
