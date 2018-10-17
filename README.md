MarketArbitrageCoin (fork of PIVX) integration/staging repository
======================================


It is recommended [use the shell script](https://github.com/MarketArbitrageCoin/MARCresources/blob/master/marcoin-mn.sh) to install a MarketArbitrageCoin Masternode on a Linux server running Ubuntu 14.04, 16.04, 18.04

***

Quick installation of the MarketArbitrageCoin daemon under linux. See detailed instructions there [build-unix.md](build-unix.md)

Installation of libraries (using root user):

    add-apt-repository ppa:bitcoin/bitcoin -y
    apt-get update
    apt-get install -y build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils
    apt-get install -y libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev
    apt-get install -y libdb4.8-dev libdb4.8++-dev

Cloning the repository and compiling (use any user with the sudo group):

    cd
    git clone https://github.com/MarketArbitrageCoin/MARCcore.git
    cd MarketArbitrageCoin
    ./autogen.sh
    ./configure
    sudo make install
    cd src
    sudo strip marcoind
    sudo strip marcoin-cli
    sudo strip marcoin-tx
    cd ..

Running the daemon:

    marcoind 

Stopping the daemon:

    marcoin-cli stop

Demon status:

    marcoin-cli getinfo
    marcoin-cli mnsync status

All binaries for different operating systems, you can download in the resources repository:

https://github.com/MarketArbitrageCoin/MARCresources

P2P port: 44004, RPC port: 44005
-
Distributed under the MIT software license, see the accompanying file COPYING or http://www.opensource.org/licenses/mit-license.php.
