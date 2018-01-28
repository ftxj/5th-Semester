#!/usr/bin/python
# -*- coding: UTF-8 -*-
import socket
import sys
import pickle
import random
import time
from threading import Thread


def toAddr(s):     
    parts = s.split(":")     
    return parts[0], int(parts[1])


class Node:
    def __init__(self, index, value, crash, allnode):
        self.skt = socket.socket(socket.AF_INET, socket.SOCK_DGRAM);
        self.skt.bind(allnode[index])
        self.skt.settimeout(0.5)
        
        self.index = index
        self.crash = crash
        self.round = 1
        self.nodes = allnode
        self.values = {value : "new", -1 : "new"}
        self.wait = 0
        self.last = 0

    def get_same(self):
        while True:
            if(self.crash == self.round):
                num = random.randint(1, len(self.nodes))
                tabu = []
                for i in range(num):
                    tabu.append(self.nodes[random.randint(0, len(self.nodes) - 1)])
                self.send_news(tabu)
                print("%d Crash!" % self.index)
                break
            
            self.send_news()
            ll = self.recv_news()

            if(self.last == ll):
                min = -1
                for key in self.values:
                    if(key < min or min == -1):
                        min = key
                print("%s last Value: %d, round %d" % (self.index, min, self.round))
                break
            self.last = ll
            self.round = self.round + 1

            time.sleep(1)

    def send_news(self, tabu = []):
        msg = []
        for key in self.values:
            if(self.values[key] == "new"):
                msg.append(key)
                if(key != -1):
                    self.values[key] = "old"
        if(len(msg) > 0):
            sid = 0
            for node in self.nodes:
                sid = sid + 1
                if (self.nodes[self.index] != node and sid != self.index):
                    sendMsg = (self.index, self.round, msg)
                    self.skt.sendto(pickle.dumps(sendMsg), node)
                    print("%s send %s to %s" % (self.index,msg, sid))
    
    def recv_news(self):
        recvd = {}
        while True:
            try:
                data, addr = self.skt.recvfrom(4396)
            except socket.timeout:
                print("%d timeout" % self.index)
                break
            (src, r, e) = pickle.loads(data)
            print("%d recv %s" % (self.index, e))

            if(r != self.round):
                print("%d not Synchronize!\n" % src)

            if(r == self.round):
                recvd[src] = e
                for i in e:
                    if(not (i in self.values)):
                        self.values[i] = "new"
        return len(recvd)


ipPort = ["127.0.0.1:5566", "127.0.0.1:5567", "127.0.0.1:5568", "127.0.0.1:5569", "127.0.0.1:5570", "127.0.0.1:5571"]
nodes = list(map(toAddr,ipPort))

node1 = Node(0, 1, 1, nodes)
node2 = Node(1, 2, 2, nodes)
node3 = Node(2, 3, 3, nodes)
node4 = Node(3, 4, -1, nodes)
node5 = Node(4, 5, -1, nodes)
node6 = Node(5, 6, -1, nodes)

print("begin")
Thread(target=node1.get_same).start()
Thread(target=node2.get_same).start()
Thread(target=node3.get_same).start()
Thread(target=node4.get_same).start()
Thread(target=node5.get_same).start()
Thread(target=node6.get_same).start()
