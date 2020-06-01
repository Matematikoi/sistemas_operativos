#python code/generar_archivo.py > input/in_mascotas_grande
g++ code/mascotas_generar_binario.cpp code/mascotas.cpp -o binaries/run_mascotas_generar.bin
#g++ code/p1-dogProgram.cpp code/mascotas.cpp code/menu.cpp code/interactuar_archivos.cpp -o binaries/run_mascotas_recuperar.bin
./binaries/run_mascotas_generar.bin < input/in_mascotas_grande
