
/*
** Code Source genered by Ghidra
*/

void phase_2(undefined4 param_1)

{
  int iVar1;
  int aiStack32 [7];
  
  read_six_numbers(param_1,aiStack32 + 1);
  if (aiStack32[1] != 1) {
    explode_bomb();
  }
  iVar1 = 1;
  do {
    if (aiStack32[iVar1 + 1] != (iVar1 + 1) * aiStack32[iVar1]) {
      explode_bomb();
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 6);
  return;
}
