# FOR GNS3 - Code (at server):
conf t
ip http server
ip http path flash:
ip http max-connections 5
ip http port 5001
ip http access-class 1
access-list 1 permit 192.168.12.0 0.0.0.255
username student privilege 15 password student
ip http authentication local
do copy running-config flash:startup-config
end

# Part 2 – Code (at server):
Dir flash:
config t
int f0/0
ip address 192.168.12.2 255.255.255.0
no shut
end

# Code (at client):
config t
int f0/0
ip address 192.168.2.1 255.255.255.0
no shut
ip http client username student
ip http client password student
do wr
end

# Connecting to HTTP server from client end
copy http://192.168.12.2:5001/startup-config null:
