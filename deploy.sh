#指定master ip 和 port
MASTER_IP = "10.0.0.15"
MASTER_PORT = 1000

#指定server worker数量以及master端口
NUM_WORKERS = $1
shift
NUM_SERVERS = $1
shift

AVAILABLE_PORTS=(1100, 1101, 1102)

#启动master worker server进程
./output/master ${MASTER_PORT}

#启动server
for((i = 0; i < ${NUM_SERVERS}; i++))
do
./output/server_entry ${MASTER_IP} ${MASTER_PORT} ${AVAILABLE_PORTS[i]}
done


#启动worker
for((i = 0; i < ${NUM_WORKERS}; i++))
do
./output/worker ${MASTER_IP} ${MASTER_PORT}
done

