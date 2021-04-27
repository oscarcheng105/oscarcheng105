from tkinter import *
import random
import time

class Game:
    #init constructor
    def __init__(self): #create the game canvas
        self.tk = Tk() 
        self.tk.title("Racing for the Exit")
        self.tk.resizable(0, 0)
        self.tk.wm_attributes("-topmost", 1)
        self.canvas = Canvas(self.tk, width=500, height=500, highlightthickness=0)
        self.canvas.pack()
        self.tk.update()
        self.canvas_height = 500
        self.canvas_width = 500
        self.bg = PhotoImage(file="background.gif") #load the background
        w = self.bg.width()
        h = self.bg.height()
        for x in range(0, 5):
            for y in range(0, 5):
                self.canvas.create_image(x * w, y * h, \
                        image=self.bg, anchor='nw')
        self.sprites = []
        self.running = True

    def mainloop(self):
        while 1: #run until game window is closed
            if self.running == True: 
                for sprite in self.sprites:
                    sprite.move()
            self.tk.update_idletasks() #redraw the screen and sleep for a fraction of a second
            self.tk.update()
            time.sleep(0.01)

class Coords: #identify sprite position
    def __init__(self, x1=0, y1=0, x2=0, y2=0):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        
def within_x(co1,co2): #check x range
    if (co1.x1 > co2.x1 and co1.x1 < co2.x2) \
            or (co1.x2 > co2.x1 and co1.x2 < co2.x2) \
            or (co2.x1 > co1.x1 and co2.x1 < co1.x2) \
            or (co2.x2 > co1.x1 and co2.x2 < co1.x1):
        return True #true if the tested coordinate object is within the other coordinate object horizontally
    else:
        return False #false if the tested coordinate object crosses over the other coordinate obeject horizontally

def within_y(co1, co2): #check y range
    if (co1.y1 > co2.y1 and co1.y1 < co2.y2) \
            or (co1.y2 > co2.y1 and co1.y2 < co2.y2) \
            or (co2.y1 > co1.y1 and co2.y1 < co1.y2) \
            or (co2.y2 > co1.y1 and co2.y2 < co1.y1):
        return True #true if the tested coordinate object is within the other coordinate object vertically
    else:
        return False #false if the tested coordinate object crosses over the other coordinate obeject vertically

def collided_left(co1, co2): #check if hit left
    if within_y(co1, co2): #check if two objects matches vertically
        if co1.x1 <= co2.x2 and co1.x1 >= co2.x1: 
            return True #return true if collide
    return False #return false if not
    
def collided_right(co1, co2): #check if hit right
    if within_y(co1, co2): #check if two objects matches vertically
        if co1.x2 >= co2.x1 and co1.x2 <= co2.x2:
            return True #return true if collide
    return False #return false if not

def collided_top(co1, co2): #check if hit top
    if within_x(co1, co2): #check if two objects matches horizontally
        if co1.y1 <= co2.y2 and co1.y1 >= co2.y1:
            return True #return true if collide
    return False #return false if not

def collided_bottom(y, co1, co2): #check if hit bottom
    if within_x(co1, co2): #check if two objects matches horizontally
        y_calc = co1.y2 + y
        if y_calc >= co2.y1 and y_calc <= co2.y2:
            return True #return true if collide
    return False #return false if not

class Sprite:
    def __init__(self, game): #takes in the game object
        self.game = game 
        self.endgame = False
        self.coordinates = None
        self.y = 0
    def move(self): #make each object not move by default
        pass
    def coords(self): #returns each object's coordinates
        return self.coordinates

class PlatformSprite(Sprite):
    def __init__(self, game, photo_image, x, y, width, height):
        Sprite.__init__(self, game) #use the object default in class sprite
        self.photo_image = photo_image #bring the platform object to life
        self.image = game.canvas.create_image(x, y, image=self.photo_image, anchor='nw')
        self.coordinates = Coords(x, y, x + width, y + height) #update the coordinates of the platform object

