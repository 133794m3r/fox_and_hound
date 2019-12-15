#!/bin/bash
# Hound14
# No obfusication can escape my watchful eye. I *grep* it all!
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -
# the one where they're grepping the password that appears after the certain string.
# also combines it with strings as the file is full of binary data.
strings ./"$(ls -A)"| grep "$1" | cut -d' ' -f2;
