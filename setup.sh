#!/bin/bash
mkdir .temp
cd .temp
git clone https://github.com/Tencent/rapidjson.git
cd rapidjson/include
cp -r rapidjson /usr/local/include/
cp -r rapidjson /usr/include/
cd ../../..
rm -r .temp

echo 'installed rapidjason library'