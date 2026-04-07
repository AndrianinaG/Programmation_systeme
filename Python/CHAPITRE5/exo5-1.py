import threading

def afficher(tab):
    print(tab)

tab = [1, 2, 3, 4, 5]

t = threading.Thread(target=afficher, args=(tab,))
t.start()
t.join()