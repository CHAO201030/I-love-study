#include "H_client.h"

#define ROUTE_IP "192.168.7.121"
#define ROUTE_PORT "9527"

int main(int argc, char *argv[])
{
    int sfd = tcp_connect(ROUTE_IP, ROUTE_PORT);

    // recv_file(sfd);

    char cluster_1_ip[32] = {0};
    char cluster_1_port[32] = {0};

    recv_cluster_info(sfd, cluster_1_ip, cluster_1_port);
    
    printf("INFO : GET Cluster Server INFO...\n"
           "       %s : %s\n", cluster_1_ip, cluster_1_port);
    
    printf("INFO : connect to cluster_1...\n");
    
    int cluster_1_sfd = tcp_connect(cluster_1_ip, cluster_1_port);
    
    printf("INFO : connect established...\n");

    recv_file(cluster_1_sfd);
    
    printf("INFO : download success..\n");

    close(sfd);
    close(cluster_1_sfd);

    return 0;
}