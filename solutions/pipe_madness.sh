#!/bin/bash
# Pipe Madness Solver.
# This script will solve the flag and give you the final string.
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 - 2020

function select_command(){
	
	#this is just so that I'm not calling $1 to make it easier to follow flow.
    local str="$1";

    case "$str" in
    	#bzip is catted with it's program also.
        'bzip2')
            command='bzcat'
        ;;
        #Gzip compresed files are catted to stdin.
        'gzip')
            command='zcat';
        ;;
        #POSIX is my shorthand for tar compressed archive.
        'POSIX')
            command='tar xO';
        ;;
        #ASCII means we're done.
        'ASCII')
            command='DONE';
        ;;
        #if the file is compressed with XZ
        'XZ')
            command='xzcat';
        ;;
        # we should never get here ever.
        *)
            command='ABSOLUTE_FAILURE';
        ;;
    esac
    #debug information is here.
    echo $command;
}


function decompression_tester(){
	#same as above just redefining parameter $1(aka first option) as a local variable
	#so that we can make it flow better.
    local filename="$1";
    # should always be 0 until we reach ASCII text stage.
    are_we_done=0;
    i=0;
    #get the file's type by converting the hex-encoded file into a raw file.
    # it's always hex encoded at the start to keep things simple for me.
    file_type=$( xxd -r "$filename" | file - | cut -d' ' -f2 );
    #get the intial command.
    command_base=$( select_command "$file_type" );
    #print the first command.
    echo "$command_base";
    return_val='';
    #if [[ "$command_base" = "tar xO" ]];then
    #    command_base="tar xO";
    #fi
    command="xxd -r $filename | $command_base";
    command_base="$command";
    echo "$command_base";
    echo "$command";
    # this should _never_ ever happen with the actual file like ever.
    if [[ "$command" == 'ABSOLUTE_FAILURE' ]];then
        echo 'Failed';
        return 255;
    fi
    #iterate over it until we're done or if we're 20 layers deep because that's the maximum
    # if we go higher than that then something's fucked up.
    while [[ ! $are_we_done && i -lt 20 ]];do
    	#make sure we get the file's type.
    	#I have to use eval because tar doesn't like being run as a string but it works.
    	
        file_type=$( eval "$command" | file - | cut -d' ' -f2 );
        command=$( select_command "$file_type" );
        
        #if we're done then break out of the loop.
        if [ "$command" == "DONE" ];then
            are_we_done=1;
            break;
        #if we failed make sure that we return the message of failed.
        elif [ "$command" == 'ABSOLUTE_FAILURE' ];then
            return_val='failed!';
            break;
        #otherwise use the command and add it to our chain.
        else
            command="$command_base | $command"
            command_base=$command;
        fi
        #increment i.
        (( i++ ));
        #echo the current full command.
        echo "$command_base";
    done
	#If it's not failed then we run the full command series, unhexlify it, then finally
	# we decode the base64 encoded string and return that as the value.
    if [ "$return_val" != 'failed!' ];then
        echo return_val=$( eval "$command_base" | xxd -r | base64 -d  );
        return 0;
    #otherwise we failed.
    else
       echo "$command";
       return 1
    fi
    
}
decompression_tester "$1";
