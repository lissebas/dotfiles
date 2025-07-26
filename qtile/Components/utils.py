import psutil
import socket
import subprocess
import json
import os

# Check Network Status
def is_connected():
    try:
        # Intenta conectarse a un DNS público (Google)
        socket.create_connection(("8.8.8.8", 53), timeout=3)
        return True
    except OSError:
        return False

def get_connection_interface():

    if not is_connected():
        return '󰖪 Disconnected'


    interfaces = psutil.net_if_stats()

    for iface, stat in interfaces.items():
        if stat.isup:
            if 'wlan' in iface:
                try:
                    essid = subprocess.check_output(['iwgetid', '-r'], text=True).strip()
                    label = f'    {essid}' if essid else 'Unknown'
                except subprocess.CalledProcessError:
                    label = '󰖪 Unknown'
                break
            elif 'eth' in iface or 'enp' in iface:
                label = '󰈀 Ethernet'
                break

    return label



# Check sound output
def get_sound_interface():
    
    try:
        path = os.path.expanduser('~/.config/.envVars/outputMedia.json')
        with open(path, 'r') as f:
            output_data = json.load(f)

        sink = subprocess.check_output(['pactl', 'get-default-sink'], text=True).strip()
        return str(output_data['sound'].get(sink))
    except Exception:
        return subprocess.check_output(['pactl', 'get-default-sink'], text=True).strip()
        #return '󰖁 Unknown'

