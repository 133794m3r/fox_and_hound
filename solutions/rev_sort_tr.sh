#!/bin/bash
# Hound 13 Solver
# Work it, let me work it. Flip it and reverse it. ti tuc ,ti rt ,ti ver ,ti qinu ,ti troS
# This hound flag will combine the following commands into one. They'll sort a file, then get the only uniq
# line. After that, reverse the string, tr it from mixed-case to lowercase. Then the flag is the second field.
# so if they use cut they can instantly get it.
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -
# below is the "normal" way using tr. 
# cat ./`(ls -A)` | sort | uniq -u | rev | tr '[A-Z]' '[a-z]' | cut -d' ' -f2
 
# I prefer abusing sed though.
# This script does _exactly_ the same thing as the line above just using sed scripting instead of
# utilizing standard unix scripts.
sort <  ./"$(ls -A)" | uniq -u | rev | sed -n -e 's/\(.*\)/\L\1/g;s/\ \(.*\)/\1/p'

