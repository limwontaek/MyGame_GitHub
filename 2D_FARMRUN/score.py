__author__ = '임원택'

from pico2d import *


class Score:
    def __init__(self):
        self.min = 0.0
        self.sec = 0.0
        self.font = load_font('font.ttf',20)
        self.time = 0
        self.rank1 =0
        self.rank2=0
        self.rank3=0
        self.rank4=0
        self.rank5=0
        self.rank6=0
        self.rank7=0
        self.rank8=0
        self.rank9=0
        self.rank10=0

    def update(self, frame_time):
        self.time = get_time()
        if self.sec == 10:
            self.sec = 0.0
            self.min +=1
        elif self.sec != 60:
            self.sec += 1
        pass

    def draw(self):
        self.font.draw(650,480, "DISTANCE: %dM" % self.min)


    def rank(self,frame_time):
        self.font.draw(650,480, "1st: %dM" % self.rank1)
        self.font.draw(650,480, "2st: %dM" % self.rank2)
        self.font.draw(650,480, "3st: %dM" % self.rank3)
        self.font.draw(650,480, "4st: %dM" % self.rank4)
        self.font.draw(650,480, "5st: %dM" % self.rank5)
        self.font.draw(650,480, "6st: %dM" % self.rank6)
        self.font.draw(650,480, "7st: %dM" % self.rank7)
        self.font.draw(650,480, "8st: %dM" % self.rank8)
        self.font.draw(650,480, "9st: %dM" % self.rank9)
        self.font.draw(650,480, "10st: %dM" % self.rank10)
