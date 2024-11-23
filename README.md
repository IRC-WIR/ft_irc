# ft_irc
In this project, we created our own IRC server.

## Abstract
ft_irc is a modular C++ Internet Relay Chat (IRC) server.
IRC is a text-based communication protocol on the Internet.
It offers real-time messaging and users can exchange direct messages and join group channels.

## How to Use
### installation
1. Clone this repository
```
git clone git@github.com:IRC-WIR/ft_irc.git
```
2. Compile with `make`
3. Run the server
```
./ircserv <port> <password>
```
- port: The port number on which your IRC server will be listening to for incoming IRC connections.
- password: The connection password. It will be needed by any IRC client that tries to connect to your server.
            password should be more than 7 letters, only within ascii code.
4. Connect with clients
You can use an actual IRC client or `nc` command to connect to the server.

### commands

## Architecture

## Document
### [UNIT TEST](https://github.com/IRC-WIR/ft_irc/wiki/UNIT-TEST)
### [UML](https://github.com/IRC-WIR/ft_irc/wiki/UTM)

## Reference
### [Internet Relay Chat Protocol 1459](https://datatracker.ietf.org/doc/rfc1459/)
### [Internet Relay Chat: Architecture](https://datatracker.ietf.org/doc/html/rfc2810)
### [Internet Relay Chat: Channel Management](https://datatracker.ietf.org/doc/html/rfc2811)
### [Internet Relay Chat: Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
### [Internet Relay Chat: Server Protocol](https://datatracker.ietf.org/doc/html/rfc2813)