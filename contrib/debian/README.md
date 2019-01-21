
Debian
====================
This directory contains files used to package bitcoind/bitcoin-qt
for Debian-based Linux systems. If you compile bitcoind/bitcoin-qt yourself, there are some useful files here.

To add URI support and clickable links (reddcoin:<Reddcoin addres>) for the Reddcoin Core QT wallet

This can be installed for either all users or the current user

### All users

#### Install desktop shortcut
    cd reddcoin
    sudo desktop-file-validate ./contrib/debian/reddcoin-qt.desktop # See Note
    sudo cp ./contrib/debian/reddcoin-qt.desktop /usr/share/applications/
    sudo update-desktop-database

#### Install icon graphics
    sudo cp share/pixmaps/reddcoin128.png /usr/share/pixmaps/

### Current user

#### Install desktop shortcut
    cd reddcoin
    sudo desktop-file-validate ./contrib/debian/reddcoin-qt.desktop # Check paths in reddcoin-qt.desktop match the installation path usually /usr/local/bin
    sudo cp ./contrib/debian/reddcoin-qt.desktop ~/.local/share/applications/
    sudo update-desktop-database

#### Install icon graphics
    sudo cp share/pixmaps/reddcoin128.png /usr/share/pixmaps/


**Note:** If you build yourself, you will either need to modify the paths in
the .desktop file or copy reddcoin-qt or symlink your reddcoin-qt binary to `/usr/local/bin`
and copy the `../../share/pixmaps/reddcoin128.png` to `/usr/share/pixmaps`


KDE
====================
bitcoin-qt.protocol (KDE)