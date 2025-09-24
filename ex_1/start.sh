#!/bin/bash

if [ ! -d ./build ]; then
	echo "./build não existe. Criando pasta..."
	mkdir ./build
fi

gcc main.c -o ./build/main
if [ $? -eq 0 ]; then
	./build/main
else
	echo "Erro na compilação do código"
fi
