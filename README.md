# socket between win and ubuntu
default port 8888
## 1.win
### server
```bash
server.exe
````

###  client
```bash
# CMD #2 (192.168.3.3)
client.exe 127.0.0.1
```

## 2.ubuntu
```bash
gcc -o server server.c 
gcc -o client client.c 
````
### server
```bash
./server
````

###  client
```bash
# CMD #2 (192.168.3.4)
./client 127.0.0.1
```