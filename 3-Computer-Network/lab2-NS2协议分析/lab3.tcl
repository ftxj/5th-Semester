# This script is created by ck

#===================================
#     Simulation parameters setup
#===================================
set val(stop)   10.0                         ;# time of simulation end

#===================================
#        Initialization        
#===================================
#Create a ns simulator
set ns [new Simulator]

#定义不同数据流的颜色
$ns color 0 black  ;#0为默认黑色 
$ns color 1 Blue  ;#1为蓝色 tcp
$ns color 2 Red  ;#2为红色 tahoe
$ns color 3 Yellow  ;#3为黄色 reno
$ns color 4 Pink  ;#4为粉色 newReno
$ns color 5 Purple  ;#4为紫色 vegas
$ns color 6 Orange  ;#4为橙色 sack
#Open the NS trace file
set tracefile [open out.tr w]
$ns trace-all $tracefile

##拥塞窗口文件#阈值窗口文件
set Cwinfile0 [open CwinFile0 w]
set winfile0 [open ThreshFile0 w]

set Cwinfile1 [open CwinFile1 w]
set winfile1 [open ThreshFile1 w]

set Cwinfile2 [open CwinFile2 w]
set winfile2 [open ThreshFile2 w]

set Cwinfile3 [open CwinFile3 w]
set winfile3 [open ThreshFile3 w]

set Cwinfile4 [open CwinFile4 w]
set winfile4 [open ThreshFile4 w]

set Cwinfile5 [open CwinFile5 w]
set winfile5 [open ThreshFile5 w]

#Open the NAM trace file
set namfile [open out.nam w]
$ns namtrace-all $namfile

#===================================
#        Nodes Definition        
#===================================
#Create 28 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
set n9 [$ns node]
set n10 [$ns node]
set n11 [$ns node]
set n12 [$ns node]
set n13 [$ns node]
set n14 [$ns node]
set n15 [$ns node]
set n16 [$ns node]
set n17 [$ns node]
set n18 [$ns node]
set n19 [$ns node]
set n20 [$ns node]
set n21 [$ns node]
set n22 [$ns node]
set n23 [$ns node]
set n24 [$ns node]
set n25 [$ns node]
set n26 [$ns node]
set n27 [$ns node]

#===================================
#        Links Definition        
#===================================
#Createlinks between nodes


$ns duplex-link $n3 $n6 100.0Mb 10ms DropTail
$ns queue-limit $n3 $n6 50


$ns duplex-link $n2 $n6 100.0Mb 10ms DropTail
$ns queue-limit $n2 $n6 50


$ns duplex-link $n4 $n6 100.0Mb 10ms DropTail
$ns queue-limit $n4 $n6 50


$ns duplex-link $n1 $n6 100.0Mb 10ms DropTail
$ns queue-limit $n1 $n6 50


$ns duplex-link $n5 $n6 100.0Mb 10ms DropTail
$ns queue-limit $n5 $n6 50


$ns duplex-link $n0 $n6 100.0Mb 10ms DropTail
$ns queue-limit $n0 $n6 50


$ns duplex-link $n15 $n14 100.0Mb 10ms DropTail
$ns queue-limit $n15 $n14 50


$ns duplex-link $n15 $n18 100.0Mb 10ms DropTail
$ns queue-limit $n15 $n18 50


$ns duplex-link $n15 $n17 100.0Mb 10ms DropTail
$ns queue-limit $n15 $n17 50


$ns duplex-link $n21 $n15 100.0Mb 10ms DropTail
$ns queue-limit $n21 $n15 50


$ns duplex-link $n15 $n19 100.0Mb 10ms DropTail
$ns queue-limit $n15 $n19 50


$ns duplex-link $n15 $n22 100.0Mb 10ms DropTail
$ns queue-limit $n15 $n22 50


$ns duplex-link $n15 $n20 100.0Mb 10ms DropTail
$ns queue-limit $n15 $n20 50


$ns duplex-link $n13 $n6 100.0Mb 10ms DropTail
$ns queue-limit $n13 $n6 50


$ns duplex-link $n7 $n8 100.0Mb 10ms DropTail
$ns queue-limit $n7 $n8 50


