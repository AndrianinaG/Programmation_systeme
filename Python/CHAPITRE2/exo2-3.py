import os

for i in range(5):
    pid = os.fork()
    if pid == 0:
        print(f"je suis le fils {i + 1}", flush=True)
        break

if pid != 0:
    for _ in range(5):
        os.wait()
    print("je suis le père", flush=True)