#!/bin/dash
# The Pin Guesser Script
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -
num_str='';
#todo make sure that they write it so that it works with dash.
#this results in a 50% speedup! huge as it saves a shitton of time.
#TODO: Add a check condition to see if the result actually has some output.
# if it does I should really break out of the loop.
cd ../c_programs/built || exit;
i=0;
max=300;

for i in $(seq 0 $max); do
    num_str=$( ./b64 $i );
    echo -n $num_str | ./givemethepin  2>&1 >/dev/null | grep 'flag';
done
