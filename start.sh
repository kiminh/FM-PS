#举例
MASTER_IP = "127.0.0.3"
MASTER_PORT = 9696

#指定server worker数量以及master端口
NUM_WORKERS = $1
shift
NUM_SERVERS = $1
shift

#启动master worker server进程
./master $MASTER_PORT
LOOP
./worker
LOOP
./server

