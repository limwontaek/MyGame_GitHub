from pico2d import *

class Mario:
    PIXEL_PER_METER = (10.0 / 0.3)  # 10 pixel 30 cm
    RUN_SPEED_KMPH = 80.0  # Km / Hour
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    UP_SPEED_KMPH = 1.0  # Km / Hour
    UP_SPEED_MPM = (UP_SPEED_KMPH * 1000.0 / 60.0)
    UP_SPEED_MPS = (UP_SPEED_MPM / 60.0)
    UP_SPEED_PPS = (UP_SPEED_MPS * PIXEL_PER_METER)

    TIME_PER_ACTION = 0.5
    ACTION_PER_TIME = 1.0 / TIME_PER_ACTION
    FRAMES_PER_ACTION = 4

    image = None

    RUN, UP,DOWM = 0, 1, 2

    def __init__(self):
        self.x, self.y = 100, 90
        self.frame = 0
        self.state = 'RUN'
        self.hp = 1500
        self.run_image = load_image('resource\\animation_sheet.png')
        self.up_image = load_image('resource\\animation_sheet.png')
        self.hp_image = load_image('resource\\hp.png')

        self.run_frame = 0
        self.jump_frame = 0
        self.total_frame  = 0


    #def collide_sound(self,monster):
    #    #self.collide_sound.play()

    def handle_up(self, frame_time):
        if self.y >300:
            self.y -= Mario.UP_SPEED_PPS
        else:
            self.y += Mario.UP_SPEED_PPS

    def handle_down(self, frame_time):
        if self.y <50:
            self.y += Mario.UP_SPEED_PPS
        else:
            self.y -= Mario.UP_SPEED_PPS


    def update(self, frame_time):
        self.total_frame += Mario.FRAMES_PER_ACTION * Mario.ACTION_PER_TIME * frame_time
        self.run_frame = int(self.total_frame) % self.FRAMES_PER_ACTION
        self.hp -= 2

        if self.state == 'RUN' :
            self.frame = (self.frame +1) % self.FRAMES_PER_ACTION
        elif self.state == 'UP':
            self.handle_up(frame_time)
        elif self.state == 'DOWN':
            self.handle_down(frame_time)

    def draw(self,frame_time):
        if self.state == 'RUN':
            self.run_image.clip_draw(self.run_frame*100,100,100,100,self.x,self.y)
        if self.state == 'UP':
            self.run_image.clip_draw(self.run_frame*100,100,100,100,self.x,self.y)
        if self.state == 'DOWN':
            self.run_image.clip_draw(self.run_frame*100,100,100,100,self.x,self.y)

        self.hp_image.clip_draw((self.run_frame)*10, 0 , 10, 20, 10, 550, self.hp, 30)

    def collide_box(self):
        draw_rectangle(*self.collide_check())

    def collide_check(self):
        return self.x -30, self.y-40,self.x+25,self.y+40
