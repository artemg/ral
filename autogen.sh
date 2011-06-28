#!/bin/sh
mkdir config m4
autoreconf --force --install -I config -I m4
