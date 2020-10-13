<?php

namespace iggyvolz\polish;

class Root extends PolishObject
{
    protected function on(string $c):void
    {

    }
    protected function create(string $class):PolishObject
    {
        $this->callMethod($id);
    }
}