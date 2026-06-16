# tcpdump tutorial for noobs
### Core 
It is a packet capture and analysis tool. terminal based. 
Comes preinstalled in most linux distros.
It needs root priviledges to run.

### Example Commands 

#### How to list Network Interfaces in Linux
```bash
ip link show
ip addr show
```
#### Example tcpdump commands 

1. **Capture all traffic on interface eth0:**
   ```
   sudo tcpdump -i eth0
   ```

2. **Capture 100 packets on interface wlan0:**
   ```
   sudo tcpdump -i wlan0 -c 100
   ```

3. **Write captured data to a file for later analysis:**
   ```
   sudo tcpdump -w capture.pcap
   ```
