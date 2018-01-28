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


$ns duplex-link $n5 $n0 30.0Mb 1ms DropTail
$ns queue-limit $n5 $n0 30


$ns duplex-link $n1 $n3 8.0Mb 1ms DropTail
$ns queue-limit $n1 $n3 30
#
#Error Model for Link from $n1to $n3 
#
set em_n1ton3 [new ErrorModel]
$em_n1ton3 unit Pkt
$em_n1ton3 set rate_ 0.05
$em_n1ton3 ranvar [new RandomVariable/Uniform]
$em_n1ton3 drop-target [new Agent/Null]
$ns lossmodel $em_n1ton3 $n1 $n3



$ns duplex-link $n11 $n4 100.0Mb 10ms DropTail
$ns queue-limit $n11 $n4 50


$ns duplex-link $n10 $n4 100.0Mb 10ms DropTail
$ns queue-limit $n10 $n4 50


$ns duplex-link $n9 $n4 100.0Mb 10ms DropTail
$ns queue-limit $n9 $n4 50


$ns duplex-link $n8 $n4 100.0Mb 10ms DropTail
$ns queue-limit $n8 $n4 50


$ns duplex-link $n4 $n7 100.0Mb 10ms DropTail
$ns queue-limit $n4 $n7 50


$ns duplex-link $n6 $n4 100.0Mb 10ms DropTail
$ns queue-limit $n6 $n4 50


$ns duplex-link $n2 $n12 100.0Mb 10ms DropTail
$ns queue-limit $n2 $n12 50


$ns duplex-link $n2 $n13 100.0Mb 10ms DropTail
$ns queue-limit $n2 $n13 50


$ns duplex-link $n2 $n14 100.0Mb 10ms DropTail
$ns queue-limit $n2 $n14 50


$ns duplex-link $n2 $n15 100.0Mb 10ms DropTail
$ns queue-limit $n2 $n15 50


$ns duplex-link $n2 $n16 100.0Mb 10ms DropTail
$ns queue-limit $n2 $n16 50


$ns duplex-link $n2 $n17 100.0Mb 10ms DropTail
$ns queue-limit $n2 $n17 50


$ns duplex-link $n4 $n0 100.0Mb 10ms DropTail
$ns queue-limit $n4 $n0 50


$ns duplex-link $n1 $n2 100.0Mb 10ms DropTail
$ns queue-limit $n1 $n2 50


$ns duplex-link $n0 $n1 10.0Mb 10ms DropTail
$ns queue-limit $n0 $n1 30
#
#Error Model for Link from $n0to $n1 
#
set em_n0ton1 [new ErrorModel]
$em_n0ton1 unit Pkt
$em_n0ton1 set rate_ 0.01
$em_n0ton1 ranvar [new RandomVariable/Uniform]
$em_n0ton1 drop-target [new Agent/Null]
$ns lossmodel $em_n0ton1 $n0 $n1


#Give node position (for NAM)
$ns duplex-link-op $n18 $n5 orient right
$ns duplex-link-op $n19 $n5 orient right
$ns duplex-link-op $n20 $n5 orient right-up
$ns duplex-link-op $n21 $n5 orient right-up
$ns duplex-link-op $n22 $n5 orient right-up
$ns duplex-link-op $n3 $n27 orient right
$ns duplex-link-op $n3 $n26 orient right-down
$ns duplex-link-op $n3 $n25 orient right-down
$ns duplex-link-op $n3 $n24 orient right-down
$ns duplex-link-op $n3 $n23 orient left-down
$ns duplex-link-op $n5 $n0 orient right-up
$ns duplex-link-op $n1 $n3 orient right-down
$ns duplex-link-op $n11 $n4 orient left-down
$ns duplex-link-op $n10 $n4 orient right-down
$ns duplex-link-op $n9 $n4 orient right-down
$ns duplex-link-op $n8 $n4 orient right-down
$ns duplex-link-op $n4 $n7 orient left-up
$ns duplex-link-op $n6 $n4 orient right-down
$ns duplex-link-op $n2 $n12 orient right-up
$ns duplex-link-op $n2 $n13 orient right-up
$ns duplex-link-op $n2 $n14 orient right-up
$ns duplex-link-op $n2 $n15 orient right-up
$ns duplex-link-op $n2 $n16 orient right
$ns duplex-link-op $n2 $n17 orient right-down
$ns duplex-link-op $n4 $n0 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n0 $n1 orient right

