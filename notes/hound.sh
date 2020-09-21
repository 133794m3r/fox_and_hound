GOALSTR='Find the flag in a file.';
padding=$( printf "%s" "$USER" | wc -c );
padding=$(( 13 - padding ));
user=$( printf "%s.%${padding}s" "$USER" '' );
clear;
# shellcheck disable=SC1004
echo '                   /##/\##\
                 _/##/  \##\_
                /###/    \###\
              _/###/      \###\
           __/####/        \###\_
         _/######/          \####\_
       _/#######/            \#####\_
     _/########/              \######\_
    /#########/                \#######\_
__/##########/   *----------*   \########\__
|###########/    | HOUND 00 |    \#########|     \e[1m*****\e[1;4mWelcome to the Hunt @ MECC\e[1m****\e[0m
|##########/     *----------*     \########|  \e[33m+=====================================+
|##########========================########|  \e[33m|\e[97m You are on currently on '"$user"'   \e[33m|
|#####                                #####|   \e[33m|\e[97m The goal of this level is to        \e[33m|
|####               -----             ####|    \e[33m|\e[97m '"$GOALSTR"'            \e[33m|
  |##             #/     \#           ####|    \e[33m|\e[97m Some interesting commands to try    \e[33m|
  |##           ##/       \##          ##/     \e[33m\ \e[97m ls,cat,file,man,info               \e[33m|
  |##         ###/         \##         ##|      \e[33m\ \e[97mIf \e[1;4myou\e[0;97m mess up: reset_ctf          \e[33m|
  |##         ##|           |##         #|       \e[33m\ \e[97mIf \e[1;4mit\e[0;97m messes up: blame -debug     \e[33m|
  |##         ##|           |##         #|        \e[33m\ \e[97;1;4mLost\e[0;97m? type: \e[1;4mtakemeback\e[0;97m           \e[33m|
  |##         ##|           |##         #|         \e[33m| \e[97mShow this help again: \e[1;4mshowbanner\e[0;97m\e[33m|
  |##         ##|           |##         #|         \e[33m| \e[97m By Macarthur Inbody            \e[33m|
  |##         ##|           |##         #|         \e[33m+=================================+
  |##         ##|           |##         #|
  ---------------           --------------
  '
