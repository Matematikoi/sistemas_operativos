Existen varias partes en las que se ha segmentado el programa para su desarrollo. Cada una de estas partes tiene estructuras y funciones que permiten que el programa se desempeñe adecuadamente. Vamos a recorrer estas funciones y estructuras de acuerdo a los headers que se crearon. 

MASCOTAS
======
Contiene la estructura `mascota` que tiene todos los datos importantes de una mascota. Dentro de las funciones que hay existen:
`int hashear_nombre(char *str);`
Nos permite obtener el hash de un arreglo de characteres
`std::string leerHistoriaClinica(char* ruta);`
Nos permite leer la historia clinica a partir de una ruta
`void escribirHistoriaClinica(char* ruta, std::string data);`
Nos permite escribir una historia clinica. Se usa para actualizarla cuando el cliente la actualiza y la envia

MENSAJE
=======
Para facilitar la comunicación entre servidor y cliente se usan dos estructuras claves, `Mensaje` y `RespuestaServidor`. Mediante la primera se envia toda la información necesaria al server desde el cliente para hacer una petición. Con las segunda tenemos una forma dentro del cliente de tener la respuesta a todas las peticiones y depues poder transformarlo en un mensaje de characteres que se le pasa al cliente. 

____


Como se puede pensar el server y el cliente tienen que tener diferentes operaciones. Mientras el Server no puede hacer un menu el cliente no debería editar archivos binarios, de hecho el único archivo que debería editar es el de la historia clínica y aún así eso lo edita un editor de texto ajeno al programa. Es por esta razón que el servidor tiene algunos headers que el cliente no.



LIBRERIAS PROPIAS DEL SERVER
==============================

PARA LA EDICIÓN DE ARCHIVOS
----------
`int recuperar_id (int num_id);`
Busca el indice en donde se encuentra almacenado en la base datos la mascota con id `num_id`

`void escribir_al_final_id (int num_idx);`
Permite añadir un nuevo id de mascota que se encuentra en el indice `num_idx`

`void escribir_id_a_indice(int id, int new_idx);`


`int recuperar_hash(int h);`


`void escribir_hash(int h, int new_index);`


`Mascota recuperar_indice(int num_item);`


`void imprimir_estructura(Mascota *m);`


`void escribir_al_final (Mascota *m);`


`void escribir_mascota_a_indice(int idx, Mascota *m);`


`void borrar_indice(int idx);`


`void anadir_mascota(Mascota *m);`

