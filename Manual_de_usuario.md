USO DEL POGRAMA
===============

El programa se divide en dos partes principales el cliente y el servidor. Para el uso del cliente se tiene que compilar el programa usando `$sh code/run_client.sh` el archivo binario compilado queda en `binaries/ejecutableCliente.bin`. Para el server se puede ejecutar de la misma manera `$sh code/run_server.sh` ó si se desea se puede llenar el cliente de datos dumies usando `$sh code/run_setup.sh`. 

Uso del Servidor
--------------
Para hacer uso del server simplemente se tiene que ejecutar el archivo compilado que se genero en el paso anterior. A partir de ahí el server va a escuchar las peticiones que lleguen de los clientes. El servidor dara como logs la fecha, la ip del cliente, el puerto usado, y la operación realizada. 

Uso del Cliente
---------------
Para usar el cliente se corre el archivo compilado en el paso anterior y se le pasa como parametro la ip del servidor que lo va a atender. El cliente una vez logre conectarse al servidor lanza un menu desde donde el usuario puede escoger la opción que desee. Existen 5 opciones distintas

1. Ver registro: mediante un id se busca la mascota en la base de datos del server y se reporta al cliente.
2. Ingresar registro: Al usuario se le pide que ingrese los datos que caracterizan a una mascota y se le pasa la información al server para que este la procese. 
3. Buscar mascota: mediante un nombre se buscan todas las mascotas en la base de datos del server que tengan dicho nombre y se reporta al cliente.
4. Borrar mascota: mediante el id se elimina una mascota de la base de datos del server.
5. Salir del menu: el cliente sale del menu y termina la conexión con el host junto con la terminación del proceso.