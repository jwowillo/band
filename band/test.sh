#!/usr/bin/env bash

ar -M <<EOM
        CREATE bin/libband-$1.a
        ADDLIB bin/libband-no-raylib-$1.a
        ADDLIB ../lib/raylib-2.6.0/src/libraylib.a
        SAVE
        END
EOM