class StickFigureSprite(Sprite):
    def __init__(self, game):
        Sprite.__init__(self, game) #update stick man's movement pitctures
        self.images_left = [ PhotoImage(file="stand.gif"),
               PhotoImage(file="Run3.gif"),
               PhotoImage(file="Run4.gif")
        ]
        self.images_right = [ PhotoImage(file="stand.gif"),
               PhotoImage(file="Run1.gif"),
               PhotoImage(file="Run2.gif")
        ]
        self.image = game.canvas.create_image(200, 470, image=self.images_left[0], anchor='nw') #draw the first image
        #set up stickman's movement and store its positions
        self.x = -2 
        self.y = 0
        self.current_image = 0
        self.current_image_add = 1
        self.jump_count = 0
        self.jumping = False
        self.follow_platform = None
        self.last_time = time.time()
        self.coordinates = Coords()
        game.canvas.bind_all('<KeyPress-Left>', self.turn_left) #make it go left
        game.canvas.bind_all('<KeyPress-Right>', self.turn_right) #make it go right
        game.canvas.bind_all('<KeyPress-Up>', self.jump) #make it go up
        
    def turn_left(self, evt): #go left
        if self.jumping == False:
            self.x = -2
        
    def turn_right(self, evt): #go right
        if self.jumping == False:
            self.x = 2

    def jump(self, evt): #go up
        if self.jumping == False:
            self.y = -4
            self.jump_count = 0
            self.jumping = True
            self.follow_platform = None

    def animate(self):
        if self.x != 0 and self.y == 0: #check if stickman is moving or jumping to animate our stickman
            if time.time() - self.last_time > 0.1:
                self.last_time = time.time()
                self.current_image += self.current_image_add
                if self.current_image >= 2:
                    self.current_image_add = -1
                if self.current_image <= 0:
                    self.current_image_add = 1
        #change the images to show animation
        if self.x < 0:
            if self.jumping == True:
                self.game.canvas.itemconfig(self.image, \
                        image=self.images_left[2])
            else:
                self.game.canvas.itemconfig(self.image, \
                        image=self.images_left[self.current_image])

        elif self.x > 0:
            if self.jumping == True:
                self.game.canvas.itemconfig(self.image, \
                        image=self.images_right[2])
            else:
                self.game.canvas.itemconfig(self.image, \
                        image=self.images_right[self.current_image])
                
    def coords(self): #store stick figures' top left and right bottom position
        xy = self.game.canvas.coords(self.image)
        self.coordinates.x1 = xy[0]
        self.coordinates.y1 = xy[1]
        self.coordinates.x2 = xy[0] + 27
        self.coordinates.y2 = xy[1] + 30
        return self.coordinates

    def move(self):
        self.animate() #carry out animation
        if self.jumping == True:
            if self.y < 0: #see if jumping
                self.jump_count += 1
                if self.jump_count > 20:
                    self.y = 4
            if self.y > 0: #see if falling
                self.jump_count -= 1
        co = self.coords() #obtain the position of the stick figure
        left = True
        right = True
        top = True
        bottom = True
        falling = True
        if self.y > 0 and co.y2 >= self.game.canvas_height: #check if hit bottom of the canvas
            self.y = 0
            self.jumping == False
            bottom = False
        elif self.y < 0 and co.y1 <= 0: #check if hit top of the canvas
            self.y = 0
            self.jumping == False
            top = False
        if self.x > 0 and co.x2 >= self.game.canvas_width: #check if hit right of the canvas
            self.x = 0
            right = False
        elif self.x < 0 and co.x1 <= 0: #check if hit left of the canvas
            self.x = 0
            left = False
        if self.follow_platform is not None:
            if not collided_bottom(5, co, self.follow_platform.coords()):
                self.follow_platform = None
                self.y = 0
            else:
                self.y = self.follow_platform.y
                bottom = False
                left = False
                right = False
        for sprite in self.game.sprites: #check if collide with other gaming objects
            if sprite == self: #ignore if stickman collides with itself
                continue
            #get new gaming object's coordinate and see if the stickman collides with anything
            sprite_co = sprite.coords()
            #check if
                #stickman didn't hit the top of the canvas
                #stickman is jumping
                #the top of the stickman has collided with other gaming objects
            if top and self.y < 0 and collided_top(co, sprite_co):
                self.y = -self.y
                top = False
            if bottom and collided_bottom(self.y, co, sprite_co) and sprite.y != 0:
                self.follow_platform = sprite
                self.y = sprite.y - 1
                self.jumping = False
                falling = False
                bottom = False
                top = False
            #check if stickman collided at the bottom
            if bottom and self.y > 0 and collided_bottom(self.y, \
                    co, sprite_co):
                self.y = sprite_co.y1 - co.y2
                if self.y < 0:
                    self.y = 0
                self.jumping = False
                falling = False
                bottom = False
                top = False
            #check if stickman is falling
            if bottom and falling and self.y == 0 \
                    and co.y2 < self.game.canvas_height \
                    and collided_bottom(1, co, sprite_co):
                falling = False
            #check if stickman collides at the left
            if left and self.x < 0 and collided_left(co, sprite_co):
                self.x = 0
                left = False
                if sprite.endgame:
                    self.game.running = False
            #check if stickman collides at the left       
            if right and self.x > 0 and collided_right(co, sprite_co):
                self.x = 0
                right = False
                if sprite.endgame:
                    self.game.running = False
        #see if the stickman should start falling
        if falling and bottom and self.y == 0 \
                and co.y2 < self.game.canvas_height:
            self.y = 4
        self.game.canvas.move(self.image, self.x, self.y) #move stickman immage according to its x and y value
        
