#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Colors {

string Black    = "\033[0;30m";                  // Black
string Red      = "\033[0;31m";                  // Red
string Green    = "\033[0;32m";                  // Green
string Yellow   = "\033[0;33m";                  // Yellow
string Blue     = "\033[0;34m";                  // Blue
string Purple   = "\033[0;35m";                  // Purple
string Cyan     = "\033[0;36m";                  // Cyan
string White    = "\033[0;37m";                  // White

};

//-----------------------------------
string interface_for_deauth = "";
string interface_for_scan = "";
string range_of_ip = "";
string whitelist = "whitelist.txt";
string mac_of_gateway = "";
string channel = "";
//-----------------------------------
vector<string> vc;
int vector_count = 0;

vector<string> vendor;
//-----------------------------------

//--Colors-----
Colors color;
//-------------

class Super_Robot_Detector {

public:

    //-----------------------Setters-----------------------------
    void Set_interface_for_scan(string interface_for_scan) {

        this->interface_for_scan = interface_for_scan;
    }
    
    void Set_interface_for_deauth(string interface_for_deauth){

        this->interface_for_deauth = interface_for_deauth;
    }

    void Set_range_of_ip(string range_of_ip) {
        
        this-> range_of_ip = range_of_ip;
    }
    
    void Set_whitelist(string whitelist) {

        this-> whitelist = whitelist;
    }

    void Set_mac_of_gateway(string mac_of_gateway){

        this-> mac_of_gateway = mac_of_gateway;
    }

    void Set_channel(string channel){

        this-> channel = channel;
    }

    //-------------------------------------------------------

    void exec(string cmd, bool flag) {
        if(flag) cmd += " > !@#c.txt";
        char command[cmd.size()];

        for(int i = 0; i <= cmd.size(); ++i) {
            command[i] = cmd[i];
        }

        system(command);
        if(flag) system("rm !@#c.txt*");
    }

    void Logo(vector<string> vc, vector<string> vec_vendor) {
             
        cout << color.Cyan;
        cout << " ____  _____ ____  ____  _____ ____     ____  ____   ___ _____ _____ ____ _____ ___ ___  _   _ "                           << endl;
        cout << "|  _ \\| ____|  _ \\/ ___|| ____/ ___|   |  _ \\|  _ \\ / _ \\_   _| ____/ ___||_ _|_  _/ _ \\| \\ | |"                    << endl;
        cout << "| | | |  _| | | | \\___ \\|  _|| |       | |_) | |_) | | | || | |  _|| |     | |  | | | | |  \\| |"                        << endl;
        cout << "| |_| | |___| |_| |___) | |__| |___    |  __/|  _ <| |_| || | | |__| |___  | |  | | |_| | |\\  |"                          << endl;
        cout << "|____/|_____|____/|____/|_____\\____|   |_|   |_| \\_\\\\___/ |_| |_____\\____| |_| |___\\___/|_| \\_|"                    << endl;
        cout << color.White << "\n-------------------------------------------------------------------------------------------------"        << endl;
        for(int i = 0; i < vector_count; ++i) {

            cout << color.Red << vc[i] << color.White << "\t\t     | " << color.Red << vec_vendor[i] << " " << color.Yellow << "┌∩┐(◣_◢)┌∩┐\n" << color.White;
        }
        cout << "\t\t\t\t     |\n";
        cout << "-------------------------------------------------------------------------------------------------" << color.Green << endl;
    }

    void Initialization(vector<string> &vc) {
        vc.reserve(100);
        for (int i = 0; i < 100; ++i) {
            vc.push_back("  \t\t");
            vendor.push_back("");
        }
    }

    void Scanning() {

	    string scan = "sudo nmap -sn -e ";
        scan = scan + interface_for_scan + " " + range_of_ip + " | grep MAC" + " > scan.txt";
        exec(scan, false);
    }

    void Preparing() {
        cout << color.Yellow << "LOADING......" << endl;;
        int count = 0;
        string monitor = "sudo airmon-ng start " + interface_for_deauth;
        exec(monitor, true);
        cout << "[+] Monitor mode on " << interface_for_scan << " started..." << endl;
        monitor = "sudo iw ";
        monitor = monitor + interface_for_deauth + " set channel " + channel;
        exec(monitor, true);
        cout << "[+] Channel changed on " << channel << "...." << endl;

        Initialization(vc);

    }

    bool Checking_mac(string mac) {
	
        ifstream ws(whitelist);
        
        while (ws) {

            string f;
            getline(ws, f);
            if (f == mac) return true;
        }

        ws.close();
        return false;
    }

    void Deauth(string mac){

        string deauth = "sudo xterm -e zsh -c 'aireplay-ng -0 40 -a ";
        deauth = deauth + mac_of_gateway + " -c " + mac + " " + interface_for_deauth + "' &"; /*+ " &"; */
        exec(deauth, false);
    }

