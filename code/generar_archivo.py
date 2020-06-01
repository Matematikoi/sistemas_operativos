from random import randint
from random import random
from random import choice

def escogerAleatoreamente():
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
    s = archivo.readline()
    if len(s) > 2 : 
        nombres.append(s[:-1])

tipos = ['perro', 'gato','hamster','tortuga','pajaro']
edades = [i for i in range(30)]
razas = ['raza_{}'.format(i) for i in range(50)]
estaturas = [ i for i in range(150)]
pesos = [ random()*50 for i in range(1000)]
sexo = ['H','M']
for i in range(10**7):
    print(escogerAleatoreamente())
