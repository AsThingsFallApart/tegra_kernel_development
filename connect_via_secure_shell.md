# Connect via Secure Shell (SSH) Protocol

## Cast
"Server" will play the role of "Remote Host"
"Your machine" will play the role of "Local Host"

## You will need
1. The private key that corresponds to the remote host's public key
    If you do not have this, contact the person who generated the key according to the instructions in file `setup_secure_shell.md` and tell them to send you a file that looks like `id_rsa` in directory `~/.ssh`
    Once you have the private key (in the form of a file like `id_rsa`), copy the file to your machine's `~/.ssh` directory
2. Server's IP Address; let this be referred to below as `serverIpAddress`
    If you do not have this, contact somebody with physical access to the server computer, tell them to sign in, run command "ip address" and send you the numbers next to "inet" and between "brd"
3. Account name on server; let this be referred to below as `accountName`
    If you do not have this, contact somebody who knows what the name of an account on the server
4. Account password on server
    If you do not have this, contact somebody who knows what the name of the password of the account on the server


## Connect
1. run command "ssh-copy-id ${accountName}@${serverIpAddress}
2. enter password of the server account
3. run "ssh ${accountName}@${serverIpAddress}

You're now connected to a terminal on the remote host