    bool Checking_exists(vector<string> vc, string mac) {

        for(int i = 0; i < 8; ++i) {

            if(vc[i] == mac) return true;
        }
        return false;
    }

    void Vendor(string mac_from_list, vector<string>& vec_vendor) {

        char vendor[mac_from_list.size() - 33];
        int count = 0;

        for(int i = 32; i < mac_from_list.size() - 1; ++i) {

            vendor[count] = mac_from_list[i];
            count++;          
        }

        vec_vendor[vector_count] = vendor;

    }
    void Processing() {

        ifstream mac("scan.txt");

        string for_vendor;

        while (mac) {

            string mac_from_list;
            getline(mac, mac_from_list);

            string real_mac = "qwertyuiopasdfghj";
            if (mac_from_list != "") {
                int count = 0;
                for (int i = 13; i < 30; ++i) {

                    real_mac[count] = mac_from_list[i];
                    count++;
                }

                if (!Checking_mac(real_mac)) { // If not exists in whitelist
                   

                    if(!Checking_exists(vc, real_mac)) { // If not exists in vector
                        
                        vc[vector_count] = real_mac; 
                        Vendor(mac_from_list, vendor);
                        vector_count++;
                        
                    }
      
                    Deauth(real_mac);
                }
            } 
        }

        system("clear");
        Logo(vc, vendor);

        mac.close();

    }



private:

string interface_for_deauth;
string interface_for_scan;
string range_of_ip;
string whitelist;
string mac_of_gateway;
string channel;

};

void Logo();
void Help();

int main(int argc, char* argv[]) {

    for (int i = 1; i < argc; i++)
    {
        if(argv[i] == string("--help")) {
            break;

        } else if (argv[i] == string("--deauth") && i + 1 < argc) {
            interface_for_deauth = argv[++i];

        } else if (argv[i] == string("--scan") && i + 1 < argc) {
            interface_for_scan = argv[++i];
        
        } else if(argv[i] == string("--arp") && i + 1 < argc) {
            range_of_ip = argv[++i];

        } else if(argv[i] == string("--mac") && i + 1 < argc) {
            mac_of_gateway = argv[++i];

        } else if(argv[i] == string("--channel") && i + 1 < argc) {
            channel = argv[++i];
        }
    }


    if(interface_for_deauth != "" && interface_for_scan != "" && range_of_ip != "" && mac_of_gateway != "" && channel != "") {

        Super_Robot_Detector srd;
        
        //------Setting arguments-----
        srd.Set_interface_for_deauth(interface_for_deauth);
        srd.Set_interface_for_scan(interface_for_scan);  
        srd.Set_range_of_ip(range_of_ip);
        srd.Set_whitelist(whitelist);
        srd.Set_mac_of_gateway(mac_of_gateway);
        srd.Set_channel(channel);
        //----------------------------

        srd.Preparing();   

        while(true){

            srd.Scanning();

            srd.Processing();

            system("sleep 1");
        }

    } else {
        Logo();
        Help();
    }

    return 0;
}

// ----------------------------

void Help() {
    cout << "\nWifi protector designed to protect networks from unwanted and untrusted device connections, designed to combat intruders who want to steal data within the network" << endl << endl;
    cout << "This code was written by Legion" << endl << endl;
    cout << "WIFI PROTECTOR USAGE:\nsudo ./wifi_protector --deauth <interface_for_deauth> --scan <interface_for_scan> --arp <range_of_ip> --mac <mac_of_gateway> --channel <channel_of_your_wifi>" << endl;
    cout << "sudo ./wifi_protector --help" << endl << endl;
    cout << "EXAMPLE:\nsudo ./wifi_protector --deauth wlan0 --scan wlan1 --arp 192.168.0.0/24 --mac 28:EE:52:60:DC:CF --channel 3\nsudo ./wifi_protector --help" << endl;
    cout << "\nDON'T FORGET TO WHITELIST YOUR TRUSTED MAC DEVICES!!!" << endl;
}

void Logo() {
    cout << " ____  _____ ____  ____  _____ ____     ____  ____   ___ _____ _____ ____ _____ ___ ___  _   _ "                           << endl;
    cout << "|  _ \\| ____|  _ \\/ ___|| ____/ ___|   |  _ \\|  _ \\ / _ \\_   _| ____/ ___||_ _|_  _/ _ \\| \\ | |"                    << endl;
    cout << "| | | |  _| | | | \\___ \\|  _|| |       | |_) | |_) | | | || | |  _|| |     | |  | | | | |  \\| |"                        << endl;
    cout << "| |_| | |___| |_| |___) | |__| |___    |  __/|  _ <| |_| || | | |__| |___  | |  | | |_| | |\\  |"                          << endl;
    cout << "|____/|_____|____/|____/|_____\\____|   |_|   |_| \\_\\\\___/ |_| |_____\\____| |_| |___\\___/|_| \\_|"                    << endl;
    cout << "                                                                                   Legion v1.0"                            << endl;
}
