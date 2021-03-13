import time
from tkinter import ttk
from ttkthemes import ThemedTk
import serial

picData = serial.Serial('COM1', baudrate=9600, timeout=1)


def limitePersonnes():
    resultat = spinbox1.get()
    picData.write(resultat.encode())
    time.sleep(2)
    return resultat


def readSerial():
    data = picData.readline().decode("ascii")

    if data != "":
        val = int(data)

        print(val)
        limite = limitePersonnes()
        if val < int(limite):
            texte = "Il y a {} personnes".format(val)
            label2.config(text=texte)
        elif val >= int(limite):
            texte = "Alerte, {} personnes !".format(val)
            label2.config(text= texte)

    ventana1.after(100, readSerial)


ventana1 = ThemedTk(themebg=True)
ventana1.set_theme("equilux")
ventana1.title("Projet d'éléctronique")

label1 = ttk.Label(ventana1, text="Veuillez séléctionner une limite:")
label1.grid(column=0, row=0, padx=10, pady=10)

spinbox1 = ttk.Spinbox(ventana1, from_=0, to=10, width=10, state='readonly')
spinbox1.set(0)
spinbox1.grid(column=1, row=0, padx=10, pady=10)

boton1 = ttk.Button(ventana1, text="Appliquer", command=limitePersonnes)
boton1.grid(column=0, row=1, padx=10, pady=10)

label2 = ttk.Label(ventana1, text="", width=20)
label2.grid(column=1, row=1, padx=10, pady=10)
ventana1.update()

if __name__ == '__main__':
    ventana1.after(100, readSerial)
    ventana1.mainloop()