$ns duplex-link $n7 $n9 100.0Mb 10ms DropTail
$ns queue-limit $n7 $n9 50


$ns duplex-link $n7 $n10 100.0Mb 10ms DropTail
$ns queue-limit $n7 $n10 50


$ns duplex-link $n7 $n11 100.0Mb 10ms DropTail
$ns queue-limit $n7 $n11 50


$ns duplex-link $n7 $n12 100.0Mb 10ms DropTail
$ns queue-limit $n7 $n12 50


$ns duplex-link $n16 $n23 100.0Mb 10ms DropTail
$ns queue-limit $n16 $n23 50


$ns duplex-link $n16 $n25 100.0Mb 10ms DropTail
$ns queue-limit $n16 $n25 50


$ns duplex-link $n26 $n16 100.0Mb 10ms DropTail
$ns queue-limit $n26 $n16 50


$ns duplex-link $n16 $n24 100.0Mb 10ms DropTail
$ns queue-limit $n16 $n24 50


$ns duplex-link $n16 $n27 100.0Mb 10ms DropTail
$ns queue-limit $n16 $n27 50


$ns duplex-link $n16 $n14 100.0Mb 10ms DropTail
$ns queue-limit $n16 $n14 50


$ns duplex-link $n13 $n14 10.0Mb 10ms SFQ
$ns queue-limit $n13 $n14 16

	#Configuration for Queue
	set n13TOn14 [[$ns link $n13 $n14] queue]
	
	#Configuration for Queue
	set n14TOn13 [[$ns link $n14 $n13] queue]
	

$ns duplex-link $n7 $n13 8.0Mb 10ms DropTail
$ns queue-limit $n7 $n13 50

#Give node position (for NAM)
$ns duplex-link-op $n3 $n6 orient right-down
$ns duplex-link-op $n2 $n6 orient right-down
$ns duplex-link-op $n4 $n6 orient right-down
$ns duplex-link-op $n1 $n6 orient right-down
$ns duplex-link-op $n5 $n6 orient right-down
$ns duplex-link-op $n0 $n6 orient right-down
$ns duplex-link-op $n15 $n14 orient left-down
$ns duplex-link-op $n15 $n18 orient right-up
$ns duplex-link-op $n15 $n17 orient left-up
$ns duplex-link-op $n21 $n15 orient left-down
$ns duplex-link-op $n15 $n19 orient right-up
$ns duplex-link-op $n15 $n22 orient right-up
$ns duplex-link-op $n15 $n20 orient right
$ns duplex-link-op $n13 $n6 orient left-up
$ns duplex-link-op $n7 $n8 orient left

$ns duplex-link-op $n7 $n9 orient left-down
$ns duplex-link-op $n7 $n10 orient left-down
$ns duplex-link-op $n7 $n11 orient left-down
$ns duplex-link-op $n7 $n12 orient left-down
$ns duplex-link-op $n16 $n23 orient right-up
$ns duplex-link-op $n16 $n25 orient right-up
$ns duplex-link-op $n26 $n16 orient left-up
$ns duplex-link-op $n16 $n24 orient right-down
$ns duplex-link-op $n16 $n27 orient right-down
$ns duplex-link-op $n16 $n14 orient left-up
$ns duplex-link-op $n13 $n14 orient right
$ns duplex-link-op $n7 $n13 orient right-up

#===================================
#        Agents Definition        
#===================================
#Setup a TCP connection
set tcp0 [new Agent/TCP]
$ns attach-agent $n3 $tcp0
set sink11 [new Agent/TCPSink]
$ns attach-agent $n17 $sink11
$ns connect $tcp0 $sink11
	$tcp0 set packetSize_ 1500.0
	$tcp0 set fid_ 0
	$sink11 set packetSize_ 1500.0

#Setup a TCP connection
set tcp1 [new Agent/TCP]
$ns attach-agent $n4 $tcp1
set sink12 [new Agent/TCPSink]
$ns attach-agent $n18 $sink12
$ns connect $tcp1 $sink12
	$tcp1 set packetSize_ 1500.0
	$tcp1 set fid_ 0
	$sink12 set packetSize_ 1500.0

