#!/bin/sh
fd_lim_per_process=`ulimit -n`
fd_lim=`cat /proc/sys/fs/file-max`
proc_lim=`cat /proc/sys/kernel/pid_max`
thread_lim=`cat /proc/sys/kernel/threads-max`
while [ true ]
do
    fd_count=0
    proc_count=0
    thread_count=`ps -mH | wc -l`
    description=
    for procid in /proc/[0-9]*
    do
        count=`ls $procid/fd | wc -l`
        fd_count=`expr $count + $fd_count`
        proc_count=`expr 1 + $proc_count`
    done
    echo `date "+%Y/%m/%d %H:%M:%S"`,fds=$fd_count/$fd_lim,procs=$proc_count/$proc_lim,threads=$thread_count/$thread_lim
    sleep 1
done