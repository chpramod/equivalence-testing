/* Generated by CIL v. 1.7.3 */
/* print_CIL_Input is true */

#line 16 "uniform_test_recv.c"
void __globinit_uniform_test_recv(void) ;
extern void __CrestInit(void)  __attribute__((__crest_skip__)) ;
extern void __CrestHandleReturn(int id , long long val )  __attribute__((__crest_skip__)) ;
extern void __CrestReturn(int id )  __attribute__((__crest_skip__)) ;
extern void __CrestCall(int id , unsigned int fid )  __attribute__((__crest_skip__)) ;
extern void __CrestBranch(int id , int bid , unsigned char b )  __attribute__((__crest_skip__)) ;
extern void __CrestApply2(int id , int op , long long val )  __attribute__((__crest_skip__)) ;
extern void __CrestApply1(int id , int op , long long val )  __attribute__((__crest_skip__)) ;
extern void __CrestClearStack(int id )  __attribute__((__crest_skip__)) ;
extern void __CrestStore(int id , unsigned long addr )  __attribute__((__crest_skip__)) ;
extern void __CrestLoad(int id , unsigned long addr , long long val )  __attribute__((__crest_skip__)) ;
#line 212 "/usr/lib/gcc/x86_64-linux-gnu/4.8/include/stddef.h"
typedef unsigned long size_t;
#line 179 "../bin/../include/crest.h"
extern void __CrestStoreZ(int  , unsigned long  )  __attribute__((__crest_skip__)) ;
#line 203
extern void __CrestInt(int *x )  __attribute__((__crest_skip__)) ;
#line 459 "/usr/include/string.h"
extern  __attribute__((__nothrow__)) void ( __attribute__((__nonnull__(1), __leaf__)) bzero)(void *__s ,
                                                                                             size_t __n ) ;
#line 16 "uniform_test_recv.c"
int main(void) 
{ 
  int a ;
  int b ;
  int c ;
  char buff[1024] ;
  int __retres5 ;

  {
  __globinit_uniform_test_recv();
  __CrestCall(1045, 37);
#line 18
  __CrestInt(& a);
#line 19
  __CrestInt(& b);
#line 20
  __CrestInt(& c);
  __CrestLoad(1046, (unsigned long )0, (long long )((size_t )1024));
#line 22
  bzero((void *)(buff), (size_t )1024);
  __CrestClearStack(1047);
  __CrestLoad(1050, (unsigned long )(& a), (long long )a);
  __CrestLoad(1049, (unsigned long )0, (long long )50);
  __CrestApply2(1048, 14, (long long )(a > 50));
#line 24
  if (a > 50) {
    __CrestBranch(1051, 291, 1);
    {
    __CrestLoad(1055, (unsigned long )(& b), (long long )b);
    __CrestLoad(1054, (unsigned long )0, (long long )25);
    __CrestApply2(1053, 14, (long long )(b > 25));
#line 25
    if (b > 25) {
      __CrestBranch(1056, 292, 1);
      __CrestLoad(1060, (unsigned long )(& a), (long long )a);
      __CrestLoad(1059, (unsigned long )(& b), (long long )b);
      __CrestApply2(1058, 0, (long long )(a + b));
      __CrestStore(1061, (unsigned long )(& c));
#line 26
      c = a + b;
#line 27
      __CrestStoreZ(2, (unsigned long )(& c));
    } else {
      __CrestBranch(1057, 293, 0);
      __CrestLoad(1064, (unsigned long )(& a), (long long )a);
      __CrestLoad(1063, (unsigned long )0, (long long )20);
      __CrestApply2(1062, 0, (long long )(a + 20));
      __CrestStore(1065, (unsigned long )(& c));
#line 32
      c = a + 20;
#line 33
      __CrestStoreZ(2, (unsigned long )(& c));
    }
    }
  } else {
    __CrestBranch(1052, 294, 0);
    __CrestLoad(1068, (unsigned long )(& b), (long long )b);
    __CrestLoad(1067, (unsigned long )0, (long long )20);
    __CrestApply2(1066, 0, (long long )(b + 20));
    __CrestStore(1069, (unsigned long )(& c));
#line 37
    c = b + 20;
#line 38
    __CrestStoreZ(2, (unsigned long )(& c));
  }
  __CrestLoad(1070, (unsigned long )0, (long long )0);
  __CrestStore(1071, (unsigned long )(& __retres5));
#line 65
  __retres5 = 0;
  __CrestLoad(1072, (unsigned long )(& __retres5), (long long )__retres5);
  __CrestReturn(1073);
#line 16
  return (__retres5);
}
}
void __globinit_uniform_test_recv(void) 
{ 


  {
  __CrestInit();
}
}