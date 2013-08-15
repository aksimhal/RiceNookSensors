from __future__ import print_function
import wx
import random
from time import sleep

log = open("C:\\Users\\anish\\Documents\\goat.txt", "w")
print("test", file = log)

class Panel(wx.Panel):
    def __init__(self, parent, id, pos, size):
        wx.Panel.__init__(self, parent, id, pos, size) 
        

class Frame(wx.Frame):
    def __init__(self, parent, id, title, pos, size, style):
        wx.Frame.__init__(self, parent, id, title, pos, size, style)
        # Panel 1
        self.framePanel1 = wx.Panel(self) #create an instance of a panel 
        self.framePanel1.SetBackgroundColour((0,0,255))
        
        
        gs = wx.GridSizer(4, 4, 0, 0)
        gs.Add(self.framePanel1, 1, wx.EXPAND)
        #@TODO: work on getting panels aligned 
        # Panel 2 
        framePanel2 = wx.Panel(self) #create an instance of a panel 
        framePanel2.SetBackgroundColour((0,255,0))
        gs.Add(framePanel2, 1, wx.EXPAND)
        # Panel 3
        framePanel3 = wx.Panel(self) #create an instance of a panel 
        framePanel3.SetBackgroundColour((255,0,0))
        gs.Add(framePanel3, 1, wx.EXPAND)
        # Panel 4
        framePanel4 = wx.Panel(self) #create an instance of a panel 
        framePanel4.SetBackgroundColour((0,180,156))
        gs.Add(framePanel4, 1, wx.EXPAND)
        # Panel 5
        framePanel5 = wx.Panel(self) #create an instance of a panel 
        framePanel5.SetBackgroundColour((123,25,0))
        gs.Add(framePanel5, 1, wx.EXPAND)
        # Panel 5
        framePanel5 = wx.Panel(self) #create an instance of a panel 
        framePanel5.SetBackgroundColour((138, 16, 202))
        gs.Add(framePanel5, 1, wx.EXPAND)
        # Panel 6
        framePanel6 = wx.Panel(self) #create an instance of a panel 
        framePanel6.SetBackgroundColour((45, 56, 8))
        gs.Add(framePanel6, 1, wx.EXPAND)
        # Panel 7
        framePanel7 = wx.Panel(self) #create an instance of a panel 
        framePanel7.SetBackgroundColour((2, 200, 49))
        gs.Add(framePanel7, 1, wx.EXPAND)
        # Panel 8
        framePanel8 = wx.Panel(self) #create an instance of a panel 
        framePanel8.SetBackgroundColour((123,25,88))
        gs.Add(framePanel8, 1, wx.EXPAND)
        # Panel 9
        framePanel9 = wx.Panel(self) #create an instance of a panel 
        framePanel9.SetBackgroundColour((88, 200, 69))
        gs.Add(framePanel9, 1, wx.EXPAND)
        # Panel 10
        framePanel10 = wx.Panel(self) #create an instance of a panel 
        framePanel10.SetBackgroundColour((13,205,10))
        gs.Add(framePanel10, 1, wx.EXPAND)
        # Panel 11
        framePanel11 = wx.Panel(self) #create an instance of a panel 
        framePanel11.SetBackgroundColour((20, 100, 255))
        gs.Add(framePanel11, 1, wx.EXPAND)
        # Panel 12
        framePanel12 = wx.Panel(self) #create an instance of a panel 
        framePanel12.SetBackgroundColour((89, 46, 100))
        gs.Add(framePanel12, 1, wx.EXPAND)
        # Panel 13
        framePanel13 = wx.Panel(self) #create an instance of a panel 
        framePanel13.SetBackgroundColour((15, 200, 200))
        gs.Add(framePanel13, 1, wx.EXPAND)
        # Panel 14
        framePanel14 = wx.Panel(self) #create an instance of a panel 
        framePanel14.SetBackgroundColour((200, 0, 145))
        gs.Add(framePanel14, 1, wx.EXPAND)
        # Panel 15
        framePanel15 = wx.Panel(self) #create an instance of a panel 
        framePanel15.SetBackgroundColour((20, 255, 56))
        gs.Add(framePanel15, 1, wx.EXPAND)
        
        self.SetSizer(gs)

        #a = random.randrange(0, 255, 1)
    

        
        
class Application(wx.App):
    def __init__(self):
        #wx.App.__init__(self)
        wx.App.__init__(self, redirect=False, filename=None, useBestVisual=False, clearSigInt=True)
        self.frame = Frame(None, -1, "Thermal IR Sensor Viewer", (-1,-1), (300,400),\
        wx.DEFAULT_FRAME_STYLE ^ (wx.RESIZE_BORDER | wx.MAXIMIZE_BOX))
        self.frame.Show()
        self.SetTopWindow(self.frame)
        l = dir(self.frame)
        print(l, file = log)
        numberOfIterations = 5; 
        self.frame.framePanel1.SetBackgroundColour((255, 255, 255))
        print ('done')        

if __name__ == '__main__':
    app = Application()
    app.frame.framePanel1.SetBackgroundColour((255, 255, 255))
    app.MainLoop()