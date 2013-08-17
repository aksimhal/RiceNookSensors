from __future__ import print_function
import wx
import random
from time import sleep

#log = open("C:\\Users\\anish\\Documents\\goat2.txt", "w")
#print("test", file = log)

class Panel(wx.Panel):
    def __init__(self, parent, id, pos, size):
        wx.Panel.__init__(self, parent, id, pos, size) 
        

class Frame(wx.Frame):
    def __init__(self, parent, id, title, pos, size, style):
        wx.Frame.__init__(self, parent, id, title, pos, size, style)        
        gs = wx.GridSizer(4, 4, 0, 0)
        
        for x in xrange(0, 15): 
            framePanel2 = wx.Panel(self) #create an instance of a panel 
            framePanel2.SetBackgroundColour((random.randrange(0, 255, 1), random.randrange(0, 255, 1), random.randrange(0, 255, 1)))
            gs.Add(framePanel2, 1, wx.EXPAND)
        
        self.SetSizer(gs)

        
class Application(wx.App):
    def __init__(self):
        #wx.App.__init__(self)
        wx.App.__init__(self, redirect=False, filename=None, useBestVisual=False, clearSigInt=True)
        self.frame = Frame(None, -1, "Thermal IR Sensor Viewer", (-1,-1), (300,400),\
        wx.DEFAULT_FRAME_STYLE ^ (wx.RESIZE_BORDER | wx.MAXIMIZE_BOX))
        self.frame.Show()
        self.SetTopWindow(self.frame)
        
        a = self.frame.GetChildren() #returns type wx.WindowList
        #l = dir(a0)
        
        for pObj in a: 
            sleep(0.05)
            pObj.SetBackgroundColour((random.randrange(0, 255, 1), random.randrange(0, 255, 1), random.randrange(0, 255, 1))); 
            pObj.Refresh()
            print (pObj.GetBackgroundColour())
        print ('done')        

if __name__ == '__main__':
    app = Application()
    app.MainLoop()