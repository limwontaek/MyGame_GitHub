from pico2d import *

class Tile:
    PIXEL_PER_METER = (10.0 / 0.3)  # 10 pixel 30 cm
    RUN_SPEED_KMPH = 60.0  # Km / Hour
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    image = None;

    def __init__(self):
        self.scrolling = 0
        self.image = load_image('resource\\grass.png')


    def draw(self):
        self.image.draw(400 - self.scrolling, 30)
        self.image.draw(1200 - self.scrolling, 30)


        if self.scrolling == 800:
            self.scrolling = 0

    def update(self, frame_time):
        self.scrolling += Tile.RUN_SPEED_PPS * frame_time
        self.scrolling %= 800