#===================================
#        Agents Definition        
#===================================
#Setup a TCP connection
set tahoe0 [new Agent/TCP]
$ns attach-agent $n11 $tahoe0
set sink6 [new Agent/TCPSink]
$ns attach-agent $n12 $sink6
$ns connect $tahoe0 $sink6
	$tahoe0 set packetSize_ 1500.0
	$tahoe0 set fid_ 1
	$sink6 set packetSize_ 1500.0

#Setup a TCP/Reno connection
set reno1 [new Agent/TCP/Reno]
$ns attach-agent $n10 $reno1
set sink7 [new Agent/TCPSink]
$ns attach-agent $n13 $sink7
$ns connect $reno1 $sink7
	$reno1 set packetSize_ 1500.0
	$reno1 set fid_ 2
	$sink7 set packetSize_ 1500.0

#Setup a TCP/Newreno connection
set newReno2 [new Agent/TCP/Newreno]
$ns attach-agent $n9 $newReno2
set sink8 [new Agent/TCPSink]
$ns attach-agent $n14 $sink8
$ns connect $newReno2 $sink8
	$newReno2 set packetSize_ 1500.0
	$newReno2 set fid_ 3
	$sink8 set packetSize_ 1500.0

#Setup a TCP/Vegas connection
set vegas3 [new Agent/TCP/Vegas]
$ns attach-agent $n8 $vegas3
set sink9 [new Agent/TCPSink]
$ns attach-agent $n15 $sink9
$ns connect $vegas3 $sink9
	$vegas3 set packetSize_ 1500.0
	$vegas3 set fid_ 4
	$sink9 set packetSize_ 1500.0

#Setup a TCP/Sack1 connection
set sack4 [new Agent/TCP/Sack1]
$ns attach-agent $n7 $sack4
set sink10 [new Agent/TCPSink]
$ns attach-agent $n16 $sink10
$ns connect $sack4 $sink10
	$sack4 set packetSize_ 1500.0
	$sack4 set fid_ 5
	$sink10 set packetSize_ 1500.0

#Setup a TCP/Fack connection
set fack5 [new Agent/TCP/Fack]
$ns attach-agent $n6 $fack5
set sink11 [new Agent/TCPSink]
$ns attach-agent $n17 $sink11
$ns connect $fack5 $sink11
	$fack5 set packetSize_ 1500.0
	$fack5 set fid_ 6
	$sink11 set packetSize_ 1500.0

#Setup a UDP connection
set udp12 [new Agent/UDP]
$ns attach-agent $n18 $udp12
set null17 [new Agent/Null]
$ns attach-agent $n27 $null17
$ns connect $udp12 $null17
	$udp12 set packetSize_ 1500.0

#Setup a UDP connection
set udp13 [new Agent/UDP]
$ns attach-agent $n19 $udp13
set null18 [new Agent/Null]
$ns attach-agent $n26 $null18
$ns connect $udp13 $null18
	$udp13 set packetSize_ 1500.0

#Setup a UDP connection
set udp14 [new Agent/UDP]
$ns attach-agent $n20 $udp14
set null19 [new Agent/Null]
$ns attach-agent $n25 $null19
$ns connect $udp14 $null19
	$udp14 set packetSize_ 1500.0

#Setup a UDP connection
set udp15 [new Agent/UDP]
$ns attach-agent $n21 $udp15
set null20 [new Agent/Null]
$ns attach-agent $n24 $null20
$ns connect $udp15 $null20
	$udp15 set packetSize_ 1500.0

#Setup a UDP connection
set udp16 [new Agent/UDP]
$ns attach-agent $n22 $udp16
set null21 [new Agent/Null]
$ns attach-agent $n23 $null21
$ns connect $udp16 $null21
	$udp16 set packetSize_ 1500.0


#===================================
#        Applications Definition        
#===================================
#Setup a FTP Application over TCP connection
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tahoe0
$ns at 1.0 "$ftp0 start"
$ns at 10.0 "$ftp0 stop"

