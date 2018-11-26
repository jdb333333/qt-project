/*********************************************************************
 * Filename: bcast_client.c
 * Description:�㲥�ͻ��˴���
 * Author: Eric(wongpz@foxmail.com)
 * Date: 2012-9-14
 ********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define IP_FOUND "IP_FOUND"
#define IP_FOUND_ACK "IP_FOUND_ACK"
#define IFNAME "eth0"
#define MCAST_PORT 9999

int main(int argc, char*argv[])
{
    int ret = -1;
    int sock = -1;
    int j = -1;
    int so_broadcast = 1;
    struct ifreq *ifr;
    struct ifconf ifc;
    struct sockaddr_in broadcast_addr; //�㲥��ַ
    struct sockaddr_in from_addr; //����˵�ַ
    int from_len = sizeof(from_addr);
    int count = -1;
    fd_set readfd; //���ļ�����������
    char buffer[1024];
    struct timeval timeout;
    timeout.tv_sec = 2; //��ʱʱ��Ϊ2��
    timeout.tv_usec = 0;

    //�������ݱ��׽���
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("create socket failed:");
        return -1;
    }

    // ��ȡ�����׽��ֽӿ�
    ifc.ifc_len = sizeof(buffer);
    ifc.ifc_buf = buffer;
    if (ioctl(sock, SIOCGIFCONF, (char *) &ifc) < 0)
    {
        perror("ioctl-conf:");
        return -1;
    }
    ifr = ifc.ifc_req;
    for (j = ifc.ifc_len / sizeof(struct ifreq); --j >= 0; ifr++)
    {
        if (!strcmp(ifr->ifr_name, "eth0"))
        {
            if (ioctl(sock, SIOCGIFFLAGS, (char *) ifr) < 0)
            {
                perror("ioctl-get flag failed:");
            }
            break;
        }
    }

    //��ʹ�õ�����ӿ����ָ��Ƶ�ifr.ifr_name�У����ڲ�ͬ�������ӿڵĹ㲥��ַ�ǲ�һ���ģ����ָ�������ӿ�
    //strncpy(ifr.ifr_name, IFNAME, strlen(IFNAME));
    //��������������ӿڵĹ㲥��ַ
    if (ioctl(sock, SIOCGIFBRDADDR, ifr) == -1)
    {
        perror("ioctl error");
        return -1;
    }
    //����õĹ㲥��ַ���Ƶ�broadcast_addr
    memcpy(&broadcast_addr, (char *)&ifr->ifr_broadaddr, sizeof(struct sockaddr_in));
    //���ù㲥�˿ں�
    printf("\nBroadcast-IP: %s\n", inet_ntoa(broadcast_addr.sin_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(MCAST_PORT);

    //Ĭ�ϵ��׽���������sock�ǲ�֧�ֹ㲥�����������׽�����������֧�ֹ㲥
    ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &so_broadcast,
            sizeof(so_broadcast));

    //���Ͷ�ι㲥�����������Ƿ��з���������
    int times = 10;
    int i = 0;
    for (i = 0; i < times; i++)
    {
        //һ������10�ι㲥��ÿ�εȴ�2���Ƿ��л�Ӧ
        //�㲥���ͷ�������ַ����
        timeout.tv_sec = 2;  //��ʱʱ��Ϊ2��
        timeout.tv_usec = 0;
        ret = sendto(sock, IP_FOUND, strlen(IP_FOUND), 0,
                (struct sockaddr*) &broadcast_addr, sizeof(broadcast_addr));
        if (ret < 0)
        {
            continue;
        }

        //�ļ���������0
        FD_ZERO(&readfd);
        //���׽����ļ����������뵽�ļ�������������
        FD_SET(sock, &readfd);
        //select�����Ƿ������ݵ���
        ret = select(sock + 1, &readfd, NULL, NULL, &timeout);
        switch (ret)
        {
        case -1:
            break;
        case 0:
            perror("select timeout\n");
            break;
        default:
            //���յ�����
            if (FD_ISSET(sock,&readfd))
            {
                count = recvfrom(sock, buffer, 1024, 0,
                        (struct sockaddr*) &from_addr, &from_len); //from_addrΪ�������˵�ַ
                printf("\trecvmsg is %s\n", buffer);
                if (strstr(buffer, IP_FOUND_ACK))
                {
                    printf("\tfound server IP is %s, Port is %d\n",
                            inet_ntoa(from_addr.sin_addr),
                            htons(from_addr.sin_port));
                }
                return -1;

            }
            break;

        }
    }
    return 0;
}