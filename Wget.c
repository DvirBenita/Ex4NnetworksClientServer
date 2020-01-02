#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SIM_LENGTH 10 
#define PORT 80 
#define MAXIMUM  1024

int main(int argc, char* argv[])
{ 
  struct sockaddr_in client_name; 
  int sock, more_read;
  char hostn[100];
  char route[100];
  char* url;
  char* prefix="http://";
  struct addrinfo* res;
  struct sockaddr_in* saddr;
  char buff[MAXIMUM];
int port;
  
  if (argc != 2) {
    perror(" hostnlookup <hostn>\n");
    exit(1);
  }

  url = argv[1];

  // check if url has a "http://" in the beggining
  if (strncmp(url, prefix, 7) != 0) {
    printf("\nno http:// found\n");
    exit(1);
  }

  // cut the http:// from the hostn
 sscanf(url, "http://%99[^/]/%99[^\n]", hostn, route);

  // check if its a valid hostn
  if (0 != getaddrinfo(hostn, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostn %s\n", hostn);
    exit(1);
  }

  printf("Client is alive and establishing socket connection.\n");
  
  
  // Create a new socket of type ipv4 and TCP, without stating the protocol and returning its ptr
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("Error create socket");
      close(sock);
      exit(1);
    }

  saddr = (struct sockaddr_in*)res->ai_addr;

  
  bzero(&client_name, sizeof(client_name)); // set all values in the buff to zero
  client_name.sin_family = AF_INET;  // family is IPv4.
  client_name.sin_addr.s_addr = inet_addr(inet_ntoa(saddr->sin_addr)); 
  client_name.sin_port = htons(PORT);

    // ---Connect to server---
    if (connect(sock, (struct sockaddr *)&client_name, sizeof(client_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }
    
    sprintf(buff, "GET %s%s HTTP/1.0\n\n", hostn, route);
    send(sock, buff, strlen(buff), 0);

    do
    {
        bzero(buff, sizeof(buff));
        more_read = recv(sock, buff, sizeof(buff), 0);
        if ( more_read > 0 )
            printf("%s", buff);
    }
    while ( more_read > 0 );

  printf("Exiting now.\n");

  close(sock); 
  exit(0);

}