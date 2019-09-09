# Dynamic Window Manager (DWM)
My fork of the suckless DWM v6.2. Following patches have been applied
* Tabv2b
* Systray
* Pertag
* Zoomswap

I have also added the session file and the display manager shortcut. They allow logging into DWM session from any Display Manager e.g. LightDM. These need to be installed manually.

## Installation
```bash
$ sudo cp -vf ./session-files/dwm-session /usr/local/bin
$ sudo cp -vf ./session-files/dwm.desktop /usr/share/xsessions/
$ sudo make install clean
```
