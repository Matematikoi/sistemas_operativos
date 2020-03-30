g++ code/mascotas_generar_binario.cpp -o binaries/run_mascotas_generar.bin
g++ code/mascotas_recuperar_binario.cpp -o binaries/run_mascotas_recuperar.bin
./binaries/run_mascotas_generar.bin < input/in_mascotas 
./binaries/run_mascotas_recuperar.bin > output/out_mascotas

