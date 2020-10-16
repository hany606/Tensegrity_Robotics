"""twice_cube_model.py: Create the agent of model of the twice cube model tensegrity robot and provide an easy interface to be used with RL algorithms"""
__author__ = "Hany Hamed"
__credits__ = ["Hany Hamed"]
__version__ = "1.0.0"
__email__ = "h.hamed.elanwar@gmail.com / h.hamed@innopolis.university"
__status__ = "Developing"


import socket
import sys
import signal
import json
from time import *
import os
import subprocess
import numpy as np

path_to_model = os.path.join(os.environ["TENSEGRITY_HOME"], "build/dev/twiceCubeConverted/AppTwiceCubeModel")
sim_exec = "gnome-terminal -e {}".format(path_to_model)

class CubeModel():
    def __init__(self, host_name='localhost', port_num=10040, packet_size=5000,
                 sim_exec=sim_exec, render_flag=True, controllers_num=16, nodes_num=16):
        self.host_name = host_name
        self.port_num = port_num
        self.packet_size = packet_size
        self.render_flag = render_flag
        self.actions_json = {
            'controllers_val': [0 for i in range(controllers_num)],
        }
        self.sim_json = {"rest_cables_lengths":
                        [0 for i in range(controllers_num)],
                        "current_cables_lengths":
                        [0 for i in range(controllers_num)],
                        "nodes":
                        [[0.,0.,0.] for i in range(nodes_num)],
                        "time": 0.,
                        "z_finished": 1,
                        "flags":[1,0,0]}

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        # print(self.port_num)
        if(self.port_num is None):
            self.port_num = 0
        self.server_address = [self.host_name, self.port_num] # Bind the socket to the port

        self.connection = None
        self.client_address = None
        self.child_process = None
        print('#########\nstarting up on {}\n#########'.format(self.server_address))
        try:
            self.sock.bind(tuple(self.server_address))

        except socket.error as exc:
            self.port_num += 1
            self.server_address[1] = self.port_num
            print('#########\nstarting up on {} after getting an error of busy port first\n#########'.format(self.server_address))
            self.sock.bind(tuple(self.server_address))
        print('#########\nConnected to port: {:}\n#########'.format(self.sock.getsockname()[1]))
        print('#########\nServer binding is finished\n#########')
        self.sock.listen(1)  # Listen for incoming connections
        self.reset_flag = False
        self.close_flag = False
        self.port_num = self.sock.getsockname()[1]
        self.orginal_sim_exec = sim_exec
        self.set_sim_exec(self.orginal_sim_exec)


    def set_sim_exec(self, sim_exec):
        self.sim_exec = sim_exec + ' {:} {:} {:}'.format(self.host_name, self.port_num, 1 if (self.render_flag) else 0)
        print("EXEC: {:}".format(self.sim_exec))

    def __del__(self):
        self.closeSimulator()
        # sys.exit(0)

    # function for writing data into TCP connection
    def write(self, data):
        # print('sending data to the client:"{}"'.format(data))
        try:
            self.connection.sendall(data.encode())
        except Exception as e:
            print("$$$$$$$$$$$$ ERROR in Writing $$$$$$$$$$$$")
            print("Error: " + str(e))

    # function for reading data from TCP connection
    def read(self):
        try:
            data = []
            counter = 1
            # Receive the data in small chunks and retransmit it
            while True:
                data.append(self.connection.recv(self.packet_size).decode("utf-8"))         #reading part
                # print('{} received "{}"'.format(counter,data[-1]))
                if 'z_finished' in str(data[-1][-14:-1]):
                    break
                counter += 1
            return "".join(data)
        except ValueError:
            print(ValueError)
            print("$$$$$$$$$$$$ ERROR in Reading $$$$$$$$$$$$")
            # sleep(2)
            return None

    def startSimulator(self):
        self.close_flag = False
        self.reset_flag = False
        if(self.sim_exec == sim_exec):
            print("#Warning: Starting an old version")
        # sleep(0.5)
        # subprocess_args = [self.sim_exec[:14], self.sim_exec[15:]]
        #Machine with Xscreen
        subprocess_args = self.sim_exec.split(" ")
        subprocess_args[2] = " ".join(subprocess_args[2:])
        self.child_process = subprocess.Popen(subprocess_args[:3])  
        #Headless
        # self.child_process = subprocess.Popen(self.sim_exec, shell=True)  
        #print('#########\nwaiting for a connection\n#########')
        self.connection, self.clientAddress = self.sock.accept()  #wait until it get a client
        #print('connection from', self.clientAddress)

    def closeSimulator(self):
        self.close_flag = True
        # kill the shell script of the simulator
        if self.connection is not None:
            self.connection.close()
        if self.child_process is not None:
            os.kill(self.child_process.pid, signal.SIGKILL)

    def render(self):
        pass
    
    def reset(self):
        self.reset_flag = True
        self.closeSimulator()
        # os.kill(self.child_process.pid, signal.SIGTERM)
        # sleep(1)
        self.startSimulator()

    def step(self):
        if (self.close_flag == False):
            if (self.reset_flag == True):
                self.reset()
            
            self.write(json.dumps(self.actions_json))   # Write to the simulator module the json object with the required info
            sim_raw_data = self.read()
            # print(sim_raw_data)
            if(sim_raw_data is not None):
                self.sim_json = json.loads(sim_raw_data)  # Parse the data from string to json
        else:
            self.closeSimulator()

    def getTime(self):
        return self.sim_json["Time"]

# This function for testing the model by itself
def main():
    cube = CubeModel()
    cube.startSimulator()
    # sleep(1)
    # cube.reset()
    while(1):
        cube.step()
    cube.closeSimulator()
    sleep(5)


if __name__ == "__main__":
    main()
