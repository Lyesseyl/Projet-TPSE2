
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
