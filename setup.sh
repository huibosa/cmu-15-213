#!/usr/bin/env bash

(
  cd reference

  gcc -shared -fpic -o libcsapp.so csapp.c -lpthread

  mv libcsapp.so /usr/local/lib/
  mv csapp.h /usr/local/include/
)
