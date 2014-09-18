from Tkinter import *
from ttk import Treeview, Scrollbar
from MechPackage import *
import math
import random
import time
import threading
from VerticalScrolledFrame import *

class SettingsFrame(Frame):

    def __init__(self, parent):
        Frame.__init__(self, parent, background="white")
        self.parent = parent
        self.initUI()

    def initUI(self):
        pass


class MacroFrame(Frame):

    def __init__(self, parent):
        Frame.__init__(self, parent, background="white")
        self.parent = parent
        self.numStates = 0
        self.initUI()

    def initUI(self):
        self.columnconfigure(0, weight=0)
        self.columnconfigure(1, weight=0)
        self.columnconfigure(2, weight=1)
        self.columnconfigure(3, weight=1)

        self.rowconfigure(0, weight=1)

        self.commandFrame = Frame(self, background="white")
        self.commandFrame.grid(row=0, column=0, columnspan=5, sticky=W+E)
        self.commandFrame.columnconfigure(1, weight=1)

        self.btnCommand = Button(self.commandFrame, text="Run")
        self.btnCommand.grid(row=0, column=0)

        self.strCommand = StringVar()
        self.entCommand = Entry(self.commandFrame, textvariable=self.strCommand)
        self.entCommand.grid(row=0, column=1, sticky=W+E)
        
        self.lstMacro = Listbox(self)
        self.lstMacro.grid(row=1, column=0, sticky=N+S+W+E)
        
        self.treeview = Treeview(self, columns=("Angle"), displaycolumns="#all", selectmode="browse")
        self.treeview.grid(row=1, column=1, columnspan=4, sticky=N+S+W+E)
        self.treeScrollbar = Scrollbar(self)
        self.treeScrollbar.grid(row=1, column=5, sticky=N+S)
        self.treeview.config(yscrollcommand=self.treeScrollbar.set)
        self.treeScrollbar.config(command=self.treeview.yview)

        self.btnFrame = Frame(self, background="white")
        self.btnFrame.grid(row=2, column=0, columnspan=5, sticky=W+E)

        self.btnRun = Button(self.btnFrame, text="Run", command=self.runMacro)
        self.btnRun.grid(row=0, column=0)
        
        self.btnStop = Button(self.btnFrame, text="Stop")
        self.btnStop.grid(row=0, column=1)

        self.btnSaveMacro = Button(self.btnFrame, text="Save Macro", command=self.saveMacro)
        self.btnSaveMacro.grid(row=0, column=2)

        self.btnDeleteMacro = Button(self.btnFrame, text="Delete Macro")
        self.btnDeleteMacro.grid(row=0, column=3)

        self.btnDeleteState = Button(self.btnFrame, text="Delete State")
        self.btnDeleteState.grid(row=0, column=4)

    def addState(self, robot):
        stateName = "state" + str(self.numStates)
        self.treeview.insert("", END, iid=stateName, text=stateName)
        limbNum = 0
        for limb in robot.getLimbs():
            limbName = "limb" + str(limbNum)
            self.treeview.insert(stateName, END, iid=stateName + "_" + limbName, text=limbName)
            partNum = 0
            for part in limb.getComponents():
                partName = "joint" + str(partNum)
                if isinstance(part, Joint):
                    self.treeview.insert(stateName + "_" + limbName,
                                         END,
                                         iid=stateName + "_" + limbName + "_" + partName,
                                         text=partName,
                                         values=[part.angle])
                    partNum += 1
            limbNum += 1
        self.numStates += 1

    def getState(self, stateNum, robot):
        stateName = "state" + str(stateNum)
        limbNum = 0
        for limb in robot.getLimbs():
            limbName = "limb" + str(limbNum)
            partNum = 0
            for part in limb.getComponents():
                partName = "joint" + str(partNum)
                if isinstance(part, Joint):
                    part.setAngle(int(self.treeview.item(stateName + "_" + limbName + "_" + partName, "values")[0]))
                    partNum += 1
            limbNum += 1

    def runMacro(self):
        thread = threading.Thread(target=self.updateState)
        thread.start()
            
    def updateState(self):
        for i in range(self.numStates):
            self.getState(i, self.parent.robotFrame.robot)
            time.sleep(.1)

    def saveMacro(self):
        pass

class JointFrame(Frame):

    def __init__(self, parent, name, joint):
        Frame.__init__(self, parent, background="white")
        self.parent = parent
        self.name = name
        self.joint = joint
        self.initUI()

    def initUI(self):
        self.lblJoint = Label(self, text=self.name + ":", background="white")
        self.lblJoint.grid(row=0, column=0)

        self.strJoint = StringVar()
        self.entJoint = Entry(self, textvariable=self.strJoint)
        self.entJoint.grid(row=0, column=1)

        self.btnCCW = Button(self, text="CCW", repeatdelay=500, repeatinterval=100, command=self.rotateCCW)
        self.btnCCW.grid(row=0, column=2)
        
        self.btnCW  = Button(self, text="CW", repeatdelay=500, repeatinterval=100, command=self.rotateCW)
        self.btnCW.grid(row=0, column=3)

    def update(self):
        self.strJoint.set(self.joint.angle)

    def rotateCCW(self):
        self.joint.setAngle(self.joint.angle + 1)

    def rotateCW(self):
        self.joint.setAngle(self.joint.angle - 1)
        

