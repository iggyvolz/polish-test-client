<?php
// Quick test server
$socket = stream_socket_server("tcp://127.0.0.1:53000");
$conns = [];
while(1) {
    while($conn = stream_socket_accept($socket, -1)) {
        $conns[]=$conn;
        fwrite($conn, pack("Q", 0));
        fwrite($conn, hex2bin("015ae42867e6e3b2bae75f0fa3fd11aac0c41e4cd51b3c0dc33383a1f6074a7e"));
        for($i=0; $i<5; $i++) {
            fwrite($conn, pack("Q", 1));
            fwrite($conn, pack("L", 500));
            fwrite($conn, pack("L", 200));
            fwrite($conn, pack("L", 200));
            fwrite($conn, pack("L", 200));
        }
    }
}