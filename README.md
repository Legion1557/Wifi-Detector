 ____  _____ ____  ____  _____ ____     ____  ____   ___ _____ _____ ____ _____ ___ ___  _   _
|  _ \| ____|  _ \/ ___|| ____/ ___|   |  _ \|  _ \ / _ \_   _| ____/ ___||_ _|_  _/ _ \| \ | |
| | | |  _| | | | \___ \|  _|| |       | |_) | |_) | | | || | |  _|| |     | |  | | | | |  \| |
| |_| | |___| |_| |___) | |__| |___    |  __/|  _ <| |_| || | | |__| |___  | |  | | |_| | |\  |
|____/|_____|____/|____/|_____\____|   |_|   |_| \_\\___/ |_| |_____\____| |_| |___\___/|_| \_|
                                                                                   Legion v1.0

Wifi protector designed to protect networks from unwanted and untrusted device connections, designed to combat intruders who want to steal data within the network

This code was written by Legion

WIFI PROTECTOR USAGE:
sudo ./wifi_protector --deauth <interface_for_deauth> --scan <interface_for_scan> --arp <range_of_ip> --mac <mac_of_gateway> --channel <channel_of_your_wifi>
sudo ./wifi_protector --help -> for help

EXAMPLE:
sudo ./wifi_protector --deauth wlan0 --scan wlan1 --arp 192.168.0.0/24 --mac 28:EE:52:60:DC:CF --channel 3
sudo ./wifi_protector --help

DON'T FORGET TO WHITELIST YOUR TRUSTED DEVICES!!!
