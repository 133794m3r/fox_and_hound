┌─[macarthur@evoc-laptop-parrot]─[~/misc_proj/fox_ctf/build_scripts]
└──╼ $find . -type f -iname 'make_hound*'  | xargs -i{} head "{}"


==> ./make_hound0 <==
#!/bin/bash
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 -
# Hound 0:  AKA `Cat presents:Give me the flag!`
#Reading the contents of a file/listing contents of a directory.
#
# This script creates the flag for hound level 0. This level requires the student
# to utilize basic linux commands to read the file. To make sure that they have to
# utilize ls to see the list of files the filename is randomized.


==> ./make_hound1 <==
#!/bin/bash
#Macarthur Inbody <mdi2455@email.vccs.edu> 2019- AGPLv3
#Hound 1 aka `Special characters never stopped me before! Go cat go!`
#"Working with special characters in the filename.
#This flag requires them to read the file either via cat ./<FILENAME> or cat '<FILENAME>'


==> ./make_hound2 <==
#!/bin/bash
#Macarthur Inbody <mdi2455@email.vccs.edu> 2019- AGPLv3
#Hound 2 AKA `Spaces! Why did it have to be spaces. You darned dirty spaces!`
#Catting filenames with spaces.
# Hound flag that involves dealing with spaces in the file name.


==> ./make_hound3 <==
#!/bin/bash
#Macarthur Inbody <mdi2455@email.vccs.edu> 2019- AGPLv3
#
# Hound3: AKA  `You think you can hide me? I am a master of detection!`
#working with hidden files.
# This flag requires the user to find a hidden file
#then read the contents of the file. As they previously
#had to read a file with spaces this is a hearken back to that moment.


==> ./make_hound4 <==
#!/bin/bash
# Hound4  AKA `I don't need no UTF8, ASCII is enough for me!`
#The Hound must find a file that's ASCII Text in type.
# Macarthur Inbody <mdi2455@email.vccs.edu> 
# 2019- 
# AGPLv3
# this flag requires them to utilize the `find` command or grep to find a file
# that is ASCII-Text but nothing else.
# they can also utilize grep(though this is a secret option) with the -I option to ignore
# binary files and look for an empty string.





==> ./make_hound5 <==
#!/bin/bash
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 - 
#
# Hound5 AKA `I can spot the most minute differences!`
#the one where they use diff to find the one line that's different
# between two files.
# It's a simple diff thing but since there's a ton of lines they can do this two
# ways. The first is to just do `diff file1 file2`.
# Other is to do `cat file1 file2 |sort |uniq -u`


==> ./make_hound6 <==
#!/bin/bash
# Hound 6 build script.
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 - 
# Hound5 aka `No obfusication can escape my watchful eye. I *grep* it all!`
# The Grep flag.
#aka the one where they're grepping the password that appears after the certain string.
#also combines it with strings as the file is full of binary data.


==> ./make_hound7 <==
#!/bin/bash
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 - 
# Hound 7 AKA `I am the master of joining. All connection are known instantly.`
# Hound7 AKA the one where they use join to find the password for a certain user.
# they could obviously do this by just opening the files but it's not very easy todo.
#this script can also be used to make fake passwd and shadow files.


==> ./make_hound8 <==
#!/bin/bash
# Hound 8 build script.
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 -
# Hound 8 aka `The greatest detective in the world has arrived. Detectice Phineas is on the case!`
# This flag requires them to find a file with certain metadata from the list of
#files. It has 4 attributes. Size,Owner,Group,Permissions.




==> ./make_hound9 <==
#!/bin/bash
# Hound 9 AKA `Why can't I hold all of these pipes?!/I'm laying down pipes like a Unix Chad!`
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 -
# Hound Flag where they have to repeatedly decompress a file many times
# Then they have to decode the hexdumped file. Followed by decoding the base64
# text to get the final flag string.

==> ./make_hound10 <==
#!/bin/bash
# Hound 10 aka `Stallman send help I'm trapped in Nano!`
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 -
#This will be a nano flag. It'll be 2 flags in one. Part will require them to find a 
#specific string that will then tell them what the file name is that they have to
#insert into their text file to then find the flag.

==> ./make_hound11 <==
#!/bin/bash
# Hound 11 aka `I'm not stuck, I'm just generating entropy for the NSA! Pls send help.`
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 -
#This will be the vim version the nano flag.
#it's basicaly just the vim flag but modified for vim purposes.
#insert into their text file to then find the flag.

==> ./make_hound12 <==
#!/bin/bash
# Hound 12 aka `Look mah I'm a hacker now, I'm cracking someone's pin!/I've been bourne again as a programmer.`
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 -
#Hound 12(maybe 13 later depends if I can fix vim1)
#It requires them to write their first bash script to bruteforce a pin 
#and then cat that data to a program which'll give them the data back. 
#But it only accepts the pin as a base64 encoded file.
#Macarthur Inbody <mdi2455@email.vccs.edu> (C) 2019-

==> ./make_hound13 <==
#!/bin/bash
# Hound 13 aka `The Unix police found out I prefer nano and locked me inside of the VIM ReEducation Program. I must now McGuver my way outta here like a true hackerman!`
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 -
#This will be the vim version the nano flag.
#it's basicaly just the vim flag but modified for vim purposes.
# but also they have set their shell to bash via
# set SHELL=/bin/bash. And then run shell.
# via the command mode.

==> ./make_hound_idunno <==
#!/bin/bash
# Hound I dunno aka `I have a problem. I know I'll use regex. Now I have 2 problems.`
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 -
# This flag requires them find a string that is a certain number of characters in length.
# They can use either awk/sed to get the answer here. Then they'll have to select the one
# that does not have some special character in it. There'll only be 2 flags that are the
# correct length as the code to get the right answer is way too complex for a flag
awk "$0 ~ /^[a-zA-Z]*$/ && length($0) == $LENGTH {print };" `<FILENAME>`;
sed -n "/.\{$LENGTH,$LENGTH\}/p" `<FILENAME>` | grep -v "[^a-z]"
