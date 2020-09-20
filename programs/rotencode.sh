#!/bin/bash
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -
function rot_47(){
    local FILENAME=$2;

    local encoded_line='';
    local new_file="$2-1";
    local i=0;
	# shellcheck disable=SC2162
	while read line
  	do

  	if [ "$1" == '-e' ]
	  then
	  encoded_line="$(echo "$line" |  tr '\!-~' 'P-~\!-O')";
	elif [ "$1" == -'d' ]
		then
		encoded_line="$(echo "$line" |  tr 'P-~\!-O' '\!-~')";
	fi
	if [ $i == 0 ];
	then
		echo "$encoded_line" > "$new_file";
	else
		echo "$encoded_line" >> "$new_file";
	fi
	echo "$encoded_line";

	i=$i+1;
	done < "$FILENAME"
}

# shellcheck disable=SC2034
function rot_n(){
    local i=0;

	local rot_1='B-ZAb-za'
	local rot_2='C-ZA-Bc-za-b'
	local rot_3='D-ZA-Cd-za-c'
	local rot_4='E-ZA-De-za-d'
	local rot_5='F-ZA-Ef-za-e'
	local rot_6='G-ZA-Fg-za-f'
	local rot_7='H-ZA-Gh-za-g'
	local rot_8='I-ZA-Hi-za-h'
	local rot_9='J-ZA-Ij-za-i'
	local rot_10='K-ZA-Jk-za-j'
	local rot_11='L-ZA-Kl-za-k'
	local rot_12='M-ZA-Lm-za-l'
	local rot_13='N-ZA-Mn-za-m'
	local rot_14='O-ZA-No-za-n'
	local rot_15='P-ZA-Op-za-o'
	local rot_16='Q-ZA-Pq-za-p'
	local rot_17='R-ZA-Qr-za-q'
	local rot_18='S-ZA-Rs-za-r'
	local rot_19='T-ZA-St-za-s'
	local rot_20='U-ZA-Tu-za-t'
	local rot_21='V-ZA-Uv-za-u'
	local rot_22='W-ZA-Vw-za-v'
	local rot_23='X-ZA-Wx-za-w'
	local rot_24='Y-ZA-Xy-za-x'
    local rot_25='ZA-Yza-y'
    local rotpattern="${!1}";
    local pattern='';
    local string=$3;
    if [ "$2" == '-d' ];then
        pattern="$rotpattern' A-Za-z'";
    elif [ "$2" == '-e' ];then
        pattern='A-Za-z '$rotpattern;
    fi
	local encoded_line='';
	local new_file=$string'-1';
	#echo ${!1};
	#echo $2;
	#echo $1;
	# shellcheck disable=SC2162
	while read line; do
		encoded_line="$(echo "$line" |  tr "$pattern")";
		if [ $i == 0 ];then
			echo "$encoded_line" > "$new_file";
		else
			echo "$encoded_line" >> "$new_file";
		fi
		echo "$encoded_line";
		i=$i+1;
	done < "$string"

}

function select_rot(){
#echo $#;
    case $1 in
        'rot_47')
            rot_47 "$2" "$3";;
        ''|'-h')
            echo "usage: rotencode.sh [{1-25}|47] [-e|-d] {filename.extension}";;
        *)
            rot_n "rot_$1" "$2" "$3";;
    esac;
    #if [ $1 == 'rot_47' ];
    #then

#    elif [[ $1 == '-h' ||  $1 == '' ]];
#    then

#    else
#    rot_n $1 $2 $3;
#    fi


}

select_rot "$1" "$2" "$3"
