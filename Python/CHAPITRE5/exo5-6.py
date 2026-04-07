import threading
import random
import time

N = 100
tableau = [0.0] * N
mutex = threading.Lock()
running = True

def init_tableau():
    global tableau
    for i in range(N):
        if i == 0 or i == N-1:
            tableau[i] = 0.0
        else:
            tableau[i] = random.uniform(0, 100)

def thread_moyenne():
    global tableau
    while running:
        with mutex:
            nouveau = tableau[:]
            for i in range(1, N-1):
                nouveau[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3.0
            tableau = nouveau
        time.sleep(random.uniform(1, 3))

def thread_affichage():
    while running:
        with mutex:
            aff = [round(val, 2) for val in tableau]
        print("Tableau actuel:", aff)
        time.sleep(4)

def main():
    init_tableau()
    t1 = threading.Thread(target=thread_moyenne)
    t2 = threading.Thread(target=thread_affichage)
    t1.daemon = True
    t2.daemon = True
    t1.start()
    t2.start()
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        global running
        running = False
        print("Arrêt")

if __name__ == "__main__":
    main()