# ag-gen-guided
Code and Setup Tutorial for RAGE Attack Graph Generator.

## Setup

RAGE can work with Linux / MacOS, but is recommended that you use a Debian-based Linux to facilitate the process. 
The following shows installation with a Debian image on VMware Player specifically, but you can use your own custom setup.  

*Note: this tutorial assumes the use of the apt package manager. If you are using a different package manager, please enter the equivalent command instead.*

### VMware with Debian

1. Download a Debian image (netinst iso is recommended)
2. Install VMware Player
3. Install Debian on VMware.  
Recommendation: Allocate at least 20GB of hard disk space and 2GB of RAM. Use the GUI installation process and guided disk partitioning when installing. This should be enough to get it running. 

### Getting sudo permissions

Adding yourself to the sudoers file:
```sh
su -
visudo
```

Add the following to the bottom of the file and save:

```sh
your_username_here ALL=(ALL)       ALL
```

Make sure you have sudo permissions by testing with something like: `sudo echo hello`

### Install VMware Tools

VMware Tools makes your life easier. Install it! (Enables copy/paste, display scaling, etc. for VM)  


```sh
sudo apt install open-vm-tools
```

Then reboot the VM, and you should have proper display scaling. 

## RAGE Installation
### Cloning this repository

You can download a clean copy of the generator as follows:

```sh 
sudo apt install git
git clone https://github.com/ferdinandmudjialim/ag-gen-guided
```

### Dependencies
Run the `deps.sh` command to install necessary dependencies.
This script supports debian based systems and Mac OSX (with homebrew)

```sh
./deps.sh
```

### Building

This application uses CMake to build.

```sh 
mkdir build
cd build
```

Generally, you should use the Release build for testing and generating your graphs (unless you need debugging information, of course)

For release builds:

```sh
cmake -DCMAKE_BUILD_TYPE=Release ../
```

For debug builds:

```sh
cmake -DCMAKE_BUILD_TYPE=Debug ../
```

Build the application:

```sh
make ag_gen
```

With this, the compiled program should be located at `build/ag_gen`. 

## PostgreSQL Setup
RAGE uses PostgreSQL for database operations.

### Create a User
First, login as the default user postgres.

`sudo -iu postgres` or `sudo su - postgres`

Then, Use the createuser and createdb scripts to create the necessary account and database in PostgreSQL. 

*Make sure the user is YOUR username (from before you logged in as postgres)*
Setting a password is recommended.

```sh
createuser -d -l -P "your_username"
createdb -O "your_username" ag_gen
```

Note: createdb with option "O" (oh) not "0" (zero)

At this point, logout from the postgres user.
(CTRL+D hotkey) or simply: `logout`

### Populating the Database

Use the `db_manage.sh` utility to populate the database (this will overwrite anything in the `ag_gen` database).
An example use of this is:

```sh
./db_manage.sh -d ag_gen
```

## Configuration

RAGE uses an ini-style configuration, located in config.ini.
Make sure the config.ini matches the username and password created earlier.

- name: name of the database
- host: IP or hostname of the database server
- port: port number of the database server
- username: database user name
- password (optional): database password

## Testing

Run `./test.sh` to populate database, compile and run the generator.
Run `./t1.sh` to only populate database and run the generator (if compilation was already done beforehand). 

### Checking the Database

After running the generator, the database should be populated. Check this by connecting to it:

```sh
psql ag_gen
```
and check the database with normal SQL commands.

### Running Manually (Example)

Execute an example from the examples directory.  
*Since the program is located at* `build/ag_gen`, *run this from the* `build` *directory.*

```sh
./ag_gen -n ../examples/thesis_example.nm -x ../examples/thesis_example.xp
```

## Contributing
### Editorconfig

When contributing code, please install the "editorconfig" plugin for your text editor.

- Adds extra newline to end of file if not already there.
- Removes whitespace at end of lines
- Automatically sets indentation to tabs set to 4 spaces
