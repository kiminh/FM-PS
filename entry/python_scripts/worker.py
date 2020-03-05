import sys
sys.path.append("../../src")
sys.path.append("../../src/common/gen-py")
from tworker.tworker import Tworker


def main(argv):
  worker = Tworker(argv[1], argv[2])
  worker.build_client_to_master()
  worker.ask_for_task()
  worker.load_data()

if __name__ == "__main__":
  main(sys.argv)