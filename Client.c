#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
  
  int socket_fd;
  //the server address and port
  struct sockaddr_in  dest;
  //information about the server
  struct hostent *hostptr;
  //messge sturct
  struct { char head; char body[100]; char tail; } msgbuf;//change body to char[100]
  struct { char head; char body[100]; char tail; } msgbuf1;
  //open socket with ipv4 ,udp protocol
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
  //rest the bits
  bzero((char *) &dest, sizeof(dest));
  //return to hostptr the information about the server by name
  hostptr = gethostbyname(argv[1]);
  //server address is ipv4
  dest.sin_family = (short) AF_INET;
  //copy to dest the server address
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
  
 
  //the server port
  dest.sin_port = htons((u_short)0x3333);
  
  
  
  //message hrad
  msgbuf.head = '<';
  
   strncpy(msgbuf1.body, argv[3],sizeof(argv[3]));
  msgbuf.tail = '>';
  
  sendto(socket_fd,&msgbuf1,sizeof(msgbuf1),0
  ,(struct sockaddr *)&dest, sizeof(dest));
  
  //  msgbuf.body = htonl(getpid()); /* IMPORTANT! */
  //copy the message from input
  strncpy(msgbuf.body, argv[2],sizeof(argv[2])); /* IMPORTANT! */ //changed to argv[2]
  msgbuf.tail = '>';
  //send the message to server
  sendto(socket_fd,&msgbuf,sizeof(msgbuf),0
  ,(struct sockaddr *)&dest, sizeof(dest));
  
  
  //recive the name back
  int dsize =sizeof(dest);
  int cc;
  cc = recvfrom(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,&dsize);
printf("Got data ::%c%s%c\n",msgbuf.head, msgbuf.body,msgbuf.tail);
  return 0;
}

