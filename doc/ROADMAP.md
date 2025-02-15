# Fiche de route des projets intégrateurs

## Etape 1 : Installation et configuration de VyOS

Cette étape consiste à mettre en place une template du routeur VyOS qu'on va pouvoir réutiliser pour mettre en place le réseau NetLab dans l'étape 5.

### Configuration minimale de la machine

- Mémoire vive : 1000 Mo
- Processeur : 1
- Stockage : 2 Gio

### Installation

1. Lancer la machine virtuelle.
2. Installer l'image : `install image`.
3. Eteindre la machine : `sudo poweroff`
4. Supprimer l'ISO.
5. Configurer un réseau bridge pour permettre l'accès à Internet.
6. Lancer la machine à nouveau et suivez les étapes d'installations.
7. Le router virtuelle est installé 🎉

### Configuration du clavier AZERTY :

```shell
configure
set system option keyboard-layout 'fr'
commit
save
```

### Homogénéiser automatiquement les noms des interfaces réseaux des machines virtuelles clonées :

1. Supprimer les interfaces présentes sur le routeur dans : `​/opt/vyatta/etc/config/config.boot`.

2. Créer un snapshot de l'état actuelle de la machine sans interfaces.

Ces étapes permettent d'avoir une template de VyOS prête à l'emploie. Attention, il ne faut plus toucher au template. Dans l'étape 5, lors de la création du NetLab nous ferons usage de cette template afin de cloner les différents routeurs du réseau.

La supression des interfaces permet lors du clone :
- Si une seule carte réseau virtuelle est rattachée à la machine virtuelle
clonée, l’interface réseau devra se nommer eth0.
- Si deux cartes réseaux virtuelles sont rattachées à la machine virtuelle
clonée, les interfaces réseaux devront se nommer eth0 et eth1.
- etc...

## Etape 2 : Installation et configuration de Alpine

Cette étape consiste à créer et configurer une machine virtuelle sous la distribution Alpine. Cette machine servira de template dans le cas où on voudrais mettre en place des machines Alpine dans le NetLab.

### Configuration minimale de la machine

- Mémoire vive : 512 Mo
- Processeur : 1
- Stockage : 3,25 Gio

### Installation de la machine Alpine

1. Lancer la machine virtuelle.
2. Installer l'image : `setup-alpine`.
3. Eteindre la machine : `sudo poweroff`
4. Supprimer l'ISO.
5. Configurer un réseau bridge pour permettre l'accès à Internet.
6. Lancer la machine à nouveau et suivez les étapes d'installations.
7. Le router virtuelle est installé 🎉

### Installation du mode graphique

Alpine met à disposition un script qui permet d'installer automatiquement le mode graphique, il suffit juste de lancer dans le terminal la commande suivante : `setup-desktop`.

> [!WARNING]
> Avant de lancer `setup-desktop`, il faut s'assurer avoir préalablement installé le package `bash`, essentiel pour installer les différents modules de l'interface graphique : `apk add bash`. De plus lors de l'installation, le script va demander de choisir une interface, je recommande l'interface `xfce` dût à sa légèreté.

### Installation et configuration de GRUB

Installation de GRUB :

```shell
apk add grub grub-bios
grub-install /dev/sda
```

Configuration du script `/etc/grub.d/40_custom`, ce script permet d'ajouter des menu d'entrée personalisé dans grub :

```bash
#!bin/sh
exec tail -n +3 s0

menu entry "Alpine Linux (Mode Graphique)" {
	set root=(hd0,1)
	linux /boot/vmlinuz-lts root=/dev/sda3 quiet graphical=true modules=sd-mod,usb-storage,ext4
	initrd /boot/initramfs-lts
}

menu entry "Alpine Linux (Mode Console)" {
	set root=(hd0,1)
	linux /boot/vmlinuz-lts root=/dev/sda3 quiet graphical=false modules=sd-mod,usb-storage,ext4
	initrd /boot/initramfs-lts
}
```

Explication du script :

Dans ce script, on ajoute 2 entrées. J'ai ajouté un argument `graphical=<true | false>` qui va permettre de différencier le mode console au mode graphique. En effet à chaque démarrage de la machine en fonction de l'entrée qu'on choisit la variable graphical sera initialisé.

Par la suite, on doit créer un script dans `/etc/local.d/setup-gui.start` qui va  s'exécuter à chaque démarrage, cela va permettre de charger l'interface graphique en fonction de si l'utilisateur choisit le mode graphique ou le mode console :

