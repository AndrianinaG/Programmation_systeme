import threading
import random

def worker(result):
    arr = [random.randint(0, 99) for _ in range(10)]
    result.append(arr)
    print("Tableau généré:", arr)

result = []
t = threading.Thread(target=worker, args=(result,))
t.start()
t.join()


