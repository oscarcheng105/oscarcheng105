from tkinter import *
import math

cal = Tk()
cal.title("Calculator")
operator = ""
text_Input = StringVar()

def btnClick(numbers):
    global operator
    operator = operator + str(numbers)
    text_Input.set(operator)

def btnClearDisplay():
    global operator
    operator=""
    text_Input.set("")

def allclear():
    global operator
    global store
    operator = ""
    store = ""
    text_Input.set(operator)

def delete():
    global operator
    operator = operator[:len(operator)-1]
    text_Input.set(operator)

def btnEqualsInput():
    global operator
    sumup = str(eval(operator))
    operator = sumup
    text_Input.set(operator)

def btnSquareroot():
    global operator
    operator = str(math.sqrt(eval(operator)))
    text_Input.set(operator)

def percentage():
    global operator
    operator = str(eval(operator+"/100"))
    text_Input.set(operator)

def recall():
    global operator
    global store
    operator = operator + store
    text_Input.set(operator)

def storeup():
    global operator
    global store
    store = operator

def unstore():
    global store
    store = ""

def PositiveNegative():
    global operator
    operator = str(eval("-"+str(eval(operator))))
    text_Input.set(operator)

txtDisplay = Entry(cal,font=('arial',20,'bold'), textvariable = text_Input,
                   bd=1, insertwidth=5, bg="white",
                   justify="right").grid(columnspan=5)

#Numbers
btn1=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='1',bg="white",command=lambda:btnClick(1)).grid(row=4,column=1)

btn2=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='2', bg="white",command=lambda:btnClick(2)).grid(row=4,column=2)

btn3=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='3', bg="white",command=lambda:btnClick(3)).grid(row=4,column=3)

btn4=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='4', bg="white",command=lambda:btnClick(4)).grid(row=3,column=1)

btn5=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='5', bg="white",command=lambda:btnClick(5)).grid(row=3,column=2)

btn6=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='6', bg="white",command=lambda:btnClick(6)).grid(row=3,column=3)

btn7=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='7', bg="white",command=lambda:btnClick(7)).grid(row=2,column=1)

btn8=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='8', bg="white",command=lambda:btnClick(8)).grid(row=2,column=2)

btn9=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='9', bg="white",command=lambda:btnClick(9)).grid(row=2,column=3)

btn0=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='0', bg="white",command=lambda:btnClick(0)).grid(row=5,column=1)

#Symbols
period=Button(cal,padx=28,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='.', bg="white",command=lambda:btnClick(".")).grid(row=5,column=2)

add=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='+', bg="white",command=lambda:btnClick("+")).grid(row=2,column=4)

subtct=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='–', bg="white",command=lambda:btnClick("-")).grid(row=3,column=4)

mtply=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='x', bg="white",command=lambda:btnClick("*")).grid(row=4,column=4)

division=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='÷', bg="white",command=lambda:btnClick("/")).grid(row=5,column=4)

p=Button(cal,padx=22,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='%', bg="white",command=lambda:percentage()).grid(row=1,column=2)

equal=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='=', bg="white",command=lambda:btnEqualsInput()).grid(row=5,column=3)

sqrt=Button(cal,padx=25,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='√', bg="white",command=lambda:btnSquareroot()).grid(row=1,column=1)

clear=Button(cal,padx=31,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='C', bg="white",command=lambda:btnClearDisplay()).grid(row=4,column=0)

r=Button(cal,padx=16,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='MRC', bg="white",command=lambda:recall()).grid(row=1,column=0)

s=Button(cal,padx=24,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='M+', bg="white",command=lambda:storeup()).grid(row=2,column=0)
              
u=Button(cal,padx=26,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='M-', bg="white",command=lambda:unstore()).grid(row=3,column=0)

ac=Button(cal,padx=26,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='AC', bg="white",command=lambda:allclear()).grid(row=5,column=0)

d=Button(cal,padx=16,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='Del', bg="white",command=lambda:delete()).grid(row=1,column=4)

pn=Button(cal,padx=19,pady=20,bd=8,fg="black", font=('arial',20,'bold'),
            text='+/-', bg="white",command=lambda:PositiveNegative()).grid(row=1,column=3)

cal.mainloop()
