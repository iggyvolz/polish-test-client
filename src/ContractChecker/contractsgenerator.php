<?php  ?>
#include<unordered_set>
#include<string>
#include "ContractChecker.hpp"
const std::unordered_set<std::string> ContractChecker::contracts = {
<?php
foreach(file(__DIR__ . "/contracts.txt") as $line)
{
    $line = trim($line);
    if($line[0] === "#") continue;
    ?>
	{std::string({<?= makecstring($line) ?>})},
    <?php
}
?>
};
<?php
function makecstring(string $hash)
{
    $hash = str_split($hash, 2);
    $hash = array_map("hexdec", $hash);
    $hash = array_map(fn(int $i) => $i>127 ? $i - 256 : $i, $hash);
    $hash = implode(",", $hash);
    return $hash;
}