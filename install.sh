#! /bin/sh

echo -e "\nCompiling...\n"
make
echo -e "\nCreating wrapper script...\n"
echo -e "#! /bin/sh\n#This is a wrapper to change the working directory to this folder (where there is internet.jpg)\n(cd `pwd`/; ./bin/lightwebsearch )" > lightwebsearch
chmod +x lightwebsearch
echo -e "\nInstalling into /usr/bin/\n"
sudo ln -s `pwd`/lightwebsearch /usr/bin/
echo -e "\nComplete!\n"
