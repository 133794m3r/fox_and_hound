#!/bin/bash
# Hound 8 aka I can _find_ anything. The greatest detective in the world has arrived.
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -

find . -uid "$1" -gid "$2" perm "$3"  -size "$4"c -exec cat {} \;
