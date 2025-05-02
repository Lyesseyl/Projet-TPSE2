
import threading
import time
import random

# Paramètres
NB_BUS_X = 5
NB_BUS_Y = 4
ALLER_RETOUR = 10

# Sémaphores et verrous
mutex = threading.Lock()
sens_XY = 0  # nombre de bus dans le sens X -> Y
sens_YX = 0  # nombre de bus dans le sens Y -> X

def log(message):
    print(f"[{time.strftime('%H:%M:%S')}] {message}")

def enter_tunnel(direction, bus_id, ville_depart, ville_arrivee):
    global sens_XY, sens_YX
    while True:
        with mutex:
            if direction == "XY":
                if sens_YX == 0:
                    sens_XY += 1
                    break
            else:
                if sens_XY == 0:
                    sens_YX += 1
                    break
        time.sleep(0.1)

def exit_tunnel(direction):
    global sens_XY, sens_YX
    with mutex:
        if direction == "XY":
            sens_XY -= 1
        else:
            sens_YX -= 1

def trajet(bus_id, ville, depart, arrivee, direction, i):
    enter_tunnel(direction, bus_id, depart, arrivee)
    log(f"Bus {bus_id} de {ville} : {depart} -> {arrivee} (Trajet {i})")
    time.sleep(random.uniform(1, 1.5))
    exit_tunnel(direction)

def bus_thread(bus_id, ville, direction_initiale):
    for i in range(1, ALLER_RETOUR + 1):
        if direction_initiale == "XY":
            trajet(bus_id, ville, "X", "Y", "XY", i)
            trajet(bus_id, ville, "Y", "X", "YX", i)
        else:
            trajet(bus_id, ville, "Y", "X", "YX", i)
            trajet(bus_id, ville, "X", "Y", "XY", i)

# Création des threads
threads = []
for i in range(1, NB_BUS_X + 1):
    t = threading.Thread(target=bus_thread, args=(f"X{i}", "Ville X", "XY"))
    threads.append(t)
for i in range(1, NB_BUS_Y + 1):
    t = threading.Thread(target=bus_thread, args=(f"Y{i}", "Ville Y", "YX"))
    threads.append(t)

# Démarrage des threads
for t in threads:
    t.start()

# Attente de la fin des threads
for t in threads:
    t.join()
