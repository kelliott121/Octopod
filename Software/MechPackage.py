class Joint:

    def __init__(self, angle, orientation):
        self.angle = angle
        self.orientation = orientation
        self.range = 180
        self.offset = 90

    def setAngle(self, newAngle):
        if -self.offset <= newAngle <= (self.range - self.offset):
            self.angle = newAngle

class Link:
    def __init__(self, length):
        self.length = length

class Limb:

    def __init__(self):
        self.startX = 0
        self.startY = 125
        self.startZ = 125
        self.components = [Joint(0, "xy"), Link(25),
                           Joint(0, "yz"), Link(50),
                           Joint(0, "yz"), Link(100)]

    def getComponents(self):
        return self.components

class Robot:

    def __init__(self):
        self.limbs = [Limb(), Limb()]

    def getLimbs(self):
        return self.limbs
