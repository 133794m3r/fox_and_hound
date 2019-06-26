#!/bin/bash

echo $1 | openssl dgst -sha1 -binary | base64 | tr '+\/' '.-';
