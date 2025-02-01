/**
 * ifshow - Afficher les informations des interfaces réseau
 * 
 * author : Mesrop Aghumyan <mesrop.aghumyan@etu.mines-ales.fr>
 * date : 2024-01-13
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INET_ADDRSTRLEN 16  // Taille maximale d'une adresse IPv4 sous forme de chaîne
#define INET6_ADDRSTRLEN 46 // Taille maximale d'une adresse IPv6 sous forme de chaîne

// Fonction pour afficher les préfixes IPv4 d'une interface
void show_ipv4_prefixes(const char *ifname) {
    char command[256];
    snprintf(command, sizeof(command), "ip -4 addr show %s", ifname);

    FILE *fp = popen(command, "r");
    if (!fp) {
        perror("popen");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "inet ")) {
            char ip[INET_ADDRSTRLEN];
            int prefix_len;
            if (sscanf(line, " inet %[^/]/%d", ip, &prefix_len) == 2) {
                printf("  IPv4 Prefix: %s/%d\n", ip, prefix_len);
            }
        }
    }

    pclose(fp);
}

// Fonction pour afficher les préfixes IPv6 d'une interface
void show_ipv6_prefixes(const char *ifname) {
    char command[256];
    snprintf(command, sizeof(command), "ip -6 addr show %s", ifname);

    FILE *fp = popen(command, "r");
    if (!fp) {
        perror("popen");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "inet6 ")) {
            char ip[INET6_ADDRSTRLEN];
            int prefix_len;
            if (sscanf(line, " inet6 %[^/]/%d", ip, &prefix_len) == 2) {
                printf("  IPv6 Prefix: %s/%d\n", ip, prefix_len);
            }
        }
    }

    pclose(fp);
}

// Fonction pour afficher les informations d'une interface spécifique
void show_interface(const char *ifname) {
    printf("Interface: %s\n", ifname);
    show_ipv4_prefixes(ifname);
    show_ipv6_prefixes(ifname);
}

// Fonction pour lister toutes les interfaces réseau
void list_all_interfaces() {
    FILE *fp = popen("ls /sys/class/net", "r");
    if (!fp) {
        perror("popen");
        return;
    }

    char ifname[256];
    while (fgets(ifname, sizeof(ifname), fp) != NULL) {
        ifname[strcspn(ifname, "\n")] = '\0';
        show_interface(ifname);
    }

    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s -i <ifname> | -a\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-i") == 0 && argc == 3) {
        // Option -i : Afficher les informations d'une interface spécifique
        show_interface(argv[2]);
    } else if (strcmp(argv[1], "-a") == 0) {
        // Option -a : Afficher les informations de toutes les interfaces
        list_all_interfaces();
    } else {
        fprintf(stderr, "Usage: %s -i <ifname> | -a\n", argv[0]);
        return 1;
    }

    return 0;
}