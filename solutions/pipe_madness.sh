#!/bin/bash
# Pipe Madness Solver.
# This script will solve the flag and give you the final string.
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -

function select_command(){
    local str="$1";

    case "$str" in
        'bzip2')
            command='bzcat'
        ;;
        'gzip')
            command='zcat';
        ;;
        'POSIX')
            command='tar xO';
        ;;
        'ASCII')
            command='DONE';
        ;;
        'XZ')
            command='xzcat';
        ;;
        *)
            command='ABSOLUTE_FAILURE';
        ;;
    esac

    echo $command;
}


function decompression_tester(){
    local filename="$1";
    are_we_done=0;
    i=0;
    file_type=$( file "$filename" | cut -d' ' -f2 );
    command_base=$( select_command "$file_type" );
    return_val='';
    if [[ "$command_base" = "tar xO" ]];then
        command_base="tar xOf";
    fi
    command="$command_base $filename";
    command_base="$command";
    while [[ $are_we_done -eq 0 && i -lt 20 ]];do
        file_type=$( eval "$command" | file - | cut -d' ' -f2 );
        command=$( select_command "$file_type" );
        if [ "$command" == "DONE" ];then
            are_we_done=1;
            break;
        elif [ "$command" == 'ABSOLUTE_FAILURE' ];then
            return_val='failed!';
            break;
        else
            command="$command_base | $command"
            command_base=$command;
        fi
        let i++;
    done

    if [ "$return_val" != 'failed!' ];then
        return_val=$( eval "$command_base" | xxd -r | base64 -d  );
    fi
    echo "$return_val";
    return 0;
}
decompression_tester "$1";
