make clean
make server_entry
start_port=1200
for((i = 0; i < 3; i++))
do
let current_port=${start_port}+${i}
echo ${current_port}
sudo nohup ./server_entry 10.0.0.15 1000 ${current_port} &
done
#make clean
