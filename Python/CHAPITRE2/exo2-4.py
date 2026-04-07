import os
import time
import random

debut = time.time()

for i in range(2):
    pid = os.fork()
    if pid == 0:
        d = random.randint(1, 10)
        time.sleep(d)
        print(f"je suis le fils {i + 1}, j'ai dormi {d} secondes", flush=True)
        os._exit(0)

for _ in range(2):
    os.wait()

fin = time.time()
print(f"durée totale: {fin - debut:.0f} secondes", flush=True)