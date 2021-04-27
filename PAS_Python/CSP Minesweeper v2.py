from tkinter import *
import random
    
class game:
    def __init__(self):
        self.board = [[' ',' ',' ',' ',' ',' ',' ',' ',' '],
                     [' ',' ',' ',' ',' ',' ',' ',' ',' '],
                     [' ',' ',' ',' ',' ',' ',' ',' ',' '],
                     [' ',' ',' ',' ',' ',' ',' ',' ',' '],
                     [' ',' ',' ',' ',' ',' ',' ',' ',' '],
                     [' ',' ',' ',' ',' ',' ',' ',' ',' '],
                     [' ',' ',' ',' ',' ',' ',' ',' ',' '],
                     [' ',' ',' ',' ',' ',' ',' ',' ',' '],
                     [' ',' ',' ',' ',' ',' ',' ',' ',' '],]
        self.num_mines = 10
        self.color = ["black","blue","pink","green","purple","navy blue","grey","orange","dark red"]
        self.wincheck= False
        self.assign_Mines()
        self.tk = Tk()
        self.tk.title("Minesweeper")
        self.head = Label(self.tk,text="MINESWEEPER",font=('Impact',"25","bold"))
        self.head.grid(column=0,row=0,columnspan=9)
        self.mines = Label(self.tk,text = "Mines: "+str(self.num_mines))
        self.mines.grid(column=0,row=10,columnspan=5)
        self.btn = {}
        self.create_buttons()

    def create_buttons(self):
        for x in range(9):
            for y in range(9):
                self.board[x][y] = str(self.assign_Number(x,y))                
                self.btn[str(x) + "," + str(y)] = Button(self.tk, width=2)                                                        
                self.btn[str(x) + "," + str(y)].grid(row=x+1, column=y, sticky=N+S+E+W)
                self.btn[str(x) + "," + str(y)].bind("<Button-1>", lambda event, index=[x, y]:self.click(event, index))
                self.btn[str(x) + "," + str(y)].bind("<Button-2>", lambda event, index=[x, y]:self.flag(event,index))
        self.re = Button(self.tk, width = 10, text = "RESTART", command=lambda:self.restart())
        self.re.grid(column=5,row=10, columnspan = 4)

    def assign_Mines(self):
        for x in range(0,10):
            randomRow = random.randint(0,8)
            randomCol = random.randint(0,8)
            while (self.board[randomRow][randomCol] != ' '):
                randomRow = random.randint(0,8)
                randomCol = random.randint(0,8)
            self.board[randomRow][randomCol] = 'X'

    def assign_Number(self,r,c):
        count = 0
        if self.board[r][c] == 'X':
            return 'X'
        conditions = [[r+1,c+1], [r+1,c], [r+1,c-1], [r-1,c+1],
                        [r-1,c], [r-1,c-1], [r,c-1], [r,c+1]]
        for lim in conditions:
            if (lim[0]<=8 and lim[0] >= 0) and (lim[1]<=8 and lim[1] >= 0):
                i = lim[0]
                j = lim[1]
                if self.board[i][j] == 'X':
                    count+=1
        return count

    def click(self,event,index):
        self.show(index[0],index[1])

    def flag(self,event,index):
        x = index[0]
        y = index[1]
        if self.btn[str(x)+","+str(y)]["text"] == "":
            self.num_mines -=1
            self.btn[str(x)+","+str(y)].configure(text = "F", foreground="red")
        elif self.btn[str(x)+","+str(y)]["text"] == "F":
            self.num_mines +=1
            self.btn[str(x)+","+str(y)].configure(text = "", foreground="black")
        self.mines["text"] = "Mines: "+str(self.num_mines)

    def show(self,x,y):
        if self.wincheck==False:
            if self.board[x][y] == '0':
                self.show_others(x,y)
            if self.board[x][y] != 'X':
                self.btn[str(x)+","+str(y)].configure(text = str(self.board[x][y]), foreground = self.color[eval(self.board[x][y])])
            self.check(x,y)

    def show_others(self,r,c):
        conditions = [[r+1,c+1], [r+1,c], [r+1,c-1], [r-1,c+1],
                        [r-1,c], [r-1,c-1], [r,c-1], [r,c+1]]
        for lim in conditions:
            if (lim[0]<=8 and lim[0] >= 0) and (lim[1]<=8 and lim[1] >= 0):
                i = lim[0]
                j = lim[1]
                if self.board[i][j] == '0' and self.btn[str(i)+","+str(j)]["text"] == '':
                    self.btn[str(i)+","+str(j)]["text"] = self.board[i][j]
                    self.show_others(i,j)
                if self.board[i][j] != '0' and self.btn[str(i)+","+str(j)]["text"] == '':
                    self.show(i,j)

    def check(self,x,y):
        count = 0
        if self.wincheck == False:
            if self.board[x][y] == 'X':
                for i in range(9):
                    for j in range(9):
                        self.btn[str(i)+","+str(j)].configure(state="disabled", text = str(self.board[i][j]))
                self.head.configure(text = "DEFEAT", foreground = "red")
                self.wincheck = True        
            else:
                for i in range(9):
                    for j in range(9):
                        if self.btn[str(i)+","+str(j)]["text"] != ('X' and '') and self.board[i][j] != 'X':
                            count+=1
                if count == 71:
                    self.wincheck = True
                    self.head.configure(text = "VICTORY!", foreground = "Navy blue")
                    self.mines["text"] = "Mines: 0"
                    for i in range(9):
                        for j in range(9):
                            if self.board[i][j] == 'X':
                                self.btn[str(i)+","+str(j)].configure(state="disabled")       
                    
    def restart(self):
        self.head.configure(text = "MINESWEEPER", foreground = "black")
        self.wincheck=False
        self.num_mines = 10
        self.mines["text"] = "Mines: "+str(self.num_mines)    
        for x in range(9):
            for y in range(9):
                self.board[x][y] = ' '
        self.assign_Mines()
        for i in range(9):
            for j in range(9):
                self.board[i][j]=str(self.assign_Number(i,j))
                if self.btn[str(i)+","+str(j)]["state"] == "disabled":
                    self.btn[str(i)+","+str(j)].configure(state="normal")
                if self.btn[str(i)+","+str(j)]["text"] != '':
                    self.btn[str(i)+","+str(j)]["text"] = '';
                self.btn[str(i)+","+str(j)]["foreground"] = "black"

g = game()
