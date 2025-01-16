############ Projet de Détection de Routes ############

## Aperçu du Projet
Ce projet a été développé par **Zongrui XUE**, **Minggao GONG** et **Haicheng WANG**, étudiants du programme **Technologies Immersives et IA à Efrei**, sous la direction de **Patrick Bonnin**. L'objectif du projet est de créer une application de détection de routes qui traite les vidéos en entrée pour identifier efficacement les routes.

## Installation et Utilisation

### Compilation
1. Accédez au répertoire `build` :

   cd build

2. Compilez le projet en utilisant la commande `make` :

   make


### Exécution de l'Application
1. Restez dans le répertoire `build`.
2. Exécutez l'application en utilisant l'une des commandes suivantes :
   - Pour traiter avec le paramètre 1 :

     ./road_detection 1

   - Pour traiter avec le paramètre 0 :

     ./road_detection 0


### Modification des Vidéos d'Entrée
1. Accédez au répertoire `data/video`.
2. Remplacez le fichier vidéo par votre vidéo souhaitée pour le traitement de la détection de routes.

## Personnalisation de la Détection de Routes
Si vous souhaitez ajuster les paramètres pour détecter différents types de routes :
1. Ouvrez le fichier source principal contenant la fonction principale.
2. Modifiez les données pertinentes dans la fonction principale selon les besoins pour adapter les conditions de route ou les exigences de détection.
3. Recompilez le projet en suivant les étapes indiquées dans la section **Compilation**.

## Remarques
- Assurez-vous que les vidéos d'entrée sont correctement formatées et placées dans le répertoire `data/video` avant d'exécuter l'application.
- Ajustez les paramètres avec soin pour améliorer les performances de détection de routes dans des conditions variées.

Pour toute question supplémentaire ou assistance, veuillez contacter l'équipe de développement.