```bash
#!/bin/bash

CMDLINE_FILE="/proc/cmdline"

if grep -q "graphical=true" "$CMDLINE_FILE"; then
    rc-update add lightdm default
    if ! rc-service lightdm status > /dev/null 2>&1; then
        rc-service lightdm start
    fi
else
    rc-service lightdm stop
    rc-update del lightdm default
    openrc default
fi
```

Donner les droits d'éxécution sur le script : `chmod +x /etc/local.d/setup-gui.start`.

Pour que le script s'active à chaque démarrage et extinction il faut également activer le service local :

```shell
rc-update add local default
rc-service local start
```

Enfin pour pouvoir charger le mode graphique il faut également activer le service dbus :

```shell
rc-update add dbus
rc-service dbus start
```

De plus il faut également configurer le fichier de configuration de GRUB `​/etc/default/grub​` qui permet de définir les paramètres généraux du menu de démarrage :

```text
GRUB_DISTRIBUTOR="Alpine"
GRUB_TIMEOUT=5
GRUB_DISABLE_SUBMENU=true
GRUB_DISABLE_RECOVERY=true
GRUB_CMDLINE_LINUX_DEFAULT="quiet rootfstype=ext4 modules=sd-mod,usb-storage,ext4"
GRUB_CMDLINE_LINUX=""
GRUB_GFXMODE=auto
GRUB_TERMINAL_OUTPUT="console"
GRUB_DISABLE_OS_PROBER=false
```

Il ne reste plus qu'à charger le nouveau fichier de configuration grub : `grub-mkconfig -o /boot/grub/grub.cfg`.

Après un reboot la machine va charger les 2 menus d'entrées et permettre de choisir entre le mode console et graphique.

Installation des packages demandés :

```shell
apk add filezilla
apk add tcpdump
apk add wireshark
apk add putty
apk add openssh
rc-update add sshd
rc-service sshd start
```

> [!NOTE]
> Il est préférable de mettre en place les paquets invités VirtualBox depuis l'interface graphique.

Installation et mise en place des paquets invités VirtualBox :

```shell
apk add virtualbox-guest-additions
apk add virtualbox-guest-additions-x11
rc-service virtualbox-guest-additions start
rc-update add virtualbox-guest-additions boot
rc-service virtualbox-drm-client start
rc-update add virtualbox-drm-client default
```

## Etape 3 : Installation et configuration de MicroCore

Cette étape consiste à créer et configurer une machine virtuelle sous la distribution MicroCore. Cette machine servira de template dans le cas où on voudrais mettre en place des machines MicroCore dans le NetLab.

### Configuration minimale de la machine

- Mémoire vive : 512 MB
- Processeur : 1
- Stockage : 150 MB

### Installation et configuration de la machine MicroCore

Une particularité de MicroCore est d’être un système non persistant (les modifications du système sont
perdues au redémarrage).

Les étapes ci-dessous permettent de configurer GRUB et de rendre les dossiers utilisateurs `/home` et logiciels `/opt` persistants.

```shell
tce-load -w -i openssl.tcz
wget git.io/tinycore-install
sh tinycore-install
```

Il reste plus qu'à éteindre la machine et enlever manuellement l'ISO depuis l'interface de VirtualBox.

Intégration automatique du clavier AZERTY :

Pour rendre persistant la configuration du clavier AZERTY, il faut installer le package `kmaps` : `tce-load -wi kmaps`.

D'autre part il faut ajouter la ligne ci-dessous dans le fichier `/opt/bootlocal.sh` :

```bash
#!/bin/bash
...

sudo loadkmap < /usr/share/kmap/fr-latin9.kmap

...
```

Installation des packages `iproute2` et `tcpdump` : `tce-load -wi iproute2 tcpdump`.

Installation de IPV6 :

En premier lieu il faut chercher les paquets disponible pour la version de ma distribution de core avec la commande `​tce-ab`​.

Pour Core 6.4 la version retenu du paquet ipv6 est : `​ipv6-3.16.6-tinycore.tcz​`.

Pour l'installer il suffit de taper la commande suivante : `tce-load -wi ipv6-3.16.6-tinycore.tcz`.

Pour finir il faut activer le module et le rendre persistant, pour cela il faut ajouter de nouveau dans le fichier `/opt/bootlocal.sh` la ligne ci-dessous :

```bash
#!/bin/bash
...

sudo modprobe ipv6

...
```

## Etape 4 :  ifshow, la commande pour lister les interfaces réseaux de la machine locale.

ifshow est une commande en ligne à développer en langage C sous Linux. Elle
affiche la liste des interfaces réseaux de la machine locale et leurs
caractéristiques. Le comportement de la commande dépend des paramètres qui
lui sont associées :

