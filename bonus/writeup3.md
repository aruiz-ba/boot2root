# Boot2root

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

since we had no way to connect to the machine we started by doing an `ifconfig` to recover the IP address that virtual box assigned to the vm

```
┌──(kali㉿kali)-[~]
└─$ ifconfig

...

wlp0s20f3: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.1.24  netmask 255.255.255.0  broadcast 192.168.1.255
        inet6 2a01:cb00:47e:b300:6b1a:5d4e:1d55:a8b0  prefixlen 64  scopeid 0x0<global>
        inet6 2a01:cb00:47e:b300:c0c9:939b:ab65:4b06  prefixlen 64  scopeid 0x0<global>
        inet6 fe80::962a:3971:e97d:a240  prefixlen 64  scopeid 0x20<link>
        ether 9c:29:76:b0:a2:e8  txqueuelen 1000  (Ethernet)
        RX packets 3700389  bytes 4972817704 (4.9 GB)
        RX errors 0  dropped 2673  overruns 0  frame 0
        TX packets 360941  bytes 70056046 (70.0 MB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0


```

we did an ip scan with nmap 

```
┌──(kali㉿kali)-[~]
└─$ nmap 192.168.1.0-255
...

Nmap scan report for kali.home (192.168.1.26)
Host is up (0.00043s latency).
All 1000 scanned ports on kali.home (192.168.1.26) are in ignored states.
Not shown: 1000 closed tcp ports (conn-refused)

Nmap scan report for borntosechackme.home (192.168.1.29)
Host is up (0.00017s latency).
Not shown: 994 closed tcp ports (conn-refused)
PORT    STATE SERVICE
21/tcp  open  ftp
22/tcp  open  ssh
80/tcp  open  http
143/tcp open  imap
443/tcp open  https
993/tcp open  imaps

Nmap done: 256 IP addresses (6 hosts up) scanned in 17.31 seconds

```

