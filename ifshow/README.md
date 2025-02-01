# ifshow

`ifshow` est une commande en ligne de commande développée en C sous Linux pour afficher les interfaces réseau de la machine locale ainsi que leurs caractéristiques. Elle prend en charge deux options principales :
- Afficher les préfixes IPv4 et IPv6 d'une interface spécifique.
- Lister toutes les interfaces réseau avec leurs préfixes IPv4 et IPv6.

---

## Table des matières
1. [Installation](#installation)
2. [Utilisation](#utilisation)
3. [Exemples](#exemples)
4. [Contact](#contact)

---

## Installation

### Prérequis
- Un système Linux.
- Le compilateur `gcc` installé.

### Étapes d'installation

1. Clonez le dépôt du projet :
    ```bash
    git clone https://github.com/votre-utilisateur/ifshow.git
    cd ifshow
    ```

2. Compilez le programme :
    ```bash
    make
    ```

3. Installez le binaire dans `/usr/local/bin/` pour un accès global :
    ```bash
    sudo make install
    ```

## Utilisation

### Syntaxe générale

```bash
ifshow -i <ifname> | -a
```

### Options
- `-i <ifname>` : Affiche les préfixes IPv4 et IPv6 de l'interface spécifiée.
- `-a` : Affiche les préfixes IPv4 et IPv6 de toutes les interfaces réseau.

## Exemples

### Afficher les informations d'une interface spécifique

```bash
./ifshow -i eth0
```

### Sortie :

```bash
Interface: eth0
  IPv4 Prefix: 192.168.1.10/24
  IPv6 Prefix: fe80::250:56ff:fea6:1234/64
```

### Afficher les informations de toutes les interfaces

```bash
./ifshow -a
```

### Sortie :

```bash
Interface: eth0
  IPv4 Prefix: 192.168.1.10/24
  IPv6 Prefix: fe80::250:56ff:fea6:1234/64
Interface: lo
  IPv4 Prefix: 127.0.0.1/8
  IPv6 Prefix: ::1/128
Interface: wlan0
  IPv4 Prefix: 192.168.0.5/24
  IPv6 Prefix: fe80::1a2b:3c4d:5e6f:1234/64
```

## Contact

Pour toute question, suggestion ou problème, vous pouvez contacter les contributeurs du projet :

- Mesrop Aghuyman
- Email : [<mesrop.aghumyan@etu.mines-ales.fr>](mailto:mesrop.aghumyan@etu.mines-ales.fr)
- GitHub : [@mesropaghumyan](https://github.com/mesropaghumyan)

## Licence

Ce projet est sous licence MIT. Voir le fichier [LICENSE](https://github.com/INFRES-175-DL-Projet-Integrateur/ifshow/blob/main/LICENSE) pour plus de détails.