- ifshow -i ifname : affiche la liste des préfixes d’adresses IPv4 et IPv6
associées à l’interface nommée ifname. (un préfixe s’écrit sous la forme d.d.d.d/p pour IPv4 et d:d:d:d:d:d:d:d/p pour IPv6) ;
- ifshow -a : affiche la liste des noms des interfaces réseaux, et leurs préfixes
d’adresses IPv4 et IPv6.

Lien du code source : https://github.com/mesropaghumyan/projets-integrateurs/tree/master/ifshow

### Intégration dans VyOS :

VyOS ne permet pas de compiler du C avec ```gcc```. Pour palier à ce problème, j'ai mis en place un serveur apache sur le WSL de ma machine hôte, dans lequel j'ai mis le compilé de ifshow.

Sur ma machine VyOS je n'ai plus qu'à récupérer le compilé présent sur le serveur Apache et le placer dans `/usr/local/bin` :

```shell
wget http://172.17.171.46/ifshow
chmod +x ./ifshow
mv ifshow /usr/local/bin/ifshow
```

### Intégration dans Alpine :

Sur une machine Alpine vous aurez besoins des paquets `musl-dev` et `gcompat` contenant respectivement dans l'un les fichiers de développement de la bibliothèque C standard et dans l'autre les outils nécessaires pour exécuter des binaires sous Linux : `apk add musl-dev gcompat`.

Ensuite il faut récupérer le compilé présent sur le serveur Apache et le placer dans `/usr/local/bin` :

```shell
wget http://172.17.171.46/ifshow
chmod +x ./ifshow
mv ifshow /usr/local/bin/ifshow
```

### Intégration dans MicroCore :

Sur une machine MicroCore vous aurez besoins des paquets `gcc` et `compiletc` : `tce-load -wi gcc compiletc`.

Ensuite il faut récupérer le fichier `.c` présent sur le serveur Apache, le compiler et le placer dans `/usr/local/bin`.

Pour que la commande `ifshow` soit persistante sur la machine il faut en premier lieu installer le fichier `.c` dans le répertoire `/opt` :

```shell
cd /opt/
wget http://172.17.171.46/ifshow.c
```

Ensuite il faut ajouter dans le fichier `/opt/bootlocal.sh` les lignes ci-dessous :

```bash
#!/bin/bash
...

gcc -o /opt/ifshow /opt/ifshow.c
chmod +x /opt/ifshow
mv  /opt/ifshow /usr/local/bin/ifshow

...
```

## Etape 5 : Configuration du NetLab

### R0

```shell
configure
set interfaces ethernet eth0 address 10.29.2.1/24
set interfaces ethernet eth1 address 10.29.1.1/24
set interfaces ethernet eth2 address 10.29.5.2/24
set protocols static route 10.29.3.0/24 next-hop 10.29.5.1
commit
save
```

### R1

```shell
configure
set interfaces ethernet eth0 address 10.29.5.1/24
set interfaces ethernet eth1 address 192.168.29.5/30
set protocols static route 10.29.1.0/24 next-hop 10.29.5.2
set protocols static route 10.29.2.0/24 next-hop 10.29.5.2
set protocols static route 10.29.3.0/24 next-hop 192.168.29.6
commit
save
```

### R2

```shell
configure
set interfaces ethernet eth0 address 10.29.3.1/24
set interfaces ethernet eth1 address 192.168.29.6/30
set protocols static route 10.29.1.0/24 next-hop 192.168.29.5
set protocols static route 10.29.2.0/24 next-hop 192.168.29.5
commit
save
```

### T1, T2 et T3 : MicroCore

Pour rendre la configuration des addresses IPv4 sur les terminaux Core peristant, il faut ajouter les lignes ci-dessous dans chacune des machines dans le fichier `/opt/bootlocal.sh` :

#### T1

```shell
sudo ifconfig eth0 10.29.1.101 netmask 255.255.255.0
sudo route add default gw 10.29.1.1
```

#### T2

```shell
sudo ifconfig eth0 10.29.2.102 netmask 255.255.255.0
sudo route add default gw 10.29.2.1
```

#### T3

```shell
sudo ifconfig eth0 10.29.3.103 netmask 255.255.255.0
sudo route add default gw 10.29.3.1
```

### T4 : Alpine

Pour le cas d'une machine Alpine, la machine est déjà persistante, il suffit donc d'entrer dans le terminal les commandes ci-dessous :

```shell
sudo ifconfig eth0 10.29.3.104 netmask 255.255.255.0
sudo route add default gw 10.29.3.1
```