#Setup a TCP connection
set tcp2 [new Agent/TCP]
$ns attach-agent $n2 $tcp2
set sink14 [new Agent/TCPSink]
$ns attach-agent $n22 $sink14
$ns connect $tcp2 $sink14
	$tcp2 set packetSize_ 1500.0
	$tcp2 set fid_ 0
	$sink14 set packetSize_ 1500.0

#Setup a TCP connection
set tcp3 [new Agent/TCP]
$ns attach-agent $n5 $tcp3
set sink13 [new Agent/TCPSink]
$ns attach-agent $n21 $sink13
$ns connect $tcp3 $sink13
	$tcp3 set packetSize_ 1500.0
	$tcp3 set fid_ 0
	$sink13 set packetSize_ 1500.0

#Setup a TCP connection
set tcp4 [new Agent/TCP]
$ns attach-agent $n1 $tcp4
set sink15 [new Agent/TCPSink]
$ns attach-agent $n19 $sink15
$ns connect $tcp4 $sink15
	$tcp4 set packetSize_ 1500.0
	$tcp4 set fid_ 0
	$sink15 set packetSize_ 1500.0

#Setup a TCP connection
set tcp5 [new Agent/TCP]
$ns attach-agent $n0 $tcp5
set sink16 [new Agent/TCPSink]
$ns attach-agent $n20 $sink16
$ns connect $tcp5 $sink16
	$tcp5 set packetSize_ 1500.0
	$tcp5 set fid_ 0
	$sink16 set packetSize_ 1500.0

#Setup a UDP connection
set udp6 [new Agent/UDP]
$ns attach-agent $n8 $udp6
set null17 [new Agent/Null]
$ns attach-agent $n23 $null17
$ns connect $udp6 $null17
	$udp6 set packetSize_ 1500.0

#Setup a UDP connection
set udp7 [new Agent/UDP]
$ns attach-agent $n10 $udp7
set null18 [new Agent/Null]
$ns attach-agent $n25 $null18
$ns connect $udp7 $null18
	$udp7 set packetSize_ 1500.0

#Setup a UDP connection
set udp8 [new Agent/UDP]
$ns attach-agent $n11 $udp8
set null19 [new Agent/Null]
$ns attach-agent $n26 $null19
$ns connect $udp8 $null19
	$udp8 set packetSize_ 1500.0

#Setup a UDP connection
set udp9 [new Agent/UDP]
$ns attach-agent $n9 $udp9
set null21 [new Agent/Null]
$ns attach-agent $n24 $null21
$ns connect $udp9 $null21
	$udp9 set packetSize_ 1500.0

#Setup a UDP connection
set udp10 [new Agent/UDP]
$ns attach-agent $n12 $udp10
set null20 [new Agent/Null]
$ns attach-agent $n27 $null20
$ns connect $udp10 $null20
	$udp10 set packetSize_ 1500.0


#===================================
#        Applications Definition        
#===================================
#Setup a FTP Application over TCP connection
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ns at 1.0 "$ftp0 start"
$ns at 10.0 "$ftp0 stop"

#Setup a FTP Application over TCP connection
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ns at 1.0 "$ftp1 start"
$ns at 10.0 "$ftp1 stop"

#Setup a FTP Application over TCP connection
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ns at 1.0 "$ftp2 start"
$ns at 10.0 "$ftp2 stop"

#Setup a FTP Application over TCP connection
set ftp3 [new Application/FTP]
$ftp3 attach-agent $tcp3
$ns at 1.0 "$ftp3 start"
$ns at 10.0 "$ftp3 stop"

#Setup a FTP Application over TCP connection
set ftp4 [new Application/FTP]
$ftp4 attach-agent $tcp4
$ns at 1.0 "$ftp4 start"
$ns at 10.0 "$ftp4 stop"

#Setup a FTP Application over TCP connection
set ftp5 [new Application/FTP]
$ftp5 attach-agent $tcp5
$ns at 1.0 "$ftp5 start"
$ns at 10.0 "$ftp5 stop"

