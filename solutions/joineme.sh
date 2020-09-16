#/bin/bash
# Hound9
# I am the master of joining. All connection are known instantly.
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -
#IFS='|';
#files=($(ls -A | tr '\n' '|' ));
mapfile -t files < <(ls -A);
IFS=' ';
join -t':' <(sort -k1 -t':' ./"${files[0]}") <(sort -k1 -t':' ./"${files[1]}") 2>/dev/null | grep $1 | cut -d':' -f8
