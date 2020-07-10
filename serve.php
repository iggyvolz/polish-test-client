<?php
// Quick test server
if(file_exists("/tmp/sock")) unlink("/tmp/sock");
posix_mkfifo("/tmp/sock", 0666);
$conn = fopen("/tmp/sock", "r+");
echo "Press enter once Polish is started...";
fgetc(STDIN);
function gwrite($conn, $data) {
    flush();
    echo "write ".bin2hex($data).PHP_EOL;
    // fgetc(STDIN);
    fwrite($conn, $data);
}
// $0:Root Constructor
// $0(Window Factory)
gwrite($conn, pack("Q", 0));
gwrite($conn, hex2bin("6ba849be4a2df9c4b23ca8567fc3dc1cc858b47e704ef16e2d5321feccc885a8"));

// Ensure contract is validated
$conts = fgets($conn, 9);
$objectId = unpack("Q", $conts)[1];
if($objectId === 0) {
    // Validate contract object
    switch(ord(fgets($conn, 2))) {
        case 1:
            echo "CONTRACT VALIDATED\n";
            break;
        case 0:
            echo "CONTRACT FAILED\n";
            die();
    }
} else {
    var_dump("UNKNOWN OBJECT ID");var_dump($objectId);die();
}
// $1:Window Factory
// $1(200, 200)
gwrite($conn, pack("Q", 1));
gwrite($conn, pack("L", 200));
gwrite($conn, pack("L", 200));
// $2:Window
// $2.setTitle("foo bar")
gwrite($conn, pack("Q", 2));
gwrite($conn, pack("Q", 0));
gwrite($conn, pack("C", strlen("foo bar")));
gwrite($conn, "foo bar");
// $2.setPosition(100,100)
gwrite($conn, pack("Q", 2));
gwrite($conn, pack("Q", 1));
gwrite($conn, pack("L", 100));
gwrite($conn, pack("L", 100));
fflush($conn);
flush();
while(1);