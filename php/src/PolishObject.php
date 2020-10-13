<?php

namespace iggyvolz\polish;

abstract class PolishObject
{
    private Polish $polish;
    private int $id;
    public function __construct(Polish $polish, int $id)
    {
        $this->polish = $polish;
        $this->id = $id;
    }
    protected function callMethod(string $data):void
    {
        $this->polish->write(pack("Q", $id).$data);
    }
    protected abstract function on(string $c):void;
}