#Setup a FTP Application over TCP/Reno connection
set ftp1 [new Application/FTP]
$ftp1 attach-agent $reno1
$ns at 1.0 "$ftp1 start"
$ns at 10.0 "$ftp1 stop"

#Setup a FTP Application over TCP/Newreno connection
set ftp2 [new Application/FTP]
$ftp2 attach-agent $newReno2
$ns at 1.0 "$ftp2 start"
$ns at 10.0 "$ftp2 stop"

#Setup a FTP Application over TCP/Vegas connection
set ftp3 [new Application/FTP]
$ftp3 attach-agent $vegas3
$ns at 1.0 "$ftp3 start"
$ns at 10.0 "$ftp3 stop"

#Setup a FTP Application over TCP/Sack1 connection
set ftp4 [new Application/FTP]
$ftp4 attach-agent $sack4
$ns at 1.0 "$ftp4 start"
$ns at 10.0 "$ftp4 stop"

#Setup a FTP Application over TCP/Fack connection
set ftp5 [new Application/FTP]
$ftp5 attach-agent $fack5
$ns at 1.0 "$ftp5 start"
$ns at 10.0 "$ftp5 stop"

#Setup a CBR Application over UDP connection
set cbr6 [new Application/Traffic/CBR]
$cbr6 attach-agent $udp12
	$cbr6 set packetSize_ 1000
	$cbr6 set rate_ 1.0Mb
	$cbr6 set interval_ 0.005
	$cbr6 set maxpkts_ 100.0
	$cbr6 set random_ false
$ns at 0.0 "$cbr6 start"
$ns at 0.0 "$cbr6 stop"

#Setup a CBR Application over UDP connection
set cbr7 [new Application/Traffic/CBR]
$cbr7 attach-agent $udp13
	$cbr7 set packetSize_ 1000
	$cbr7 set rate_ 1.0Mb
	$cbr7 set interval_ 0.005
	$cbr7 set maxpkts_ 100.0
	$cbr7 set random_ false
$ns at 8.0 "$cbr7 start"
$ns at 10.0 "$cbr7 stop"

#Setup a CBR Application over UDP connection
set cbr8 [new Application/Traffic/CBR]
$cbr8 attach-agent $udp14
	$cbr8 set packetSize_ 1000
	$cbr8 set rate_ 1.0Mb
	$cbr8 set interval_ 0.005
	$cbr8 set maxpkts_ 100.0
	$cbr8 set random_ false
$ns at 8.0 "$cbr8 start"
$ns at 10.0 "$cbr8 stop"

#Setup a CBR Application over UDP connection
set cbr9 [new Application/Traffic/CBR]
$cbr9 attach-agent $udp15
	$cbr9 set packetSize_ 1000
	$cbr9 set rate_ 1.0Mb
	$cbr9 set interval_ 0.005
	$cbr9 set maxpkts_ 100.0
	$cbr9 set random_ false
$ns at 8.0 "$cbr9 start"
$ns at 10.0 "$cbr9 stop"

#Setup a CBR Application over UDP connection
set cbr10 [new Application/Traffic/CBR]
$cbr10 attach-agent $udp16
	$cbr10 set packetSize_ 1000
	$cbr10 set rate_ 1.0Mb
	$cbr10 set interval_ 0.005
	$cbr10 set maxpkts_ 100.0
	$cbr10 set random_ false
$ns at 8.0 "$cbr10 start"
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
$ns at 0.1 "plotWindow $tahoe0 $Cwinfile0 $winfile0"
$ns at 0.1 "plotWindow $reno1 $Cwinfile1 $winfile1"
$ns at 0.1 "plotWindow $newReno2 $Cwinfile2 $winfile2"
$ns at 0.1 "plotWindow $vegas3 $Cwinfile3 $winfile3"
$ns at 0.1 "plotWindow $sack4 $Cwinfile4 $winfile4"
$ns at 0.1 "plotWindow $fack5 $Cwinfile5 $winfile5"
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "finish"
$ns at $val(stop) "puts \"done\" ; $ns halt"
$ns run
