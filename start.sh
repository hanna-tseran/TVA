NGXCFGFOLDER=$(pwd)
sudo nginx -c $(echo $NGXCFGFOLDER"/nginx.cfg")
sudo nginx -s reopen
g++ main.cpp tva.cpp -lfcgi++ -lfcgi -I$HOME/mongo-client-install/include -L$HOME/mongo-client-install/lib -lmongoclient -lboost_thread -lboost_system -lboost_regex -o videohandler
spawn-fcgi -p 8000 -n videohandler
