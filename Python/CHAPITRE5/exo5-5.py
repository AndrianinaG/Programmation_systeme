import sys
import threading
import time
import random

compt = 0
mutex = threading.Lock()
stop = False

def incrementer(limite):
    global compt, stop
    while not stop:
        with mutex:
            if compt >= limite:
                stop = True
                break
            compt += 1
            print(f"Incrémentation: compt = {compt}")
        time.sleep(random.uniform(1, 5))

def afficher(limite):
    global compt, stop
    while not stop:
        with mutex:
            if compt >= limite:
                stop = True
                break
            val = compt
        print(f"Affichage: compt = {val}")
        time.sleep(2)

def main():
    if len(sys.argv) != 2:
        print("Usage: python programme.py <limite>")
        sys.exit(1)
    limite = int(sys.argv[1])
    
    t1 = threading.Thread(target=incrementer, args=(limite,))
    t2 = threading.Thread(target=afficher, args=(limite,))
    
    t1.start()
    t2.start()
    
    t1.join()
    t2.join()

if __name__ == "__main__":
    main()