# Fiche de route des projets intégrateurs

## Etape 1 : Installation et configuration de VyOS

Cette étape consiste à mettre en place une template du routeur VyOS qu'on va pouvoir réutiliser pour mettre en place le réseau NetLab dans l'étape 5.

### Configuration minimal de la machine

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

### Configuration minimal de la machine

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