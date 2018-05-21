#!/bin/sh
echo "Welcome to use Peanut backend!"
echo "Any problem visit http://codeyourlife.cn"

# cfg
PNAME=Peanut
STATIC=blog_cyl
CFG_FILE=Peanut.cfg
INDEX_PAGE=${STATIC}/index.html

#check necessary file
echo "Check necessary file."
if [ ! -x "${PNAME}" ]; then
    echo "Can not find ${PNAME}"
    exit 1
fi
if [ ! -d "${STATIC}" ]; then
    echo "Can not find ${STATIC} dir"
    exit 1
fi
if [ ! -f "${CFG_FILE}" ]; then
    echo "Can not find ${CFG_FILE}"
    exit 1
fi
if [ ! -f "${INDEX_PAGE}" ]; then
    echo "Can not find ${INDEX_PAGE}"
    exit 1
fi

#Start or End
if [ "$1" == "cstart" ]; then
    cmake -Drelease=1 ./
    make
    ./${PNAME} >& ${PNAME}.log &
    echo "Peanut backend start finished."
elif [ "$1" == "start" ]; then
    ./${PNAME} >& ${PNAME}.log &
    echo "Peanut backend start finished."
elif [ "$1" == "end" ]; then
    ps -ef | grep ${PNAME} | grep -v grep | awk '{print $2}' | xargs kill -9 
    echo "Peanut backend shutdown finished."
else
    echo "parameter error! we need start or end as paramater"
fi