/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include<stdbool.h>

int main(void)
{
        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;
        char server_message[2000], client_message[2000];

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
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        //Put the socket into Listening State
        
        if(listen(socket_desc, 1) < 0)
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Listening for Incoming Connections.....\n");
        
        //Accept the incoming Connections
	int i=0;
	while(i==0)
	{
        
		client_size = sizeof(client_addr);
		client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
		
		if (client_sock < 0)
		{
		        printf("Accept Failed. Error!!!!!!\n");
		        return -1;
		}
		
		printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		
		//Receive the message from the client
		
		if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
		{
		        printf("Receive Failed. Error!!!!!\n");
		        return -1;
		}
		
		printf("Client Message: %s\n",client_message);
		
		//Send the message back to client
		

		//strcpy(server_message, client_message);
		//server_message = "Hello I am server. Your received id is ";
		char returntext[50]="h";
		int size=0;
                int realsize=0;
                bool invertcheck=false;
                int servermsgsize=0;
		while(client_message[size]!='\0')
		{
			realsize++;
			
		}
		while(size<realsize)
		{
                        invertcheck=false;
			int i=0;
			int j=0;
			while(client_message[size]!=' '||client_message[size]!='.'||client_message[size]!='\0'||client_message[size]!=',')
			{
                               returntext[i]=client_message[size];
                              
                               if(client_message[size+1]==' '||client_message[size+1]=='.'||client_message[size+1]=='\0'||client_message[size+1]==',')
                                {
                                        returntext[i+1]='\0';
                                       // i++;
                                }
                               size++;
                               i++;

                        }
                        printf("first while : %s\n",returntext);
                        for(j=0;j<i;j++)
                        {
                                if(returntext[j]=='a'||returntext[j]=='e'||returntext[j]=='i'||returntext[j]=='o'||returntext[j]=='u')
                                {
                                        invertcheck=true;

                                }

                        }
                        if(invertcheck==true)
                        {
                                char temp;
                                int k=0;
                                int a=0;
                                for( k=0 , a=i-1;k<(i/2);k++ , a--)
                                {
                                        temp =returntext[k];
                                        returntext[k]=returntext[a];
                                        returntext[a]=temp;
                                }
                        }
                           int b=0;	
                        for(b=0;b<i;b++)
                        {
                                server_message[servermsgsize]=returntext[b];
                                servermsgsize++;
                                if(returntext[b+1]=='\0')
                                {
                                        server_message[servermsgsize]=' ';
                                        servermsgsize++;
                                }
                        }
                        size++;
			printf("converted text is : %s\n",server_message);
                       
						
		}

                printf("msg : %s\n",server_message);
			
		if (send(client_sock, server_message, servermsgsize+2,0)<0)
		{
		        printf("Send Failed. Error!!!!!\n");
		        return -1;
		}
		
		memset(server_message,'\0',sizeof(server_message));
		memset(client_message,'\0',sizeof(client_message));
		      
		//Closing the Socket
        }
        close(client_sock);
        close(socket_desc);
        return 0;       
}
