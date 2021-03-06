# This script is created by ck

#===================================
#     Simulation parameters setup
#===================================
set val(stop)   12.0                         ;# time of simulation end

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
set tracefile [open TcpUdp.tr w]
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
set namfile [open TcpUdp.nam w]
$ns namtrace-all $namfile

#===================================
#        Nodes Definition        
#===================================
#Create 29 nodes
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
set n28 [$ns node]

#===================================
#        Links Definition        
#===================================
#Createlinks between nodes


$ns duplex-link $n11 $n4 10.0Mb 1ms DropTail
$ns queue-limit $n11 $n4 16


$ns duplex-link $n10 $n4 10.0Mb 1ms DropTail
$ns queue-limit $n10 $n4 16


$ns duplex-link $n9 $n4 10.0Mb 1ms DropTail
$ns queue-limit $n9 $n4 16


$ns duplex-link $n8 $n4 10.0Mb 1ms DropTail
$ns queue-limit $n8 $n4 16


$ns duplex-link $n7 $n4 10.0Mb 1ms DropTail
$ns queue-limit $n7 $n4 16


$ns duplex-link $n6 $n4 10.0Mb 1ms DropTail
$ns queue-limit $n6 $n4 16


$ns duplex-link $n18 $n5 10.0Mb 1ms DropTail
$ns queue-limit $n18 $n5 16


$ns duplex-link $n19 $n5 10.0Mb 1ms DropTail
$ns queue-limit $n19 $n5 16


$ns duplex-link $n20 $n5 10.0Mb 1ms DropTail
$ns queue-limit $n20 $n5 16


$ns duplex-link $n21 $n5 10.0Mb 1ms DropTail
$ns queue-limit $n21 $n5 16


$ns duplex-link $n22 $n5 10.0Mb 1ms DropTail
$ns queue-limit $n22 $n5 16


$ns duplex-link $n2 $n12 1.5Mb 1ms DropTail
$ns queue-limit $n2 $n12 16


$ns duplex-link $n2 $n13 1.5Mb 1ms DropTail
$ns queue-limit $n2 $n13 16


$ns duplex-link $n2 $n14 1.5Mb 1ms DropTail
$ns queue-limit $n2 $n14 16


$ns duplex-link $n2 $n15 1.5Mb 1ms DropTail
$ns queue-limit $n2 $n15 16


$ns duplex-link $n2 $n16 1.5Mb 1ms DropTail
$ns queue-limit $n2 $n16 16


$ns duplex-link $n2 $n17 1.5Mb 1ms DropTail
$ns queue-limit $n2 $n17 16


$ns duplex-link $n3 $n27 1.5Mb 1ms DropTail
$ns queue-limit $n3 $n27 16


$ns duplex-link $n3 $n26 1.5Mb 1ms DropTail
$ns queue-limit $n3 $n26 16


$ns duplex-link $n3 $n25 1.5Mb 1ms DropTail
$ns queue-limit $n3 $n25 16


$ns duplex-link $n3 $n24 1.5Mb 1ms DropTail
$ns queue-limit $n3 $n24 16


$ns duplex-link $n3 $n23 1.5Mb 1ms DropTail
$ns queue-limit $n3 $n23 16


$ns duplex-link $n4 $n0 30.0Mb 1ms DropTail
$ns queue-limit $n4 $n0 30


$ns duplex-link $n5 $n0 30.0Mb 1ms DropTail
$ns queue-limit $n5 $n0 30


$ns duplex-link $n0 $n1 9.0Mb 1ms DropTail
$ns queue-limit $n0 $n1 50


$ns duplex-link $n1 $n2 8.0Mb 1ms DropTail
$ns queue-limit $n1 $n2 30


$ns duplex-link $n1 $n3 8.0Mb 1ms DropTail
$ns queue-limit $n1 $n3 30

#Give node position (for NAM)
$ns duplex-link-op $n11 $n4 orient left-down
$ns duplex-link-op $n10 $n4 orient right-down
$ns duplex-link-op $n9 $n4 orient right-down
$ns duplex-link-op $n8 $n4 orient right-down
$ns duplex-link-op $n7 $n4 orient right-down
$ns duplex-link-op $n6 $n4 orient right
$ns duplex-link-op $n18 $n5 orient right
$ns duplex-link-op $n19 $n5 orient right
$ns duplex-link-op $n20 $n5 orient right-up
$ns duplex-link-op $n21 $n5 orient right-up
$ns duplex-link-op $n22 $n5 orient right-up
$ns duplex-link-op $n2 $n12 orient right-up
$ns duplex-link-op $n2 $n13 orient right-up
$ns duplex-link-op $n2 $n14 orient right-up
$ns duplex-link-op $n2 $n15 orient right-up
$ns duplex-link-op $n2 $n16 orient right
$ns duplex-link-op $n2 $n17 orient right-down
$ns duplex-link-op $n3 $n27 orient right
$ns duplex-link-op $n3 $n26 orient right-down
$ns duplex-link-op $n3 $n25 orient right-down
$ns duplex-link-op $n3 $n24 orient right-down
$ns duplex-link-op $n3 $n23 orient left-down
$ns duplex-link-op $n4 $n0 orient right-down
$ns duplex-link-op $n5 $n0 orient right-up
$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n1 $n3 orient right-down

#===================================
#        Agents Definition        
#===================================
#Setup a TCP connection
set tcp0 [new Agent/TCP]
$ns attach-agent $n11 $tcp0
set sink11 [new Agent/TCPSink]
$ns attach-agent $n12 $sink11
$ns connect $tcp0 $sink11
	$tcp0 set packetSize_ 1500.0
	$tcp0 set fid_ 0
	$sink11 set packetSize_ 1500.0

