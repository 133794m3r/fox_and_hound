#!/bin/bash
# Hound4: AKA I don't need no UTF8, ASCII is enough for me!
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -

cd "$1" || echo "Directory doesn't exist.";
file .* | grep ': ASCII text' | cut -f1 -d':' | xargs -i{} cat '{}' 
