<?php
echo '#include "PolishClient.hpp"'.PHP_EOL;
echo '#include <unordered_map>'.PHP_EOL;
echo '#include<string>'.PHP_EOL;
$decl = "";
foreach(file("specs.txt") as $line) {
    if(preg_match("/^([0-9a-f]{64}) +(.+)$/", $line, $matches) === 1) {
        [$_, $hash, $method] = $matches;
        $hash = str_split($hash, 2);
        $hash = array_map("hexdec", $hash);
        $hash = array_map(fn(int $i) => $i>127 ? $i - 256 : $i, $hash);
        $hash = implode(",", $hash);
        $decl .= "\t{std::string({{$hash}}, 32), $method}".PHP_EOL;
        echo "void $method(const TcpClient*);".PHP_EOL;
    }
}
?>
const std::unordered_map<std::string, void(*)(const TcpClient*)> PolishClient::functions = {
<?= $decl; ?>
};