class LimbFrame(Frame):

    def __init__(self, parent, limb):
        Frame.__init__(self, parent, background="white")
        self.parent = parent
        self.limb = limb
        self.jointFrames = []
        self.yzJoints = 0
        self.xyJoints = 0
        self.initUI()

    def initUI(self):
        self.lblTitle = Label(self, text="Leg 1", font=("Helvetica", 16), background="white")
        self.lblTitle.grid(row=0, column=0, columnspan=4)
        
        self.yzCanvas = Canvas(self, borderwidth=2, relief=RAISED, background="black")
        self.yzCanvas.grid(row=1, column=0, rowspan=2, columnspan=2)

        self.xyCanvas = Canvas(self, borderwidth=2, relief=RAISED, background="black")
        self.xyCanvas.grid(row=1, column=2, rowspan=2, columnspan=2)

        for part in self.limb.getComponents():
            if isinstance(part, Joint):
                
                if part.orientation == "yz":
                    newJoint = JointFrame(self, "Joint " + str(len(self.jointFrames)), part)
                    newJoint.grid(row=(3 + self.yzJoints), column=0, columnspan=2)
                    self.jointFrames.append(newJoint)
                    self.yzJoints += 1
                elif part.orientation == "xy":
                    newJoint = JointFrame(self, "Joint " + str(len(self.jointFrames)), part)
                    newJoint.grid(row=(3 + self.xyJoints), column=2, columnspan=2)
                    self.jointFrames.append(newJoint)
                    self.xyJoints += 1


    def update(self):
        for jointFrame in self.jointFrames:
            jointFrame.update()
        self.yzCanvas.delete("all")
        self.xyCanvas.delete("all")
        components = self.limb.getComponents()
        currentX_yz = self.limb.startX
        currentZ_yz = self.limb.startZ
        currentX_xy = self.limb.startX
        currentY_xy = self.limb.startY
        currentAngleXZ = 0
        currentAngleXY = 0
        for part in components:
            if isinstance(part, Joint):
                if part.orientation == "yz":
                    currentAngleXZ += part.angle
                    fillXZ = "green"
                    fillXY = "grey"
                elif part.orientation == "xy":
                    currentAngleXY += part.angle
                    fillXZ = "grey"
                    fillXY = "green"
                self.yzCanvas.create_oval(currentX_yz-5, currentZ_yz-5, currentX_yz+5, currentZ_yz+5, fill=fillXZ, tags="joint")
                self.xyCanvas.create_oval(currentX_xy-5, currentY_xy-5, currentX_xy+5, currentY_xy+5, fill=fillXY, tags="joint")
            elif isinstance(part, Link):
                nextX_yz = currentX_yz + part.length * math.cos(math.radians(currentAngleXZ))
                nextZ_yz = currentZ_yz - part.length * math.sin(math.radians(currentAngleXZ))
                nextX_xy = currentX_xy + part.length * math.cos(math.radians(currentAngleXY))
                nextY_xy = currentY_xy - part.length * math.sin(math.radians(currentAngleXY))
                self.yzCanvas.create_line(currentX_yz, currentZ_yz, nextX_yz, nextZ_yz, width=3, fill="blue", tags="link")
                self.xyCanvas.create_line(currentX_xy, currentY_xy, nextX_xy, nextY_xy, width=3, fill="blue", tags="link")
                self.yzCanvas.tag_lower("link")
                self.xyCanvas.tag_lower("link")
                currentX_yz = nextX_yz
                currentZ_yz = nextZ_yz
                currentX_xy = nextX_xy
                currentY_xy = nextY_xy


class RobotFrame(Frame):

    def __init__(self, parent):
        Frame.__init__(self, parent, background="white")
        self.parent = parent

        # Initialize to default robot
        self.robot = Robot()

        # Initialize empty list for limb frames
        self.limbFrames = []
        
        self.initUI()

        # Start the update cycle
        self.update()

    def initUI(self):
        self.rowconfigure(0, pad=3, weight=1)
        self.columnconfigure(0, pad=3, weight=1)

        # Create a vertically scrolling frame to hold all of the limb frames
        self.scrollFrame = VerticalScrolledFrame(self, background="white")

        # Generate a limb frame for each limb in the robot
        for limb in self.robot.getLimbs():
            newLimbFrame = LimbFrame(self.scrollFrame.interior, limb)
            newLimbFrame.grid(row=len(self.limbFrames), column=0)
            self.limbFrames.append(newLimbFrame)

        # Set the scrolling frame to fill the window
        self.scrollFrame.grid(row=0, column=0, sticky=N+S+W+E)

        # Add a button to store the state of the robot in the active macro
        self.btnSaveState = Button(self, text="Save State", command=self.saveState)
        self.btnSaveState.grid(row=1, column=0)

    # Saves the state of the current robot in the macro frame
    def saveState(self):
        self.parent.macroFrame.addState(self.robot)

    # Continuously update the limb frames
    def update(self):
        for limbFrame in self.limbFrames:
            limbFrame.update()
        self.after(20, self.update)
        

class MainWindow(Frame):
  
    def __init__(self, parent):
        Frame.__init__(self, parent, background="white")
        self.parent = parent
        self.initUI()
    
    def initUI(self):
      
        self.parent.title("Motion Controller")

        # Configure main widgets to expand to the full width of the window
        self.columnconfigure(0, pad=3, weight=1)

        # Hide the settings frame for now
        self.rowconfigure(0, pad=3, weight=0)
        # The visualizer to should be me prominent since it's visually larger
        self.rowconfigure(1, pad=3, weight=2)
        self.rowconfigure(2, pad=3, weight=1)

        # Visualizes the robot legs
        self.robotFrame = RobotFrame(self)
        self.robotFrame.grid(row=1, column=0, sticky=N+S+W+E)

        # Used for recording and playing macros
        self.macroFrame = MacroFrame(self)
        self.macroFrame.grid(row=2, column=0, sticky=N+S+W+E)
        
        self.pack(fill=BOTH, expand=1)

def main():
  
    root = Tk()
    app = MainWindow(root)
    root.mainloop()  


if __name__ == '__main__':
    main()  
