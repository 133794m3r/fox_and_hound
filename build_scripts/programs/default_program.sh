#!/bin/bash
# Hound 16 Base Script. Goal is to make it run.
# Then it'll give them the flag.
# Macarthur Inbody <mdi2455@email.vccs.edu>
# AGPLv3
# 2019 -
function ord(){
    printf '%x' "'$1'";
}

function chr(){
    perl -e "printf '%c',$1;";
}

function b32_encode(){
    return 0;
}

function str_index() {
  local x="${1%%$2*}"
  [[ "$x" = "$1" ]] && echo -1 || echo "${#x}"
}

function generate_sequence(){
    local a=0;
    local b=1;
    local num=0;
    local start=$1;
    local end=$(($start + 5 ));
    for (( i=0; i<10; i++ )) {
        num=$(( a + b ));
        a=$b;
        b=$num;
        if [[ $i -ge $start ]];then
            printf "$a ";
        fi
        if [[ $i = $end ]];then
            break;
        fi
    }
}

function get_specific_string(){
    local filename="$1";
    local len=$2;
    local pattern=$3;
    awk_str="\$0 ~ /[\\$pattern]/ && length(\$0) == $len {gsub(/[^A-Za-z0-9\+\_]/,\"\"); print};"
    cat "$filename" | awk "$awk_str";
}

function parse_string(){
    local base_str=$1;
    base_str=$( echo $base_str | base64 -d );
    str_part_1=$(( 16#${base_str:0:2} ));
    str_part_2=$(( 16#${base_str:3:2} ));
    str_part_3=$(( (16#${base_str:4}) - 127 ));
    printf "$str_part_1 $str_part_2 $str_part_3";
}


function decrypt(){
    local str="$1";
    local sequence;
    local str_len=${#str};
    local sequence_start=$2;
    read -r -a sequence <<< $(generate_sequence $sequence_start );
    local output_str='';
    local i=0;
    local j=0;
    local byte='';
    local chr='';
    local b32_dict='ybndrfg8ejkmcpqxot1uwisza345h769';
    local b64_dict='ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+_';
    local index=0;
    #echo 'ss '$sequence_start;
    #echo 'seq'"${sequence[*]}";
    for ((i=0;i<str_len;++i)){
        byte=${str:$i:1};
        index=`(str_index $b64_dict $byte )`;
        index=$(( $index ^ ${sequence[$j]} ));
        ouput_str+="${b32_dict:$index:1}";
        #printf ${b64_dict:$index:1};
        let j++;
        if [[ $j -ge 5 ]];then
            j=0;
        fi
    }

    printf "$ouput_str\n";
}

function uncipher_string(){
	local code_1='B-ZAb-za'
	local code_2='C-ZA-Bc-za-b'
	local code_3='D-ZA-Cd-za-c'
	local code_4='E-ZA-De-za-d'
	local code_5='F-ZA-Ef-za-e'
	local code_6='G-ZA-Fg-za-f'
	local code_7='H-ZA-Gh-za-g'
	local code_8='I-ZA-Hi-za-h'
	local code_9='J-ZA-Ij-za-i'
	local code_10='K-ZA-Jk-za-j'
	local code_11='L-ZA-Kl-za-k'
	local code_12='M-ZA-Lm-za-l'
	local code_13='N-ZA-Mn-za-m'
	local code_14='O-ZA-No-za-n'
	local code_15='P-ZA-Op-za-o'
	local code_16='Q-ZA-Pq-za-p'
	local code_17='R-ZA-Qr-za-q'
	local code_18='S-ZA-Rs-za-r'
	local code_19='T-ZA-St-za-s'
	local code_20='U-ZA-Tu-za-t'
	local code_21='V-ZA-Uv-za-u'
	local code_22='W-ZA-Vw-za-v'
	local code_23='X-ZA-Wx-za-w'
	local code_24='Y-ZA-Xy-za-x'
    local code_25='ZA-Yza-y'
    local pattern="${!1}";
    local final_pattern='';
    local string=$2;
    #final_pattern="'A-Za-z' '$pattern'";
    printf "$string" | tr "$pattern" 'A-Za-z';
}

function main(){
    local passed_string="$1";
    local filename="$2";
    local str_len="$4";
    local pattern="$3";
    local chosen_string=`(get_specific_string "$filename" $str_len "$pattern")`
    local parsed_array;
    read -r -a parsed_array <<< `(parse_string $1 )`;
    local string='';
    echo ${parsed_array[2]};
    string=`(uncipher_string "code_${parsed_array[2]}" $chosen_string)`;
    string=`(decrypt $string ${parsed_array[0]})`;
    printf "$string\n";
}

if [[ $# -ge 1 ]];then
    case $1 in
        '-h'|'help')
            printf "Help: -h to print this message. Pass the string you were given to this program. Once it runs it'll give you the flag. Also include the file you were told to give it.\nUsage: <PROGAM_FILENAME_PLACEHOLDER> <STRING> <PATTERN> <LINE_LENGTH> <FILENAME_TO_BE_READ>\n";
        ;;
        *)
            main "$1" "$2" "$3" $4;
        ;;
    esac
else
    printf "Help: -h to print this message. Pass the string you were given to this program. Once it runs it'll give you the flag. Also include the file you were told to give it.\nUsage: <PROGAM_FILENAME_PLACEHOLDER> <STRING>  <PATTERN> <LINE_LENGTH> <FILENAME_TO_BE_READ>\n";
fi