/* Copyright (c) 2008, Jacob Burnim (jburnim@cs.berkeley.edu)
 *
 * This file is part of CREST, which is distributed under the revised
 * BSD license.  A copy of this license can be found in the file LICENSE.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See LICENSE
 * for details.
 */

#include <crest.h>
#include <stdio.h>
#include <server.h>

int main(void) {
  int a, b, c;
  CREST_int(a);
  CREST_int(b);
  CREST_int(z);

  if (a > 50) {
    if (b > 25) {
      z = a + b;
      __CrestStoreZ(2, (unsigned long )(& z));
      // printf("From program: %d\n",c);
    }
    else{
      // sprintf(buff,"200");  
      z = a + 20;
      __CrestStoreZ(2, (unsigned long )(& z));
      // printf("From program: %d\n",c);
    }
  }else{
    z = b + 20;
    __CrestStoreZ(2, (unsigned long )(& z));
    // printf("From program: %d\n",c);
  }  

  // if(c>10000){
  //   printf("Taken:%d\n",x);
  // }else{
  //   x = 2;
  //   printf("Not taken\n");
  // }

  // if (a > 50) {
  //   if (b > 25) {
  //     sprintf(buff,"100");
  //   }
  //   else{
  //     sprintf(buff,"200");  
  //   }
  // }else{
  //   sprintf(buff,"300");

  // printf("a:%d b:%d c:%d\n",a,b,c);
  /* match outputs */
  // FILE *fp = fopen("client_output","w");
  // fprintf(fp,"%s",buff);
  // fclose(fp);

  return 0;
}
