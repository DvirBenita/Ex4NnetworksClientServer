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

int main(int argc, char *argv[])
{
  int socket_fd;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
  struct { char head; char body[100]; char tail; } msgbuf;//change body to char[100]

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
  bzero((char *) &dest, sizeof(dest)); /* They say you must do this */
  hostptr = gethostbyname(argv[1]);
  dest.sin_family = (short) AF_INET;
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
  dest.sin_port = htons((u_short)0x3333);

  msgbuf.head = '<';
  //  msgbuf.body = htonl(getpid()); /* IMPORTANT! */
  strncpy(msgbuf.body, argv[2],sizeof(argv[2])); /* IMPORTANT! */ //changed to argv[2]
  msgbuf.tail = '>';

  sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,
                  sizeof(dest));
  //recive the name back
  
  int dsize =sizeof(dest);
  int cc;
  cc = recvfrom(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,&dsize);
printf("Got data ::%c%s%c\n",msgbuf.head, msgbuf.body,msgbuf.tail);
  return 0;
}

