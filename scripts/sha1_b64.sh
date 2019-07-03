#!/bin/bash
#Macarthur Inbody <mdi2455@email.vccs.edu> 2019- AGPLv3
echo $1 | openssl dgst -sha1 -binary | base64 | tr '+\/' '.-';
