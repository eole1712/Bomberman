#!/bin/bash

# generateBuff
# generate buffs from a base file
# filenames, class names and headers file inclusion are replaced
# be careful with methods actions /!\

baseFile="BuffIncSpeed"
baseClass="IncSpeed"

if [ $# -lt 1 ]
then
    echo "Usage: $0 NAME"
    exit 0
fi

cp "$baseFile.cpp" "Buff$1.cpp"
cp "$baseFile.hpp" "Buff$1.hpp"

sed -i s/"IncSpeed"/"$1"/g "Buff$1.cpp"
sed -i s/"IncSpeed"/"$1"/g "Buff$1.hpp"

sed -i s/"INCSPEED"/$(echo $1 | tr 'a-z' 'A-Z')/g "Buff$1.hpp"