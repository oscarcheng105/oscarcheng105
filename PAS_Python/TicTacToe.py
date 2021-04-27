from tkinter import *
mark = 1 #O's turn
board = [' ',' ',' ',' ',' ',' ',' ',' ',' '] #create an imaginary table

#Change Board's Mark
def play(num):
    global mark
    global board
    if board[num-1] != "X" and board[num-1] != "O": #Change it to O or X if the block does not have any mark
        if mark==1:
            mark=2; #Other player's turn
            board[num-1]="O" #modify the imaginary board
            exec('btn'+str(num)+'.configure(text="O")') #show mark on tkinter
            show("X's Turn")#change text
        elif mark==2:
            mark=1; #Other player's turn
            board[num-1]="X" #modify the imaginary board
            exec('btn'+str(num)+'.configure(text="X")') #show mark on tkinter
            show("O's Turn")#change text
    checkWin()

#Check Winning Condition
def checkWin():
    global board
    if (board[0] == "O" and board[1] == "O" and board[2] == "O" or #top horizontal
        board[3] == "O" and board[4] == "O" and board[5] == "O" or #middle horizontal
        board[6] == "O" and board[7] == "O" and board[8] == "O" or  #bottom horizontal
        board[0] == "O" and board[3] == "O" and board[6] == "O" or #left vertical
        board[1] == "O" and board[4] == "O" and board[7] == "O" or #middle vertical
        board[2] == "O" and board[5] == "O" and board[8] == "O" or #right vertical
        board[0] == "O" and board[4] == "O" and board[8] == "O" or #diagonal
        board[2] == "O" and board[4] == "O" and board[6] == "O"): #diagonal
        for x in range(0,9): #Disable other buttons if winning condition is achieved
            if board[x] == " ":
                exec('btn'+str(x+1)+'.configure(state="disabled")')
        show("O Wins!") #show winning text
        
    elif (board[0] == "X" and board[1] == "X" and board[2] == "X" or #top horizontal
        board[3] == "X" and board[4] == "X" and board[5] == "X" or #middle horizontal
        board[6] == "X" and board[7] == "X" and board[8] == "X" or #bottom horizontal
        board[0] == "X" and board[3] == "X" and board[6] == "X" or #left vertical
        board[1] == "X" and board[4] == "X" and board[7] == "X" or #middle vertical
        board[2] == "X" and board[5] == "X" and board[8] == "X" or #right vertical
        board[0] == "X" and board[4] == "X" and board[8] == "X" or #diagonal
        board[2] == "X" and board[4] == "X" and board[6] == "X"): #diagonal
        for y in range(0,9): #Disable other buttons if winning condition is achieved
            if board[y] == " ":
                exec('btn'+str(y+1)+'.configure(state="disabled")')
        show("X Wins!") #show winning text
        
    elif ((board[0] == "O" or board[0] == "X") and (board[1] == "O" or board[1] == "X") and #check tie condition
        (board[2] == "O" or board[2] == "X") and (board[3] == "O" or board[3] == "X") and
        (board[4] == "O" or board[4] == "X") and (board[5] == "O" or board[5] == "X") and
        (board[6] == "O" or board[6] == "X") and (board[7] == "O" or board[7] == "X") and
        (board[8] == "O" or board[8] == "X")):
        show("Game Tied!") #show tied text

#Restart the Game
def restart():
    global mark
    global board
    board = [' ',' ',' ',' ',' ',' ',' ',' ',' '] #reset the imaginary board
    for x in range (1,10): #reset all buttons to normal state
        if board[x-1] == " ":
            exec('btn'+str(x)+'.configure(state="normal")')
        exec('btn'+str(x)+'.configure(text=" ")') #erase all marks on buttons
    mark = 1 
    show("Start!")

#ModifyText
def show(txt): 
    lb["text"]=txt

#Initiate Tkinter
tk=Tk()
tk.title("Tic Tac Toe")

#create buttons 
lb = Label(tk, text = "Start!",font=('Impact','25',"bold"))
lb.grid(column=1,row=0,columnspan=3)
btn1 = Button(tk, text=board[0],width=6,height=3,font=('Arial','20'),command=lambda: play(1))
btn1.grid(column=1, row=1)
btn2 = Button(tk, text=board[1],width=6,height=3,font=('Arial','20'),command=lambda: play(2))
btn2.grid(column=2, row=1)
btn3 = Button(tk, text=board[2],width=6,height=3,font=('Arial','20'),command=lambda: play(3))
btn3.grid(column=3, row=1)
btn4 = Button(tk, text=board[3],width=6,height=3,font=('Arial','20'),command=lambda: play(4))
btn4.grid(column=1, row=2)
btn5 = Button(tk, text=board[4],width=6,height=3,font=('Arial','20'),command=lambda: play(5))
btn5.grid(column=2, row=2)
btn6 = Button(tk, text=board[5],width=6,height=3,font=('Arial','20'),command=lambda: play(6))
btn6.grid(column=3, row=2)
btn7 = Button(tk, text=board[6],width=6,height=3,font=('Arial','20'),command=lambda: play(7))
btn7.grid(column=1, row=3)
btn8 = Button(tk, text=board[7],width=6,height=3,font=('Arial','20'),command=lambda: play(8))
btn8.grid(column=2, row=3)
btn9 = Button(tk, text=board[8],width=6,height=3,font=('Arial','20'),command=lambda: play(9))
btn9.grid(column=3, row=3)
re = Button(tk,width=25,text = "RESTART",font=('Impact','15','bold'), command=lambda:restart())
re.grid(column=1,row=4,columnspan=3)

tk.mainloop()
