cmd_kernel/built-in.o :=  arm-none-linux-gnueabi-ld -EL    -r -o kernel/built-in.o kernel/fork.o kernel/exec_domain.o kernel/panic.o kernel/printk.o kernel/cpu.o kernel/exit.o kernel/itimer.o kernel/time.o kernel/softirq.o kernel/resource.o kernel/sysctl.o kernel/sysctl_binary.o kernel/capability.o kernel/ptrace.o kernel/timer.o kernel/user.o kernel/signal.o kernel/sys.o kernel/kmod.o kernel/workqueue.o kernel/pid.o kernel/task_work.o kernel/rcupdate.o kernel/extable.o kernel/params.o kernel/posix-timers.o kernel/kthread.o kernel/wait.o kernel/sys_ni.o kernel/posix-cpu-timers.o kernel/mutex.o kernel/hrtimer.o kernel/rwsem.o kernel/nsproxy.o kernel/srcu.o kernel/semaphore.o kernel/notifier.o kernel/ksysfs.o kernel/cred.o kernel/async.o kernel/range.o kernel/groups.o kernel/lglock.o kernel/smpboot.o kernel/sched/built-in.o kernel/power/built-in.o kernel/cpu/built-in.o kernel/freezer.o kernel/stacktrace.o kernel/time/built-in.o kernel/futex.o kernel/rtmutex.o kernel/smp.o kernel/spinlock.o kernel/uid16.o kernel/module.o kernel/kallsyms.o kernel/cgroup.o kernel/stop_machine.o kernel/kprobes.o kernel/irq/built-in.o kernel/rcutree.o kernel/relay.o kernel/utsname_sysctl.o kernel/elfcore.o kernel/irq_work.o kernel/cpu_pm.o kernel/events/built-in.o kernel/jump_label.o 
