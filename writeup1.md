### Lost Linux root password - Recovery mode

it is possible to pass parameters to the kernel in the BIOS because the access to the kernel parameters is not protected so we can change the password of `root` and boot normally or add more users to sudoers


pass the init=/bin/bash parameter to the kernel. This will give you a root shell without connecting or anything, but system initialization will not be done either (but/etc/ must be on the root filesystem and it will be mounted). 

[Read more](https://www.kernel.org/doc/html/v4.14/admin-guide/kernel-parameters.html)

```
  init =        [KNL]
                Format: <full_path>
                Run specified binary instead of /sbin/init as init
                process.
```
___
|parameter 	|Description|
|----|----|
|init| 	Run specified binary instead of /sbin/init as init process. The systemd-sysvcompat package symlinks /sbin/init to /usr/lib/systemd/systemd to use systemd. Set it to /bin/sh to boot to the shell.|
|rw |	Mount root device read-write on boot. |
____

## Step 1 

During boot, press and hold `Shift` (for BIOS) or `ESC` (for UEFI). 
pass the init=/bin/bash parameter to the kernel. This will give you a root shell without connecting or anything, but system initialization will not be done either (but/etc/ must be on the root filesystem and it will be mounted). 

```
boot > live rw init=/bin/bash
```
___
![Bios](/.github/VirtualBox_boot2root_BIOSBOOT.png)
___
This will display a screen whit a root prompt.

## Step 2

Mount your root filesystem in read-write mode , in this way the changes are saved

```
    mount -n -o remount,rw /
```

## Step 3 

You can now reset the root password by using the following command

```
    passwd root
```
___
![ROOT](.github/VirtualBox_boot2root_ROOT.png)
___
also you can add a new user and add this user to sudoers

```
    adduser smoreno-
```
___
![CREATUSER](.github/VirtualBox_boot2root_CREATUSER.png)
___
```
    usermod -aG sudo smoreno-
```
## Step 4 

Once you are done, type:
```
    exec /sbin/init
```
This will exit the prompt and reboot the computer.
____
![BOOTNEWUSER](.github/VirtualBox_boot2root_BOOTNEWUSER.png)
____
![ADDUSEFIN](.github/VirtualBox_boot2root_ADDUSERFIN_39.png)
____

