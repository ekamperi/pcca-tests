#!/bin/sh
#
# Given that the following tests excercise heavily the various code paths,
# there is a high chance that we catch a resource leak by hitting a system-wide
# limit.
#
cnt=0
while [ $cnt -lt 100000 ];
do
    ./t_mq_ambig
    ./t_mq_close
    ./t_mq_open
    ./t_mq_open_close
    ./t_mq_open_umask
    ./t_mq_parent_child
    ./t_mq_parent_child_multmsg
    ./t_mq_send
    ./t_mq_setattr
    cnt=$((cnt+1))
done