there is some interesting information it seems that it has web server
we searched in kalitools, what allowed us to do a scan of the web server we try with `cmseek`,`wig`, `rta` ect.. but whoever gave us the most information was [DIRB](https://www.kali.org/tools/dirb/) `dirb` is a Web Content Scanner. It looks for existing (and/or hidden) Web Objects. It basically works by launching a dictionary based attack against a web server and analyzing the responses.

```
┌──(kali㉿kali)-[~/Desktop/boot2root_git]
└─$ sudo apt install dirb 
┌──(kali㉿kali)-[~/Desktop/boot2root_git]
└─$ dirb https://192.168.1.29                                                                  130 ⨯

-----------------
DIRB v2.22    
By The Dark Raver
-----------------

START_TIME: Wed Mar  2 17:48:20 2022
URL_BASE: https://192.168.1.29/
WORDLIST_FILES: /usr/share/dirb/wordlists/common.txt

-----------------

GENERATED WORDS: 4612                                                          

---- Scanning URL: https://192.168.1.29/ ----
+ https://192.168.1.29/cgi-bin/ (CODE:403|SIZE:289)                                                 
==> DIRECTORY: https://192.168.1.29/forum/                                                          
==> DIRECTORY: https://192.168.1.29/phpmyadmin/                                                     
+ https://192.168.1.29/server-status (CODE:403|SIZE:294)                                            
==> DIRECTORY: https://192.168.1.29/webmail/                                                        
                                                                                                    
---- Entering directory: https://192.168.1.29/forum/ ----
+ https://192.168.1.29/forum/backup (CODE:403|SIZE:293)                                             
+ https://192.168.1.29/forum/config (CODE:403|SIZE:293)                                             
==> DIRECTORY: https://192.168.1.29/forum/images/                                                   
==> DIRECTORY: https://192.168.1.29/forum/includes/                                                 
+ https://192.168.1.29/forum/index (CODE:200|SIZE:4935)                                             
+ https://192.168.1.29/forum/index.php (CODE:200|SIZE:4935)                                         
==> DIRECTORY: https://192.168.1.29/forum/js/                                                       
==> DIRECTORY: https://192.168.1.29/forum/lang/                                                     
==> DIRECTORY: https://192.168.1.29/forum/modules/                                                  
==> DIRECTORY: https://192.168.1.29/forum/templates_c/                                              
==> DIRECTORY: https://192.168.1.29/forum/themes/                                                   
==> DIRECTORY: https://192.168.1.29/forum/update/                                                   
                                                                                                    
---- Entering directory: https://192.168.1.29/phpmyadmin/ ----
+ https://192.168.1.29/phpmyadmin/favicon.ico (CODE:200|SIZE:18902)                                 
+ https://192.168.1.29/phpmyadmin/index.php (CODE:200|SIZE:7540)                                    
==> DIRECTORY: https://192.168.1.29/phpmyadmin/js/                                                  
+ https://192.168.1.29/phpmyadmin/libraries (CODE:403|SIZE:301)                                     
==> DIRECTORY: https://192.168.1.29/phpmyadmin/locale/                                              
+ https://192.168.1.29/phpmyadmin/phpinfo.php (CODE:200|SIZE:7540)                                  
+ https://192.168.1.29/phpmyadmin/setup (CODE:401|SIZE:480)                                         
==> DIRECTORY: https://192.168.1.29/phpmyadmin/themes/                                              
                                                                                                    
---- Entering directory: https://192.168.1.29/webmail/ ----
+ https://192.168.1.29/webmail/class (CODE:403|SIZE:294)                                            
==> DIRECTORY: https://192.168.1.29/webmail/config/                                                 
+ https://192.168.1.29/webmail/functions (CODE:403|SIZE:298)                                        
+ https://192.168.1.29/webmail/help (CODE:403|SIZE:293)                                             
==> DIRECTORY: https://192.168.1.29/webmail/images/                                                 
+ https://192.168.1.29/webmail/include (CODE:403|SIZE:296)                                          
+ https://192.168.1.29/webmail/index.php (CODE:302|SIZE:0)                                          
+ https://192.168.1.29/webmail/locale (CODE:403|SIZE:295)                                           
==> DIRECTORY: https://192.168.1.29/webmail/plugins/                                                
==> DIRECTORY: https://192.168.1.29/webmail/src/                                                    
==> DIRECTORY: https://192.168.1.29/webmail/themes/ 

```

It seems that the web server uses phpmyadmin this reminded us that when we explored the files in the home we had seen various password so we tried them

We managed to login as root on phpmyadmin with the password of this email.

```
┌──(root💀kali)-[/mnt/fs/home/laurie@borntosec.net/mail]
└─# ls                   
INBOX.Drafts  INBOX.Sent  INBOX.Trash

┌──(root💀kali)-[/mnt/fs/home/laurie@borntosec.net/mail]
└─# cat * 
 ...
 From laurie@borntosec.net  Thu Oct 08 23:25:25 2015
Received: from 192.168.1.22
        (SquirrelMail authenticated user laurie@borntosec.net)
        by 192.168.1.8 with HTTP;
        Thu, 8 Oct 2015 23:25:25 +0200
Message-ID: <e231e4a59416c44fd367fc5eeff1e8f5.squirrel@192.168.1.8>
Date: Thu, 8 Oct 2015 23:25:25 +0200
Subject: DB Access
From: laurie@borntosec.net
To: ft_root@mail.borntosec.net
User-Agent: SquirrelMail/1.4.22
MIME-Version: 1.0
Content-Type: text/plain;charset=iso-8859-1
Content-Transfer-Encoding: 8bit
X-Priority: 3 (Normal)
Importance: Normal
X-UID: 2
Status: R
X-Keywords:                                                                        
Content-Length: 93

Hey Laurie,

You cant connect to the databases now. Use root/Fg-'kKXBj87E:aJ$

Best regards.

```
By browsing the web server, the forum, the emails, the db we realized that this is information that we already had available, when we made the mount of the iso, so we tried to connect us in ftp to the machine, we tried with the root password without success, then we tried with the other password that we have in the 'LOOKATME' folder

```
┌──(root💀kali)-[/mnt/fs/home]
└─# ls                                                                                                                                 130 ⨯
ft_root  laurie  laurie@borntosec.net  lmezard  LOOKATME  thor  zaz
┌──(root💀kali)-[/mnt/fs/home]
└─# ls -la LOOKATME
total 1
drwxr-x--- 2 www-data www-data  31 Oct  8  2015 .
drwxrwx--x 9 www-data root     126 Oct 13  2015 ..
-rwxr-x--- 1 www-data www-data  25 Oct  8  2015 password
┌──(root💀kali)-[/mnt/fs/home]
└─# cat LOOKATME/password
lmezard:G!@M6f4Eatau{sF"

```
```
┌──(root💀kali)-[/mnt/fs/home]
└─# ftp 172.20.10.8
Connected to 172.20.10.8.
220 Welcome on this server
Name (172.20.10.8:kali): lmezard
331 Please specify the password.
Password:
230 Login successful.
Remote system type is UNIX.
Using binary mode to transfer files.
ftp> ls
200 PORT command successful. Consider using PASV.
150 Here comes the directory listing.
-rwxr-x---    1 1001     1001           96 Oct 15  2015 README
-rwxr-x---    1 1001     1001       808960 Oct 08  2015 fun
226 Directory send OK.
ftp> get fun
local: fun remote: fun
200 PORT command successful. Consider using PASV.
150 Opening BINARY mode data connection for fun (808960 bytes).
226 Transfer complete.
808960 bytes received in 0.04 secs (20.0084 MB/s)

```
we got back the fun file in host

```
┌──(kali㉿kali)-[~]
└─$ file fun 
fun: POSIX tar archive (GNU)
┌──(kali㉿kali)-[~]
└─$ tar -xvf fun
ft_fun/
ft_fun/C4D03.pcap
ft_fun/GKGEP.pcap
ft_fun/A5GPY.pcap
ft_fun/K8SEB.pcap
ft_fun/PFG98.pcap
ft_fun/U89WD.pcap
ft_fun/8YK9P.pcap
ft_fun/R6GKQ.pcap
ft_fun/UBX8K.pcap
...
ft_fun/DFO1G.pcap
ft_fun/G3VJZ.pcap
ft_fun/Y8S1M.pcap
```

we do a cat on `.pcap` files we found a main(), which makes a printf of the return of several `getme()` functions.. which are cut on diffferent files, to find the return of each function we do `grep` searching the beginning of the function then go to the next specified file//file** 

```
int main() {
	printf("M");
	printf("Y");
	printf(" ");
	printf("P");
	printf("A");
	printf("S");
	printf("S");
	printf("W");
	printf("O");
	printf("R");
	printf("D");
	printf(" ");
	printf("I");
	printf("S");
	printf(":");
	printf(" ");
	printf("%c",getme1());
	printf("%c",getme2());
	printf("%c",getme3());
	printf("%c",getme4());
	printf("%c",getme5());
	printf("%c",getme6());
	printf("%c",getme7());
	printf("%c",getme8());
	printf("%c",getme9());
	printf("%c",getme10());
	printf("%c",getme11());
	printf("%c",getme12());
	printf("\n");
	printf("Now SHA-256 it and submit");
}
```

|Return values:||
|---------|------|
| getme1() | 'I' |
| getme2() | 'h' |
| getme3() | 'e' |
| getme4() | 'a' |
| getme5() | 'r' |
| getme6() | 't' |
| getme7() | 'p' |
| getme8() | 'w' |
| getme9() | 'n' |
| getme10()| 'a' |
| getme11()| 'g' |
| getme12()| 'e' |
|||
______________________

The last printf of the main tell us do a SHA-256 :

```
┌──(kali㉿kali)-[~/ft_fun]
└─$ echo -n Iheartpwnage | sha256sum
330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4  -
                                                                                                 
```
```
┌──(root💀kali)-[/mnt/fs/home]
└─# cat lmezard/README                                                                                                                   
Complete this little challenge and use the result as password for user 'laurie' to login in ssh

```
So now we can log on ssh to the VW

```
┌──(kali㉿kali)-[~/ft_fun]
└─ sshpass -p "330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4" ssh laurie@172.20.10.8                                                                
        ____                _______    _____           
       |  _ \              |__   __|  / ____|          
       | |_) | ___  _ __ _ __ | | ___| (___   ___  ___ 
       |  _ < / _ \| '__| '_ \| |/ _ \\___ \ / _ \/ __|
       | |_) | (_) | |  | | | | | (_) |___) |  __/ (__ 
       |____/ \___/|_|  |_| |_|_|\___/_____/ \___|\___|

                       Good luck & Have fun
laurie@BornToSecHackMe:~$
laurie@BornToSecHackMe:~$ ls -l
total 27
-rwxr-x--- 1 laurie laurie 26943 Oct  8  2015 bomb
-rwxr-x--- 1 laurie laurie   158 Oct  8  2015 README
laurie@BornToSecHackMe:~$ file bomb 
bomb: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.0.0, not stripped
laurie@BornToSecHackMe:~$ 
laurie@BornToSecHackMe:~$ cat README 
Diffuse this bomb!
When you have all the password use it as "thor" user with ssh.

HINT:
P
 2
 b

o
4

NO SPACE IN THE PASSWORD (password is case sensitive
```

In the home/laurie directory we found a executable, we have annalysed it with [ghidra](https://ghidra-sre.org/) and `gdb`, it is a program that waits for several inputs that correspond to "phases_n", if it does not correspond to what is expected the bomb explodes.

```
int __regparm3 main(int argc,char **argv)

{
  undefined4 uVar1;
  int in_stack_00000004;
  undefined4 *in_stack_00000008;
  
  if (in_stack_00000004 == 1) {
    infile = stdin;
  }
  else {
    if (in_stack_00000004 != 2) {
      printf("Usage: %s [<input_file>]\n",*in_stack_00000008);
                    /* WARNING: Subroutine does not return */
      exit(8);
    }
    infile = (_IO_FILE *)fopen((char *)in_stack_00000008[1],"r");
    if ((FILE *)infile == (FILE *)0x0) {
      printf("%s: Error: Couldn\'t open %s\n",*in_stack_00000008,in_stack_00000008[1]);
                    /* WARNING: Subroutine does not return */
      exit(8);
    }
  }
  initialize_bomb();
  printf("Welcome this is my little bomb !!!! You have 6 stages with\n");
  printf("only one life good luck !! Have a nice day!\n");
  uVar1 = read_line();
  phase_1(uVar1);
  phase_defused();
  printf("Phase 1 defused. How about the next one?\n");
  uVar1 = read_line();
  phase_2(uVar1);
  phase_defused();
  printf("That\'s number 2.  Keep going!\n");
  uVar1 = read_line();
  phase_3(uVar1);
  phase_defused();
  printf("Halfway there!\n");
  uVar1 = read_line();
  phase_4(uVar1);
  phase_defused();
  printf("So you got that one.  Try this one.\n");
  uVar1 = read_line();
  phase_5(uVar1);
  phase_defused();
  printf("Good work!  On to the next...\n");
  uVar1 = read_line();
  phase_6(uVar1);
  phase_defused();
  return 0;

```

## Phase_1

HINT : ( first key is a 'P' )

Here it’s just a simple cmp with the string "Public speaking is very easy."

[Phase_1 Flow Control Graph][1]

[1]: /.github/phase_1.txt

[Phase_1 Code Source][2]

[2]: /scripts/bomb/phase_1.c

- 1 Password => Public speaking is very easy.

## Phase_2

HINT : ( Second key is a int 2 )

Here we must enter a sequence of six numbers all separated by white spaces (" "). The bomb explodes if the first digit is different from 1, the next number must be the current number multiplied by the next position on the string.


[Phase_2 Control Flow Graph][3]

[3]: /.github/phase_2.txt

[Phase_2 Code Source][4]

[4]: /scripts/bomb/phase_2.c

- 2 Password => 1 2 6 24 120 720.

## Phase_3

HINT : ( Second key is a char 'b' )

Here we must enter 3 arguments according to sscanf format string number - caratere - number. 
The first number determines which switch case is executed.
If we enter 1 the case 1 is executed, and the char of the user vill be compared with a predefined char, in `case 1:` is 'b', Finally the last number will also be compared by a predefined number; here 0xd6 or 214.
This reasoning is valid for all phase `case`.

[Phase_3 Control Flow Graph][5]

[5]: /.github/phase_3.txt

[Phase_3 Code Source][6]

[6]: /scripts/bomb/phase_3.c

- 3 Password => 1 b 214.

## Phase_4

HINT : ( )

This phase waits for a number and passes it to the `fun4()`. It compares the return of the function with the value 55. If this is not the right value, the bombre explodes. Looking at the content of `fun4()`, we quickly realize that this is the ***Fibonacci's suite***. 55 being the 9th term of the sequel.

[Phase_4 Control Flow Graph][12]

[12]: /.github/phase_4.txt

[Phase_4 Code Source][7]

[7]: /scripts/bomb/phase_4.c

- 4 Password => 9.

## Phase 5

HINT : ( First key is a char 'o' )

The program waits for a chain of carateres. If the length is different from 6 the bomb explodes. Then it goes through the string, and makes the following instructions for each caratere:

- Let v be the ascii value of the caratere
- Pose tmp = v & 0xf appli a mask (keeps only the 4 bits ***LSB***)
- uses tmp as an index of a global array named array.123
- recupere array.123[tmp] and stores it in a new local_c table

Finally the program checks that the table is equal to the chain `giants`, otherwise the bomb explodes.

[Phase_5 Control Flow Graph][8]

[8]: /.github/phase_5.txt

[Phase_5 Code Source][9]

[9]: /scripts/bomb/phase_5.c

- 5 Password => opekmq.

## Phase 6

HINT : ( First key is a int 4 )

The program waits for a sequence of six numbers, otherwise the bomb explodes. Here several loops operate:

- The first checks that each number is between 1 and 6, and differs from each other.
- The second retrieves the pointer of a node in a string list with a precise index by a number. For each digit (index), the pointer is stored in a pointer array.
- Then the next fields of each node are reordered according to the precise order by the user.

Finally the program verifies that in this new order the value of each is in order of decrease. Otherwise the bomb explodes.

[Phase_6 Control Flow Graph][10]

[10]: /.github/phase_6.txt

[Phase_6 Code Source][11]

[11]: /scripts/bomb/phase_6.c

- 6 Password => 4 2 6 3 1 5.

```
┌──(kali㉿kali)-[~/Desktop]
└─$ ./bomb      
Welcome this is my little bomb !!!! You have 6 stages with
only one life good luck !! Have a nice day!
Public speaking is very easy.
Phase 1 defused. How about the next one?
1 2 6 24 120 720
That's number 2.  Keep going!
1 b 214
Halfway there!
9
So you got that one.  Try this one.
opekmq
Good work!  On to the next...
4 2 6 3 1 5
Congratulations! You've defused the bomb!
 
Publicspeakingisveryeasy.126241207201b2149opekmq426135
```
[12]: /thor/turtle.md

[thor suit][12]

[13]: /zaz/zaz_overflow.md

[zaz suit][13]