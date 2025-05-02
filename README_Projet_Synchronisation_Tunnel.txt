Noms: Messaoudi Ilyes et Hadad Abderrezak isil groupe 02 

Projet : Synchronisation des Bus de Transport dans un Tunnel

Contexte :
Deux villes, X et Y, sont reliées par un tunnel à voie unique emprunté quotidiennement par des bus de transport en commun.
- La ville X dispose de 5 bus.
- La ville Y dispose de 4 bus.

Règles de Circulation :
- Pas de croisement : Le tunnel ne peut jamais contenir de bus circulant en sens opposés en même temps.
- Circulation groupée : Plusieurs bus du même sens peuvent utiliser le tunnel simultanément.
- Équité : Aucun des deux sens (X->Y ou Y->X) ne doit monopoliser l’accès au tunnel.
- Allers-retours : Chaque bus effectue 10 trajets aller-retour par jour.

Comportement d’un Bus :
Chaque bus réalise 10 trajets aller-retour complets :
1) Trajet Aller (X->Y ou Y->X) :
   - Affichage : Bus [ID] de [Ville] : [VilleDépart] -> [VilleArrivée] (Trajet [i])
   - Simulation du trajet : sleep aléatoire entre 1 et 1.5 secondes
2) Trajet Retour (Y->X ou X->Y) :
   - Affichage : Bus [ID] de [Ville] : [VilleDépart] -> [VilleArrivée] (Trajet [i])
   - Simulation du trajet : sleep aléatoire entre 1 et 1.5 secondes

Tâches :
- Implémenter une solution avec des sémaphores pour respecter toutes les règles.
- Chaque bus est modélisé par un thread ou un processus.
- Envoyer le lien du repo GitHub contenant votre projet, avec la liste des étudiants ayant participé.
- Vérifier les quatre conditions de l’exclusion mutuelle.
- Rendre sur papier le jour du TP.

Vérification des quatre conditions de l’exclusion mutuelle :
Exclusion mutuelle
Le tunnel ne peut être utilisé que par des bus circulant dans un seul sens à la fois. L'accès au tunnel est contrôlé par des vérifications protégées par un mutex (pthread_mutex_t), garantissant qu'aucun bus en sens opposé ne peut y entrer simultanément.

Avancement
Les bus qui veulent entrer dans le tunnel peuvent le faire dès que le tunnel est libre dans leur direction. Aucun bus ne reste bloqué indéfiniment si le tunnel est disponible.

Attente bornée (Bounded Waiting)
Un bus ne peut pas être bloqué indéfiniment par d'autres bus. Une fois qu’un groupe de bus termine son passage, les bus du sens opposé ont la possibilité d’entrer, garantissant une alternance et évitant la famine.

Progrès
Si plusieurs bus veulent entrer dans le tunnel et que le tunnel est vide, l’un d’eux finira toujours par progresser. Aucune ressource partagée ne reste inutilisée si elle est disponible.

Cet algorithme peut-il être retenu comme solution pour protéger le tunnel ?
Oui.
L’algorithme utilise correctement les threads et la synchronisation via mutex, ce qui garantit que :

le tunnel n’est jamais utilisé par des bus de directions opposées en même temps,

plusieurs bus peuvent entrer dans le tunnel s’ils vont dans le même sens,

l’accès reste équitable grâce à une attente alternée,

les quatre conditions de l’exclusion mutuelle sont respectées.
