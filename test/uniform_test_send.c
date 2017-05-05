#include <crest.h>
#include <stdio.h>
#include <server.h>
int main(void) {
  int a, b,z;
  CREST_int(a);
  CREST_int(b);
  CREST_int(z);

  struct INPUT *in = (struct INPUT*)malloc(sizeof(*in));
  in->num = 3;
  in->inputs[0] = a;
  in->inputs[1] = b;
  in->inputs[2] = z; 
  store_input(in); 
  printf("Storing server input\n");

  if (a > 50) {
    if (b > 25) {
      z = a + b;
      __CrestStoreZ(1, (unsigned long )(& z));
    }
    else{
      z = a + 20;
      __CrestStoreZ(1, (unsigned long )(& z));
    }
  }else{
    z = b + 20;
    __CrestStoreZ(1, (unsigned long )(& z));
  }
  return 0;
}
