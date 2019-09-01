# ~/.profile: executed by the command interpreter for login shells.
# This file is not read by bash(1), if ~/.bash_profile or ~/.bash_login
# exists.
# see /usr/share/doc/bash/examples/startup-files for examples.
# the files are located in the bash-doc package.
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -
# the default umask is set in /etc/profile; for setting the umask
# for ssh logins, install and configure the libpam-umask package.
#umask 022

if [ -z "$SSH_CONNECTION" ];then
    exit;
fi

if [ "$BASH" != "/bin/bash" ];then
    #str=$( echo '\e[1ma' );
        dirname=$(echo "$SSH_CONNECTION$USER" | openssl dgst -sha1 -binary | base64 | tr '+\/' '-_')
        mkdir -p /tmp/foxhunt/"$dirname";
        tar -xJf /home/$USER/challenge_file.txz -C /tmp/foxhunt/"$dirname";
        cd /tmp/foxhunt/"$dirname";
        chmod 444 *;
        vim vim_welcome_msg;
        kill -9 $PPID;
fi


# if running bash
if [ -n "$BASH_VERSION" ]; then
    # include .bashrc if it exists
    if [ -f "$HOME/.bashrc" ]; then
	. "$HOME/.bashrc"
    fi
fi


# set PATH so it includes user's private bin if it exists
if [ -d "$HOME/bin" ] ; then
    PATH="$HOME/bin:$PATH"
fi
