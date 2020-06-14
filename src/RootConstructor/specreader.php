<?php
echo '#include "PolishClient.hpp"'.PHP_EOL;
echo '#include <unordered_map>'.PHP_EOL;
echo '#include<string>'.PHP_EOL;
$decl = "";
foreach(file(__DIR__ . "/specs.txt") as $line) {
    if(preg_match("/^([0-9a-f]+) +(.+)$/", $line, $matches) === 1) {
        [$_, $hash, $method] = $matches;
        echo "HASHES LENGTH: ".strlen($hash).PHP_EOL;
        $hash = str_split($hash, 2);
        $hash = array_map("hexdec", $hash);
        $hash = array_map(fn(int $i) => $i>127 ? $i - 256 : $i, $hash);
        $hash = implode(",", $hash);
        $decl .= "\t{std::string({{$hash}}), $method}".PHP_EOL;
        echo "void $method(const TcpClient*);".PHP_EOL;
    }
}
?>
const std::unordered_map<std::string, void(*)(const TcpClient*)> PolishClient::functions = {
<?= $decl; ?>
};
