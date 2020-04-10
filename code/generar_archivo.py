from random import randint
from random import random
from random import choice
def procesar_nombre(s):
    x = s.replace('\n','')
    for mal, bien in zip ('áéíóúäëïöüÁÉÍÓÚÄËÏÖÜ ','aeiouaeiouAEIOUAEIOU_'):
        x = x.replace(mal,bien)
    return x.encode('ascii','ignore').decode()
def escoger():
    return '{} {} {} {} {} {} {}'.format(
        choice(nombres),
        choice(tipos),
        choice(edades),
        choice(razas),
        choice(estaturas),
        choice(pesos),
        choice(sexo)
    )
archivo, nombres,n = open('input/nombres_mascotas.txt'),[],1717
for i in range(n):
    s = procesar_nombre(archivo.readline())
    if len(s) > 0 : 
        nombres.append(s)

tipos = ['perro', 'gato','hamster','tortuga','pajaro']
edades = [i for i in range(30)]
razas = ['raza_{}'.format(i) for i in range(50)]
estaturas = [ i for i in range(150)]
pesos = [ random()*50 for i in range(1000)]
sexo = ['H','M']
for i in range(10**7):
    print(escoger())