class DoorSprite(Sprite):
    def __init__(self, game, photo_image, x, y, width, height):
        Sprite.__init__(self, game) #make it a gaming object
        self.photo_image = photo_image #make gaming object visible with pictures
        self.image = game.canvas.create_image(x, y, \
            image=self.photo_image, anchor='nw')
        self.coordinates = Coords(x, y, x + (width / 2), y + height) #setup its coordinates
        self.endgame = True #game ends when stickman hits the door

class VMovingPlatformSprite(PlatformSprite):
    def __init__(self, game, photo_image, x, y, width, height):
        PlatformSprite.__init__(self, game, photo_image, x, y, width, height)
        self.y = 2
        self.old_y = 2
        self.counter = 0
        self.last_time = time.time()
        self.width = width
        self.height = height
    def coords(self):
        xy = list(self.game.canvas.coords(self.image))
        self.coordinates.x1 = xy[0]
        self.coordinates.y1 = xy[1]
        self.coordinates.x2 = xy[0] + self.width
        self.coordinates.y2 = xy[1] + self.height
        return self.coordinates
    def move(self):
        if time.time() - self.last_time > 0.03:
            self.y = self.old_y
            self.last_time = time.time()
            self.game.canvas.move(self.image, 0, self.y)
            self.counter += 1
            if self.counter > 20:
                self.y *= -1
                self.old_y = self.y
                self.counter = 0
        else:
            self.y = 0

g = Game()

#create platforms
platform1 = PlatformSprite(g, PhotoImage(file="Platform1.gif"), \
    0, 480, 100, 10)
platform2 = PlatformSprite(g, PhotoImage(file="Platform1.gif"), \
    150, 440, 100, 10)
platform3 = PlatformSprite(g, PhotoImage(file="Platform1.gif"), \
    300, 400, 100, 10)
platform4 = VMovingPlatformSprite(g, PhotoImage(file="Platform1.gif"), \
    300, 160, 100, 10)
platform5 = PlatformSprite(g, PhotoImage(file="Platform2.gif"), \
    175, 350, 66, 10)
platform6 = PlatformSprite(g, PhotoImage(file="Platform2.gif"), \
    50, 300, 66, 10)
platform7 = PlatformSprite(g, PhotoImage(file="Platform2.gif"), \
    170, 120, 66, 10)
platform8 = PlatformSprite(g, PhotoImage(file="Platform2.gif"), \
    45, 60, 66, 10)
platform9 = PlatformSprite(g, PhotoImage(file="Platform3.gif"), \
    170, 250, 32, 10)
platform10 = PlatformSprite(g, PhotoImage(file="Platform3.gif"), \
    230, 200, 32, 10)

#add all gaming objects to sprite
g.sprites.append(platform1) 
g.sprites.append(platform2)
g.sprites.append(platform3)
g.sprites.append(platform4)
g.sprites.append(platform5)
g.sprites.append(platform6)
g.sprites.append(platform7)
g.sprites.append(platform8)
g.sprites.append(platform9)
g.sprites.append(platform10)

door = DoorSprite(g, PhotoImage(file="door1.gif"), 45, 30, 40, 35)
g.sprites.append(door)

sf = StickFigureSprite(g)
g.sprites.append(sf)

g.mainloop()