#Setup a TCP connection
set tcp1 [new Agent/TCP]
$ns attach-agent $n10 $tcp1
set sink12 [new Agent/TCPSink]
$ns attach-agent $n13 $sink12
$ns connect $tcp1 $sink12
	$tcp1 set packetSize_ 1500.0
	$tcp1 set fid_ 0
	$sink12 set packetSize_ 1500.0

#Setup a TCP connection
set tcp2 [new Agent/TCP]
$ns attach-agent $n9 $tcp2
set sink13 [new Agent/TCPSink]
$ns attach-agent $n14 $sink13
$ns connect $tcp2 $sink13
	$tcp2 set packetSize_ 1500.0
	$tcp2 set fid_ 0
	$sink13 set packetSize_ 1500.0

#Setup a TCP connection
set tcp3 [new Agent/TCP]
$ns attach-agent $n8 $tcp3
set sink14 [new Agent/TCPSink]
$ns attach-agent $n15 $sink14
$ns connect $tcp3 $sink14
	$tcp3 set packetSize_ 1500.0
	$tcp3 set fid_ 0
	$sink14 set packetSize_ 1500.0

#Setup a TCP connection
set tcp4 [new Agent/TCP]
$ns attach-agent $n7 $tcp4
set sink15 [new Agent/TCPSink]
$ns attach-agent $n16 $sink15
$ns connect $tcp4 $sink15
	$tcp4 set packetSize_ 1500.0
	$tcp4 set fid_ 0
	$sink15 set packetSize_ 1500.0

#Setup a TCP connection
set tcp5 [new Agent/TCP]
$ns attach-agent $n6 $tcp5
set sink16 [new Agent/TCPSink]
$ns attach-agent $n17 $sink16
$ns connect $tcp5 $sink16
	$tcp5 set packetSize_ 1500.0
	$tcp5 set fid_ 0
	$sink16 set packetSize_ 1500.0

#Setup a UDP connection
set udp6 [new Agent/UDP]
$ns attach-agent $n18 $udp6
set null17 [new Agent/Null]
$ns attach-agent $n27 $null17
$ns connect $udp6 $null17
	$udp6 set packetSize_ 1500.0

#Setup a UDP connection
set udp7 [new Agent/UDP]
$ns attach-agent $n19 $udp7
set null18 [new Agent/Null]
$ns attach-agent $n26 $null18
$ns connect $udp7 $null18
	$udp7 set packetSize_ 1500.0

#Setup a UDP connection
set udp8 [new Agent/UDP]
$ns attach-agent $n20 $udp8
set null19 [new Agent/Null]
$ns attach-agent $n25 $null19
$ns connect $udp8 $null19
	$udp8 set packetSize_ 1500.0

#Setup a UDP connection
set udp9 [new Agent/UDP]
$ns attach-agent $n21 $udp9
set null20 [new Agent/Null]
$ns attach-agent $n24 $null20
$ns connect $udp9 $null20
	$udp9 set packetSize_ 1500.0

#Setup a UDP connection
set udp10 [new Agent/UDP]
$ns attach-agent $n22 $udp10
set null21 [new Agent/Null]
$ns attach-agent $n23 $null21
$ns connect $udp10 $null21
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
set cbr11 [new Application/Traffic/CBR]
$cbr11 attach-agent $udp6
	$cbr11 set packetSize_ 1500
	$cbr11 set rate_ 2.0Mb
	$cbr11 set interval_ 0.005
	$cbr11 set maxpkts_ 1000.0
	$cbr11 set random_ false
$ns at 5.0 "$cbr11 start"
$ns at 10.0 "$cbr11 stop"

#Setup a CBR Application over UDP connection
set cbr12 [new Application/Traffic/CBR]
$cbr12 attach-agent $udp7
	$cbr12 set packetSize_ 1500
	$cbr12 set rate_ 2.0Mb
	$cbr12 set interval_ 0.005
	$cbr12 set maxpkts_ 1000.0
	$cbr12 set random_ false
$ns at 5.0 "$cbr12 start"
$ns at 10.0 "$cbr12 stop"

#Setup a CBR Application over UDP connection
set cbr13 [new Application/Traffic/CBR]
$cbr13 attach-agent $udp8
	$cbr13 set packetSize_ 1500
	$cbr13 set rate_ 2.0Mb
	$cbr13 set interval_ 0.005
	$cbr13 set maxpkts_ 1000.0
	$cbr13 set random_ false
$ns at 5.0 "$cbr13 start"
$ns at 10.0 "$cbr13 stop"

#Setup a CBR Application over UDP connection
set cbr14 [new Application/Traffic/CBR]
$cbr14 attach-agent $udp9
	$cbr14 set packetSize_ 1500
	$cbr14 set rate_ 1.0Mb
	$cbr14 set interval_ 0.005
	$cbr14 set maxpkts_ 1000.0
	$cbr14 set random_ false
$ns at 5.0 "$cbr14 start"
$ns at 10.0 "$cbr14 stop"

#Setup a CBR Application over UDP connection
set cbr15 [new Application/Traffic/CBR]
$cbr15 attach-agent $udp10
	$cbr15 set packetSize_ 1500
	$cbr15 set rate_ 1.0Mb
	$cbr15 set interval_ 0.005
	$cbr15 set maxpkts_ 1000.0
	$cbr15 set random_ false
$ns at 5.0 "$cbr15 start"
$ns at 10.0 "$cbr15 stop"


#===================================
#        Termination        
#===================================
#Define a 'finish' procedure
proc finish {} {
    global ns tracefile namfile
    $ns flush-trace
    close $tracefile
    close $namfile
    exec nam TcpUdp.nam &
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
