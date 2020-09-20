#!/bin/bash
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -
echo "$1" | openssl dgst -sha1 -binary | base64 | tr '+\/' '.-' | tr -d '=';
