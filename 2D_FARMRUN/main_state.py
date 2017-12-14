from pico2d import*
import game_framework
import end_state

from Mario import Mario
from BackGround import BackGround
from Tile import Tile
from Barrier import Barrier
from Monster import Monster
from Monster2 import Monster2
from Monster3 import Monster3
from Item import Item
from Stage import Stage
from Stage2 import Stage2
from score import Score

name = "MainState"

mario = None
background = None


def make_world():
    global mario, background, tile, barrier, monster, monster2, monster3 , item, stage, stage2, score
    mario = Mario()
    background = BackGround()
    tile = Tile()
    barrier = Barrier()
    monster = Monster()
    monster2 = Monster2()
    monster3 = Monster3()
    item = Item()
    stage = Stage()
    stage2 = Stage2()
    score = Score()

def delete_world():
    global mario, background, tile, barrier, monster, monster2, monster3, item, stage, stage2, score
    del(mario)
    del(background)
    del(tile)
    del(barrier)
    del(monster)
    del(monster2)
    del(monster3)
    del(item)
    del(stage)
    del(stage2)
    del(score)

def enter():
    global object
    open_canvas()
    make_world()

def exit():
    delete_world()
    close_canvas()

def pause():
    pass

def resume():
    pass

def handle_events(frame_time):
    global mario, score, i
    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            game_framework.quit()
        elif event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
            game_framework.push_state(end_state)

        elif event.type == SDL_KEYDOWN:
            if event.key == SDLK_UP:
                mario.state = 'UP'
            if event.key == SDLK_DOWN:
                mario.state = 'DOWN'

        elif event.type == SDL_KEYUP:
            mario.state = 'RUN'

        if mario.hp < 0:
            game_framework.push_state(end_state)


def collide(a, b):
    left_a, bottom_a, right_a, top_a = a.collide_check()
    left_b, bottom_b, right_b, top_b = b.collide_check()

    if left_a > right_b: return False
    if right_a < left_b: return False
    if bottom_a > top_b: return False
    if top_a < bottom_b: return False
    return True

def update(frame_time):
   global  mario, background, tile, barrier, monster, monster2,monster3, item, stage,stage2, score
   stage.update(frame_time)
   background.update(frame_time)
   stage2.update(frame_time)
   tile.update(frame_time)
   barrier.update(frame_time)
   monster.update(frame_time)
   monster2.update(frame_time)
   monster3.update(frame_time)
   mario.update(frame_time)
   item.update(frame_time)
   score.update(frame_time)
   if collide(mario, monster):
       if monster.collide_button == True:
           monster.collide_button = False
           #monster.collide_sound.play()
           mario.hp -= 20
   if collide(mario, monster2):
       if monster2.collide_button == True:
           monster2.collide_button = False
           mario.hp -= 20
   if collide(mario, monster3):
       if monster3.collide_button == True:
           monster3.collide_button = False
           mario.hp -= 20
   if collide(mario, item):
       if item.collide_button == True:
           item.collide_button = False
           mario.hp += 20
   if background.mx > 2000:
       background.stage_button = False
       stage.stage_button = True
       stage2.stage_button = False
   if background.mx >4000:
       background.stage_button =False
       stage.stage_button = False
       stage2.stage_button = True
   if background.mx >6000:
       background.mx = 100
       background.stage_button = True
       stage.stage_button = False
       stage2.stage_button = False

def draw(frame_time):
    global mario,background, tile,barrier, monster, monster2,monster3,item,stage,stage2,score
    clear_canvas()

    if background.stage_button == True:
        background.draw()
    if stage.stage_button == True:
        stage.draw()
    if stage2.stage_button == True:
        stage2.draw()
    tile.draw()
    barrier.draw()
    mario.draw(frame_time)
    #mario.collide_box()
    #item.collide_box()
    if collide(mario,item):
        if item.collide_button == False:
            item.erase()
            item.collide_button = True
    else:
       item.draw()

    if collide(mario, monster):
        if monster.collide_button == False:
            monster.erase()
            monster.collide_button = True
    else:
        monster.draw()

    if collide(mario, monster2):
        if monster2.collide_button == False:
            monster2.erase()
            monster2.collide_button = True
    else:
        monster2.draw()

    if collide(mario, monster3):
        if monster3.collide_button == False:
            monster3.erase()
            monster3.collide_button = True
    else:
        monster3.draw()
    #monster.collide_box()
    #monster2.collide_box()
    #monster3.collide_box()

    score.draw()


    delay(0.02)
    update_canvas()