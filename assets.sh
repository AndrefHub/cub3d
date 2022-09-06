#!/bin/bash

ASSETS_LINK='https://drive.google.com/u/0/uc?id=1LN2mkGPS0Jez69ijpsC_n7bsKnlIN_l_&amp;export=download&amp;confirm=t&amp;uuid=0b510e91-6ef2-4b65-b99b-6dc131cd1590'
GOINFRE=~/goinfre

if [ ! -f ${GOINFRE}/assets ]
    then
        ./gdrive_download.py ${ASSETS_LINK} ${GOINFRE}/assets.zip
        unzip ${GOINFRE}/assets.zip
else
    echo "assets or assets.zip (or even both!) already exists. Delete them?"
fi 