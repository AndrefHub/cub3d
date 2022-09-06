#!/bin/bash

ASSETS_LINK='https://drive.google.com/file/d/1LN2mkGPS0Jez69ijpsC_n7bsKnlIN_l_/view?usp=sharing'
GOINFRE=~/goinfre

if [ ! -f ${GOINFRE}/assets ]
    then
        ./gdrive_download.py ${ASSETS_LINK} ${GOINFRE}/assets.zip
        unzip ${GOINFRE}/assets.zip
else
    echo "assets or assets.zip (or even both!) already exists. Delete them?"
fi 