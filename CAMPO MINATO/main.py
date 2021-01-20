import cppyy
cppyy.include("campo_minato.cpp")
from cppyy.gbl import Campo_minato

from boardgame_g2d import BoardGameGui
ok_mine=False
ok_w=False
ok_h=False

while ok_w==False:
    w=int(input("Inserisci larghezza matrice: "))
    
    if w>2:
        ok_w=True
    else:
        print("\nLarghezza matrice non valida!\n")


while ok_h==False:
    h=int(input("Inserisci altezza matrice: "))
    
    if h>2:
        ok_h=True
    else:
        print("\nAltezza matrice non valida!\n")

while ok_mine==False:
    n=int(input("Inserisci numero mine: "))
    
    if n>0 and n<(w*h):
        ok_mine=True
    else:
        print("\nNumero mine non valido!\n")

game = Campo_minato(h,w,n)
gui = BoardGameGui(game)
gui.main_loop()
