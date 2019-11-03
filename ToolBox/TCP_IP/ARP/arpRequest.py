#!/usr/bin/python3
from scapy.all import *
import os
import re
import sys
def get_mac_from_iface(ifname):
      raw_data = os.popen('ifconfig '+ifname).read().split()
      for x in raw_data:
            if re.match('\w\w:\w\w:\w\w:\w\w:\w\w:\w\w',x):
                  return x
      return 'mac not available'            
      
def get_ip_from_iface(ifname):
      raw_data = os.popen('ifconfig '+ifname).read().split()
      index = 0
      for x in raw_data:
            if x=='inet':
                  return raw_data[index+1]
            else:
                  index = index +1

      return 'ip not found'     

def request_for_mac_addr(ifname,dstIP):
      localIP = get_ip_from_iface(ifname)
      localMac = get_mac_from_iface(ifname)
      #ARP(op=1,2) 1: request 2:response psrc: src ip; pdst: dst ip
      result_raw,unanswered = srp(Ether(src=localMac,dst='FF:FF:FF:FF:FF:FF')/
                  ARP(op=1,hwsrc=localMac,hwdst='00:00:00:00:00:00',psrc=localIP,pdst=dstIP),
                  iface='ens33',timeout = 5,verbose=True)
      result_raw.show()            
      return ("requested IP: " + result_raw.res[0][1].getlayer(ARP).fields['psrc'] 
            + "   requested MAC: " + result_raw.res[0][1].getlayer(ARP).fields['hwsrc'])

if __name__ == "__main__":
      if len(sys.argv) < 3:
            print("arpRequest 'ifname' 'requested ip'") 
      else:
            mac = request_for_mac_addr(sys.argv[1],sys.argv[2])
            print(mac)

