import sys
sys.path.append("../src/tworker")
sys.path.append("../src")
sys.path.append("../src/common")
sys.path.append("../src/common/gen-py")
from tworker import *


def main(argv):
  worker = Tworker(argv[1], argv[2])
  worker.build_client_to_master()
  worker.ask_for_task()
  #worker.load_data()
  logger.info("worker准备连接参数服务器")
  worker.connect_to_server()
  worker.pull_parameter(0)
  worker.print_newest_parameter()

if __name__ == "__main__":
  main(sys.argv)