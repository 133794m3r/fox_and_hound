#!/bin/bash
# Hound 16 Base Script. Goal is to make it run.
# Then it'll give them the flag.
# Macarthur Inbody
# mdi2455@email.vccs.edu / admin-contact@transcendental.us
# Licenesed under AGPLv3
# (C) 2019 -

#TODO: Fix this bad boy up real good.
#recreation of the PHP function that converts a byte string to a decimal number.
function ord(){
    printf '%d' "'$1'";
}
#converts a byte to the textual character.
function chr(){
    perl -e "printf '%c',$1;";
}

#decided against this insanity.
function b32_encode(){
    return 0;
}

#here be black magic. It's abusing bash in ways unheard of.
#Only Stallman fully understands this code.
function str_index() {
#!?!?!?!?!
#(V) (;,,;) (V)
  local x="${1%%$2*}"
  #WAT?!
  [[ "$x" = "$1" ]] && echo -1 || echo "${#x}"
}

function generate_sequence(){
    local a=0;
    local b=1;
    local num=0;
    local start=$1;
    #using math requires $(( 2+2)) to get the result.
    local end=$(($start + 5 ));
    # a for loop the C style.
    for ( i=0; i<10; i++ ) {
        num=$(( a + b ));
        a=$b;
        b=$num;
        #if logic statement.
        if [[ $i -ge $start ]];
            printf "$a ";
        #else if this value we do this.
        elif [[ $i = $end ]];then
            break;
        fi
    }
}

function get_specific_string(){
    local filename="$1";
    local len=$2;
    local pattern=$3;
    #utilizing awk to get a certain string of a certain length.
    #you need to escape $0 because otherwise bash will convert it to the program's name
    #but awk uses $0 for the current line.
    awk_str="\$0 ~ /[\\$pattern]/ && length(\$0) == $len {gsub(/[^A-Za-z0-9\+\_]/,\"\"); print};"
    #piping the data from the filename to awk.
    cat "$filename" | awk "$awk_str";
}

function parse_string(){
    local base_str=$1;
    #calling a subshell.
    base_str=$( echo $base_str | base64 -d );
    str_part_1=$(( 16#${base_str:0:2} ));
    str_part_2=$(( 16#${base_str:3:2} ));
    str_part_3=$(( (16#${base_str:4}) - 127 ));
    printf "$str_part_1 $str_part_2 $str_part_3";
}

# a function.
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

    #a for loop in Shell style.
    for (i=0;i<str_len;++i)); do
        #getting a substring out of a string.
        byte=${str:$i:1};
        index=`(str_index $b64_dict $byte )`;
        index=$(( $index ^ ${sequence[$j]} ));
        ouput_str+="${b32_dict:$index:1}";
        #printf ${b64_dict:$index:1};
        let j++;
        #if logic statement.
        if [[ $j -ge 5 ]];then
            j=0;
        fi
    done

    printf "$ouput_str\n";
}

function uncipher_string(){
	local code_1='B-ZAb-za';
	local code_2='C-ZA-Bc-za-b';
	local code_3='D-ZA-Cd-za-c';
	local code_4='E-ZA-De-za-d';
	local code_5='F-ZA-Ef-za-e';
	local code_6='G-ZA-Fg-za-f';
	local code_7='H-ZA-Gh-za-g';
	local code_8='I-ZA-Hi-za-h';
	local code_9='J-ZA-Ij-za-i';
	local code_10='K-ZA-Jk-za-j';
	local code_11='L-ZA-Kl-za-k';
	local code_12='M-ZA-Lm-za-l';
	local code_13='N-ZA-Mn-za-m';
	local code_14='O-ZA-No-za-n';
	local code_15='P-ZA-Op-za-o';
	local code_16='Q-ZA-Pq-za-p';
	local code_17='R-ZA-Qr-za-q';
	local code_18='S-ZA-Rs-za-r';
	local code_19='T-ZA-St-za-s';
	local code_20='U-ZA-Tu-za-t';
	local code_21='V-ZA-Uv-za-u';
	local code_22='W-ZA-Vw-za-v';
	local code_23='X-ZA-Wx-za-w';
	local code_24='Y-ZA-Xy-za-x';
    local code_25='ZA-Yza-y';
    #utilizing this command we use the value of a variable as a command that gets expanded to the value that that variable is pointing to.
    #ex try this command.
    #$a='123'; b='a'; echo ${!b};
    # you should get
    # 123.
    local pattern="${!1}";
    local final_pattern='';
    local string=$2;
    #final_pattern="'A-Za-z' '$pattern'";
    printf "$string" | tr "$pattern" 'A-Za-z';
}

#the main function.
function main(){
#the arguments are from $0-$n. $0=program name. $1 is first argument and so on.
    local passed_string="$1";
    local str_len="$2";
    local pattern="$3";
    local filename="$4";
    #this utilizes command substitution to get the result back to it w/o using a subshell.
    local chosen_string=`(get_specific_string "$filename" $str_len "$pattern")`
    local parsed_array;
    #reading data in into an array. <<< moves data into stdin.
    read -r -a parsed_array <<< `(parse_string $1 )`;
    local string='';
    #the second element of the array.
    #${parsed_array[2]};
    string=`(uncipher_string "code_${parsed_array[2]}" $chosen_string)`;
    string=`(decrypt $string ${parsed_array[0]})`;
    printf "$string\n";
}

#if logic statement.
if [ $# -ge 1 ]];then
    #case switch statements.
    case $1 in
    #one of the cases. You can use | to make it match any of the strings.
        '-h'|'help')
            #this prints how to use the program. This is always a good idea.
            printf "Help: -h to print this message. Pass the string you were given to this program. Once it runs it'll give you the flag. Also include the file you were told to give it.\nUsage: ./<PROGAM_FILENAME_PLACEHOLDER> <STRING> <PATTERN> <LINE_LENGTH> <FILENAME_TO_BE_READ>\n";
        ;;
        #the default case.
        *)
        #we are passing the arguments given to the script to the program.
        #the string variables are enclosed in "" as this'll replace their value with the
        #string value and won't mess up the argument number if there are special characters.
            main "$1" "$2" $3 "$4";
        ;;
    esac
    #else statement.
else
    #this prints how to use the program. This is always a good idea.
    printf "Help: -h to print this message. Pass the string you were given to this program. Once it runs it'll give you the flag. Also include the file you were told to give it.\nUsage: ./<PROGAM_FILENAME_PLACEHOLDER> <STRING>  <PATTERN> <LINE_LENGTH> <FILENAME_TO_BE_READ>\n";
fi
