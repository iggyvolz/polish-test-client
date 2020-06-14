<?php
// https://www.php.net/manual/en/class.recursivedirectoryiterator.php#97228
$Directory = new RecursiveDirectoryIterator(__DIR__."/..");
$Iterator = new RecursiveIteratorIterator($Directory);
$Regex = new RegexIterator($Iterator, '/^.+\.hpp$/i', RecursiveRegexIterator::GET_MATCH);
$hppfiles = iterator_to_array($Regex);
$hppfiles = array_map(fn(array $x) => $x[0], $hppfiles);
$hppfiles = array_map("realpath", $hppfiles);
$hppfiles = array_values($hppfiles);
$hashes = [];
$classes = [];
$files = [];
foreach($hppfiles as $file) {
    $conts = file_get_contents($file);
    if(preg_match("@^// HASH (.+)@m", $conts, $matches))
    {
        [$_, $hash] = $matches;
        // TODO namespace
        if(preg_match("@^class ([a-zA-Z0-9]+) *:@m", $conts, $matches)) {
            [$_, $class] = $matches;
            $hashes[] = $hash;
            $classes[] = $class;
            $files[] = $file;
        }
    }
}
?>
#include<unordered_map>
#include<string>
#include "RootConstructor.hpp"
<?php
foreach($files as $file)
{
    ?>
#include "<?= substr(relativePath(__DIR__, $file), 0, -1) ?>"
    <?php
}
?>

const std::unordered_map<std::string, PolishObject*(*)(PolishClient*)> RootConstructor::constructors = {
<?php
foreach($hashes as $i => $hash)
{
    $class = $classes[$i];
    ?>

	{std::string({<?= makecstring($hash) ?>}), <?= $class ?>::create},
    <?php
}
?>

};
<?php
/**
 * https://stackoverflow.com/a/6608425
 * Return the relative path between two paths / Retourne le chemin relatif entre 2 chemins
 *
 * If $path2 is empty, get the current directory (getcwd).
 * @return string
 */
function relativePath($path1, $path2='') {
    if ($path2 == '') {
        $path2 = $path1;
        $path1 = getcwd();
    }
    
    //Remove starting, ending, and double / in paths
    $path1 = trim($path1,'/');
    $path2 = trim($path2,'/');
    while (substr_count($path1, '//')) $path1 = str_replace('//', '/', $path1);
    while (substr_count($path2, '//')) $path2 = str_replace('//', '/', $path2);
    
    //create arrays
    $arr1 = explode('/', $path1);
    if ($arr1 == array('')) $arr1 = array();
    $arr2 = explode('/', $path2);
    if ($arr2 == array('')) $arr2 = array();
    $size1 = count($arr1);
    $size2 = count($arr2);
    
    //now the hard part :-p
    $path='';
    for($i=0; $i<min($size1,$size2); $i++)
    {
        if ($arr1[$i] == $arr2[$i]) continue;
        else $path = '../'.$path.$arr2[$i].'/';
    }
    if ($size1 > $size2)
        for ($i = $size2; $i < $size1; $i++)
            $path = '../'.$path;
    else if ($size2 > $size1)
        for ($i = $size1; $i < $size2; $i++)
            $path .= $arr2[$i].'/';
    
    return $path;
    }
    function makecstring(string $hash)
    {
        $hash = str_split($hash, 2);
        $hash = array_map("hexdec", $hash);
        $hash = array_map(fn(int $i) => $i>127 ? $i - 256 : $i, $hash);
        $hash = implode(",", $hash);
        return $hash;
    }