#Setup a CBR Application over UDP connection
set cbr6 [new Application/Traffic/CBR]
$cbr6 attach-agent $udp6
	$cbr6 set packetSize_ 1000
	$cbr6 set rate_ 10.0Mb
	$cbr6 set interval_ 0.005
	$cbr6 set maxpkts_ 10000.0
	$cbr6 set random_ false
$ns at 5.0 "$cbr6 start"
$ns at 10.0 "$cbr6 stop"

#Setup a CBR Application over UDP connection
set cbr7 [new Application/Traffic/CBR]
$cbr7 attach-agent $udp7
	$cbr7 set packetSize_ 1000
	$cbr7 set rate_ 10.0Mb
	$cbr7 set interval_ 0.005
	$cbr7 set maxpkts_ 10000.0
	$cbr7 set random_ false
$ns at 5.0 "$cbr7 start"
$ns at 10.0 "$cbr7 stop"

#Setup a CBR Application over UDP connection
set cbr8 [new Application/Traffic/CBR]
$cbr8 attach-agent $udp8
	$cbr8 set packetSize_ 1000
	$cbr8 set rate_ 10.0Mb
	$cbr8 set interval_ 0.005
	$cbr8 set maxpkts_ 10000.0
	$cbr8 set random_ false
$ns at 5.0 "$cbr8 start"
$ns at 10.0 "$cbr8 stop"

#Setup a CBR Application over UDP connection
set cbr9 [new Application/Traffic/CBR]
$cbr9 attach-agent $udp9
	$cbr9 set packetSize_ 1000
	$cbr9 set rate_ 10.0Mb
	$cbr9 set interval_ 0.005
	$cbr9 set maxpkts_ 10000.0
	$cbr9 set random_ false
$ns at 5.0 "$cbr9 start"
$ns at 10.0 "$cbr9 stop"

#Setup a CBR Application over UDP connection
set cbr10 [new Application/Traffic/CBR]
$cbr10 attach-agent $udp10
	$cbr10 set packetSize_ 1000
	$cbr10 set rate_ 10.0Mb
	$cbr10 set interval_ 0.005
	$cbr10 set maxpkts_ 10000.0
	$cbr10 set random_ false
$ns at 5.0 "$cbr10 start"
$ns at 10.0 "$cbr10 stop"


#===================================
#        Termination        
#===================================
#Define a 'finish' procedure
proc finish {} {
    global ns tracefile namfile
    $ns flush-trace
    close $tracefile
    close $namfile
    exec nam out.nam &
    exit 0
}

#===================================
#        create congestion window        
#===================================
proc plotWindow {tcpSource file_Cwnd file_wnd} {
    global ns
#设置抽样距离，每过0.1s后再调用自己
    set time 0.1
    set now [$ns now]
#拥塞窗口
    set cwnd [$tcpSource set cwnd_]
#通告窗口
    set wnd [$tcpSource set ssthresh_]
#把当前时间数据和cwnd的数据记录到file_Cwnd所指向的文件中
    puts $file_Cwnd "$now $cwnd"
#把当前时间数据和wnd的数据记录到file_wnd所指向的文件中
    puts $file_wnd "$now $wnd"
#这是一个递归过程，在过了0.1秒后继续调用本函数，并记录时间数据和cwnd数据
    $ns at [expr $now+$time] "plotWindow $tcpSource $file_Cwnd $file_wnd"
}
#===================================
#调用函数捕获tcp0的窗口数据
$ns at 0.1 "plotWindow $tcp0 $Cwinfile0 $winfile0"
$ns at 0.1 "plotWindow $tcp1 $Cwinfile1 $winfile1"
$ns at 0.1 "plotWindow $tcp2 $Cwinfile2 $winfile2"
$ns at 0.1 "plotWindow $tcp3 $Cwinfile3 $winfile3"
$ns at 0.1 "plotWindow $tcp4 $Cwinfile4 $winfile4"
$ns at 0.1 "plotWindow $tcp5 $Cwinfile5 $winfile5"
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "finish"
$ns at $val(stop) "puts \"done\" ; $ns halt"
$ns run
