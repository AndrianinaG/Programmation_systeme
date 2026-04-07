import os

r, w = os.pipe()

pid = os.fork()

if pid == 0:
    os.close(w)
    message = os.read(r, 1024).decode()
    print(message)
    os.close(r)
    os._exit(0)
else:
    os.close(r)
    message = "bonjour depuis le pere"
    os.write(w, message.encode())
    os.close(w)
    os.wait()