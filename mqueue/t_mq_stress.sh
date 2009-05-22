#!/bin/sh
cnt=0
while [ $cnt -lt 100000 ];
do
    ./t_mq_open
    let cnt=cnt+1
done
