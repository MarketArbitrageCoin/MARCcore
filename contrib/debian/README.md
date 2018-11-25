
Debian
====================
This directory contains files used to package marcoind/marcoin-qt
for Debian-based Linux systems. If you compile marcoind/marcoin-qt yourself, there are some useful files here.

## marcoin: URI support ##


marcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install marcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your marcoinqt binary to `/usr/bin`
and the `../../share/pixmaps/marcoin128.png` to `/usr/share/pixmaps`

marcoin-qt.protocol (KDE)

