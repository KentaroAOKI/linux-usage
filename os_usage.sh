#!/bin/sh
echo date,fd,fd_lim,proc,proc_lim,thread,thread_lim
while [ true ]
do
    fd_lim_per_process=`ulimit -n`
    fd_lim=`cat /proc/sys/fs/file-max`
    proc_lim=`cat /proc/sys/kernel/pid_max`
    thread_lim=`cat /proc/sys/kernel/threads-max`
    fd_count=0
    proc_count=0
    thread_count=`ps -mH | wc -l`
    for procid in /proc/[0-9]*
    do
        count=`ls $procid/fd | wc -l`
        fd_count=`expr $count + $fd_count`
        proc_count=`expr 1 + $proc_count`
        proc_name=`cat $procid/status|grep ^Name|sed -e "s/Name:\t//g"`
    done
    echo `date "+%Y/%m/%d %H:%M:%S"`,$fd_count,$fd_lim,$proc_count,$proc_lim,$thread_count,$thread_lim
    sleep 1
done
