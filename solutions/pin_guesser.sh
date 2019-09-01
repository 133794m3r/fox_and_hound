#!/bin/dash
num_str='';
#todo make sure that they write it so that it works with dash.
#this results in a 50% speedup! huge as it saves a shitton of time.
cd ../c_programs/built;
i=0;
max=300;

for i in `seq 0 300`; do
    num_str=$( ./b64 $i );
    echo -n $num_str | ./givemethepin  2>&1 >/dev/null | grep 'flag';
done
