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
sudo apt install open-vm-tools-desktop
```

Then reboot the VM, and you should have proper display scaling, copy/paste, and related features. 

## RAGE Installation
### Updating packages
Note: If you don't have sudo permissions yet, see [above](https://github.com/ferdinandmudjialim/ag-gen-guided#getting-sudo-permissions)  
Don't forget to update your system packages!
```sh 
sudo apt-get update && sudo apt-get upgrade
```

### Cloning this repository
You can download a clean copy of the generator as follows:

```sh 
sudo apt install git
git clone https://github.com/ferdinandmudjialim/ag-gen-guided
```

### Dependencies
Run the `deps.sh` script (in project main directory) to install necessary dependencies.
This script supports debian based systems and *should* support Mac OSX (with homebrew)

```sh
cd ag-gen-guided/
./deps.sh
```

### Building (Manually)
This section is mainly for reference or those who want to learn about the building process.  
It is done automatically in scripts later.  
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

With this, the compiled program should be located in the `build` directory as `ag_gen`. 

## PostgreSQL Setup
RAGE uses PostgreSQL for its database operations.

### Create a User
First, login as the default user postgres.

`sudo -iu postgres` or `sudo su - postgres`

Then, use the createuser and createdb commands to create the necessary account and database in PostgreSQL. 

*Make sure the user is YOUR "personal" username (from before you logged in as postgres)*  
Setting a password is recommended, but not required.

```sh
createuser -d -l -P "your_username"
createdb -O "your_username" ag_gen
```

Note: createdb uses option "O" (oh) not "0" (zero)

At this point, logout from the postgres user.
(CTRL+D hotkey) or simply: `logout`

### Populating the Database (Manually)
Note: The test scripts included should do this automatically. This section is included in case it is useful to someone.  
Use the `db_manage.sh` script (in project main directory) to populate the database (this will overwrite anything in the `ag_gen` database).
An example use of this is:

```sh
./db_manage.sh -d ag_gen
```

## Configuration
RAGE uses an ini-style configuration, located in the project main directory as `config.ini`.
Make sure the `config.ini` matches the username and password created earlier for PostgreSQL.

- name: name of the database
- host: IP or hostname of the database server
- port: port number of the database server
- username: database user name
- password (optional): database password

## Testing
Test scripts are included in the project main directory.  
Choose one:  
Run `./test.sh` to populate database, compile and run the generator. (if you are running for the first time and haven't compiled).  
Run `./t1.sh` to only populate database and run the generator (for subsequent testing, if compilation has been completed).  
Note: These examples are fairly large, so it might take some time to generate the graphs. If you want to generate a smaller graph for testing instead, see [here](https://github.com/ferdinandmudjialim/ag-gen-guided#generating-dot-files-for-visualization)  

### Checking the Database
After running the generator, the database should be populated. Check this by connecting to it:
```sh
psql ag_gen
```
and check the database with normal SQL/PostgreSQL commands.  
If the database is populated with graph data, the tests were successful.  

### Running Manually (Example)
Execute an example from the examples directory.  
*Since the program should be located at* `build/ag_gen`, *run this from the* `build` *directory.*

```sh
cd build/
./ag_gen -n ../examples/thesis_example.nm -x ../examples/thesis_example.xp 24 96
```
Note: the 24 and 96 are the `thread_count` and `init_qsize` respectively. (Used for multiprocessing)

## Troubleshooting
### Duplicate Key Value
If you are getting:
```sh
Importing Models and Exploits into Database: Database Exception: ERROR:  duplicate key value violates unique constraint "asset_pkey"
DETAIL:  Key (id)=(0) already exists.

./t1.sh: line 5: 13780 Aborted                 ./ag_gen -n ../examples/1.nm -x ../examples/1.xp 24 96
```
Run the included `./clear_db.sh` script, then try again. 

## Graphviz
### Generating dot files for visualization
Note: For larger graphs (like the included thesis_example), the graph/image generation will take some time.  
You may want to instead use the smaller `cars3_rsh.nm` and `cars3_rsh.xp` located in the `examples` folder to test the GraphViz functionality.  
For convenience, the `./tcars.sh` script (in project main directory) should automatically generate a dot and png for the cars3_rsh example.  

For reference, this is how to generate dot files manually:  
Use the `-g <filename>` option in the command line to generate a dot file for GraphViz to read. 
Remember to run this from the `build` directory as `ag_gen` is located in `build/ag_gen`.
Example:
```sh
cd build/
./ag_gen -n ../examples/cars3_rsh.nm -x ../examples/cars3_rsh.xp -g ../graph.dot 24 96
```  

Then, `cd` back to the project main directory and generate a png from the generated dot file using the `dot` command:
```sh
cd ..
dot graph.dot -Tpng -o graph.png
```

Finally, you can make a script for your own custom nm/xp files to automate the graph generation process.  

## Contributing
### Editorconfig

When contributing code, please install the "editorconfig" plugin for your text editor.

- Adds extra newline to end of file if not already there.
- Removes whitespace at end of lines
- Automatically sets indentation to tabs set to 4 spaces
