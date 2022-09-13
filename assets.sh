#!/bin/bash

yaDiskLink='https://cloud-api.yandex.net/v1/disk/public/resources/download?public_key='
assetsLink='https://disk.yandex.ru/d/mAoZ9b8dmaQWXA'
OAuthToken='y0_AgAAAAAUbd_zAADLWwAAAADOJupZ3JK4Uy0eQkmrkkhi0tAWU-lHwT4'
goinfre=$1

if [ ! -d $goinfre ]
    then
        goinfre="."
fi

folderPath="$goinfre"/assets
savePath="$folderPath".zip

if [ ! -d $folderPath ]
    then
        downloadLink=$(curl -s "$yaDiskLink""$assetsLink" | cut -d'"' -f4)
        curl -H "Authorization: OAuth $OAuthToken" -L "$downloadLink" -o "$savePath"
        unzip "$savePath" -d "$goinfre"
        echo "Assets saved to $savePath!"
else
    echo "assets or assets.zip (or even both!) already exists"
fi 
