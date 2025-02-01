# Projets et Tâches

Ce fichier README.md sert à suivre l'avancement des projets et des tâches.

![Représentation du réseau avec Packet Tracer](Représentation%20du%20réseau.png)

---

## 1. VyOS : Le routeur virtuel

VyOS est un système d’exploitation Linux basé sur Debian. Il permet de transformer une machine virtuelle en routeur virtuel.

### Tâches :
- [x] **1.1** Créer une machine virtuelle intégrant VyOS (version 1.4.0).
- [x] **1.2** Intégrer automatiquement le clavier azerty.
- [x] **1.3** Homogénéiser les noms des interfaces réseau des machines virtuelles clonées :
  - Si une seule carte réseau : `eth0`.
  - Si deux cartes réseau : `eth0` et `eth1`.
  - Etc.

---

## 2. Alpine : Le terminal en mode graphique

Alpine est une distribution Linux graphique légère, idéale pour exécuter plusieurs machines virtuelles en parallèle.

### Tâches :
- [x] **2.1** Créer une machine virtuelle intégrant Alpine (version 3.20.3).
  - Installer Grub.
- [x] **2.2** Configurer Grub pour démarrer en mode graphique ou console.
- [x] **2.3** Intégrer les outils suivants :
  - Openssh
  - Filezilla
  - Navigateur Web
  - Tcpdump
  - Wireshark
  - Putty
- [x] **2.4** Installer VMware Tools (intégration souris et résolution d'écran).
- [x] **2.5** Optimiser la taille du disque dur (utiliser `df` pour vérifier).
- [x] **2.6** Optimiser l'utilisation de la mémoire RAM (utiliser `free` pour vérifier).

---

## 3. MicroCore : Le terminal en mode console

MicroCore est une distribution Linux en mode console, non persistante et très légère.

### Tâches :
- [x] **3.1** Créer une machine virtuelle intégrant MicroCore (version téléchargeable sur [tinycorelinux.net](http://tinycorelinux.net/)).
- [x] **3.2** Intégrer automatiquement le clavier azerty.
- [x] **3.3** Configurer les dossiers utilisateurs (`/home`) et logiciels (`/opt`) pour qu'ils deviennent persistants.
- [x] **3.4** Intégrer les outils suivants :
  - IPv6
  - Commandes `ip` (gestion des adresses IP et de la table de routage)
  - Tcpdump (analyseur de trafic)

---

## 4. ifshow : Lister les interfaces réseau locales

`ifshow` est une commande en langage C pour afficher les interfaces réseau locales.

### Tâches :
- [X] **4.1** Développer `ifshow` sur la machine hôte.
- [X] **4.2** Intégrer `ifshow` à VyOS.
- [X] **4.3** Intégrer `ifshow` à Alpine.
- [X] **4.4** Intégrer `ifshow` à MicroCore.

---

## 5. NetLab : Le réseau virtuel

NetLab est un réseau virtuel composé des machines virtuelles créées dans les projets précédents.

### Tâches :
- [X] **5.1** Configurer les équipements pour la communication IPv4 (routage statique ou dynamique).
- [X] **5.2** Configurer les équipements pour la communication IPv6 (configuration automatique des adresses).

---

## 6. ifnetshow : Lister les interfaces réseau distantes

`ifnetshow` est une commande en langage C pour afficher les interfaces réseau d'une machine distante.

### Tâches :
- [ ] **6.1** Développer `ifnetshow` et son agent sur la machine hôte.
- [ ] **6.2** Intégrer `ifnetshow` et son agent à VyOS.
- [ ] **6.3** Intégrer `ifnetshow` et son agent à Alpine.
- [ ] **6.4** Intégrer `ifnetshow` et son agent à MicroCore.

---

## 7. neighborshow : Lister les machines voisines

`neighborshow` est une commande en langage C pour afficher les machines voisines sur le même réseau.

### Tâches :
- [ ] **7.1** Développer `neighborshow` sur la machine hôte.
- [ ] **7.2** Intégrer `neighborshow` à VyOS, Alpine et MicroCore.
- [ ] **7.3** Développer l'extension `neighborshow -hop n` pour afficher les équipements accessibles en `n` sauts.

---

