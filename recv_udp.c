#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
 

void printsin(struct sockaddr_in *s, char *str1, char *str2) {
  printf("%s\n", str1);
  printf("%s: ", str2);
  printf("%s= %s, %s= %d", "ip", inet_ntoa(s->sin_addr), "port", s->sin_port);
  printf("\n");
}

 
int main(int argc, char *argv[])
{
  
  int socket_fd, cc, fsize;
  //address and port of server/client
  struct sockaddr_in  s_in, from;
  //sturct represting massge
  struct { char head; char body[100]; char tail;} msg;
  //open new socket with ipv3 and udp protocol
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
 //reset the address and port of client
  bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */
  //changes the type  ipv4/6 of server to ipv4 
  s_in.sin_family = (short)AF_INET;
  //init the server internet address and casting from regular address to network
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);
  //init the server port and casting from regular adrress ip to network address
  s_in.sin_port = htons((u_short)0x3333);
  printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  
  
  fflush(stdout);//clean standart input
  //bind connect address and port with socket
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));
 //^^socket return,pointer to sockaddr , len of the sturct

  
  for(;;) {
    //the size of address and port of server
    fsize = sizeof(from);
    //recive massge from the client
    cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
    printsin((struct sockaddr*) &from, "recv_udp: ", "Packet from:");
   
    //print when got the data from the client
    printf("Got data ::%c%s%c\n",msg.head, msg.body,msg.tail);
    //send back the name

    sendto(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,
                  sizeof(from));
    //clean the standart input 
    fflush(stdout);
  }
   
  return 0;
}