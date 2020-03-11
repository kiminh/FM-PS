import logging

logging.basicConfig(level=logging.INFO,
              format='%(asctime)s %(levelname)s '
              '%(filename)s:%(lineno)d; '
              '%(message)s')
logger = logging.getLogger(__name__)

class RepeatedConnectError(Exception):
  def __init__(self):
    pass

  def __str__(self):
    logger.warning("Client has been built, and connected to master")