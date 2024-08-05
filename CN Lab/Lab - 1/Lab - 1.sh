# Terminal Commands to make a virtual environment:
python3 -m venv gns3env

# Activate the virtual environment:
source gns3env/bin/activate

# Install required libraries:
pip install pyqt5
pip install gns3-server
pip install gns3-gui

# Execute this under virtual environment:
gns3

# In console, assign an IP to computer by running the following commands:
ip 192.168.1.1 255.255.255.0

# For Virtual PC 2 onwards:
ip 192.168.1.2/24 # Change last decimal for consecutive PCs.

# Ping a PC:
ping 192.168.1.2 # Assuming you are PC1 right now and pinging PC2.

# To define number of packets to ping a PC:
ping 192.168.1.2 -c 5 # Sends 5 packets to PC2.

# Saving terminal commands:
save # Execute this while being inside terminal of any PC.

# View information about assigned commands to a PC:
show ip
