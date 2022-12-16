#include <stdio.h>

/*
**      array.123    XREF[2]:     phase_5:08048d52(*), 
**                   phase_5:08048d5f(R)  
**  0804b220 69              ??         69h    i
**  0804b221 73              ??         73h    s
**  0804b222 72              ??         72h    r
**  0804b223 76              ??         76h    v
**  0804b224 65              ??         65h    e
**  0804b225 61              ??         61h    a
**  0804b226 77              ??         77h    w
**  0804b227 68              ??         68h    h
**  0804b228 6f              ??         6Fh    o
**  0804b229 62              ??         62h    b
**  0804b22a 70              ??         70h    p
**  0804b22b 6e              ??         6Eh    n
**  0804b22c 75              ??         75h    u
**  0804b22d 74              ??         74h    t
**  0804b22e 66              ??         66h    f
**  0804b22f 67              ??         67h    g
**
**______________________________________________________
**| [0] | [1] | [2]| [3]| [4]| [5] | [6] | [7] | [8] | [9] | [10] | [11] | [12] | [13] | [14] | [15]|
**|  i     s     r    v    e    a     w     h     o     b      p      n     u      t       f     g  | 
**
*/
/*
void phase_5(int param_1)

{
  int iVar1;
  undefined local_c [6];
  undefined local_6;
  
  iVar1 = string_length(param_1);
  if (iVar1 != 6) {
    explode_bomb();
  }
  iVar1 = 0;
  do {
    local_c[iVar1] = (&array.123)[(char)(*(byte *)(iVar1 + param_1) & 0xf)];
    iVar1 = iVar1 + 1;
  } while (iVar1 < 6);
  local_6 = 0;
  iVar1 = strings_not_equal(local_c,"giants");
  if (iVar1 != 0) {
    explode_bomb();
  }
  return;
}
*/

int main()
{
    char str[] = "opekmq";
    char *array123 = "isrveawhobpnutfg";
    int i = 0;

   while(str[i])
    {
        switch(str[i] & 0xf)
        {
            case 15: 
            {
                printf("%d\n", str[i] & 0xf);
                printf("=> %c\n", array123[str[i] & 0xf]);
                break;
            }
            case 0: 
            {
                printf("%d\n", str[i] & 0xf);
                printf("=> %c\n", array123[str[i] & 0xf]);
                break;
            }
            case 5: 
            {
                printf("%d\n", str[i] & 0xf);
                printf("=> %c\n", array123[str[i] & 0xf]);
                break;
            }
            case 11:
            {
                printf("%d\n", str[i] & 0xf);
                printf("=> %c\n", array123[str[i] & 0xf]);
                break;
            }
            case 13: 
            {
                printf("%d\n", str[i] & 0xf);
                printf("=> %c\n", array123[str[i] & 0xf]);
                break;
            }
            case 1: 
            {
                printf("%d\n", str[i]& 0xf);
                printf("=> %c\n", array123[str[i] & 0xf]);
                break;
            }
            default:
                break;
        }
        i++;  
    }
}