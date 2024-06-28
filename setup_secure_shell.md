# Setup Secure Shell (SSH) Protocol

## Cast
"Jetson Orin Nano Devkit" will play the role of "Remote Host"
"Your machine" will play the role of "Local Host"

## On a Jetson Orin Nano Devkit that was recently flashed:
1. go through configuration
2. activate 'Open Terminal' shortcut on Ubuntu by pressing (Ctrl + Alt + t)
3. run command "sudo apt install openssh-server"
    By default, Remote Login is enabled
4. run command "ip address"
5. note the Jetson Orin Nano Devkit's ip address: this is the IP address between "inet" and "brd", e.g. "inet 192.168.1.251/24 brd ..."
    The IP address in the example above would be "192.168.1.251", the "/24" indicates the ip address is on port 24. The port is not needed for the following steps

## On your machine:
5. run command "ssh-keygen -t rsa"
6. on prompt "Enter file in which to save the key (/home/${accountName}/.ssh/id_rsa):", Press 'Enter' for default
7. on prompt "Enter passphrase (empty for no passphrase):", Press 'Enter' for no password 
8. on prompt "Enter same passphrase again:", Press 'Enter' to confirm no password 

The keys for SSH authentication have been generated:
    private key: `id_rsa` is found at path `~/.ssh/id_rsa`
    public key: `id_rsa.pub` is found at path `~/.ssh/id_rsa.pub`

9. run command "cd ~/.ssh"
10. run command "sftp ${accountName}@${jetsonOrinNanoDevkitIpAddress}"
    where: ${accountName} is a user on the Jetson Orin Nano Devkit and ${jetsonOrinNanoDevkitIpAddress} is the number noted in step 5
11. enter the password set in step 1
    If your machine and the Jetson Orin Nano Devkit are on the same network, you're now in the Secure File Transfer Protocol (sftp) shell: "sftp>"
12. run command "cd .ssh"
13. run command "ls"
    there should only be two files in the Jetson Orin Nano Devkit's `~/.ssh` directory: (1) `known_hosts` and (2) `known_hosts.old`
14. run "put id_rsa.pub"
15. run "ls"
    now there are three files: (1) `id_rsa.pub`, (2) `known_hosts`, and `known_hosts.old`
16. run "quit"
17. run "ssh-copy-id ${accountName}@${jetsonOrinNanoDevkitIpAddress}"
18. enter the password set in step 1

Your machine now is authorized to SSH into the Jetson Orin Nano Devkit

## Resources
1. https://ubuntu.com/server/docs/openssh-server
