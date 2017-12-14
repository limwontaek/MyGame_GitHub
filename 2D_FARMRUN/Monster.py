from pico2d import *
import random

class Monster:
    PIXEL_PER_METER = (10.0 / 0.3)  # 10 pixel 30 cm
    RUN_SPEED_KMPH = 80.0  # Km / Hour
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    TIME_PER_ACTION = 0.5
    ACTION_PER_TIME = 1.0 / TIME_PER_ACTION
    FRAMES_PER_ACTION = 4

    def __init__(self):
        self.image = load_image('Resource\\Monster1.png')
        self.collide_image = load_image("Resource\\collide.png")
        self.frame = 0
        self.x = random.randint(300,800)
        self.y = random.randint(50,300)
        self.speed = random.randint(15,20)
        self.collide_button = True

        self.run_frame = 0
        self.total_frame = 0

        #self.collide_sound = load_music("walk.mp3")
        #self.collide_sound.set_volume(32)

    def update(self, frame_time):
        self.total_frame += Monster.FRAMES_PER_ACTION * Monster.ACTION_PER_TIME* frame_time
        self.run_frame = int(self.total_frame + 1)%self.FRAMES_PER_ACTION
        self.x = self.x - self.speed

        if self.x <  0:
            self.x = 800
            self.speed = random.randint(15,20)
            self.y = random.randint(50,300)

    def draw(self):
        self.image.clip_draw(self.run_frame * 100, 0, 100, 100, self.x, self.y)

    def erase(self):
        self.collide_image.clip_draw(200, 0, 100, 100, self.x, self.y)

    def collide_box(self):
        draw_rectangle(*self.collide_check())

    def collide_check(self):
        return self.x - 30, self.y - 40, self.x + 25, self.y + 40