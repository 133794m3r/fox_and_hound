/*!
*    Various functions that I have written or have came across to make my life easier.
*
*     Copyright 2011, Macarthur Inbody
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the Lesser GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the Lesser GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.html>.
*
*   2011-06-20 06:03:57 PM -0400
*
*   These functions work by any input that is provided. For a function demonstrating it.
*    Please look at the second source file at the post of the question on stack overflow.
*    It also includes an answer for implenting it using recursion if that is your favored
*    way of doing it. I personally do not feel comfortable working with recursion so that is
*    why I went with the implementation that I have included.
*/

/*
*This is the primary file for other items that aren't as important as they kinda are. Include this if you want them all.
*
*
*/
#include "functions.h"
#define count(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))));


unsigned long microtime(void){
    struct timeval time;
    gettimeofday(&time,NULL);
    unsigned long times=((unsigned long long) time.tv_sec*1000000)+(time.tv_usec);
    return times;
}

int match(const char *string, char *pattern) {
  int status;
  regex_t re;
  if(regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
    return 0;
  }
  status = regexec(&re, string, (size_t)0, NULL, 0);
  regfree(&re);
  if(status != 0) {
    return 0;
   }

  return 1;
}
