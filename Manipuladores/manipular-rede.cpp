#include <iostream>    
#include <cstdlib>    
#include <string>    
#include <unistd.h>    

using namespace std;    

void print_banner() {
    system("clear");
    cout << "\033[1;36m";
    system("figlet GEASE BUFF NET");
}    

void verifica_nmap() {
    if (system("which nmap > /dev/null") != 0) {
        system("pkg install nmap -y > /dev/null 2>&1");
    }
}    

void scan_rede_agressivo() {
    system("nmap -T4 -n -sn $(ip route | grep src | awk '{print $1}')");
    system("nmap -T5 --min-rate 1000 $(ip route | grep src | awk '{print $1}') > /dev/null 2>&1 &");
}    

void buff_monstro() {
    system("sysctl -w net.core.rmem_max=16777216");
    system("sysctl -w net.core.wmem_max=16777216");
    system("sysctl -w net.ipv4.tcp_rmem='4096 87380 16777216'");
    system("sysctl -w net.ipv4.tcp_wmem='4096 65536 16777216'");
    system("sysctl -w net.core.netdev_max_backlog=10000");
}    

void threads_doidas() {
    system("sysctl -w kernel.threads-max=999999");
    system("sysctl -w vm.max_map_count=999999");
    system("sysctl -w kernel.pid_max=999999");
}    

void conexoes_insanas() {
    system("sysctl -w net.ipv4.tcp_max_syn_backlog=999999");
    system("sysctl -w net.core.somaxconn=999999");
    system("sysctl -w net.ipv4.tcp_max_tw_buckets=9999999");
    system("sysctl -w net.ipv4.ip_local_port_range='1024 65535'");
}    

void sistema_info() {
    system("uname -a");
    system("free -h");
    system("df -h");
}    

int main() {
    print_banner();
    verifica_nmap();
    scan_rede_agressivo();
    buff_monstro();
    threads_doidas();
    conexoes_insanas();
    sistema_info();
    return 0;
}