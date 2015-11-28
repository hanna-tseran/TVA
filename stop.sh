sudo kill $(ps aux | grep '[n]ginx' | awk '{print $2}')
sudo nginx -s stop
