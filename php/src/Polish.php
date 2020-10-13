<?php

namespace iggyvolz\polish;


class Polish
{
    private $conn;
    /**
     * @var PolishObject
     */
    private array $objects;
    public function __construct(string $path)
    {
        if(file_exists($path)) unlink($path);
        posix_mkfifo($path, 0666);
        $this->conn = fopen($path, "r+");
        $this->root = new Root($this, 0);
        $this->objects[] = $this->root; 
    }
    public function getRoot():Root
    {
        return $this->objects[0];
    }
    /**
     * @internal
     */
    public function write(string $conts):void
    {
        fwrite($this->conn, $conts);
        fflush($this->conn);
    }
    /**
     * @internal
     */
    public function read(int $length):void
    {
        fread($this->conn, $length);
    }
}