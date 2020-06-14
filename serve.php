<?php
// Quick test server
$socket = stream_socket_server("tcp://127.0.0.1:53000");
while(1) {
    while($conn = stream_socket_accept($socket, -1)) {
        fwrite($conn, pack("Q", 0));
        fwrite($conn, hex2bin("136a9ce36bea406a719ca34a95f00b6e67326d7f01f32d29072422fc75f0589b"));
    }
}