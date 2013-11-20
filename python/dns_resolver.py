#!/usr/bin/python           # This is dns_resolver.py file
from dns_query import *
import struct


listRootServers = ['198.41.0.4', '192.228.79.201', '192.33.4.12', '199.7.91.13', '192.203.230.10', '192.5.5.241', '192.112.36.4', '128.63.2.53', '192.36.148.17', '192.58.128.30', '193.0.14.129', '199.7.83.42', '202.12.27.3']

def findIP(website):
    query = DnsQuery()
    query.op = DQFlags.QUERY
    query.rd = 0
    query.addQuestion(website, DRType.A, DQClass.IN)
    query.convertInStr()
    result = query.sendQuery('91.121.69.41')
    print result

findIP('www.allocine.fr')