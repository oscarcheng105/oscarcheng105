from tkinter import *
import random
import time
   
class Ball:
    def __init__(self, canvas, paddle, score, color):
        self.canvas = canvas #assign parameter to object value
        self.paddle = paddle 
        self.score = score 
        self.id = canvas.create_oval(10, 10, 25, 25, fill=color) #create an oval
        self.canvas.move(self.id, 245, 100) #move the oval to position (245,100)
        starts = [-3, -2, -1, 1, 2, 3] 
        random.shuffle(starts) #randomly make the ball start in various directions
        self.x = starts[0]
        self.y = -3 #speed up the ball
        self.canvas_height = self.canvas.winfo_height() #obtain cavan height info
        self.canvas_width = self.canvas.winfo_width() #obtain cavan width info
        self.hit_bottom = False #initialize that ball hasn't hit the paddle
    def hit_paddle(self, pos):
        paddle_pos = self.canvas.coords(self.paddle.id) #obtain paddle coordinate
        if pos[2] >= paddle_pos[0] and pos[0] <= paddle_pos[2]: #see if ball is hit
            if pos[3] >= paddle_pos[1] and pos[3] <= paddle_pos[3]:
                self.x += self.paddle.x #add paddle speed to ball
                self.score.hit() #add score
                return True
        return False
    def draw(self):
        self.canvas.move(self.id, self.x, self.y)
        pos = self.canvas.coords(self.id)
        if pos[1] <= 0: #Make the ball move a same speed in y direction
            self.y = 3
        if pos[3] >= self.canvas_height:
            self.hit_bottom = True
        if self.hit_paddle(pos) == True:
            self.y = -3
        if pos[0] <= 0: #Make the ball move a same speed in x direction
            self.x = 3
        if pos[2] >= self.canvas_width:
            self.x = -3
            
class Paddle:
    def __init__(self, canvas, color):
        self.canvas = canvas #assign parameter to object value
        self.id = canvas.create_rectangle(0, 0, 100, 10, fill=color) #create a rectangle
        self.canvas.move(self.id, 200, 300)  #place the rectangle at position (200,300)
        self.x = 0 
        self.canvas_width = self.canvas.winfo_width()
        self.started = False
        self.canvas.bind_all('<KeyPress-Left>', self.turn_left) #make rectangle go to specific direction with keyboard input
        self.canvas.bind_all('<KeyPress-Right>', self.turn_right)
        self.canvas.bind_all('<Button-1>', self.start_game)
    def draw(self):
        self.canvas.move(self.id, self.x, 0)
        pos = self.canvas.coords(self.id)
        if pos[0] <= 0: #make the paddle move in x axis without exceeding canvas
            self.x = 0
        elif pos[2] >= self.canvas_width:
            self.x = 0
    def turn_left(self, evt): #rectangle go left
        self.x = -2
    def turn_right(self, evt): #rectangle go right
        self.x = 2
    def start_game(self, evt): #initialize rectange
        self.started = True
        
class Score:
    def __init__(self, canvas, color): #show score
        self.score = 0
        self.canvas = canvas
        self.id = canvas.create_text(450, 10, text=self.score, \
fill=color) #create score number
    def hit(self): #add score when called
        self.score += 1
        self.canvas.itemconfig(self.id, text=self.score)
        
tk = Tk()#establish tkinter
tk.title("Game")
tk.resizable(0, 0) #make window into a fixed size
tk.wm_attributes("-topmost", 1) #put the window in front
canvas = Canvas(tk, width=500, height=400, bd=0, highlightthickness=0) 
canvas.pack() #create canvas
tk.update() #initialize tkinter

score = Score(canvas, 'green') #create and object of class Score
paddle = Paddle(canvas, 'blue') #create and object of class Paddle
ball = Ball(canvas, paddle, score, 'red') #create and object of class Ball
game_over_text = canvas.create_text(250, 200, text='GAME OVER', \
        state='hidden') #create game over text and hide it until it is summoned

while 1:
    if ball.hit_bottom == False and paddle.started == True: #start game
        ball.draw() 
        paddle.draw()
    if ball.hit_bottom == True: #show when game over
        time.sleep(1)
        canvas.itemconfig(game_over_text, state='normal') 
    tk.update_idletasks()
    tk.update()
    time.sleep(0.01) #make he program not run too fast
